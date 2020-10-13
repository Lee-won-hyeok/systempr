#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int arg, char* argv[]){
	int fd;		
	
	if((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open");
		exit(1);
	}
	int linenum = 1;
	int index = 0;
	char c;
	char buffer[40];
	char **check = malloc(sizeof(char*)*10);
	int readptr = 0;
	int wordnum = 0;
	int i = 0;
	int methodnum = 1;
	
	while(read(STDIN_FILENO, &c, 1) != 0){
		//write(STDOUT_FILENO, &c, 1);
		if(c == ' '){
			//if(methodnum == 1) methodnum = 2;
			lseek(STDIN_FILENO, -1*readptr - 1, SEEK_CUR);
			read(STDIN_FILENO, buffer, readptr);
			//check[i] = buffer;
			write(STDOUT_FILENO, buffer, sizeof(buffer));
			//i++;
			
			lseek(STDIN_FILENO, 1, SEEK_CUR);
			//readptr = 0;
		}/*
		else if(c == '*'){
			lseek(STDIN_FILENO, -1*readptr, SEEK_CUR);
			read(STDIN_FILENO, check[i++], readptr);
			lseek(STDIN_FILENO, 1, SEEK_CUR);
			methodnum = 4;
		}
		else if(c == '['){
			methodnum = 3;
		}*/
	/*	else if(c == '\n'|| c == ']'){
			lseek(STDIN_FILENO, -1*readptr, SEEK_CUR);
			read(STDIN_FILENO, buffer, readptr);
			check[i] = buffer;
			//printf(buffer);
			i++;
		}*/
		else{
			readptr += 1;
		}
	}
	//write(STDOUT_FILENO, check[0], sizeof(check[0]));
		
	if(close(fd) < 0) {
		perror("close");
		exit(1);
	}
}

