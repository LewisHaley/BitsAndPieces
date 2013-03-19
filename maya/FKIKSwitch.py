#
# FKIKSwitch Python Script for Autodesk Maya
#
# Created by: Lewis Haley (www.lewishaley.co.uk)
# - lewismhaley@gmail.com
#
# Outline
# - Procedurally sets up duplicate joint chains that drive original skeleton
# - based on an added attribute (an IK "switch") on a global control
#
# Usage/Liscence
# - This script is free for use by anyone who finds it in their possession
# - Anyone can edit this script to their own liking (open source, etc)
# - Redistribution is allowed provided credit is given to the original creator
# - and any/all persons who modify and which to be mentioned, and that it
# - remains FREE. Under no circumstances may a fee of any kind be charged for
# - the ownership, usage, liscencing, or anything else in regards to this script.
#
# Version History
# - Version 1.0 (Nov 3rd 2011)
# - - Completed all main functions, algorithms, UI elements
# - Version 1.1 (Nov 17th 2011)
# - - Changed switch attribute type from boolean to float
# - - upon request (allows for smooth transistion between FK and IK)
#
# ToDo
# - Errr.... make it work more than once...
# - Yeah... it only works once. I think it something to do with variable/object names
# - Which is like, totally a major issue
#

import maya.cmds as cmds

"""
- duplicate joint chain
- rename new chains
"""
def duplicateJointChain():
	jointList = cmds.ls(sl=True)
	targetJoint = jointList[0]
	cmds.duplicate(targetJoint, name=targetJoint+"_IK")
	pathListIK = cmds.listRelatives(ad=1, f=1)
	objListIK = cmds.listRelatives(ad=1)
	for i in range(0,len(objListIK)):
	    cmds.rename(pathListIK[i],objListIK[i]+"_IK")

	cmds.duplicate(targetJoint, name=targetJoint+"_FK")
	cmds.select(targetJoint+"_FK")
	pathListFK = cmds.listRelatives(ad=1, f=1)
	objListFK = cmds.listRelatives(ad=1)
	for i in range(0,len(objListFK)):
	    cmds.rename(pathListFK[i],objListFK[i]+"_FK")
	return targetJoint

"""
- parent constrains original joints to new joints
"""
def parentConstrain(targetJoint):
	# parenting to IK
	cmds.select(cl=True)
	cmds.select(targetJoint+"_IK")
	cmds.select(targetJoint, add=True)
	cmds.parentConstraint(mo=True, weight=1)
	cmds.pickWalk(d="down")
	cmds.parentConstraint(mo=True, weight=1)
	cmds.pickWalk(d="down")
	cmds.parentConstraint(mo=True, weight=1)
	# parenting to FK
	cmds.select(cl=True)
	cmds.select(targetJoint+"_FK")
	cmds.select(targetJoint, add=True)
	cmds.parentConstraint(mo=True, weight=1)
	cmds.pickWalk(d="down")
	cmds.parentConstraint(mo=True, weight=1)
	cmds.pickWalk(d="down")
	cmds.parentConstraint(mo=True, weight=1)

"""
- reads in user input
- creates switch
"""
def makeAttr():
    switchInput = cmds.textField(myField, q=1, tx=1)
    cmds.addAttr(ln=str(switchInput), at="float", k=1)


import math

"""
- gets list of attributes from the parent constraints
- gets DAG path to the control switch
- connects Switch output to PC weight
- connects switch output to PC weight via reverse node
"""
def connectAttributes():
	# makes a list of all parent constraint objects
	listOfPC = cmds.ls(typ="parentConstraint")
	listOfAttrs=[]
	for i in range(0,len(listOfPC)):
		attrs = cmds.listAttr(listOfPC[i])
		for j in range(0,len(attrs)):
			if (attrs[j][0]==listOfPC[i][0]) and (attrs[j][1]==listOfPC[i][1]) and (attrs[j][2]==listOfPC[i][2]):
				listOfAttrs.append(attrs[j])
	#print listOfPC
	#print listOfAttrs
	# get location of control object
	control = cmds.textField(myField, q=1, tx=1)
	listOE = cmds.ls()
	for x in range(0,len(listOE)):
	    attrsOE = cmds.listAttr(listOE[x])
	    for y in range(0,len(attrsOE)):
		if attrsOE[y]==control:
		    controlLoc = listOE[x]
	# connect each parent constraint attribute to the IK Switch
	for a in range(0,len(listOfPC)):
		# the full name of the attribute to connect to (the weight of the parent constraint
		# is a concatenation of the list of parent constraints
		# and the list of attributes
		attrFullName = listOfPC[a]+"."+listOfAttrs[a*2]
		cmds.connectAttr(controlLoc+"."+control, attrFullName, f=1)
	# make a reverse node
	reverseNode = cmds.shadingNode("reverse", au=1)
	# connect the IKSwitch to the reverse node
	cmds.connectAttr(controlLoc+"."+control, reverseNode+".inputX", f=1)
	for b in range(0,len(listOfPC)):
		# the full name of the attribute to connect to (the weight of the parent constraint
		# is a concatenation of the list of parent constraints
		# and the list of attributes
		attrFullName = listOfPC[b]+"."+listOfAttrs[(b*2)+1]
		cmds.connectAttr(reverseNode+".outputX", attrFullName, f=1)

"""
- connect visibility of animation controls for FK to switch attr
"""
def visibilityFK():
	# get location of control object
	control = cmds.textField(myField, q=1, tx=1)
	listOE = cmds.ls()
	for x in range(0,len(listOE)):
		attrsOE = cmds.listAttr(listOE[x])
		for y in range(0,len(attrsOE)):
			if attrsOE[y]==control:
				controlLoc = listOE[x]
	controls = cmds.ls(sl=1)
	reverseNode2 = cmds.shadingNode("reverse", au=1)
	cmds.connectAttr(controlLoc+"."+control, reverseNode2+".inputY", f=1)
	for ctrl in controls:
		cmds.connectAttr(reverseNode2+".outputY", ctrl+".visibility", f=1)

"""
- connect visibility of animation controls for IK to switch attr
"""
def visibilityIK():
	# get location of control object
	control = cmds.textField(myField, q=1, tx=1)
	listOE = cmds.ls()
	for x in range(0,len(listOE)):
		attrsOE = cmds.listAttr(listOE[x])
		for y in range(0,len(attrsOE)):
			if attrsOE[y]==control:
				controlLoc = listOE[x]
	controls = cmds.ls(sl=1)
	for ctrl in controls:
		cmds.connectAttr(controlLoc+"."+control, ctrl+".visibility", f=1)

"""
- show instructions
"""
def showInstrs():
	cmds.text(instrs, e=1, l="1) Select the the joint chain to duplicate\n2) Press the \"Duplicate Joint Chain\" button\n3) Press the \"Add Constraints\" button\n4) Select your control object for the switch attribute\n5) Enter a name for your IK Switch and press the \"Create Attr\" button\n6) Press the \"Make Connections\" button\n7) Select you IK controls, press \"IK Control Visibility\"\n8) Select you FK controls, press \"FK Control Visibility\"")
	cmds.window(myWindow, e=1, wh=[300,370])
	cmds.button(instrButton, e=1, en=0)

#			#
#  UI CODE STARTS HERE	#
#			#
	
# create window
myWindow = cmds.window(title="FK/IK Switch Tool")
# assign 1 column layout
cmds.rowColumnLayout(nc=1, cal=[1,"center"], co=([1,"both", 10]), ro=([1,"top",10],[1,"bottom",5],[2,"both",5],[3,"both",5],[4,"both",5],[5,"both",5],[6,"both",5],[7,"both",5]))
# show instructions
instrButton = cmds.button(label="Display Instructions", command=("showInstrs()"))
# instructions field
instrs = cmds.text(l=" ")
# duplicate joint chain button
cmds.button(label="Duplicate Joint Chain", command=("target = duplicateJointChain()"))
# add parent constraints button
cmds.button(label="Add Constraints", command=("parentConstrain(target)"))

# assign 2 column layout
cmds.rowColumnLayout(nc=2, cal=([1,"center"]), co=([1,"right",5],[2,"left",5]))
# text field for switch name
myField = cmds.textField(tx="...")
# create attr button
createAttrButton = cmds.button(l="Create Attr", c=("makeAttr()"))
cmds.setParent("..")

# make connections button
cmds.button(label="Make Connections", command=("connectAttributes()"))
# assign 1 column layout
cmds.rowColumnLayout(nc=2, cal=([1,"center"]), co=([1,"right",5],[2,"left",5]))
# make IK visibility connections button
cmds.button(label="IK Control Visibility", command=("visibilityIK()"))
# make FK visibility connections button
cmds.button(label="FK Control Visibility", command=("visibilityFK()"))
cmds.setParent("..")
# close button
closeButton = cmds.button(l="Close", c=("cmds.deleteUI(myWindow)"))
cmds.setParent("..")
# changes window size
cmds.showWindow(myWindow)
cmds.window(myWindow, e=1, wh=[300,270])
