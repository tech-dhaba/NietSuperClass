#!/usr/bin/python3
import random
import string
import sys

def generate_random_name():
    return "".join(random.choices(string.ascii_lowercase,k=5))
def generate_random_roll():
    return "".join(random.choices(string.digits,k=3))
def generate_random_marks():
    return [random.randint(20,100) for i in range(3)]
 
# print(generate_random_name())
# print(generate_random_roll())
# print(generate_random_marks())

with open("student_detail.txt","w") as file:
    for _ in range(int(sys.argv[1])):
        file.write("Name: {} ".format(generate_random_name()))
        file.write("Roll: {} ".format(generate_random_roll()))
        for i,mark in enumerate(generate_random_marks(),1):
            file.write("Subject {}: {} ".format(i,mark))
        file.write("\n")


    
    

    
