#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {

    FILE* rf = NULL;
    FILE* wf = NULL;
    rf = fopen("../../FOREMAN_CIF30.yuv", "rb");
    wf = fopen("1_FOREMAN_CIF30_Y.yuv", "wb");


    int frame_size = 352 * 288;
    unsigned char* frame = (unsigned char*)malloc(frame_size);

    for (int i = 0; i < 300; i++) {
        memset(frame, 0, frame_size);
        fread(frame, sizeof(unsigned char), frame_size, rf);
        fwrite(frame, sizeof(unsigned char), frame_size, wf);
        fread(frame, sizeof(unsigned char), frame_size / 2, rf);
        memset(frame, 128, frame_size);
        fwrite(frame, sizeof(unsigned char), frame_size / 2, wf);
    }

    fclose(rf);
    fclose(wf);
    free(frame);
    return 0;
}