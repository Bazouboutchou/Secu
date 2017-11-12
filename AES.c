

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// a simple hex-print routine. could be modified to print 16 bytes-per-line
static void hex_print(const void* pv, size_t len)
{
    const unsigned char * p = (const unsigned char*)pv;
    if (NULL == pv)
        printf("NULL");
    else
    {
        size_t i = 0;
        for (; i<len;++i)
            printf("%02X ", *p++);
    }
    printf("\n");
}

// main entrypoint
int main(int argc, char **argv)
{
    int keylength;
    printf("Give a key length [only 128 or 192 or 256!]:\n");
    scanf("%d", &keylength);

    /* generate a key with a given length */
    unsigned char aes_key[keylength/8];
    memset(aes_key, 0, keylength/8);
    if (!RAND_bytes(aes_key, keylength/8))
        exit(-1);

    /* generate input with a given length */
	struct stat fileAesStat;
	lstat("aes.txt", &fileAesStat);
	size_t inputslength = fileAesStat.st_size -1; // on enleve le \0
    unsigned char aes_input[inputslength];
	char c; 	
	FILE *fileAes;
	// get all caracteres in file
	fileAes = fopen (argv[1], "rb");
	int i = 0;
	while ((fread(&c, sizeof(char), 1, fileAes))){
		aes_input[i] = c;
		++i; 	
	}
    //memset(aes_input, 'X', inputslength);
		

    /* init vector */
    unsigned char iv_enc[AES_BLOCK_SIZE], iv_dec[AES_BLOCK_SIZE];
    RAND_bytes(iv_enc, AES_BLOCK_SIZE);
    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    // buffers for encryption and decryption
    const size_t encslength = ((inputslength + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char enc_out[encslength];
    unsigned char dec_out[inputslength];
    memset(enc_out, 0, sizeof(enc_out));
    memset(dec_out, 0, sizeof(dec_out));

    // so i can do with this aes-cbc-128 aes-cbc-192 aes-cbc-256
    AES_KEY enc_key, dec_key;
    AES_set_encrypt_key(aes_key, keylength, &enc_key);
    AES_cbc_encrypt(aes_input, enc_out, inputslength, &enc_key, iv_enc, AES_ENCRYPT);

    AES_set_decrypt_key(aes_key, keylength, &dec_key);
    AES_cbc_encrypt(enc_out, dec_out, encslength, &dec_key, iv_dec, AES_DECRYPT);

    printf("original:\t");
    hex_print(aes_input, sizeof(aes_input));

    printf("encrypt:\t");
    hex_print(enc_out, sizeof(enc_out));

	FILE *fileC;
	fileC = fopen ("chiffre.txt", "wb");
	int j; 	
	for(j = 0; j < encslength; ++j){
		fwrite (&enc_out[j], sizeof(unsigned char), 1, fileC);	
	}

    printf("decrypt:\t");
    hex_print(dec_out, sizeof(dec_out));
	fclose (fileAes);
	fclose (fileC);
    return 0;
}
