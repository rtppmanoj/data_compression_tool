#include <stdio.h>
#include <stdlib.h>

// Function to compress a file using RLE
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening file(s).\n");
        exit(1);
    }

    char ch, prev;
    int count = 1;

    prev = fgetc(in);
    if (prev == EOF) {
        printf("Input file is empty!\n");
        fclose(in);
        fclose(out);
        return;
    }

    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(out, "%d%c", count, prev);
            prev = ch;
            count = 1;
        }
    }
    fprintf(out, "%d%c", count, prev);

    fclose(in);
    fclose(out);
    printf("Compression completed. Output written to %s\n", outputFile);
}

// Function to decompress a file using RLE
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening file(s).\n");
        exit(1);
    }

    int count;
    char ch;

    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression completed. Output written to %s\n", outputFile);
}

int main() {
    int choice;
    char inputFile[50], outputFile[50];

    while (1) {
        printf("\n===== RUN-LENGTH ENCODING TOOL =====\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output (compressed) file name: ");
                scanf("%s", outputFile);
                compressFile(inputFile, outputFile);
                break;
            case 2:
                printf("Enter compressed file name: ");
                scanf("%s", inputFile);
                printf("Enter output (decompressed) file name: ");
                scanf("%s", outputFile);
                decompressFile(inputFile, outputFile);
                break;
            case 3:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
