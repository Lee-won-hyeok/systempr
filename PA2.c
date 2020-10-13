#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int readline(int fd, char* buf, int byte){
	int rbyte = 0;
	int retval;
	while(rbyte < byte - 1){
		//write(STDOUT_FILENO, "while1", 6);
		if((retval = read(fd, buf + rbyte, 1)) == 0){
			//write(STDOUT_FILENO, &buf[rbyte], 1);
			//write(STDOUT_FILENO, &rbyte, sizeof(rbyte));
			//printf("%d", rbyte);
			return rbyte;
		}
		if(buf[rbyte] == '\n'){
			buf[rbyte+1] = '\0';
			return rbyte + 1;
		}
		rbyte++;
	}
}

int main(int arg, char* argv[]){
	int fd;		
	
	if((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open");
		exit(1);
	}
	
	while(1){
		char buf[512];
		if(read(STDIN_FILENO, buf, sizeof(buf)) < 0){
			perror("read");
			exit(1);
		}
			
		char *words[10];
		int k = 0;
		int lastptr = 0;
		int mod = 1;
		// k = max_index_of_words
		for(int i = 0; i < 512; i++){	
			if(buf[i] == '\n'||buf[i] == ']'){
				words[k] = malloc(sizeof(char)*40);
				for(int j = 0; j < i - lastptr; j++){
					words[k][j] = buf[lastptr + j];
				}
				words[k][i - lastptr] = '\0';
				break;
			}
			else if(buf[i] == ' '||buf[i] == '*'){
				if(buf[i] == ' '&&mod == 1) mod = 2;
				if(buf[i] == '*') mod = 4;
				words[k] = malloc(sizeof(char)*40);
				for(int j = 0; j < i - lastptr; j++){
					words[k][j] = buf[lastptr + j];
				}
				words[k][i - lastptr] = '\0';
				k++;
				lastptr = i + 1;
			}
			else if(buf[i] == '['){
				mod = 3;
				lastptr = i + 1;
			}
		}
		for(int p = 0; p <= k; p++){
			write(STDOUT_FILENO, words[p], 8);
		}
		
		char *Inwords[20];
		char bufp[50];
		int rbyte = 0;
		int linenum = 1;
		int index = 0;
		switch(mod){
			case 1:
			//	while(1){
				rbyte = readline(fd, bufp, 50);
				write(STDOUT_FILENO, bufp, 50);
		//		rbyte = readline(fd, bufp, 50);
		//		rbyte = readline(fd, bufp, 50);
		//			break;
			//		}
					//write(STDOUT_FILENO, bufp, 50);
				
		}			
	}
}

