#include <stdio.h>
#include <string.h>

char divisor[] = "10001000000100001";
#define CRC_SIZE 16

void crc_cal(char *input, char *crc) {
    int input_len = strlen(input);
    char dividend[input_len + 1];
    strcpy(dividend, input);

    for (int j = 0; j <= input_len - CRC_SIZE; j++) {
        if (dividend[j] == '1') {
            for (int i = 0; i < CRC_SIZE + 1; i++) {
                dividend[j + i] = (dividend[j + i] == divisor[i]) ? '0' : '1';
            }
        }
    }
    
    strncpy(crc, dividend + input_len - CRC_SIZE, CRC_SIZE);
    crc[CRC_SIZE] = '\0';
    printf("CRC: %s\n", crc);
}

int main() {
    char data[100], frame[120];
    char src_crc[CRC_SIZE + 1], dest_crc[CRC_SIZE + 1];
    char zero_crc[CRC_SIZE + 1] = "0000000000000000";

    printf("Enter the data to be sent: ");
    scanf("%s", data);

    // Append CRC_SIZE zero bits
    char concatdata[117];
    strcpy(concatdata, data);
    strcat(concatdata, zero_crc);

    crc_cal(concatdata, src_crc);

    printf("Transmitted Frame: %s%s\n", data, src_crc);

    printf("\nEnter the received frame: ");
    scanf("%s", frame);

    crc_cal(frame, dest_crc);
    printf("%s\n", (strcmp(dest_crc, zero_crc) == 0) ? "\nReceived frame is error-free" : "\nReceived frame has an error");

    return 0;
}

