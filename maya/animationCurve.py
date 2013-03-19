#
# Animation Curve Python Script for Autodesk Maya
#
# Created by: Lewis Haley (www.lewishaley.co.uk)
# - lewismhaley@gmail.com
#
# Outline
# - Procedurally creates a CV curve that follows the motion of any user
# - specified object, the purpose of which is to allow for animators to
# - check their animation arks are to their liking
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
# - Version 1.0 (Nov 1st 2011)
# - - Completed all main functions, algorithms, UI elements
# - Version 1.0.1 (September 1st 2012)
# - - added more detailed comments
#

import maya.cmds as cmds


# function that draws the curve in maya
# input: target - the object to trace
# input: start - start frame
# input: end - end frame
# input: colour - colour of the curve
# input: samples - number of samples during time period (cannot exceed end-start)
def drawCurve( target,start,end,colour,samples ):
	# print target,start,end,samples,colour
	# make locator, constrain to target
	cmds.spaceLocator( name="myLocator" )
	cmds.select( target )
	cmds.select( "myLocator", add=True )
	cmds.pointConstraint()

	# make a new render layer with locator, and change display colour
	cmds.select( "myLocator" )
	exists = cmds.objExists( "AnimationCurves" )
	if ( exists==False ):
		cmds.createDisplayLayer( name="AnimationCurves", number=1, nr=True )
		cmds.createDisplayLayer( name="Spheres", number=1, nr=True )
		cmds.setAttr( "AnimationCurves.color", colour )
		cmds.setAttr( "Spheres.color", 16 )		

	# make a list of all the frames where points for the curve will be created
	frameList = []
	frameList.append( start )
	length = end - start
	samples = cmds.intField( samplesField, q=1, v=1 )
	interval = int( length / (samples-1) ) # using int() to ensure integer frame numbers
	for i in range( 1,samples ):
		frameList.append( start+interval*i )
	frameList.append( end )

	# make a list of tuples containing the locations of the target/locator for every frame needed
	xFormList = []
	n = 0
	for frame in ( frameList ):
		x = cmds.getAttr( "myLocator.tx",time=frame )
		y = cmds.getAttr( "myLocator.ty",time=frame )
		z = cmds.getAttr( "myLocator.tz",time=frame )
		currentXForm = ( x,y,z )
		xFormList.append( currentXForm )
		cmds.sphere( n="sphere"+str(n), r=0.2 )
		cmds.move( x,y,z, "sphere"+str(n), a=True )
		n+=1
		# print frame, "= ", x,y,z
	cmds.editDisplayLayerMembers( "Spheres", "sphere*", nr=True )

	# create curve using list of tuples
	cmds.curve( p=xFormList, d=1, ws=True )
	cmds.rename( target+"_animation_curve" )
	cmds.group( target+"_animation_curve", "sphere*", n="curve" )
	# add curve to animation curves layer
	cmds.editDisplayLayerMembers( "AnimationCurves", "curve", nr=True )
	cmds.delete("myLocator")
	cmds.button( ccButton, e=1, en=0 )
	cmds.frameLayout( buttonGroup, e=1, l="Delete curve before creating another" )

# retrieves the name of the currently selected object, also updates text field
# input: -
# output: STRING - name of target
def useSelectedTarget():
	obj = cmds.ls(sl=True)
	cmds.textField(targetField, edit=True, text=obj[0])
	target = cmds.textField(targetField, query=True, text=True)
	cmds.setFocus(startField)
	return target

# returns name of target from text field entry
# input: -
# output: STRING - name of target (or null)
def changeTarget():
	target = cmds.textField(targetField, query=True, text=True)
	targEx = cmds.objExists(target)
	if (targEx == True):
		cmds.setFocus(startField)
		return target
	else:
		print "ERROR: target does not exist"
		cmds.textField(targetField, edit=True, text="joint, control, etc")
		return 0

# change the start value
# input: -
# output: INT - new start value
def changeStart():
	start = cmds.intField(startField, query=True, value=True)
	end = cmds.intField(endField, query=True, value=True)
	# start must be less than end
	if (start < end):
		cmds.intField(samplesField, edit=True, value=end-start)
		cmds.setFocus(endField)
		return start
	else:
		print "WARNING: start must be less than end"
		cmds.intField(samplesField, edit=True, value=4)
		cmds.intField(endField, edit=True, value=start+1)
		cmds.setFocus(endField)
		return end-4

# change the end value
# input: -
# output: INT - new end value
def changeEnd():
	end = cmds.intField(endField, query=True, value=True)
	start = cmds.intField(startField, query=True, value=True)
	# end must be greater than start
	if (end > start):
		cmds.intField(samplesField, edit=True, value=end-start)
		cmds.setFocus(colourField)
		return end
	else:
		print "WARNING: end must be greater than start"
		cmds.intField(samplesField, edit=True, value=4)
		cmds.intField(startField, edit=True, value=end-1)
		cmds.setFocus(colourField)
		return start+4

# change the samples value
# input: -
# output: INT - new samples value
def changeSamples():
	samples = cmds.intField(samplesField, query=True, value=True)
	end = cmds.intField(endField, query=True, value=True)
	start = cmds.intField(startField, query=True, value=True)
	# can't be more samples than frame range
	if ((end-start)>=samples):
		cmds.setFocus(startField)
		return samples
	else:
		print "ERROR: too many samples for frame range"
		cmds.intField(samplesField, edit=True, value=end-start)
		return (end-start)

# change the colour variable
# input: -
# output: INT - number corresponds to colour options
def changeColour():
	col = cmds.textField(colourField, query=True, text=True)
	col = col.lower()
	if (col == "red"):
		cmds.setFocus(targetField)
		return 13
	elif (col == "blue"):
		cmds.setFocus(targetField)
		return 6
	elif (col == "green"):
		cmds.setFocus(targetField)
		return 14
	elif (col == "yellow"):
		cmds.setFocus(targetField)
		return 17
	elif (col == "purple"):
		cmds.setFocus(targetField)
		return 9
	elif (col == "white"):
		cmds.setFocus(targetField)
		return 16
	else:
		print "ERROR: Invalid colour"
		# red by default
		cmds.textField(colourField, edit=True, text="red, blue, green, yellow, purple, white")
		return 13

# deletes the curve
# input: -
# output: -
def deleteCurve():
	cmds.select("curve*", "sphere*")
	cmds.delete()
	cmds.button(ccButton, e=1, en=1)
	cmds.frameLayout(buttonGroup, e=1, l=" ")

# deletes layer associated with curve
# input: -
# output: -
def deleteLayers():
	cmds.delete("AnimationCurves")
	cmds.delete("Spheres")

#			#
#  UI CODE STARTS HERE	#
#			#

window = cmds.window(title="Animation Curves Tool", iconName='ACTool', s=False, tlb=True)
cmds.frameLayout(label="Animation Curves Tool")
cmds.rowColumnLayout(nc=2, columnAlign=(1, "center"),
			columnWidth=[(1, 250), (2, 250)],
			ro=[(1,"top",20), (2,"top",10), (3,"top",20), (4,"top",10),],
			co=[(1,"left",10), (1,"right",10), (2,"left",10), (2,"right",10)])
cmds.frameLayout(label="Target Object to Trace")
cmds.rowColumnLayout(nc=2)
targetField = cmds.textField(tx=str("joint, control, etc"), ec=("target = str(changeTarget())"))
cmds.button(label="Use Selected", command=("target = str(useSelectedTarget())"))
cmds.setParent("..")
cmds.setParent("..")

cmds.frameLayout(label="Number of Samples (min. 4)")
cmds.columnLayout()
samplesField = cmds.intField(cc=("samples = int(changeSamples())"), ec=("cmds.setFocus(startField)"))
cmds.setParent("..")
cmds.setParent("..")

cmds.frameLayout(label="Start Frame")
cmds.columnLayout()
startField = cmds.intField(cc=("start = int(changeStart())"), ec=("cmds.setFocus(endField)"))
cmds.setParent("..")
cmds.setParent("..")

cmds.frameLayout(label="End Frame")
cmds.columnLayout()
endField = cmds.intField(v=int(1), min=1, cc=("end = int(changeEnd())"), ec=("cmds.setFocus(colourField)"))

cmds.setParent("..")
cmds.setParent("..")

cmds.frameLayout(label="Colour")
cmds.rowColumnLayout()
colourField = cmds.textField(tx="red, blue, green, yellow, purple, white", cc=("colour = int(changeColour())"))
cmds.setParent("..")
cmds.setParent("..")

buttonGroup = cmds.frameLayout(label=" ")
cmds.rowColumnLayout(nc=2,
		ro=[(1,"top",10), (2,"top",10), (2,"bottom",10)],
		co=[(1,"left",10), (1,"right",10), (2,"left",10), (2,"right",10)])
		
ccButton = cmds.button(label="Create Curve", command=("drawCurve(target,start,end,colour,samples=4)"))
dcButton = cmds.button(label="Delete Curve", command=("deleteCurve()"))
dlButton = cmds.button(label="Delete Layers", command=("deleteLayers()"))
cmds.button(label="Close", command=("cmds.deleteUI(\"" + window + "\", window=True)") )

cmds.setParent("..")
cmds.setParent("..")

#			#
#   UI CODE ENDS HERE	#
#			#

cmds.showWindow(window)
