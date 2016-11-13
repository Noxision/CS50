from __future__ import print_function
import cs50
import sys

if len(sys.argv) < 2 or not sys.argv[1].isalpha():
    sys.exit('usage : ./vigenere + k')
    
print("plaintext: ")
string = cs50.get_string()

cipherIter = 0
inputIter = 0

for char in string:
    if char.isalpha():
        cipherPointer = cipherIter%len(sys.argv[1])
        
        cipherRemoval = sys.argv[1][cipherPointer].isupper() and 65 or 97

        slip = ord(sys.argv[1][cipherPointer]) - cipherRemoval
        
        inputRemoval = char.isupper() and 64 or 96

        cipherCharASCII = ord(char) - inputRemoval + slip  
        
        if cipherCharASCII != 26:
            cipherCharASCII = ((ord(char) - inputRemoval) + slip)%26
            
        cipherCharASCII += inputRemoval 
        
        char = chr(cipherCharASCII)
        cipherIter += 1
    
    if inputIter == 0:
        string = char + string[inputIter+1:]
    else:
        string = string[:inputIter] + char + string[inputIter+1:]
    inputIter += 1

print("ciphertext: ", end="")
print(string)
