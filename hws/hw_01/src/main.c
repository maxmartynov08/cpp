#include "bmp.h"

static void free_memory(BMP* bmp) {
    for (int i = 0; i < bmp->info_header.biHeight; i++) 
        free(bmp->image[i]);
    free(bmp->image);
    free(bmp);
}

int main(int argc, char** argv) {
    if (argc < 8) {
        return 1;
    }
    char* action = argv[1];
    if (strcmp(action, "crop-rotate") != 0) {
        return 1;
    }
    char* input_file_name = argv[2];
    char* output_file_name = argv[3];
    
    BMP* bmp = load_bmp(input_file_name);

    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);

    if (x < 0 || x + w > bmp->info_header.biWidth || y < 0 || y + h > bmp->info_header.biHeight){
        return 1;
    }
 
    BMP* cropped_bmp = crop(bmp, x, y, w, h);

    BMP* rotated_bmp = rotate(cropped_bmp);

    save_bmp(rotated_bmp, output_file_name);
    
    free_memory(bmp);
    free_memory(cropped_bmp);
    free_memory(rotated_bmp);

    return 0;
}