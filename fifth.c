#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
					
int checkRow (int**arr, int magic, int n){
	int i=0;
	int j=0;
	int count=0;
	int a=0;

	for (i=0; i<n; ++i){
		a=*(*(arr+i)+j);
		for (j=0; j<n; ++j){
			count +=*(*(arr+i)+j);
			if (a==*(*(arr+i)+j)&&j!=0){
				return -1;
			}
		}
		j=0;
		if (count != magic){
			return -1;
		}
		count =0;
	}
	return 1;	  

}

int checkCol (int**arr, int magic, int n){
	int i=0;
	int j=0;
	int count=0;
	int a=0;
	for (j=0; j<n; ++j){
		a=*(*(arr+i)+j);
		for (i=0; i<n; ++i){
			count +=*(*(arr+i)+j);
			if (a==*(*(arr+i)+j)&&i!=0){
				return -1;
			}

		}
		i=0;
		if (count != magic){
			return -1;
		}
		count =0;
	}
	return 1;	  
}

int checkDiagDown (int**arr, int magic, int n){
	int i=0;
	int j=0;
	int count=0;
	int a=*(*(arr+0)+0);
	for (i=0; i<n; i++){
		count +=*(*(arr+i)+j);
		if (a==*(*(arr+i)+j)&&j!=0){
			return -1;
		}

		j++;	
	}
	if (count != magic){
		return -1;
	}
	return 1;	  
}


int checkDiagUp (int**arr, int magic, int n){
	int i=0;
	int j=0;
	int count=0;
	int a=*(*(arr+(n-1))+0);
	for (i=n-1; i>=0; i--){
		count +=*(*(arr+i)+j);
		if (a==*(*(arr+i)+j)&&j!=0){
			return -1;
		}
		j++;	
	}
	if (count != magic){
		return -1;
	}
	return 1;	 
}

int **createArray(char*buffer, int *val){
	int i=0;
	char*str=(char*)malloc(sizeof(char)*20);
	while (buffer[i]!='\n'){
		str[i]=buffer[i];
		++i;
	}
	++i;
	int n=atoi(str);
	*val=n;
	int temp=0;
	int j=0;
	int k=0;
	int index=0;
	int**arr=(int**)malloc(sizeof(int*)*n);
/*	if(arr==NULL){
		printf("ERROR:OUT OF MEMORY");
		return NULL;
	}*/
	for(j=0; j<n;++j){
		arr[j]=malloc(sizeof(int)*n);
		/*if(arr[j]==NULL){
			printf("ERROR: OUT OF MEMORY");
			return NULL;
		}*/
	}
	j=0;
	while(buffer[i]!='\0'){
		if (buffer[i]=='\t'){
			temp=atoi(str);	
			arr[j][k]=temp;
			index=0;
			++i;
			++k;
		}else if (buffer[i]=='\n'){
			temp=atoi(str);
			*(arr[j]+k)=temp;
			index=0;
			++i;
			k=0;
			++j;
		}
		else{
			str[index]=buffer[i];
			++index;
			++i;
		}
	}

	return arr;
}

int main (int argc, char* argv[]){
	int magic=15;
	int n=0;

 	int fd =open (argv[1], O_RDONLY);
	if (fd==-1){
		return -1;
	}
	int i=0;
	int numBytes=100;
	char*buffer=(char*) malloc(sizeof(char)*numBytes);
	for (i=0; i<99; ++i){
		buffer[i]='\0';
	}
	read(fd, buffer, numBytes);

	int**arr=createArray(buffer, &n);

	free(buffer);
	
	if (checkRow(arr, magic, n)==-1){
		printf("not-magic");
	}
	else if (checkCol(arr, magic, n)==-1){
		printf("not-magic");

	}
	else if (checkDiagDown(arr, magic, n)==-1){
		printf("not-magic");
	}
	else if (checkDiagUp(arr, magic, n)==-1){
		printf("not-magic");
	}
	else{
		printf("magic");
	}
	return 0;

}
