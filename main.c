#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
    char dir_to_open[1000];
    if(argc == 1){
        printf("Please specify a directory to open: \n");
        scanf("%999s", dir_to_open);
    }
    if(argc == 2){
        strncpy(dir_to_open, argv[1], 999);
    }
    if(argc > 2) {
        printf("Too many inputs!\n");
        return 0;
    }

    DIR *directory; //typedef struct __dirstream
    directory = opendir(dir_to_open); 
    if(directory == NULL) { //Something went wrong
        printf("Error: %s called %s\n", strerror(errno), dir_to_open);
        return 0;
    }

    int size = 0;
    struct dirent *directory_entry;
    directory_entry = readdir(directory); //Open directory

    printf("Statistics for Directory: %s\n", directory_entry->d_name);

    struct stat reg_file;
    while (directory_entry){ //Loop through files to find total size
        if (directory_entry->d_type == DT_REG){
            stat(directory_entry->d_name, &reg_file);
            size += reg_file.st_size;
        }
        directory_entry = readdir(directory);
    }

    //show the total size of all the regular files the directory
    printf("Total Directory Size: %d bytes\n", size);

    //Reset directory position
    rewinddir(directory);

    printf("Directories:\n"); //specify which files are directories (if any)

    while (directory_entry = readdir(directory)){
        if (directory_entry->d_type == DT_DIR){
            printf("\t%s\n", directory_entry->d_name);
        }
    }

    //Reset directory position
    rewinddir(directory);

    printf("Files:\n");

    while (directory_entry = readdir(directory)){
        if (directory_entry->d_type == DT_REG){
            printf("\t%s\n", directory_entry->d_name); //print file names
        }
    }
    closedir(directory);
}