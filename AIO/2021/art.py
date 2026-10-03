import sys
sys.setrecursionlimit(1000000000)

#
# Solution Template for Art Class II
# 
# Australian Informatics Olympiad 2021
# 
# This file is provided to assist with reading of input and writing of output 
# for the problem. You may modify this file however you wish, or
# you may choose not to use this file at all.
#

# N is the number of holes.
N = 0

# x and y contain the locations of the holes.
x = []
y = []

answer = 0

# Read the value of N.
N = int(input().strip())

# Read the location of each hole.
for i in range(0, N):
    input_vars = list(map(int, input().strip().split()))
    x.append(input_vars[0])
    y.append(input_vars[1])

# TODO: This is where you should compute your solution. Store the area of the
# smallest poster that will cover all the holes into the variable answer.
maxx = 0
minx = 10001
maxy = 0
miny = 10001

for i in range(N):
    if x[i] > maxx:
        maxx = x[i]
    if x[i] < minx:
        minx = x[i]
    if y[i] > maxy:
        maxy = y[i]
    if y[i] < miny:
        miny = y[i]

answer = (maxx - minx) * (maxy - miny)

# Write the answer.
print(answer)
