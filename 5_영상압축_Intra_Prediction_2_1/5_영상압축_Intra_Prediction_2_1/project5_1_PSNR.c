#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

int main() {

    FILE* enc = NULL;
    FILE* dec = NULL;

    enc = fopen("5_1_FOREMAN_CIF30_RECON_DC_ENC.yuv", "rb");;
    dec = fopen("5_1_FOREMAN_CIF30_RECON_DC_DEC.yuv", "rb");

    int height = 288 * 3 / 2, width = 352;
    int frame_size = 352 * 288 * 3 / 2;

    unsigned char* frame_enc = (unsigned char*)malloc(frame_size);
    unsigned char* frame_dec = (unsigned char*)malloc(frame_size);

    double mse = 0, psnr;

    for (int f = 0; f < 300; f++) {
        memset(frame_enc, 0, frame_size);
        memset(frame_dec, 0, frame_size);
        fread(frame_enc, sizeof(unsigned char), frame_size, enc);
        fread(frame_dec, sizeof(unsigned char), frame_size, dec);

        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                mse += (double)((frame_enc[j * width + i] - frame_dec[j * width + i]) * (frame_enc[j * width + i] - frame_dec[j * width + i]));
            }
        }
        mse /= (width * height);
        psnr = mse != 0.0 ? 10.0 * log10(255 * 255 / mse) : 99.99;
        printf("frame%d\nMSE = %.2lf\nPSNR = %.2lf dB\n", f, mse, psnr);
    }

    fclose(enc);
    fclose(dec);

    return 0;
}