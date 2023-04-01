// I never finished HW3 so this program does not have any HW3 functionality

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dirent.h>
#include<unistd.h>

int main(void) {
    char buffer[1024];
    char dwelt_buffer[1024];
    char path_buffer[1024];
    char path_buffer1[1024];
    char path_buffer2[1024];
    char* args[128];
    char** arguement;
    struct dirent *directory;
    int counter = 0;
    FILE *f;
    FILE * read_file;
    FILE * write_file;
    char c;
    DIR *d;
    DIR* d1;
    DIR* d2;


    while(!feof(stdin)) {
        fputs("# ", stdout);
        
        if (fgets(buffer, 2048, stdin)) {
            arguement = args;
            *arguement++ = strtok(buffer," \n");
            while ((*arguement++ = strtok(NULL," \n")));

            if (args[0]) {
                // exit the shell
                if (strcmp(args[0], "byebye") == 0) {
                    break;
                }

                // run dwelt command
                if (strcmp(args[0], "dwelt") == 0) {
                    // find current path
                    char * dwelt_path = getcwd(dwelt_buffer, sizeof(dwelt_buffer));

                    // concatenate current path and arguement
                    strcat(dwelt_path, "/");
                    strcat(dwelt_path, args[1]);

                    // open a file to check
                    f = fopen(dwelt_path, "r");
                    d = opendir(dwelt_path);

                    // print appropiate message
                    if (f == NULL) {
                        printf("Dwelt not.\n");
                        continue;
                    } else if (d != NULL) {
                        printf("Abode is.\n");
                        continue;
                    } else {
                        printf("Dwelt Indeed.\n");
                        continue;
                    }
                    
                    // close pointer just in case
                    closedir(d);
                    fclose(f);
                }

                // run maik command
                if (strcmp(args[0], "maik") == 0) {
                    // find current path
                    char * filepath = getcwd(path_buffer, sizeof(path_buffer));

                    // concatenate current path and arguement
                    strcat(filepath, "/");
                    strcat(filepath, args[1]);

                    // check if file exists
                    f = fopen(filepath, "r");
                    if (f != NULL){
                        printf("Error, File already exists\n");
                        fclose(f);
                        continue;
                    }
                    fclose(f);

                    // open for writing a file
                    f = fopen(filepath, "w+");

                    // check for errors
                    if (f == NULL) {
                        printf("Error making a new file\n");
                        continue;
                    }

                    // writing the word draft
                    fprintf(f, "%s", "Draft");

                    fclose(f);
                }
                
                // run coppy command
                if (strcmp(args[0], "coppy") == 0) {        
                    // find current path
                    char * source_path = getcwd(path_buffer1, sizeof(path_buffer));
                    char * destination_path = getcwd(path_buffer2, sizeof(path_buffer));

                    // concatenate current path and arguement
                    strcat(source_path, "/");
                    strcat(source_path, args[1]);
                    strcat(destination_path, "/");
                    strcat(destination_path, args[2]);

                    // Destination file already exsists
                    FILE * check_file = fopen(destination_path, "r");
                    if (check_file != NULL) {
                        printf("Error, destination File already exists\n");
                        fclose(check_file);
                        continue;
                    }
                    fclose(check_file);

                    // open read and write files
                    read_file = fopen(source_path, "r");

                    // Source file doesn't exist
                    if (read_file == NULL) {
                        printf("Error, Source file Doesn't exist\n");
                        continue;
                    }

                    write_file = fopen(destination_path, "w+");
                    // Destination Directory doesn't exist
                    if (write_file == NULL) {
                        printf("Error, Destination directory doesn't exsist\n");
                        continue;
                    }

                    // coppy contents of file
                    while( (c = fgetc(read_file)) != EOF) {
                        fputc(c, write_file);
                    }
                    
                    // close files
                    fclose(read_file);
                    fclose(write_file);
                } 
            }
        }
    }

    return 0;
}