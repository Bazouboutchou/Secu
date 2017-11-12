#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

void bindec(char binaire[]){

        int rep_decimale=0;

        char bit[8];
		char zeros[8];


        if(strlen(binaire) < 8) // Si on se retrouve avec moins de 8 caractères.

        {

            zeros[8-strlen(binaire)] = '0';
			int j;			
			for (j = 0; j < strlen(binaire); ++j){
				zeros
				binaire = zeros[binaire];				
			}

        }

		int i;
        for(i=0;i<=7;i++)

        {

            bit = binaire[i];

            if(bit == "1")

            {

                rep_decimale += pow(2, 7-i);

            }

        }


        return rep_decimale;

}


void hide (){
	char tab [100000];
	int i = 0;	
	FILE *img; 
	int c;
	int z=0;
	img = fopen ("img.png", "rb");
	fseek(img, 33*8, SEEK_SET);
	char message[6] = "secret";
	char octet_decoupe [2];

	char caractere;

	char *valeur_octet = NULL;
	valeur_octet = malloc (sizeof(char));
 	char octet_binaire[8];
	int octet_image;
	for(i=0; i < 6; ++i){

		caractere = message[i];
	
	    sprintf(valeur_octet,"%d",caractere);

		decbin(atoi(valeur_octet), octet_binaire);
		int j;
		printf("%s\n", octet_binaire);
		for (j = 0; j < 7; j += 2){
//			printf("%c", octet_binaire[j]);
//			printf("%c", octet_binaire[j+1]);
			
			int partie_octet;			
			for(partie_octet = 0; partie_octet < 2; ++partie_octet){
				fread(&octet_image,sizeof(char),1, img);				
//				printf("%d\n", octet_image);
        		octet_image -= octet_image%4; 
				//printf("%d", octet_image);
				partie_octet = bindec(octet_binaire[j]); 
				printf("%d\n", partie_octet);
		
				
			}

		}


	}
	/*while(fread(&c,sizeof(char),1, img)){
        
   		decbin(c);
		++i;
    }*/	
    
    fclose(img);
     
	
}

/*
void recover {

}*/
int main (){
	hide ();
}
