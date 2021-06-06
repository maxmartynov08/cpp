#include "bmp.h"
#include <assert.h>
#include <stdio.h>

const int BYTES_PER_PIXEL = 3;

int with_padding(const int current_size) {
    return current_size + ((4 - (current_size % 4)) % 4);
}

BMP* load_bmp(const char* input_file) {
    FILE *file = fopen(input_file, "rb");

    BMP* bmp = malloc(sizeof(BMP));
    assert(bmp);

    fread(&(bmp->file_header), sizeof(BITMAPFILEHEADER), 1, file);
    fread(&(bmp->info_header), sizeof(BITMAPINFOHEADER), 1, file);
    
    fseek(file, bmp->file_header.bfOffBits, SEEK_SET);

    int rows = bmp->info_header.biHeight;
    
    bmp->image = malloc(sizeof(char*) * rows);
    assert(bmp->image);

    int size_of_row = with_padding(bmp->info_header.biWidth * BYTES_PER_PIXEL);

    for (int row = 0; row < rows; row++) {
        bmp->image[row] = malloc(sizeof(char) * size_of_row);
        assert(bmp->image[row]);
        fread(bmp->image[row], size_of_row, 1, file);
    }
    fclose(file);

    return bmp;
}

BMP* crop(const BMP* bmp, const int x, const int y, const int w, const int h) {
    BMP* cropped_bmp = malloc(sizeof(BMP));
    assert(cropped_bmp);

    cropped_bmp->file_header = bmp->file_header;
    cropped_bmp->info_header = bmp->info_header;

    cropped_bmp->info_header.biHeight = h;
    cropped_bmp->info_header.biWidth = w;

    int size_of_row = w * BYTES_PER_PIXEL;
    int size_of_row_with_padding = with_padding(size_of_row);

    cropped_bmp->info_header.biSizeImage = h * size_of_row_with_padding;
    cropped_bmp->file_header.bfSize = sizeof(BMP) + cropped_bmp->info_header.biSizeImage;

    cropped_bmp->image = malloc(sizeof(char*) * h);
    assert(cropped_bmp->image);
    
    for (int row = 0; row < h; row++) {
        cropped_bmp->image[row] = malloc(sizeof(char) * size_of_row_with_padding);
        assert(cropped_bmp->image[row]);

        int row_in_bmp = bmp->info_header.biHeight - (y + h) + row;
        int col_in_bmp = x * BYTES_PER_PIXEL;
        memcpy(cropped_bmp->image[row], bmp->image[row_in_bmp] + col_in_bmp, size_of_row);

        for (int extra_col = size_of_row; extra_col < size_of_row_with_padding; extra_col++)
            cropped_bmp->image[row][extra_col] = 0x00;
    }
    return cropped_bmp;
}

BMP* rotate(const BMP* bmp) {
    BMP* rotated_bmp = malloc(sizeof(BMP));
    assert(rotated_bmp);

    rotated_bmp->file_header = bmp->file_header;
    rotated_bmp->info_header = bmp->info_header;

    rotated_bmp->info_header.biHeight = bmp->info_header.biWidth;
    rotated_bmp->info_header.biWidth = bmp->info_header.biHeight;

    int rows = rotated_bmp->info_header.biHeight;
    int size_of_row = rotated_bmp->info_header.biWidth * BYTES_PER_PIXEL;
    int size_of_row_with_padding = with_padding(rotated_bmp->info_header.biWidth * BYTES_PER_PIXEL);

    rotated_bmp->info_header.biSizeImage = rows * size_of_row_with_padding;
    rotated_bmp->file_header.bfSize = sizeof(BMP) + rotated_bmp->info_header.biSizeImage;

    rotated_bmp->image = malloc(sizeof(char*) * rows);
    assert(rotated_bmp->image);

    for (int row = 0; row < rows; row++) {
        rotated_bmp->image[row] = malloc(sizeof(char) * size_of_row_with_padding);
        assert(rotated_bmp->image[row]);
        
        for (int pixel = 0; pixel < bmp->info_header.biHeight; pixel++) {
            char* pos_in_rotated = rotated_bmp->image[row] + pixel * BYTES_PER_PIXEL;
            char* pos_in_bmp = bmp->image[pixel] + (rows - row - 1) * BYTES_PER_PIXEL;
            memcpy(pos_in_rotated, pos_in_bmp, BYTES_PER_PIXEL);
        }        
        for (int extra_col = size_of_row; extra_col < size_of_row_with_padding; extra_col++)
            rotated_bmp->image[row][extra_col] = 0x00;
    }
    return rotated_bmp;
}

void save_bmp(const BMP* bmp, const char* output_file) {
    FILE *file = fopen(output_file, "wb");

    fwrite(&(bmp ->file_header), sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(&(bmp ->info_header), sizeof(BITMAPINFOHEADER), 1, file);

    int rows = bmp->info_header.biHeight;
    int size_of_row = with_padding(bmp->info_header.biWidth * BYTES_PER_PIXEL);

    for (int row = 0; row < rows; row++) {
        fwrite(bmp->image[row], size_of_row, 1, file);
    }
    fclose(file);
}