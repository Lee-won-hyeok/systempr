#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void itoa(int num, char *str){
	int deg = 1;
	int pow = 0;

	while(1){
		if((num/deg)>0)
			pow++;
		else
			break;
		deg *= 10;
	}
	deg /= 10;
	for(int i = 0; i < pow ; i++){
		*(str+i) = num/deg + '0';
		num -= ((num/deg)*deg);
		deg /=10;
	}
	*(str + pow) = '\0';
}

void pnum(int num, char *str){
	if(num == 0) write(STDOUT_FILENO, "0", 2);
	else if(num < 10) write(STDOUT_FILENO, str, 1);
	else if(num < 100) write(STDOUT_FILENO, str, 2);
	else if(num < 1000) write(STDOUT_FILENO, str, 3);
	else if(num < 10000) write(STDOUT_FILENO, str, 4);
	else if(num < 100000) write(STDOUT_FILENO, str, 5);
}

int readline(int fd, char* buf, int byte){
	int rbyte = 0;
	int retval;
	while(rbyte < byte - 1){
		//write(STDOUT_FILENO, "while1", 6);
		//write(STDOUT_FILENO, buf, 50);
		if((retval = read(fd, buf + rbyte, 1)) == 0){
			return rbyte;
		}
		if(buf[rbyte] == '\n'){
			buf[rbyte+1] = '\0';
			//write(STDOUT_FILENO, buf, 50);
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
		lseek(fd, 0, SEEK_SET);
			
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
		
		//char *Inwords[20];
		char bufp[512];
		int rbyte = 0;
		int linenum = 0;
		switch(mod){
			case 1:
				while(1){
					linenum ++;
					rbyte = readline(fd, bufp, 512);
					if(rbyte == 0) break;
					//write(STDOUT_FILENO, "\n", 1);
					//write(STDOUT_FILENO, bufp, 512); 

					char *lnwords[20];
					int marker = 0;
					char num[10];
					int i = 0;
					int flag = 0;
					
					while(i < rbyte){
						if(bufp[i] == '\n') break;
						else if(bufp[i] == ' ' || bufp[i] == '\t'){
							marker = i + 1;
							flag = 0;
						}
						else{
							if(marker == i || flag == 1){
								if(bufp[i] == words[0][i - marker]){
									flag = 1;
									if(words[0][i - marker + 1] == '\0'){
										if((bufp[i + 1] == '\n' || bufp[i + 1] == '\t' || bufp[i+1] == ' ' || bufp[i + 1] == EOF)){
											itoa(linenum, num);
											pnum(linenum, num);
											write(STDOUT_FILENO, ":", 1);
											itoa(marker, num);
											pnum(marker, num);
											write(STDOUT_FILENO, "\n", 1);
										}
									}
								}
								else flag = 0;
							}
						}
						i++;
					}
					/*
					for(int i = 0; i < 512; i++){
						if(bufp[i] == '\n')
							break;
						else if(bufp[i] == ' ' || bufp[i] = '\t'){
							if(marker != i){
								lnwords[j] = malloc(sizeof(char)*40);
								for(int k = 0; k < i - marker; k++)
									lnwords[j][k] = bufp[marker + k];
								lnwords[j][i - marker] = '\0';
								j++;
							}
							marker = i + 1;
						}
					}*/
				}
				break;
			case 2:
				break;
		}
	}
}

