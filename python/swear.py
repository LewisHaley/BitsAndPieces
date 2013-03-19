import random

def randletter():
	return random.randint(32,126)

def convertletter(letter):
	return chr(letter)

def letter():
	return convertletter(randletter())

def word(ward):
	wordfull = ""
	for i in range(0,(len(ward)-lettercount)):
		wordfull = wordfull+letter() 
	return ward[0:lettercount]+wordfull


def prints(ward):
	swear = 0
	num = 0
	global lettercount
	lettercount = 1
	while swear == 0:
		newword = word(ward)
		for i in range(1,len(ward)):
			if newword[0:i] == ward[0:i]:
				lettercount = i
	print newword,
	num += 1
	if newword == ward:
		swear = 1
	print ""
	print "GREAT SUCCESS! found",ward,"after",num,"tries!"


ward = raw_input("give me ANYTHING: ")

prints(ward)
