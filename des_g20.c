#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef unsigned long long ull;
FILE *INPUT;
FILE *OUTPUT;
FILE *HEX_OUTPUT;
FILE *KEY;

int expansion_table[] = { 32,  1,  2, 3,  4,  5,
                          4,  5,  6,  7,  8,  9,
                          8,  9, 10, 11, 12, 13,
                          12, 13, 14, 15, 16, 17,
                          16, 17, 18, 19, 20, 21,
                          20, 21, 22, 23, 24, 25,
                          24, 25, 26, 27, 28, 29,
                          28, 29, 30, 31, 32,  1 };

int word_permutationp_Table[] = { 16,  7, 20, 21,
                                  29, 12, 28, 17,
                                  1, 15, 23, 26,
                                  5, 18, 31, 10,
                                  2,  8, 24, 14,
                                  32, 27,  3,  9,
                                  19, 13, 30,  6,
                                  22, 11,  4, 25 };

int s_boxes_table[8*64] = {

        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
        0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
        4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 ,

        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
        3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
        0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 ,

        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
        1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 ,

        7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
        3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 ,

        2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
        4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 ,

        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
        9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
        4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 ,

        4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
        1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
        6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 ,

        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
        1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
        7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
        2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11

};

int initial_key_permutaion[] = {57, 49,  41, 33,  25,  17,  9,
                                1, 58,  50, 42,  34,  26, 18,
                                10,  2,  59, 51,  43,  35, 27,
                                19, 11,   3, 60,  52,  44, 36,
                                63, 55,  47, 39,  31,  23, 15,
                                7, 62,  54, 46,  38,  30, 22,
                                14,  6,  61, 53,  45,  37, 29,
                                21, 13,   5, 28,  20,  12,  4};

int initial_message_permutation[] =	   {58, 50, 42, 34, 26, 18, 10, 2,
                                           60, 52, 44, 36, 28, 20, 12, 4,
                                           62, 54, 46, 38, 30, 22, 14, 6,
                                           64, 56, 48, 40, 32, 24, 16, 8,
                                           57, 49, 41, 33, 25, 17,  9, 1,
                                           59, 51, 43, 35, 27, 19, 11, 3,
                                           61, 53, 45, 37, 29, 21, 13, 5,
                                           63, 55, 47, 39, 31, 23, 15, 7};


int final_message_permutation[] =  {40,  8, 48, 16, 56, 24, 64, 32,
                                    39,  7, 47, 15, 55, 23, 63, 31,
                                    38,  6, 46, 14, 54, 22, 62, 30,
                                    37,  5, 45, 13, 53, 21, 61, 29,
                                    36,  4, 44, 12, 52, 20, 60, 28,
                                    35,  3, 43, 11, 51, 19, 59, 27,
                                    34,  2, 42, 10, 50, 18, 58, 26,
                                    33,  1, 41,  9, 49, 17, 57, 25};


int sub_key_permutation[] =    {14, 17, 11, 24,  1,  5,
                                3, 28, 15,  6, 21, 10,
                                23, 19, 12,  4, 26,  8,
                                16,  7, 27, 20, 13,  2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32};

int key_shift_sizes[] = {0, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
int key_shift_sizes_DEC[] = {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1};

ull generic_prem(ull inp, const int  permutation_table[] , int inp_len , int out_len){
    ull out = 0;
    for(int i=0; i<out_len; i++){
        out |= ((inp >> (inp_len-permutation_table[i]))&1) << (out_len-i-1);
    }
    return out;
}

ull leftRotate(ull num, int dist){
    return ((num<<dist)|(num>>(28-dist)))&268435455;
}

ull rightRotate(ull num, int dist){
    return ((num>>dist)|(num<<(28-dist)))&268435455;
}

ull left_circular_shift(ull inp, int round_num){
    ull out =0;
    ull c = (inp&72057593769492480)>>28;
    ull d=inp;
    d&=268435455;
    out |= leftRotate(c,key_shift_sizes[round_num])<<28 | leftRotate(d,key_shift_sizes[round_num]);
    return out;
}

ull right_circular_shift(ull inp, int round_num){
    ull out =0;
    ull c = (inp&72057593769492480)>>28;
    ull d=inp;
    d&=268435455;
    out |= rightRotate(c,key_shift_sizes_DEC[round_num])<<28 | rightRotate(d,key_shift_sizes_DEC[round_num]);
    return out;
}

//INPUT -> 48 bit
//OUTPUT -> 32 bit
ull s_boxes(ull in) {
    ull out = 0;
    for (int i = 0; i <= 7; ++i) {
        ull offset = i * 64; //initial position of the sub table
        ull idx = in >> (7 - i) * 6 & 0x3F; //getting the index
        idx = idx >> 1 & 15 | (idx & 1) << 4 | idx & 32; //converting the 2d access into 1d access - reordering bits
        out |= (ull)s_boxes_table[offset + idx] << (7 - i) * 4; //concatenating the result
    }
    return out;
}

//INPUT -> 32 bit
//OUTPUT -> 32 bit
ull function(ull in, ull sub_key) {
    ull expansion_output = generic_prem(in, expansion_table,32,48);
    ull sbox_output = s_boxes(expansion_output ^ sub_key);
    return generic_prem(sbox_output,word_permutationp_Table,32,32);
}

//INPUT -> sub_key -> 48 bit
//OUTPUT -> in -> 64 bit
ull des_round(ull in,ull sub_key) {
    ull in_right_word = in & 0xFFFFFFFF; //the least significant 32 bits
    ull in_left_word = in >> 32 & 0xFFFFFFFF; //the most significant 32 bits
    ull out_right_word = in_left_word ^ function(in_right_word, sub_key);
    return (ull)out_right_word | (in_right_word << 32); //the INPUT to the next round
}

ull read_file_hex(FILE* file) {
    ull block;
    block = fgetc(file);
    if (block == -1) return block;
    if (block >= 48 && block <= 57) {
        block = block - 48;
    }
    else if (block >= 65 && block <= 70) {
        block = block - 55;
    }
    else if (block >= 97 && block <= 102) {
        block = block - 87;
    }
    for (int i = 0; i < 15; ++i) {
        int c = fgetc(file);
        if (c >= 48 && c <= 57) {
            c = c - 48;
        }
        else if (c >= 65 && c <= 70) {
            c = c - 55;
        }
        else if (c >= 97 && c <= 102) {
            c = c - 87;
        }
        block = (block << 4) | c;
    }
    return block;
}

ull read_file_ascii(FILE* file) {
    ull block = 0;
    unsigned char buffer[8];
    fread(buffer,sizeof(buffer),1,file);
    if (feof(file)) return -1;
    for (int i = 0; i < 8; ++i) {
        block = (block << 8) | buffer[i];
    }
    return block;
}

void decrypt(ull key) {
    ull plain_text;
    while (1) {
        ull curr_block = read_file_ascii(INPUT);
        if (curr_block == -1) break;
        ull plain_text_permutation = generic_prem(curr_block, initial_message_permutation, 64, 64);
        ull key_permutation = generic_prem(key, initial_key_permutaion, 64, 56);
        for (int i = 1; i <= 16; ++i) {
            key_permutation = right_circular_shift(key_permutation, i-1);
            ull round_key = generic_prem(key_permutation, sub_key_permutation, 56, 48);
            plain_text_permutation = des_round(plain_text_permutation, round_key);
        }
        plain_text_permutation = (plain_text_permutation << 32) | (plain_text_permutation >> 32);
        plain_text = generic_prem(plain_text_permutation, final_message_permutation, 64, 64);
        for (int i = 0; i < 8; ++i) {
            int c = plain_text >> (7 - i) * 8 & 0xFF;
            fprintf(OUTPUT, "%c", c);
        }
    }
}
void encrypt(ull key){
    while (1) {
        ull curr_block = read_file_ascii(INPUT);
        if (curr_block == -1) break;
        ull plain_text_permutation = generic_prem(curr_block, initial_message_permutation, 64, 64);
        ull key_permutation = generic_prem(key, initial_key_permutaion, 64, 56);
        for (int i = 1; i <= 16; ++i) {
            key_permutation = left_circular_shift(key_permutation, i);
            ull round_key = generic_prem(key_permutation, sub_key_permutation, 56, 48);
            plain_text_permutation = des_round(plain_text_permutation, round_key);
        }
        plain_text_permutation = (plain_text_permutation << 32) | (plain_text_permutation >> 32);
        ull final_permutation = generic_prem(plain_text_permutation, final_message_permutation, 64, 64);
        fprintf(HEX_OUTPUT, "%016llx", final_permutation);
        for (int i = 0; i < 8; ++i) {
            ull c = final_permutation >> (7 - i) * 8 & 0xFF;
            fprintf(OUTPUT, "%c", c);
        }
    }
}
//-e -k key.txt -i input.txt -o OUTPUT.txt
//-d -k key.txt -i input.txt -o OUTPUT.txt
int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("Invalid number of arguments. Please use\n-e -k key.txt -i plain.txt -o encrypted.txt for encryption\n"
               "-d -k key.txt -i encrypted.txt -o decrypt.txt for decryption");
        return -1;
    }
    int mode;
    if (strcmp(argv[1], "-e") == 0) {
        mode = 1;
    }
    else if (strcmp(argv[1], "-d") == 0) {
        mode = 2;
    }
    else {
        printf("Invalid mode. Please enter -e for encryption or -d for decryption");
        return 0;
    }
    KEY = fopen(argv[4], "r");
    int correct_args = 0;
    char* output_file_name;
    for (int i = 2; i < 8; ++i) {
        if (strcmp(argv[i], "-k") == 0) {
            KEY = fopen(argv[++i], "r");
            correct_args++;
        }
        else if (strcmp(argv[i], "-i") == 0) {
            INPUT = fopen(argv[++i], "rb");
            correct_args++;
        }
        else if (strcmp(argv[i], "-o") == 0) {
            OUTPUT = fopen(argv[++i], "wb");
            output_file_name = argv[i];
            correct_args++;
        }
    }
    if (correct_args != 3) {
        printf("Invalid arguments. Please enter -k key.txt -i INPUT.txt -o OUTPUT.txt in any order");
        return 0;
    }
    if (mode == 1) {
        ull key_block = read_file_hex(KEY);
        char* hex_output_file_name = (char*)malloc(strlen(output_file_name) + 5);
        strcpy(hex_output_file_name, output_file_name);
        strcat(hex_output_file_name, ".hex");
        HEX_OUTPUT = fopen(hex_output_file_name, "w");
        encrypt(key_block);
    }
    else {
        ull key_block = read_file_hex(KEY);
        decrypt(key_block);
    }
}
