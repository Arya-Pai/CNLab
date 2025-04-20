#include<stdio.h>

int h[12];

void genhamcode() {
    int i, temp;
    // Calculate parity bits
    h[1] = (h[3] + h[5] + h[7] + h[9] + h[11]) % 2;
    h[2] = (h[3] + h[6] + h[7] + h[10] + h[11]) % 2;
    h[4] = (h[5] + h[6] + h[7]) % 2;
    h[8] = (h[9] + h[10] + h[11]) % 2;

    // Display transmitted codeword
    printf("\nTransmitted codeword: ");
    for (i = 1; i < 12; i++) printf("%d ", h[i]);
}

void makeerror() {
    int pos;
    printf("\nEnter position to make error: ");
    scanf("%d", &pos);
    h[pos] = (h[pos] == 1) ? 0 : 1; // Flip the bit
    printf("\nError introduced: ");
    for (int i = 1; i < 12; i++) printf("%d ", h[i]);
}

void correcterror() {
    int r1 = (h[1] + h[3] + h[5] + h[7] + h[9] + h[11]) % 2;
    int r2 = (h[2] + h[3] + h[6] + h[7] + h[10] + h[11]) % 2;
    int r4 = (h[4] + h[5] + h[6] + h[7]) % 2;
    int r8 = (h[8] + h[9] + h[10] + h[11]) % 2;
    int errpos = r8 * 8 + r4 * 4 + r2 * 2 + r1;

    if (errpos) {
        printf("\nError at position %d\n", errpos);
        h[errpos] = (h[errpos] == 1) ? 0 : 1; // Flip the erroneous bit
    } else {
        printf("\nNo error detected.\n");
    }

    printf("\nCorrected codeword: ");
    for (int i = 1; i < 12; i++) printf("%d ", h[i]);
}

int main() {
    printf("\nEnter the message bits (positions 3, 5, 6, 7, 9, 10, 11):\n");
    for (int i = 1; i < 12; i++) {
        if (i == 3 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11)
            scanf("%d", &h[i]);
    }

    genhamcode();

    int ch;
    printf("\nDo you want to introduce an error? (1 for Yes, 0 for No): ");
    scanf("%d", &ch);
    if (ch) {
        makeerror();
        correcterror();
    } else {
        printf("\nNo error.\n");
    }

    return 0;
}

