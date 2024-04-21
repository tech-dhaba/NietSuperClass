#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFFER_SIZE 1



int main(int argc, char **argv)
{
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read )
        {
            fprintf(stderr, "Error writing to stdout\n");
            return 1;
        }
    }

    if(bytes_read == -1)
    {
        fprintf(stderr, "Error reading from stdin\n");
        return 1;
    }

    return 0;
}
