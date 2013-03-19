#
# Sumation of numbers within text
#
# Created by: Lewis Haley (www.lewishaley.co.uk)
# - lewismhaley@gmail.com
#
# Outline
# - Scans through lines of text identifying numbers
# - Converts these numbers into digits
# - Adds them up and prints the total
# - This was set as a challenge by BEN ICETON ( http://www.linkedin.com/pub/ben-iceton/13/18/486 )
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
# - Version 1.0 (August 12th 2012)
# - - Original version
#

f = '''
The Galaxy Song

Just remember that you're standing on a planet that's evolving
And revolving at nine hundred miles an hour,
That's orbiting at nineteen miles a second, so it's reckoned,
A sun that is the source of all our power.
The sun and you and me and all the stars that we can see
Are moving at a million miles a day
In an outer spiral arm, at forty thousand miles an hour,
Of the galaxy we call the 'Milky Way'.
Our galaxy itself contains a hundred billion stars.
It's a hundred thousand light years side to side.
It bulges in the middle, sixteen thousand light years thick,
But out by us, it's just three thousand light years wide.
We're thirty thousand light years from galactic central point.
We go 'round every two hundred million years,
And our galaxy is only one of millions of billions
In this amazing and expanding universe.

The universe itself keeps on expanding and expanding
In all of the directions it can whizz
As fast as it can go, at the speed of light, you know,
Twelve million miles a minute, and that's the fastest speed there is.
So remember, when you're feeling very small and insecure,
How amazingly unlikely is your birth,
And pray that there's intelligent life somewhere up in space,
'Cause there's bugger all down here on Earth.
'''

# dictionary of primitive numbers
numDict = dict(	one = 1,
			two = 2,
			three = 3,
			four = 4,
			five = 5,
			six = 6,
			seven = 7,
			eight = 8,
			nine = 9,
			ten = 10,
			eleven = 11,
			twelve = 12,
			thirteen = 13,
			fourteen = 14,
			fifteen = 15,
			sixteen = 16,
			seventeen = 17,
			eighteen = 18,
			nineteen = 19,
			twenty = 20,
			thirty = 30,
			forty = 40,
			fifty = 50,
			sixty = 60,
			seventy = 70,
			eighty = 80,
			ninety = 90 )

powDict = dict( 	hundred = 100,
			thousand = 1000,
			million = 1000000,
			billion = 1000000000 )

# open up the text document
#f = open( 'C:\Users\Lewis\Documents\TheGalaxySong.txt' )

# set current total as zero
total = 0

# prepare string for analysis
lines = ''
for line in f:
	lines += line

#lines = 'kyle has five chickens and I have ten donkeys. If I trade him a thousand potatoes he will give me forty seven carrots.'

lines = lines.lower() # make sure its all lowercase to reduce comparisons

# remove punctuation
tmp = []
for ch in lines:
	tmp.append(ch)
bl = True
while bl:
	try:
		tmp.remove( ',' ) # keep trying to remove commas
	except:
		bl = False
bl = True
while bl:
	try:
		tmp.remove( '.' ) # keep trying to remove fullstops
	except:
		bl = False
lines = ''
for ch in tmp:
	lines += ch # reassemblying string...

words = lines.split() # split up string into words

# this gets rid of any instance of the word 'and'
# that don't occur between 2 numbers
# e.g. two hundred AND fifty gets kept
adding = False
x = 0
while x < len(words)-1:
	if words[x] in numDict or words[x] in powDict:
		x +=1
		adding = True
	elif words[x] == 'and' and adding == False:
		words.pop(x)
	else:
		x += 1
		adding = False

numbers = [] # make and empty list for any numbers found

# scan through every word in the string
for word in words:
	if word in numDict or word in powDict or word == 'and': # if the word is in either dictionary, add it to the list
		numbers.append( word )
	elif len(numbers) != 0 and numbers[ -1 ] != '\n': # if not a number, add a \n marker between numbers
		numbers.append( '\n' )

numbers.append( '\n' )
print numbers

isPow = False
# while there are numbers still to sum
while len(numbers) > 1:
	enum = 0
	# try reading the number from the num dictionary
	try:
		tmpNum = numDict[ numbers[enum] ]
	# if not, get it from pow dict
	except:
		tmpNum = powDict[ numbers[enum] ]
	# go onto the next number in the list, unless its a \n
	while numbers[enum+1] != '\n':
		if numbers[enum+1] == 'and':
			isPow = False
		# if the next num is a power of ten
		elif numbers[enum+1] in powDict:
			isPow = True
			# multiply the last number by the pow ten
			tmpNum *= powDict[ numbers[enum+1] ]
			print str(tmpNum).rjust(14, ' ')
		# if its another 'regular' num
		elif numbers[enum+1] in numDict:
			# if the last operation was a pow
			if isPow:
				# flush the tmp value to the total
				total += tmpNum
				tmpNum = 0
				isPow = False
			# start adding from zero
			tmpNum += numDict[ numbers[enum+1] ]
			print str(tmpNum).rjust(14, ' ')
		enum += 1
	# once a \n is reached
	while enum >= -1:
		# remove all numbers so far 
		numbers.pop(0)
		enum -= 1
	total += tmpNum

print "Total =",total
