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

    FILE* wf_p1 = NULL;
    FILE* wf_e1 = NULL;
    FILE* wf_r1 = NULL;
    rf = fopen("../../FOREMAN_CIF30.yuv", "rb");
    wf_p = fopen("4_FOREMAN_CIF30_PRED_HOR.yuv", "wb");
    wf_e = fopen("4_FOREMAN_CIF30_ERROR_HOR.yuv", "wb");
    wf_r = fopen("4_FOREMAN_CIF30_RECON_HOR.yuv", "wb");

    wf_p1 = fopen("4_FOREMAN_CIF30_PRED_VER.yuv", "wb");
    wf_e1 = fopen("4_FOREMAN_CIF30_ERROR_VER.yuv", "wb");
    wf_r1 = fopen("4_FOREMAN_CIF30_RECON_VER.yuv", "wb");

    int height = 288 * 3 / 2, width = 352;
    int frame_size = 352 * 288 * 3 / 2;
    unsigned char* frame = (unsigned char*)malloc(frame_size);
    unsigned char* frame_p = (unsigned char*)calloc(frame_size, sizeof(unsigned char));
    unsigned char* frame_e = (unsigned char*)calloc(frame_size, sizeof(unsigned char));
    unsigned char* frame_r = (unsigned char*)calloc(frame_size, sizeof(unsigned char));

    for (int f = 0; f < 300; f++) {
        memset(frame, 0, frame_size);
        fread(frame, sizeof(unsigned char), frame_size, rf);

        //Horizontal
        for (int p = 0; p < height / 16; p++) {
            for (int q = 0; q < width / 16; q++) {
                for (int j = p * 16; j < (p + 1) * 16; j++) {
                    for (int i = q * 16; i < (q + 1) * 16; i++) {
                        if (q == 0) {
                            frame_p[j * width + i] = frame[j * width + i] - 128;
                            frame_e[j * width + i] = frame_p[j * width + i] / 10;
                            frame_r[j * width + i] = frame_e[j * width + i] * 10 + 128;
                        }
                        else {
                            frame_p[j * width + i] = frame[j * width + i] - frame_r[j * width + (i - 1)];
                            frame_e[j * width + i] = frame_p[j * width + i] / 10;
                            frame_r[j * width + i] = frame_e[j * width + i] * 10 + frame_r[j * width + (i - 1)];
                        }
                    }
                }
            }
        }
        fwrite(frame_p, sizeof(unsigned char), frame_size, wf_p);
        fwrite(frame_e, sizeof(unsigned char), frame_size, wf_e);
        fwrite(frame_r, sizeof(unsigned char), frame_size, wf_r);

        //Vertical
        for (int p = 0; p < height / 16; p++) {
            for (int q = 0; q < width / 16; q++) {
                for (int j = p * 16; j < (p + 1) * 16; j++) {
                    for (int i = q * 16; i < (q + 1) * 16; i++) {
                        if (p == 0) {
                            frame_p[j * width + i] = frame[j * width + i] - 128;
                            frame_e[j * width + i] = frame_p[j * width + i] / 10;
                            frame_r[j * width + i] = frame_e[j * width + i] * 10 + 128;
                        }
                        else {
                            frame_p[j * width + i] = frame[j * width + i] - frame_r[(j - 1) * width + i];
                            frame_e[j * width + i] = frame_p[j * width + i] / 10;
                            frame_r[j * width + i] = frame_e[j * width + i] * 10 + frame_r[(j - 1) * width + i];
                        }
                    }
                }
            }
        }
        fwrite(frame_p, sizeof(unsigned char), frame_size, wf_p1);
        fwrite(frame_e, sizeof(unsigned char), frame_size, wf_e1);
        fwrite(frame_r, sizeof(unsigned char), frame_size, wf_r1);
    }

    fclose(rf);
    fclose(wf_p);   fclose(wf_p1);
    fclose(wf_e);   fclose(wf_e1);
    fclose(wf_r);   fclose(wf_r1);

    free(frame_p);  free(frame_e);  free(frame_r);
    return 0;
}