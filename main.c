#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    DIR *directory; //typedef struct __dirstream
    directory = opendir("."); 
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