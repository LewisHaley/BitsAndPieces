#
# Cobble Generation Python Script for Autodesk Maya
#
# Created by: Lewis Haley (www.lewishaley.co.uk)
# - lewismhaley@gmail.com
#
# Outline
# - Procedures to generate randomised cobbles fro a cobbled floor
# - Eachs cobble is slightly different
# - Requires user provided original cobble called cobble0
#
# ToDo
# - Add genericism so that object doesn't have to be called "cobble0"
# - Work on spiralCobbles() - not quite right.
# 

import maya.cmds as cmds
import random
import math

# randomises the vert positions of an object
# input: amount - INT/FLOAT general idea of how much verts will be moved
# input: obj - STRING name of object to randomise
# output: -
def randVerts( amount, obj=0 ):
	# if no obj provided, uses selected object
	if obj == 0:
		obj = cmds.ls(sl=1)
		obj = obj[0]
	numVerts = cmds.polyEvaluate(v=1)
	for i in range( 0,numVerts ):
		cmds.move(	random.uniform(-1,1)*amount,
		    		random.uniform(-1,1)*amount,
		    		random.uniform(-1,1)*amount,
		    		obj+".vtx["+str(i)+"]", r=1 )

# creates a grid cobble layout
# input: gridx - INT number of cobbles in x dir (def: 10)
# input: gridz - INT number of cobbles in z dir (def: 10)
# input: randMove - INT/FLOAT variance in cobble layout (def: 0.1)
# output: -
def gridCobbles( gridx=10, gridz=10, randMove=0.1 ):
	assert( type(gridx) == type(gridz) == type(1) )
	listOfCobbles = []
	for x in range( 0,gridx ):
		for z in range( 0,gridz ):
			newCobb = cmds.duplicate( "cobble0" )
			randVerts( 0.1, newCobb[0] )
			cmds.move(	x*1.1+random.uniform(-randMove,randMove),
                        		z*1.4+random.uniform(-randMove,randMove),
                        		newCobb[0], xz=1, a=1 )
			cmds.move( random.uniform(-randMove/5,randMove/5)*0.1, newCobb[0], y=1, a=1 )
			listOfCobbles.append( newCobb[0] )

# UNFINISHED #
# creates a spiral pattern of cobbles
def spiralCobbles():
	listOfCobbles = []
	for r in range( 0,200 ):
		newCobb = cmds.duplicate( "cobble0" )
		randVerts( 0.1, newCobb[0] )
		cmds.move( math.sin(r)*r*0.01, math.cos(r)*r*0.01, newCobb[0], xz=1, r=1 )

# EXAMPLE USAGE
cmds.polyCube( n="cobble0", sx=2,sy=2,sz=2 )
gridCobbles( 10, 10, 0.15772 )
