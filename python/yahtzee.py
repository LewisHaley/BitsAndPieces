#
# Yahtzee Rolling inc. Statistical Averages
#
# Created by: Lewis Haley (www.lewishaley.co.uk)
# - lewismhaley@gmail.com
#
# Outline
# - A series of procedures that simulate rolling a set of 5 die, with the aim of rolling a yahtzee (a roll of (any) 5 identical values)
# - Prints out a running average of number of rolls need to get a yahtzee, also records this data in a text file which can be read into MS Excel, etc
# - The statistical average is 1,296 rolls
# - Runs in a command line/shell environment
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
# - Version 1.0 (July 26th 2012)
# - - Completed all main functions, algorithms, up to working standard
# - Version 1.0.1 (August 31st 2012)
# - - Slight edit to output file, further commenting
#

import random, math, os

# synthesises rolling the 5 dice
# input: -
# output: LIST containing 5 dice values
def diceRoll():
	newRoll = [1,1,1,1,1]
	for i in range( 0, 5 ):
		newRoll[i] = random.randint(1,6)
	return newRoll

# checks dice for yahtzee combination
# input: LIST (should contain 5 ints)
# output: BOOL
def checkYahtzee( dice ):
	# assert checks to ensure dice contains 5 interger values
	assert( len( dice ) == 5 )
	assert( type( dice[0] + dice[1] + dice[2] + dice[3] + dice[4] ) == type(1) )
	# returns whether the 5 values are equal
	return ( dice[0] == dice[1] == dice[2] == dice[3] == dice[4] )

# keeps rolling and checking until  a yahtzee is rolled
# input: -
# output: INTEGER count of number of iterations to get a yahtzee
def rollYahtzee():
    rolling = True
    counter = 0
    while rolling:
        counter += 1
        dice = diceRoll()
        # if a yahtzee is rolled, we stop rolling
        rolling = not checkYahtzee( dice )
    return counter

# calculates a floating point average of a list of numbers
# input: LIST (integers / undefined size)
# output: FLOAT
def getAverage( numberList ):
	# check all values are int
	for i in numberList:
		assert( type(i) == type(1) )
	# floating point sum of all items in list
	val = math.fsum( numberList )
	return float( val / len( numberList ) )

#			#
#  PROGRAM STARTS HERE	#
#			#

# creates/erases contents of txt file
open( os.getcwd()+"/yahtzeeAverages.txt", "w" ).close()
# opens file ready for writing to
f = open( os.getcwd()+"/yahtzeeAverages.txt", "a" )

rolling = 0
countList = []

# user input for number of yahtzee averages to record
it = int( raw_input( "Number of interations: " ) )
pr = str( raw_input( "Print output? Y/N " ) ).upper()

while rolling<it:
	# add value from rollYahtzee to list of roll counts
	countList.append( rollYahtzee() )
	# calculate the average number of rolls
	average = float( getAverage( countList ) )
	# writes average to file
	f.write( str( average )+"\n" )
	if pr == "Y":
		print average
	rolling += 1
