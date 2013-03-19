import maya.cmds as cmds
import random

cmds.select(all=True)
cmds.delete()

# get edges
def getEdge(lastEdge, edgeCounter, maxTreeLevel, specialEdgeCounter):
	if edgeCounter == 0:
		#print "CHECK first EDGE"
		return 8, (edgeCounter+1), specialEdgeCounter
	else:
		for i in range(2,maxTreeLevel+3):
			if edgeCounter == (2**i)-2:
				#print "CHECK special edgeCounter"
				return lastEdge + specialEdge(specialEdgeCounter+1), edgeCounter+1, specialEdgeCounter+1
	if edgeCounter%2 == 1:
		#print "CHECK edgeCounter is ODD"
		return (lastEdge+3), (edgeCounter+1), specialEdgeCounter
	elif edgeCounter%2 == 0:
		#print "CHECK edgeCounter is EVEN"
		return (lastEdge+5), (edgeCounter+1), specialEdgeCounter

def specialEdge(specialEdgeCounter):
	#print specialEdgeCounter
	if specialEdgeCounter == 1:
		return 8
	else:
		return specialEdge(specialEdgeCounter-1) + 2**(specialEdgeCounter) - 2**(specialEdgeCounter-2)

# get face
def getFace(list):
	# get length of current list
	length = len(list)
	# for each item, get another two and append
	for item in list[length/2:length]:
		#print item
		newVal = (item*2)+3
		list.append(newVal)
		list.append(newVal+1)
		#print "in proc list is = ", list
	return list

# split face
def splitFace(edgeStart, edgeEnd):
	cmds.select("planeOrig")
	cmds.polySplit( ip=[(edgeStart,0.5), (edgeEnd,0.5)] )

# select face and extrude
def selectAndExtrude(currentFace):
	if currentFace == 0:
		cmds.select("planeOrig.f["+str(currentFace)+"]")
		cmds.polyExtrudeFacet(ltx=random.uniform(-2.0,2.0), lty=random.uniform(-2.0,2.0), ltz=(random.uniform(1.0,1.5)), # random translates, ltz is UP
				s=(0.7,1.05,1.0))
	else:
		cmds.select("planeOrig.f["+str(currentFace)+"]")
		cmds.polyExtrudeFacet(ltx=random.uniform(-2.0,2.0), lty=random.uniform(-2.0,2.0), ltz=(random.uniform(0.5,1.0)), # random translates, ltz is UP
				s=(0.5,1.1,1.0))

# pause program
def pause_prog():
	paused = True
	while paused == True:
		response = raw_input("")
		if response == " ":
			paused = False

# PROGRAM STARTS #

print ""
print "PROGRAM STARTS"
print ""

# initiate variables
faceNumber = 0
edgeCounter = 0
lastEdge = 0
specialEdgeCounter = 0
facesList = [0,6]
maxTreeLevel = 3
previousFaceIteration = 1
currentTreeLevel = 0

# create plane
cmds.polyPlane(name="planeOrig", sx=1, sy=1)
cmds.scale(2.5,2.5,1.5)
# make into furst cube
selectAndExtrude(faceNumber)

# change rotation for next branches

print "### PROGRAM STARTS ###"

# main repetition procedure
# for each level of the tree, getEdges, splitFaces, extrude for each face in the face list
for currentTreeLevel in range(1, maxTreeLevel+1):
	#pause_prog()
	print ""
	print "currentTreeLevel = ", currentTreeLevel

	print ""
	print "# ~ RUNNING ~ #"
	print ""

	for numberOfSplits in range(0, 2**(currentTreeLevel-1)):
		# get edges and then split
		#print "last edge = ", lastEdge
		lastEdge, edgeCounter, specialEdgeCounter = getEdge(lastEdge, edgeCounter, maxTreeLevel, specialEdgeCounter)
		#print "got edge", lastEdge, "edgeCounter", edgeCounter
		edgeStart = lastEdge
		lastEdge, edgeCounter, specialEdgeCounter = getEdge(lastEdge, edgeCounter, maxTreeLevel, specialEdgeCounter)
		#print "got edge", lastEdge, "edgeCounter", edgeCounter
		edgeEnd = lastEdge
		splitFace(edgeStart,edgeEnd)
		print ""
		print "split edges", edgeStart,edgeEnd
		#pause_prog()

	# extrude faces
	for currentFace in facesList:
		#print currentFace, facesList
		selectAndExtrude(currentFace)
		print ""
		print "extruded face", currentFace, "when currentTreeLevel", currentTreeLevel

	facesList = getFace(facesList)
	#print facesList
print "DONE!"
