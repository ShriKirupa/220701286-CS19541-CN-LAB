#include <stdio.h>
#include <math.h>

#define TOTAL_BITS 12

// Function to detect and correct errors
void receiver(int data[]) {
    int errorPosition = 0;

    for (int i = 0; i < 4; i++) {
        int parityIndex = (1 << i) - 1;
        int parity = 0;

        for (int j = parityIndex; j < TOTAL_BITS; j++) {
            if (((j + 1) & (parityIndex + 1)) != 0) {
                parity ^= data[j];
            }
        }
        if (parity != 0) {
            errorPosition += parityIndex + 1;
        }
    }

    if (errorPosition == 0) {
        printf("No errors detected.\n");
    } else {
        printf("Error detected at position: %d\n", errorPosition);
        data[errorPosition - 1] ^= 1; // Correct the error
        printf("Corrected data: ");
        for (int i = 0; i < TOTAL_BITS; i++) {
            printf("%d", data[i]);
        }
        printf("\n");
    }
}

int main() {
    int receivedData[TOTAL_BITS];
    FILE *file = fopen("encoded_data.txt", "r");

    if (file == NULL) {
        printf("Error opening file 'encoded_data.txt'. Ensure the file exists.\n");
        return 1;
    }

    printf("Enter the received data (12 bits with parity): ");
    for (int i = 0; i < TOTAL_BITS; i++) {
        fscanf(file, "%1d", &receivedData[i]); // Read each bit from the file
    }
    fclose(file);

    receiver(receivedData);
    return 0;
}
