#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    
    // Open the directory
    if ((dir = opendir(argv[1])) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
    // Iterate over the directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Get the full path of the file
        char filepath[PATH_MAX];
        snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name);
        
        // Get the file status
        if (stat(filepath, &filestat) == -1) {
            perror("stat");
            continue;
        }
        
        // Check if the file is executable
        if (S_ISREG(filestat.st_mode) && (filestat.st_mode & S_IXUSR)) {
            // Delete the executable file
            if (unlink(filepath) == -1) {
                perror("unlink");
            } else {
                printf("Deleted: %s\n", filepath);
            }
        }
    }
    
    // Close the directory
    closedir(dir);
    
    return 0;
}
