import sys
sys.setrecursionlimit(1000000000)

#
# Solution Template for Level Ground
# 
# Australian Informatics Olympiad 2022
# 
# This file is provided to assist with reading of input and writing of output 
# for the problem. You may modify this file however you wish, or
# you may choose not to use this file at all.
#

# N is the number of segments.
N = 0

# A contains the altitude of the segments.
A = []

answer = 0

# Read the value of N.
N = int(input().strip())

# Read the altitudes.
A = list(map(int, input().strip().split()))

# TODO: This is where you should compute your solution. Store the highest
# intensity that can be achieved into the variable answer.

lasta = 0
intensity = 0
length = 0

for i in A:
    if i == lasta:
        intensity += i 
    else: 
        intensity = i
    answer = max(answer, intensity)
    lasta = i

# Write the answer.
print(answer)
