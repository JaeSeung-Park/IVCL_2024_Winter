#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {

    FILE* rf = NULL;
    FILE* wf_p = NULL;
    FILE* wf_e = NULL;
    FILE* wf_r = NULL;
    rf = fopen("../../FOREMAN_CIF30.yuv", "rb");
    wf_p = fopen("2_FOREMAN_CIF30_PRED.yuv", "wb");
    wf_e = fopen("2_FOREMAN_CIF30_ERROR.yuv", "wb");
    wf_r = fopen("2_FOREMAN_CIF30_RECON.yuv", "wb");

    int height = 288 * 3 / 2, width = 352;
    int frame_size = 352 * 288 * 3 / 2;
    unsigned char* frame = (unsigned char*)malloc(frame_size);
    unsigned char* frame_p = (unsigned char*)calloc(frame_size, sizeof(unsigned char));
    unsigned char* frame_e = (unsigned char*)calloc(frame_size, sizeof(unsigned char));
    unsigned char* frame_r = (unsigned char*)calloc(frame_size, sizeof(unsigned char));


    for (int q = 0; q < 300; q++) {
        memset(frame, 0, frame_size);
        fread(frame, sizeof(unsigned char), frame_size, rf);
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                frame_p[j * width + i] = frame[j * width + i] - 128;
                frame_e[j * width + i] = frame_p[j * width + i] / 10;
                frame_r[j * width + i] = frame_e[j * width + i] * 10 + 128;
            }
        }
        fwrite(frame_p, sizeof(unsigned char), frame_size, wf_p);
        fwrite(frame_e, sizeof(unsigned char), frame_size, wf_e);
        fwrite(frame_r, sizeof(unsigned char), frame_size, wf_r);
    }

    fclose(rf);
    fclose(wf_p);
    fclose(wf_e);
    fclose(wf_r);
    free(frame); free(frame_p); free(frame_e); free(frame_r);
    return 0;
}