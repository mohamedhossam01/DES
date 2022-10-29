Compilation
==========================
 
1. Compile using: g++ .\des_g20.c

Usage
=====
1.To encrypt a file using a key, use the following command:
> .\des.exe -e -k .\key.txt -i .\plain.txt -o encrypted.txt
<br>
 
 
This will encrypt the plain.txt file and save the encrypted text in encrypted.txt in plaintext format.
<br>
It will also save the encrypted text in encrypted.txt.hex in hex format.

2.To decrypt a file using a key, use the following command
> .\des.exe -d -k .\key.txt -i .\encrypted.txt -o .\decrypt.txt


This will decrypt the encrypted.txt file and save the decrypted text in decrypt.txt in plaintext format.

### Recap of file formats
1. Key.txt => Hex
2. Plain.txt => ASCII
3. Encrypted.txt => ASCII
4. Encrypted.txt.hex => Hex
5. Decrypt.txt => ASCII


More Features
====
This implementation of DES supports the following features:
1. Encrypt/Decrypt any file(image, text, video, etc) using a key in hex format.
2. Any order of input file, output file, key file in command line arguments is supported.
<br>Example:
> .\des.exe -e -k .\key.txt -i .\plain.txt -o encrypted.txt

> .\des.exe -e -i .\plain.txt -k .\key.txt -o encrypted.txt

> .\des.exe -e -o encrypted.txt -i .\plain.txt -e -k .\key.txt
