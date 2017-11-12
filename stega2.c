#include <stdio.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/*unsigned bindec(char bin[]){
	int i;
	int j = 7;
	res
	for (i = 0; i < strlen(bin), ++i){
	}
}*/

void decbin(int decimal, char rep_binaire[])
{
    //char rep_binaire[1000000];

    if(decimal > 255)
    {
        printf("Trop grand");
        return ;
    }
    else
    {
		int i;
    	for(i = 7;i>=0;i--){	
			if(decimal >= pow(2, i)){
			    rep_binaire[i] = '1';
			    decimal -= pow(2, i);
			}
			else{
			     rep_binaire[i] = '0';
			}
		}

  		//printf("%s",rep_binaire);

    }
}
int main (){
	FILE *pngFile;
	pngFile = fopen("img.png", "rb");
	FILE *newFile;
	newFile = fopen("new.png", "wb");
	struct stat fileAesStat;
	lstat("img.png", &fileAesStat);
//	printf("test size : %d", fileAesStat.st_size);
	size_t inputslength = fileAesStat.st_size -1; // on enleve le \0
	unsigned char data[inputslength];
	unsigned char c;
	int i = 0; 
	while (i < 33){
		fread(&c, sizeof(unsigned char), 1, pngFile);
		data[i]= c;
		printf("c : %d", data[i]);

		++i;
	}
//	fseek(pngFile, 33*8, SEEK_SET);

	unsigned char new;	 
	unsigned char mes = 255;
	//char binMess [8] = bindec(mes, binMess);
	while ((fread(&c, sizeof(char), 1, pngFile))){
		//fwrite(&c,  sizeof(unsigned char), 1, newFile);		
		//printf ("%d ", c);
		new = c &~(1<<1);
		new = c &~(1<<0);
 		new = new ^ 3;
		//printf ("Apres : %d\n", new);
		data[i] = c;
		++i;
	} 
	fseek(pngFile, -12, SEEK_END);
	i = i - 12;
	while ((fread(&c, sizeof(char), 1, pngFile))){
		data[i] = c;
		printf("%d ", data[i]);
		printf("%d ", c);
		++i;
	}
	//fseek(pngFile, 33*8, SEEK_SET);
	fwrite(&data, sizeof(unsigned char), inputslength, newFile);
	fclose(pngFile);
	
}
