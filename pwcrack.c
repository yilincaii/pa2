#include <stdint.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <assert.h>

//milestone1
uint8_t hex_to_byte(unsigned char h1, unsigned char h2){
    //check if h1 and h2 are valid 16 based char
    assert((h1>='0'&& h1<='9')||(h1>='a'&& h1<='f')||(h1>='A'&& h1 <='F')&&"invalid hex char in h1");
    assert((h2>='0'&& h2<='9')||(h2>='a'&& h2<='f')||(h2>='A'&& h2 <='F')&&"invalid hex char in h2");
    uint8_t n1 = (h1>='0'&& h1<='9')? h1-'0':
                 (h1>='a'&& h1<='f')? h1-'a'+10:
                 (h1>='A'&& h1<='F')? h1-'A'+10: 0;

    uint8_t n2 = (h2>='0'&& h2<='9')? h2-'0':
                 (h2>='a'&& h2<='f')? h2-'a'+10:
                (h2>='A'&& h2<='F')? h2-'A'+10: 0;


    return (n1<<4)|n2;
}
void hexstr_to_hash(unsigned char hexstr[],char hash[32]){
    for (int i =0; i< 32; i++){
        hash[i] = hex_to_byte(hexstr[i*2], hexstr[i*2+1 ]);
    }
}
//milestone2 function-compare hash

// check password fucntion 
int8_t check_password(char password[], char given_hash[32]){
    unsigned char hash[ SHA256_DIGEST_LENGTH];
    // check if password null or too long.
    assert(password != NULL && "password can't be null");
    assert( strlen(password)>0 && "password cannot be empty");
    //get password hash
    SHA256((unsigned char *)password, strlen(password), hash);
    //check if hash is 32 bytes.
    assert (SHA256_DIGEST_LENGTH ==32 && "SHA256 hash length mismatch");
    //chekc if given hash = calculate hash
    for(int i = 0;i< 32; i++){
        if (hash[i]!= ( unsigned char)given_hash[i]){
            return 0;// not match 
        }
    }
    return 1;// match
}
int8_t crack_password ( char password[], char given_hash[32]){
    //check if matching with orignal password
    if (check_password(password, given_hash)){
        return 1;
    }
    int length = strlen(password);
    for (int i =0; i < length;i++){
        char ori_char = password[i];
        if(islower(ori_char)){
            password[i] = toupper(ori_char);
            if (check_password(password,given_hash)){
                return 1;
            }
            password[i] = ori_char;
        }
        //if uppercase->turn to lowercase
        if(isupper(ori_char)){
            password[i] = tolower(ori_char);
            if(check_password(password, given_hash)){
                return 1;
            }
            password[i] = ori_char;
        }
    }
    return 0; // 0 for if not match 
}
/*、
//test
int main(){
    char password[] = "paSsword";
    char hashtest[ ]="5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";
    char given_hash[32];
    hexstr_to_hash((unsigned char*)hashtest,given_hash);
    int8_t match = crack_password(password, given_hash);
    if(match){
        printf("password matched: %s\n", password);

    }
    else{
        printf("No matching password found.\n");
    }
    return 0;
}
*/
const int SHA_LENGTH = 32;
int main(int argc, char** argv){
    if(argc !=2){
        fprintf (stderr, "usage: %s <sha256_hash>\n", argv[0]);
        return 1;
    }
        char given_hash[32];
        hexstr_to_hash((unsigned char*)argv[1], given_hash);

        char password[256];

        //read ps from stdin
        while (fgets((password) , sizeof(password),stdin)){
            //remove new line char if exixt
            size_t len =strlen(password);
            if(password[len-1]=='\n'){
                password[len-1]='\0';
                }
            if (crack_password(password, given_hash)){
                printf("Found password: SHA256(%s) = %s\n",password, argv[1]);
                return 0; //once match ehtn exit
            }
        }
    printf("Did not find a matching password\n");
    return 0;
}
