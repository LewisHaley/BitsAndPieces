#! /usr/bin/python

#Import libraries
import Image, ImageDraw, ImageFont, time, commands
#Create Image "img"
img = Image.new('RGBA', (700,500))
#Create Draw Object
draw = ImageDraw.Draw(img)

#background
def background():
	'''
	Procedure to recreate the background of the image each time it need to be loaded
	Includes the sky, sun, grounds, poles, and pole shadows
	There are no arguments for it
	'''
	#sky
	for i in range (0, 255):
		draw.rectangle((0,i,701,i), fill=(i,0,0,255))
	#sun
	for i in range (0, 255):
		draw.ellipse((175+i,100+i,525-i,450-i), fill=(255,255,i,255))
	#ground
	for i in range (0, 255):
		draw.rectangle((0,255+i,701,255+i), fill=(0,i,0,255))

	for i in range (0, 20):
		#start pole
		draw.rectangle((140,150,160-i,400), fill=(i*10,0,0))
		#destintion pole
		draw.rectangle((340,150,360-i,400), fill=(i*10,0,0))
		#spare pole
		draw.rectangle((540,150,560-i,400), fill=(i*10,0,0))
	#pole shadows
	for i in range (0, 20):
		draw.line((140+i,400, 60+4*i,500), fill=(0,0,0))
		draw.line((340+i,400, 310+4*i,500), fill=(0,0,0))
		draw.line((540+i,400, 580+4*i,500), fill=(0,0,0))

#Title Text
def titletext():
	'''
	Draws the text for the title screen
	Takes no arguments
	'''
	FONT = "/nccaba1/i7989478/Desktop/Lewis_Haley_CFG/The_Towers_of_Hanoi/font_xxii_arabian_onenightstand/XXII_ARABIAN-ONENIGHTSTAND.ttf"
												#Assigns file path of font to 'FONT'
	font1 = ImageFont.truetype(FONT, size=70)						#Sets up font1 to allow for truetype font
	draw.text((23,23), "The Towers of Hanoi", fill=(0,0,0), font=font1)			#Draws shadow for main title (must come first so it can be drawn over)
	draw.text((20,20), "The Towers of Hanoi", fill=(255,255,255), font=font1)		#Draws main title
	font2 = ImageFont.truetype(FONT, size=40)						#Sets up font2 to allow for truetype font
	draw.text((133,410), "Produced by Lewis Haley", fill=(0,0,0), font=font2)		#Draws shadow for subtitle (must come first so it can be drawn over)
	draw.text((130,410), "Produced by Lewis Haley", fill=(255,255,255), font=font2)		#Draws subtitle

#The following 5 procedures contain the code for drawing each of the 5 possible disks to be used in the game
def disk1(offset, height):
	'''
	Draws the largest disk
	height	:	height of disk up pole - will always be 0 for the disk, as it is largest and must be on the bottom, added in for clarity
	offset 	:	determines which pole disk is drawn onto
	'''
	for i in range(0, 20):
		draw.rectangle((offset,400-i, offset+200,380), fill=(50+3*i,50+3*i,50+3*i))
		
def disk2(offset, height):
	'''
	Draws the 2nd largest disk	
	height	:	height of disk up pole
	offset 	:	determines which pole disk is drawn onto
	'''
	for i in range(0, 20):
		draw.rectangle((offset+10,400-i-height, offset+190,380-height), fill=(50+3*i,50+3*i,50+3*i))


def disk3(offset, height):
	'''
	Draws the 3rd largest disk
	height	:	height of disk up pole
	offset 	:	determines which pole disk is drawn onto
	'''
	for i in range(0, 20):
		draw.rectangle((offset+20,400-i-height, offset+180,380-height), fill=(50+3*i,50+3*i,50+3*i))

def disk4(offset, height):
	'''
	Draws the 4th largest disk
	height	:	height of disk up pole
	offset 	:	determines which pole disk is drawn onto
	'''
	for i in range(0, 20):
		draw.rectangle((offset+30,400-i-height, offset+170,380-height), fill=(50+3*i,50+3*i,50+3*i))
	
def disk5(offset, height):
	'''
	Draws the 5th largest disk
	height	:	height of disk up pole
	offset 	:	determines which pole disk is drawn onto
	'''
	for i in range(0, 20):
		draw.rectangle((offset+40,400-i-height, offset+160,380-height), fill=(50+3*i,50+3*i,50+3*i))

	#Creditation to 3rd party source
		'''
		Concept of using lists within a list to keep record of the location of each disk
		and using list fuctions e.g. pop, append, add, remove to control list contents taken from:

												http://tuxradar.com/content/code-project-tower-hanoi-python

		This is a 'pygame' script, which uses functions not present in regular python.
		I have modified parts of the script to make it work in normal python.
		'''

def polesSetup(numdisks):
	offset = 50 				#Offset is the distance from the left hand side of the image plane
	'''
	Reads in user input of number of disks, then runs procedures of drawing disks and sets up a list for the 'contents' of each pole
	numdisks :	read in from user input, determines number of disks used in puzzle
	'''
	if numdisks == 1:
		disk1(offset, 0)		#Draws the largest disk, with offset of 50, height of 0...
		stacks = [[1], [], []]		#Sets up list of stack contents... i.e. 1 disk on the left most pole
		WIN = [[], [1], []]		#Sets up the 'winning condition, i.e. all disks in order on middle pole
		return stacks, WIN		#Returns both lists 'stacks' and 'WIN' to the main procedure
	elif numdisks == 2:		
		disk1(offset, 0)		#Draws the largest disk, with offset of 50, height of 0...
		disk2(offset, 20)		#Draws the second largest disk, with offset of 50+10 (see disk2 procedure), height of 20...
		stacks = [[2,1], [], []]	#Etc...
		WIN = [[], [2,1], []]
		return stacks, WIN
	elif numdisks == 3:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		stacks = [[3,2,1], [], []]
		WIN = [[], [3,2,1], []]
		return stacks, WIN
	elif numdisks == 4:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		disk4(offset, 60)
		stacks = [[4,3,2,1], [], []]
		WIN = [[], [4,3,2,1], []]
		return stacks, WIN
	elif numdisks == 5:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		disk4(offset, 60)
		disk5(offset, 80)
		stacks = [[5,4,3,2,1], [], []]
		WIN = [[],[5,4,3,2,1], []]
		return stacks, WIN

#The following 4 procedures are used simple to cut down the amount of repeated code in drawDisks(), and serve no greater prupose than shortening the length of the source code
def drawDisks2(x, offset):
	'''
	Procedure that controls that feeds into drawDisks() for all combinations where disk2() is the smallest disk used
	x	:	fed in from for loop in drawDisks(), controls which pole is beign drawn on
	offset	:	controls the x coordinate that the disk in drawn at
	'''
	if stacks[x] == [2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
	if stacks[x] == [2]:
		disk2(offset, 0)

def drawDisks3(x, offset):
	'''
	Procedure that controls that feeds into drawDisks() for all combinations where disk3() is the smallest disk used
	x	:	fed in from for loop in drawDisks(), controls which pole is beign drawn on
	offset	:	controls the x coordinate that the disk in drawn at
	'''
	if stacks[x] == [3,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
	if stacks[x] == [3,2]:
		disk2(offset, 0)
		disk3(offset, 20)
	if stacks[x] == [3,1]:
		disk1(offset, 0)
		disk3(offset, 20)
	if stacks[x] == [3]:
		disk3(offset, 0)

def drawDisks4(x, offset):
	'''
	Procedure that controls that feeds into drawDisks() for all combinations where disk4() is the smallest disk used
	x	:	fed in from for loop in drawDisks(), controls which pole is beign drawn on
	offset	:	controls the x coordinate that the disk in drawn at
	'''
	if stacks[x] == [4,3,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		disk4(offset, 60)
	if stacks[x] == [4,3,2]:
		disk2(offset, 0)
		disk3(offset, 20)
		disk4(offset, 40)
	if stacks[x] == [4,3,1]:
		disk1(offset, 0)
		disk3(offset, 20)
		disk4(offset, 40)
	if stacks[x] == [4,3]:
		disk3(offset, 0)
		disk4(offset, 20)
	if stacks[x] == [4,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk4(offset, 40)
	if stacks[x] == [4,2]:
		disk2(offset, 0)
		disk4(offset, 20)
	if stacks[x] == [4,1]:
		disk1(offset, 0)
		disk4(offset, 20)
	if stacks[x] == [4]:
		disk4(offset, 0)

def drawDisks5(x, offset):
	'''
	Procedure that controls that feeds into drawDisks() for all combinations where disk5() is the smallest disk used
	x	:	fed in from for loop in drawDisks(), controls which pole is beign drawn on
	offset	:	controls the x coordinate that the disk in drawn at
	'''
	if stacks[x] == [5,4,3,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		disk4(offset, 60)
		disk5(offset, 80)
	if stacks[x] == [5,4,3,2]:
		disk2(offset, 0)
		disk3(offset, 20)
		disk4(offset, 40)
		disk5(offset, 60)
	if stacks[x] == [5,4,3,1]:
		disk1(offset, 0)
		disk3(offset, 20)
		disk4(offset, 40)
		disk5(offset, 60)
	if stacks[x] == [5,4,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk4(offset, 40)
		disk5(offset, 60)
	if stacks[x] == [5,4,3]:
		disk3(offset, 0)
		disk4(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,4,2]:
		disk2(offset, 0)
		disk4(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,4,1]:
		disk1(offset, 0)
		disk4(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,4]:
		disk4(offset, 0)
		disk5(offset, 20)
	if stacks[x] == [5,3,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk3(offset, 40)
		disk5(offset, 60)
	if stacks[x] == [5,3,2]:
		disk2(offset, 0)
		disk3(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,3,1]:
		disk1(offset, 0)
		disk3(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,3]:
		disk3(offset, 0)
		disk5(offset, 20)
	if stacks[x] == [5,2,1]:
		disk1(offset, 0)
		disk2(offset, 20)
		disk5(offset, 40)
	if stacks[x] == [5,2]:
		disk2(offset, 0)
		disk5(offset, 20)
	if stacks[x] == [5,1]:
		disk1(offset, 0)
		disk5(offset, 20)
	if stacks[x] == [5]:
		disk5(offset, 0)

def drawDisks(numdisks):
	'''
	Contains if statements that reads the list called 'stacks', and decides which block/pole procedures to run
	numdisks	:	int variable set up by user input, determines which 'for' loop and 'if' statements are carried out to draw disks in correct position after each user move
	'''
	offset = 50				#Offset starts at 50 (pixels from left hand side of image plane)
	if numdisks == 1:			#If user input is to use 1 disk...
		for x in range (0, 3):		#'x' starts at 0, i.e. left hand pole, each loop 'x' increases by 1, move to the pole to its right, thus cycling through all disk position posibilities.
			if stacks[x] == [1]:	#If the list 'stack' contains this/these item(s), disk(s) are drawn
				disk1(offset, 0)
			offset = offset + 200	#Increases offset by 200 at the end of each loop, this will make the disks be drawn on the next pole along when the loop goes to the next value of 'i'
	if numdisks == 2:			
		for x in range (0, 3):
			drawDisks2(x, offset)	#Calls drawDisk2, which contains the different combinations of disks where disk2() is the smallest disk
			if stacks[x] == [1]:	#No point in assigning the combinations of disk1() to a procedure, there are only 2 lines of code
				disk1(offset, 0)
			offset = offset + 200
	if numdisks == 3:
		for x in range (0, 3):
			drawDisks3(x, offset)	#Calls drawDisk3, which contains the different combinations of disks where disk3() is the smallest disk
			drawDisks2(x, offset)
			if stacks[x] == [1]:
				disk1(offset, 0)
			offset = offset + 200
	if numdisks == 4:
		for x in range (0, 3):
			drawDisks4(x, offset)	#Etc...
			drawDisks3(x, offset)
			drawDisks2(x, offset)
			if stacks[x] == [1]:
				disk1(offset, 0)
			offset = offset + 200
	if numdisks == 5:
		for x in range (0, 3):
			drawDisks5(x, offset)
			drawDisks4(x, offset)
			drawDisks3(x, offset)
			drawDisks2(x, offset)
			if stacks[x] == [1]:
				disk1(offset, 0)
			offset = offset + 200

def show():
	'''
	Shows images plane, waits 4 seconds, then closes plane
	No arguments
	'''
	img.show()				#Shows imagae
	time.sleep(4)				#Waits 4 seconds
	commands.getoutput("killall eog")	#Closes window

#Hello/Introductions
print (" ") 
print "*~*~ Welcome to The Towers of Hanoi game! ~*~*"
print (" ")

#First picture shown/title screen
background()	#Draws background image on image plane
titletext()	#Draws title 'The Towers Of Hanoi'
show()		#Shows images, waits 4, closes

print(" ")
print "Legend has it that in a temple in the Far East, priests are attempting to move a stack of disks from one peg to another."
raw_input(" ") #All 'raw_input(" ")' simply makes user press return to proceed to the next line of text/instructions
print "The initial stack had 64 disks threaded onto one peg (the source peg) and arranged from bottom to top by decreasing size."
raw_input(" ")
print "The priests are attempting to move the stack form this peg to a second peg (the destination peg) under the constraints that"
raw_input(" ")
print "exactly one disk is moved at a time, and at no time may a larger disk be placed above a smaller disk."
raw_input(" ")
print "A third peg (the auxiliary peg) is available for temporarily holding disks."
raw_input(" ")
print "Supposedly the world will end if the priests complete their task."
raw_input(" ")
print "Please close the image window (press 'q' - you will need to do this after every image for the next one to appear.)"

#Instructions
raw_input(" ")
print "Your objective in this game is to achieve the task the priests have been working on for millenia... albeit on a much smaller scale..."
raw_input(" ")
print "First, choose the number of disks you want to play with. You can have up to 5 disks."
raw_input(" ")

playAgain = 1 									#Set up boolean for later in the game...
while playAgain == 1:
	#Sets up number of disks as per user input...
	comply = 0
	while (comply == 0):
		numdisks = raw_input("How many disks would you like to use? ")	#Asks user for a keyboard input for number of disks used in game
		print " "
		try:								#Help given by Ari on implementing this control structure
			numdisks = int(numdisks)				#Tries to assign the str() user input to be an int()
		except:								#If the user input cannot be an int() then the program 'ignores' it and the while loop restarts
			pass
		if type(numdisks) == type(1):					#If the user input is the type of 1 i.e. an int()
			if (numdisks < 6):					#And if the input is less than 6
				comply = 1					#Bool 'comply' variable changes to True, thus escapes while loop
				#print "Comply: ",comply			#Prints value of comply/Commented out - only needed for construction use by developer...
			else:
				print "You can only have a maximum of 5 disks."	#Otherwise, while loop continues, user reminded of input conditions.
				print " "

	numdisks = int(numdisks)		#Convert user input from str to int...

	background() 				#Reloads background to image plane
	stacks, WIN = polesSetup(numdisks) 	#Takes variables 'stacks' and 'WIN' from return of polesSetup() procedure.
						#polesSetup sets up 'stack' list depending on user input
						#Calls disk*() procedures for input number of disks
	show()
	#print " "
	#print "Stack setup: ",stacks		#Shows the list for the set up of the 3 poles/Commented out - only needed for construction use by developer...
	#print " "
	#print "Winning condition: ",WIN	#Shows the 'winning condition' for the game setup, i.e. all disks on middle peg/Commented out - only needed for construction use by developer...

	#The game begins...
	print (" ")
	print ("Now all you have to do is move the disks one by one onto the middle (destination) peg!")
	raw_input(" ")
	print ("Simply enter '*peg number* to *peg number*'. E.g. '1 to 3', '2 to 1', etc.")
	raw_input(" ")

	background()
	moveCount = 0
	while (stacks != WIN):					#While the stacks are NOT in the 'winning condition'
		move = str(raw_input("Make your move! "))
		if (move == "1 to 2"):
			if stacks[0] == []:				#As long as the stack is not empty...
				print " "
				print "*~*~ Invalid move! D:< ~*~*"	#If stack is empty, prints error message
				print " "
			else:
				pop = stacks[0].pop(0) 			#Pops the first item from the subset of the said item off the list, assigns to variable 'pop'
				stacks[1].insert(0, pop)		#Inserts 'pop' to the beginning of the subset of the second list
				background()				#Redraws bckground to cover up current disk positions
				drawDisks(numdisks)			#Draws disks in new positions
				#print " "
				#print stacks				#Prints list 'stacks' to show current list setup
				#print " "
				show()
				moveCount = moveCount + 1		#Adds 1 to move count
				print "Move count = ",moveCount 	#Prints number of moves performed thus far
				print " "
		if (move == "1 to 3"):
			if stacks[0] == []:
				print " "
				print "*~*~ Invalid move! D:< ~*~*"
				print " "
			else:
				pop = stacks[0].pop(0)
				stacks[2].insert(0, pop)
				background()
				drawDisks(numdisks)
				print " "
				print stacks
				print " "
				show()
				moveCount = moveCount + 1
				print "Move count = ",moveCount
				print " "
		if (move == "2 to 1"):
			if stacks[1] == []:
				print " "
				print "*~*~ Invalid move! D:< ~*~*"
				print " "
			else:
				pop = stacks[1].pop(0)
				stacks[0].insert(0, pop)
				background()
				drawDisks(numdisks)
				#print " "
				#print stacks
				#print " "
				show()
				moveCount = moveCount + 1
				print "Move count = ",moveCount
				print " "
		if (move == "2 to 3"):
			if stacks[1] == []:
				print " "
				print "*~*~ Invalid move! D:< ~*~*"
				print " "
			else:
				pop = stacks[1].pop(0)
				stacks[2].insert(0, pop)
				background()
				drawDisks(numdisks)
				#print " "
				#print stacks
				#print " "
				show()
				moveCount = moveCount + 1
				print "Move count = ",moveCount
				print " "
		if (move == "3 to 1"):
			if stacks[2] == []:
				print " "
				print "*~*~ Invalid move! D:< ~*~*"
				print " "
			else:
				pop = stacks[2].pop(0)
				stacks[0].insert(0, pop)
				background()
				drawDisks(numdisks)
				#print " "
				#print stacks
				#print " "
				show()
				moveCount = moveCount + 1
				print "Move count = ",moveCount
				print " "
		if (move == "3 to 2"):
			if stacks[2] == []:
				print " "
				print "*~*~ Invalid move! D:< ~*~*"
				print " "
			else:
				pop = stacks[2].pop(0)
				stacks[1].insert(0, pop)
				background()
				drawDisks(numdisks)
				#print " "
				#print stacks
				#print " "
				show()
				moveCount = moveCount + 1
				print "Move count = ",moveCount
				print " "
		if (move != "1 to 2" and not "1 to 3" and not "2 to 1" and not "2 to 3" and not "3 to 1" and not "3 to 2"): #Basically, if the user enters anything other than a valid move, do this
			print " "
			print "*~*~ Invalid move! D:< ~*~*"
			print " "
	
	print "Congratulations! You've won! :D" #This is printed once the winning condition is achieved
	print " "
	again = raw_input("Play again? (y/n) ")	#User asked whether to play again... (yes or no)
	if again == 'n':			#If user replies 'n' (no)...
		playAgain = 0			#playAgain bool changed to False, while loop ends...

print " "
print "See you next time!" #Pointless goobye message
