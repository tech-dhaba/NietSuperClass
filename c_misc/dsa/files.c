//program to read the details of n students from a text file and assign them grades based on their marks and write to another file

#include <stdio.h>
#include <stdlib.h>

int main() {
    int input;
    printf("number of students: ");
    scanf("%d", &input);
    char command[100];
    sprintf(command, "./script.py %d", input);
    system(command);

    FILE* details=fopen("student_detail.txt","r");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), details) != NULL) {
    printf("Read: %s", buffer);
}

    fclose(details);


    return 0;
}