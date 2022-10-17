import re
import string
from collections import Counter

# added import counter function
# function that reads the input file, and prints each word and their frequency
# closes the read file after use 

def ReadList():

    f = open(r"C:\Users\sally\OneDrive\Documents\SNHU School\2022\Programming Languages CS-210\ProjectThree\x64\Release\CS210_Project_Three_Input_File.txt")
    items = f.read().split()
    individual = sorted(set(items))

    for word in individual:
        print(word,"  ", "\t\t", items.count(word))

    f.close()

# function that finds an item that a user types in and displays how many times it was found
# returns -1 if the word is not found 

def PurchaseHistory(v):

    f = open(r"C:\Users\sally\OneDrive\Documents\SNHU School\2022\Programming Languages CS-210\ProjectThree\x64\Release\CS210_Project_Three_Input_File.txt")
    items = f.read().split()
    individual = sorted(set(items))
    f.close()

    totalpurchase = 0
    totalItems = 0
    itemCount = 0

    for word in individual:
        itemCount += 1

    for word in individual:
        temp_String = word
        totalItems += 1
        if (temp_String == v): 
            totalpurchase = items.count(word)
            totalItems -= 1
        if (temp_String != v):
            return -1

        return totalpurchase

# function that opens the .dat file and allows it to be written 


def readAndWrite():

    f = open(r"C:\Users\sally\OneDrive\Documents\SNHU School\2022\Programming Languages CS-210\ProjectThree\x64\Release\CS210_Project_Three_Input_File.txt")
    data = open("frequency.dat", "w")
    items = f.read().split()
    individual = sorted(set(items))

# write the word and their frequency

    for word in individual: 
        data.write(word)
        data.write(" ")
        data.write(str(items.count(word)))
        data.write("\n")

# close the file 

    data.close()

# open the frequency.dat file 
# search for the frequency of each item name 

    readfile = open("frequency.dat", "r")
    readlines = readfile.readlines()

    itemFreq = 0
    itemName = 0

    for line in readlines:
        tempint = 0
        tempstring = line.split()
        for word in tempstring: 
            tempint += 1
            if (tempint == 1): 
                itemName = word
                print(itemName, end = " ")
            if (tempint == 2): 
                itemFreq = int(word)

# prints the * for the times the count finds for each item in the loop

        for i in range(itemFreq): 
            print("*", end = "")
        print("\n")