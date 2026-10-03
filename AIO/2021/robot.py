import sys
sys.setrecursionlimit(1000000000)

#
# Solution Template for Robot Vacuum
# 
# Australian Informatics Olympiad 2021
# 
# This file is provided to assist with reading of input and writing of output 
# for the problem. You may modify this file however you wish, or
# you may choose not to use this file at all.
#

# K is the number of instructions.
K = 0

# instrs contains the sequence of instructions.
instrs = ""

answer = 0

# Read the value of K and the sequence of instructions.
K = int(input().strip())
instrs = input().strip()

# TODO: This is where you should compute your solution. Store the fewest number
# of instructions you need to add to the end of the sequence into the variable
# answer.

x = 0
y = 0
for i in instrs[:K]:
    if i == 'E':
        x += 1
    elif i == 'W':
        x -= 1
    elif i == 'N':
        y += 1
    elif i == 'S':
        y -= 1

answer = abs(x) + abs(y)

# Write the answer.
print(answer)
