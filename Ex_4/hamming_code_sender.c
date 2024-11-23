#include <stdio.h>
#include <math.h>

#define TOTAL_BITS 12
#define DATA_BITS 8

// Function to calculate parity bits
void calculateParityBits(int data[]) {
    for (int i = 0; i < 4; i++) {
        int parityIndex = (1 << i) - 1;
        int parity = 0;

        for (int j = parityIndex; j < TOTAL_BITS; j++) {
            if (((j + 1) & (parityIndex + 1)) != 0) {
                parity ^= data[j];
            }
        }
        data[parityIndex] = parity;
    }
}

// Function to encode data
void sender(int data[]) {
    int encodedData[TOTAL_BITS] = {0};
    int j = 0;

    for (int i = 0; i < TOTAL_BITS; i++) {
        if ((i + 1) == 1 || (i + 1) == 2 || (i + 1) == 4 || (i + 1) == 8) {
            encodedData[i] = 0; // Reserve for parity bits
        } else {
            encodedData[i] = data[j++];
        }
    }

    calculateParityBits(encodedData);

    FILE *file = fopen("encoded_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save encoded data.\n");
        return;
    }

    for (int i = 0; i < TOTAL_BITS; i++) {
        fprintf(file, "%d", encodedData[i]);
    }

    fclose(file);
    printf("Encoded data saved to 'encoded_data.txt'.\n");
}

int main() {
    int data[DATA_BITS];
    printf("Enter 8 data bits (0 or 1): ");
    for (int i = 0; i < DATA_BITS; i++) {
        scanf("%d", &data[i]);
    }

    sender(data);
    return 0;
}
