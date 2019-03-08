// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
// Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Size = 128;//Sizerow=Sizecol=Size

// Check for proper syntax
    if (argc < 13) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

// Check if image is grayscale or color
    if (argc < 14) {
        BytesPerPixel = 1; // default is grey image
    } else {
        BytesPerPixel = atoi(argv[13]);
// Check if size is specified
        if (argc >= 15) {
            Size = atoi(argv[14]);
        }
    }
// Allocate image data array

    unsigned char Imagedata[Size][Size][BytesPerPixel];
    float Imagedatabig[Size + 4][Size + 4][BytesPerPixel];
    float Imagedata1[Size ][Size ][BytesPerPixel];
    float Imagedata2[Size ][Size ][BytesPerPixel];
    float Imagedata3[Size ][Size ][BytesPerPixel];
    float Imagedata4[Size ][Size ][BytesPerPixel];
    float Imagedata5[Size ][Size ][BytesPerPixel];
    float Imagedata6[Size ][Size ][BytesPerPixel];
    float Imagedata7[Size ][Size ][BytesPerPixel];
    float Imagedata8[Size ][Size ][BytesPerPixel];
    float Imagedata9[Size ][Size ][BytesPerPixel];
//int E[5] = {-1, -2, 0, 2, 1};
//int S[5] = {-1, 0, 2, 0, -1};
//int W[5] = {-1, 2, 0, -2, 1};
    int ES[5][5] = {{1,0,-2,0,1},{2,0,-4,0,2},{0,0,0,0,0},{-2,0,4,0,-2},{-1,0,2,0,-1}};
    int SE[5][5] = {{1,2,0,-2,-1},{0,0,0,0,0},{-2,-4,0,4,2},{0,0,0,0,0},{1,2,0,-2,1}};
    int EW[5][5] = {{1,-2,0,2,-1},{2,-4,0,4,-2},{0,0,0,0,0},{-2,4,0,-4,2},{-1,2,0,-2,1}};
    int WE[5][5] = {{1,2,0,-2,-1},{-2,-4,0,4,2},{0,0,0,0,0},{2,4,0,-4,-2},{-1,-2,0,2,1}};
    int SW[5][5] = {{1,-2,0,2,-1},{0,0,0,0,0},{-2,4,0,-4,2},{0,0,0,0,0},{1,-2,0,2,-1}};
    int WS[5][5] = {{1,0,-2,0,1},{-2,0,4,0,-2},{0,0,0,0,0},{2,0,-4,0,2},{-1,0,2,0,-1}};
    int EE[5][5] = {{1,2,0,-2,-1},{2,4,0,-4,-2},{0,0,0,0,0},{-2,-4,0,4,2},{-1,-2,0,2,1}};
    int SS[5][5] = {{1,0,-2,0,1},{0,0,0,0,0},{-2,0,4,0,-2},{0,0,0,0,0},{1,0,-2,0,1}};
    int WW[5][5] = {{1,-2,0,2,-1},{-2,4,0,-4,2},{0,0,0,0,0},{2,-4,0,4,-2},{-1,2,0,-2,1}};
    float featurevector[12][9];

    for (int count = 1; count <=12; count++) {
// Read image (filename specified by first argument) into image data matrix
        if (!(file = fopen(argv[count], "rb"))) {
            cout << "Cannot open file: " << argv[count] << endl;
            exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Size * Size * BytesPerPixel, file);
        fclose(file);

///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
/*int sum = 0;
int mean=0;
for (int i = 0; i < Size; i++) {
    for (int j = 0; j < Size; j++) {
        sum =sum+ Imagedata[i][j][0];
    }
}
mean = sum / (Size * Size);
for (int i = 0; i < Size; i++) {
    for (int j = 0; j < Size; j++) {
        Imagedata[i][j][0] = Imagedata[i][j][0] - mean;
    }
}*/
//extension
        for (int i = 2; i < Size + 2; i++) {
            for (int j = 2; j < Size + 2; j++) {
                Imagedatabig[i][j][0] = (float)Imagedata[i - 2][j - 2][0];
            }
        }
        for (int j = 0; j < Size+2; j++) {
            Imagedatabig[0][j][0] = (float)Imagedata[0][j][0];
            Imagedatabig[1][j][0] = (float)Imagedata[0][j][0];
            Imagedatabig[Size - 2][j][0] = (float)Imagedata[Size][j][0];
            Imagedatabig[Size - 1][j][0] = (float)Imagedata[Size][j][0];
        }
        for (int i = 0; i < Size + 2; i++) {
            Imagedatabig[i][0][0] = (float)Imagedata[i][0][0];
            Imagedatabig[i][1][0] = (float)Imagedata[i][1][0];
            Imagedatabig[i][Size + 1][0] = (float)Imagedata[i][Size][0];
            Imagedatabig[i][Size + 2][0] = (float)Imagedata[i][Size][0];
        }

//ES
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata1[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * ES[0][0] + Imagedatabig[i - 2][j - 1][0] * ES[0][1] +
                        Imagedatabig[i - 2][j][0] * ES[0][2] + Imagedatabig[i - 2][j + 1][0] * ES[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * ES[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * ES[1][0] + Imagedatabig[i - 1][j - 1][0] * ES[1][1] +
                        Imagedatabig[i - 1][j][0] * ES[1][2] + Imagedatabig[i - 1][j + 1][0] * ES[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * ES[1][4] +
                        Imagedatabig[i][j - 2][0] * ES[2][0] + Imagedatabig[i][j - 1][0] * ES[2][1] +
                        Imagedatabig[i][j][0] * ES[2][2] + Imagedatabig[i][j + 1][0] * ES[2][3] +
                        Imagedatabig[i][j + 2][0] * ES[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * ES[3][0] + Imagedatabig[i + 1][j - 1][0] * ES[3][1] +
                        Imagedatabig[i + 1][j][0] * ES[3][2] + Imagedatabig[i + 1][j + 1][0] * ES[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * ES[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * ES[4][0] + Imagedatabig[i + 2][j - 1][0] * ES[4][1] +
                        Imagedatabig[i + 2][j][0] * ES[4][2] + Imagedatabig[i + 2][j + 1][0] * ES[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * ES[4][4];
            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata1[i][j][0]=Imagedata1[i][j][0]/24.0;
            }
        }
        float enyes = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyes += Imagedata1[i][j][0] * Imagedata1[i][j][0];
            }
        }
        featurevector[count-1][0] = enyes / (Size * Size);
//SE
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata2[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * SE[0][0] + Imagedatabig[i - 2][j - 1][0] * SE[0][1] +
                        Imagedatabig[i - 2][j][0] * SE[0][2] + Imagedatabig[i - 2][j + 1][0] * SE[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * SE[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * SE[1][0] + Imagedatabig[i - 1][j - 1][0] * SE[1][1] +
                        Imagedatabig[i - 1][j][0] * SE[1][2] + Imagedatabig[i - 1][j + 1][0] * SE[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * SE[1][4] +
                        Imagedatabig[i][j - 2][0] * SE[2][0] + Imagedatabig[i][j - 1][0] * SE[2][1] +
                        Imagedatabig[i][j][0] * SE[2][2] + Imagedatabig[i][j + 1][0] * SE[2][3] +
                        Imagedatabig[i][j + 2][0] * SE[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * SE[3][0] + Imagedatabig[i + 1][j - 1][0] * SE[3][1] +
                        Imagedatabig[i + 1][j][0] * SE[3][2] + Imagedatabig[i + 1][j + 1][0] * SE[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * SE[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * SE[4][0] + Imagedatabig[i + 2][j - 1][0] * SE[4][1] +
                        Imagedatabig[i + 2][j][0] * SE[4][2] + Imagedatabig[i + 2][j + 1][0] * SE[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * SE[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata2[i][j][0]=Imagedata2[i][j][0]/24.0;
            }
        }
        float enyse = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyse += Imagedata2[i][j][0] * Imagedata2[i][j][0];
            }
        }
        featurevector[count-1][1] = enyse / (Size * Size);
//EW
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata3[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * EW[0][0] + Imagedatabig[i - 2][j - 1][0] * EW[0][1] +
                        Imagedatabig[i - 2][j][0] * EW[0][2] + Imagedatabig[i - 2][j + 1][0] * EW[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * EW[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * EW[1][0] + Imagedatabig[i - 1][j - 1][0] * EW[1][1] +
                        Imagedatabig[i - 1][j][0] * EW[1][2] + Imagedatabig[i - 1][j + 1][0] * EW[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * EW[1][4] +
                        Imagedatabig[i][j - 2][0] * EW[2][0] + Imagedatabig[i][j - 1][0] * EW[2][1] +
                        Imagedatabig[i][j][0] * EW[2][2] + Imagedatabig[i][j + 1][0] * EW[2][3] +
                        Imagedatabig[i][j + 2][0] * EW[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * EW[3][0] + Imagedatabig[i + 1][j - 1][0] * EW[3][1] +
                        Imagedatabig[i + 1][j][0] * EW[3][2] + Imagedatabig[i + 1][j + 1][0] * EW[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * EW[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * EW[4][0] + Imagedatabig[i + 2][j - 1][0] * EW[4][1] +
                        Imagedatabig[i + 2][j][0] * EW[4][2] + Imagedatabig[i + 2][j + 1][0] * EW[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * EW[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata3[i][j][0]=Imagedata3[i][j][0]/36.0;
            }
        }
        float enyew = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyew += Imagedata3[i][j][0] * Imagedata3[i][j][0];
            }
        }
        featurevector[count-1][2] = enyew / (Size * Size);
//WE
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata4[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * WE[0][0] + Imagedatabig[i - 2][j - 1][0] * WE[0][1] +
                        Imagedatabig[i - 2][j][0] * WE[0][2] + Imagedatabig[i - 2][j + 1][0] * WE[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * WE[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * WE[1][0] + Imagedatabig[i - 1][j - 1][0] * WE[1][1] +
                        Imagedatabig[i - 1][j][0] * WE[1][2] + Imagedatabig[i - 1][j + 1][0] * WE[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * WE[1][4] +
                        Imagedatabig[i][j - 2][0] * WE[2][0] + Imagedatabig[i][j - 1][0] * WE[2][1] +
                        Imagedatabig[i][j][0] * WE[2][2] + Imagedatabig[i][j + 1][0] * WE[2][3] +
                        Imagedatabig[i][j + 2][1] * WE[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * WE[3][0] + Imagedatabig[i + 1][j - 1][0] * WE[3][1] +
                        Imagedatabig[i + 1][j][0] * WE[3][2] + Imagedatabig[i + 1][j + 1][0] * WE[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * WE[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * WE[4][0] + Imagedatabig[i + 2][j - 1][0] * WE[4][1] +
                        Imagedatabig[i + 2][j][0] * WE[4][2] + Imagedatabig[i + 2][j + 1][0] * WE[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * WE[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata4[i][j][0]=Imagedata4[i][j][0]/36.0;
            }
        }
        float enywe = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enywe += Imagedata4[i][j][0] * Imagedata4[i][j][0];
            }
        }
        featurevector[count-1][3] = enywe / (Size * Size);
//SW
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata5[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * SW[0][0] + Imagedatabig[i - 2][j - 1][0] * SW[0][1] +
                        Imagedatabig[i - 2][j][0] * SW[0][2] + Imagedatabig[i - 2][j + 1][0] * SW[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * SW[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * SW[1][0] + Imagedatabig[i - 1][j - 1][0] * SW[1][1] +
                        Imagedatabig[i - 1][j][0] * SW[1][2] + Imagedatabig[i - 1][j + 1][0] * SW[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * SW[1][4] +
                        Imagedatabig[i][j - 2][0] * SW[2][0] + Imagedatabig[i][j - 1][0] * SW[2][1] +
                        Imagedatabig[i][j][0] * SW[2][2] + Imagedatabig[i][j + 1][0] * SW[2][3] +
                        Imagedatabig[i][j + 2][0] * SW[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * SW[3][0] + Imagedatabig[i + 1][j - 1][0] * SW[3][1] +
                        Imagedatabig[i + 1][j][0] * SW[3][2] + Imagedatabig[i + 1][j + 1][0] * SW[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * SW[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * SW[4][0] + Imagedatabig[i + 2][j - 1][0] * SW[4][1] +
                        Imagedatabig[i + 2][j][0] * SW[4][2] + Imagedatabig[i + 2][j + 1][0] * SW[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * SW[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata5[i][j][0]=Imagedata5[i][j][0]/24.0;
            }
        }
        float enysw = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enysw += Imagedata5[i][j][0] * Imagedata5[i][j][0];
            }
        }
        featurevector[count-1][4] = enysw / (Size * Size);
//WS
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata6[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * WS[0][0] + Imagedatabig[i - 2][j - 1][0] * WS[0][1] +
                        Imagedatabig[i - 2][j][0] * WS[0][2] + Imagedatabig[i - 2][j + 1][0] * WS[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * WS[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * WS[1][0] + Imagedatabig[i - 1][j - 1][0] * WS[1][1] +
                        Imagedatabig[i - 1][j][0] * WS[1][2] + Imagedatabig[i - 1][j + 1][0] * WS[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * WS[1][4] +
                        Imagedatabig[i][j - 2][0] * WS[2][0] + Imagedatabig[i][j - 1][0] * WS[2][1] +
                        Imagedatabig[i][j][0] * WS[2][2] + Imagedatabig[i][j + 1][0] * WS[2][3] +
                        Imagedatabig[i][j + 2][0] * WS[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * WS[3][0] + Imagedatabig[i + 1][j - 1][0] * WS[3][1] +
                        Imagedatabig[i + 1][j][0] * WS[3][2] + Imagedatabig[i + 1][j + 1][0] * WS[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * WS[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * WS[4][0] + Imagedatabig[i + 2][j - 1][0] * WS[4][1] +
                        Imagedatabig[i + 2][j][0] * WS[4][2] + Imagedatabig[i + 2][j + 1][0] * WS[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * WS[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata6[i][j][0]=Imagedata6[i][j][0]/24.0;
            }
        }
        float enyws = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyws += Imagedata6[i][j][0] * Imagedata6[i][j][0];
            }
        }
        featurevector[count-1][5] = enyws / (Size * Size);
//EE
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata7[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * EE[0][0] + Imagedatabig[i - 2][j - 1][0] * EE[0][1] +
                        Imagedatabig[i - 2][j][0] * EE[0][2] + Imagedatabig[i - 2][j + 1][0] * EE[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * EE[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * EE[1][0] + Imagedatabig[i - 1][j - 1][0] * EE[1][1] +
                        Imagedatabig[i - 1][j][0] * EE[1][2] + Imagedatabig[i - 1][j + 1][0] * EE[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * EE[1][4] +
                        Imagedatabig[i][j - 2][0] * EE[2][0] + Imagedatabig[i][j - 1][0] * EE[2][1] +
                        Imagedatabig[i][j][0] * EE[2][2] + Imagedatabig[i][j + 1][0] * EE[2][3] +
                        Imagedatabig[i][j + 2][0] * EE[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * EE[3][0] + Imagedatabig[i + 1][j - 1][0] * EE[3][1] +
                        Imagedatabig[i + 1][j][0] * EE[3][2] + Imagedatabig[i + 1][j + 1][0] * EE[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * EE[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * EE[4][0] + Imagedatabig[i + 2][j - 1][0] * EE[4][1] +
                        Imagedatabig[i + 2][j][0] * EE[4][2] + Imagedatabig[i + 2][j + 1][0] * EE[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * EE[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata7[i][j][0]=Imagedata7[i][j][0]/36.0;
            }
        }
        float enyee = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyee += Imagedata7[i][j][0] * Imagedata7[i][j][0];
            }
        }
        featurevector[count-1][6] = enyee / (Size * Size);
//SS
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata8[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * SS[0][0] + Imagedatabig[i - 2][j - 1][0] * SS[0][1] +
                        Imagedatabig[i - 2][j][0] * SS[0][2] + Imagedatabig[i - 2][j + 1][0] * SS[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * SS[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * SS[1][0] + Imagedatabig[i - 1][j - 1][0] * SS[1][1] +
                        Imagedatabig[i - 1][j][0] * SS[1][2] + Imagedatabig[i - 1][j + 1][0] * SS[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * SS[1][4] +
                        Imagedatabig[i][j - 2][0] * SS[2][0] + Imagedatabig[i][j - 1][0] * SS[2][1] +
                        Imagedatabig[i][j][0] * SS[2][2] + Imagedatabig[i][j + 1][0] * SS[2][3] +
                        Imagedatabig[i][j + 2][0] * SS[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * SS[3][0] + Imagedatabig[i + 1][j - 1][0] * SS[3][1] +
                        Imagedatabig[i + 1][j][0] * SS[3][2] + Imagedatabig[i + 1][j + 1][0] * SS[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * SS[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * SS[4][0] + Imagedatabig[i + 2][j - 1][0] * SS[4][1] +
                        Imagedatabig[i + 2][j][0] * SS[4][2] + Imagedatabig[i + 2][j + 1][0] * SS[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * SS[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata8[i][j][0]=Imagedata8[i][j][0]/16.0;
            }
        }
        float enyss = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyss += Imagedata8[i][j][0] * Imagedata8[i][j][0];
            }
        }
        featurevector[count-1][7] = enyss / (Size * Size);
//WW
        for (int i = 2; i < Size+2; i++) {
            for (int j = 2; j < Size+2; j++) {
                Imagedata9[i-2][j-2][0] =
                        Imagedatabig[i - 2][j - 2][0] * WW[0][0] + Imagedatabig[i - 2][j - 1][0] * WW[0][1] +
                        Imagedatabig[i - 2][j][0] * WW[0][2] + Imagedatabig[i - 2][j + 1][0] * WW[0][3] +
                        Imagedatabig[i - 2][j + 2][0] * WW[0][4] +
                        Imagedatabig[i - 1][j - 2][0] * WW[1][0] + Imagedatabig[i - 1][j - 1][0] * WW[1][1] +
                        Imagedatabig[i - 1][j][0] * WW[1][2] + Imagedatabig[i - 1][j + 1][0] * WW[1][3] +
                        Imagedatabig[i - 1][j + 2][0] * WW[1][4] +
                        Imagedatabig[i][j - 2][0] * WW[2][0] + Imagedatabig[i][j - 1][0] * WW[2][1] +
                        Imagedatabig[i][j][1] * WW[2][2] + Imagedatabig[i][j + 1][0] * WW[2][3] +
                        Imagedatabig[i][j + 2][0] * WW[2][4] +
                        Imagedatabig[i + 1][j - 2][0] * WW[3][0] + Imagedatabig[i + 1][j - 1][0] * WW[3][1] +
                        Imagedatabig[i + 1][j][0] * WW[3][2] + Imagedatabig[i + 1][j + 1][0] * WW[3][3] +
                        Imagedatabig[i + 1][j + 2][0] * WW[3][4] +
                        Imagedatabig[i + 2][j - 2][0] * WW[4][0] + Imagedatabig[i + 2][j - 1][0] * WW[4][1] +
                        Imagedatabig[i + 2][j][0] * WW[4][2] + Imagedatabig[i + 2][j + 1][0] * WW[4][3] +
                        Imagedatabig[i + 2][j + 2][0] * WW[4][4];

            }
        }
        for (int i=0;i<Size;i++){
            for (int j=0;j<Size;j++){
                Imagedata9[i][j][0]=Imagedata9[i][j][0]/36.0;
            }
        }
        float enyww = 0;
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                enyww += Imagedata9[i][j][0] * Imagedata9[i][j][0];
            }
        }
        featurevector[count-1][8] = enyww / (Size * Size);
    }

   
    //KMEAN

     //initial
          int k = 4;
          int count[4] = {};
          int cluster[4][12] ;
          for(int i=0;i<4;i++){
              for (int j=0;j<12;j++)
                  cluster[i][j]=-1;
          }
          int center[4][9] = {};
          for(int i=0;i<4;i++){
          for (int j=0;j<9;j++)
            center[i][j]=0;
          }

          for (int i=0;i<9;i++) {
              center[0][i] = featurevector[0][i];
          }
          cluster[0][0] = 0;
          count[0] = 0;

          for (int i=0;i<9;i++) {
           center[1][i] = featurevector[1][i];
          }
          cluster[1][0] = 1;
          count[1] = 0;

          for (int i=0;i<9;i++) {
           center[2][i] = featurevector[2][i];
          }
          cluster[2][0] = 2;
          count[2] = 0;

          for (int i=0;i<9;i++) {
             center[3][i] = featurevector[6][i];
           }
          cluster[3][0] =6 ;
          count[3] = 0;

          int errornew[4] = {};
          int errorold[4] = {};
          int iter=0;

      do{
          for (int b =0; b < 12; b++) {
              int d[4] = {};
              d[0] = sqrt(pow((featurevector[b][0] - center[0][0]), 2) + pow((featurevector[b][1] - center[0][1]), 2) +
                     pow((featurevector[b][2] - center[0][2]), 2) + pow((featurevector[b][3] - center[0][3]), 2) +
                     pow((featurevector[b][4] - center[0][4]), 2) + pow((featurevector[b][5] - center[0][5]), 2) +
                     pow((featurevector[b][6] - center[0][6]), 2) + pow((featurevector[b][7] - center[0][7]), 2) +
                     pow((featurevector[b][8] - center[0][8]), 2));
              d[1] = sqrt(pow((featurevector[b][0] - center[1][0]), 2) + pow((featurevector[b][1] - center[1][1]), 2) +
                     pow((featurevector[b][2] - center[1][2]), 2) + pow((featurevector[b][3] - center[1][3]), 2) +
                     pow((featurevector[b][4] - center[1][4]), 2) + pow((featurevector[b][5] - center[1][5]), 2) +
                     pow((featurevector[b][6] - center[1][6]), 2) + pow((featurevector[b][7] - center[1][7]), 2) +
                     pow((featurevector[b][8] - center[1][8]), 2));
              d[2] = sqrt(pow((featurevector[b][0] - center[2][0]), 2) + pow((featurevector[b][1] - center[2][1]), 2) +
                     pow((featurevector[b][2] - center[2][2]), 2) + pow((featurevector[b][3] - center[2][3]), 2) +
                     pow((featurevector[b][4] - center[2][4]), 2) + pow((featurevector[b][5] - center[2][5]), 2) +
                     pow((featurevector[b][6] - center[2][6]), 2) + pow((featurevector[b][7] - center[2][7]), 2) +
                     pow((featurevector[b][8] - center[2][8]), 2));
              d[3] = sqrt(pow((featurevector[b][0] - center[3][0]), 2) + pow((featurevector[b][1] - center[3][1]), 2) +
                     pow((featurevector[b][2] - center[3][2]), 2) + pow((featurevector[b][3] - center[3][3]), 2) +
                     pow((featurevector[b][4] - center[3][4]), 2) + pow((featurevector[b][5] - center[3][5]), 2) +
                     pow((featurevector[b][6] - center[3][6]), 2) + pow((featurevector[b][7] - center[3][7]), 2) +
                     pow((featurevector[b][8] - center[3][8]), 2));
              //find min distance
              int min = d[0];
              int key = 0;
              for (int j = 1; j < 4; j++) {
                  if (d[j] < min) {
                      min = d[j];
                      key = j;
                  }
              }
              int o=0;
              for (int i=0;i<12;i++){
                  if (cluster[key][i]==b)
                      o++;
              }
              if (o==0) {
                  count[key]++;
                  cluster[key][count[key]] = b;
              }
          }

          //error

          for (int p = 0; p < k; p++) {
              int distance=0;
              for (int l = 0; l < count[p]+1; l++) {
                  int d=0;
                  for (int i = 0; i < 9; i++) {
                      d=d+pow((featurevector[cluster[p][l]][i] - center[p][i]), 2);
                  }
                  distance+=d;
              }
              errorold[p]=distance ;
          }

          //recenter
          for (int p = 0; p < 4; p++) {
              int sum[9] = {};
              for (int i = 0; i < 9; i++) {
                  for (int l = 0; l < count[p]+1; l++) {
                      sum[i] = sum[i] + featurevector[cluster[p][l]][i];
                  }
                  center[p][i] = sum[i] / (count[p]+1);
              }
          }
          //error

          for (int p = 0; p < k; p++) {
              int distance=0;
              for (int l = 0; l < count[p]+1; l++) {
                  int d = 0;
                  for (int i = 0; i < 9; i++) {
                      d = d+pow((featurevector[cluster[p][l]][i] - center[p][i]), 2);
                  }
                   distance+= d;
              }
              errornew[p]=distance;
          }
          iter++;
      } while(((errorold[0]-errornew[0])+(errorold[1]-errornew[1])+(errorold[2]-errornew[2])+(errorold[3]-errornew[3])>1));


    // Write image data (filename specified by second argument) from image data matrix
    cout<<" Feature Vector of every Image"<<endl;
    cout<<setw(20)<<"feature_1"<<setw(10)<<"feature_2"<<setw(10)<<"feature_3"<<setw(10)<<"feature_4"<<setw(10)<<"feature_5"<<setw(10)<<"feature_6"<<setw(10)<<"feature_7"<<setw(10)<<"feature_8"<<setw(10)<<"feature_9"<<endl;
    for (int i=0;i<12;i++)
    {    cout<<"Image"<<setw(2)<<i+1<<":";
        for (int j=0;j<9;j++)
        {
          cout<<setw(10)<<(int)featurevector[i][j];
        }
        cout<<endl;
    }
    for (int j=0;j<k;j++){
        cout<<"Cluster["<<j+1<<"]:";

    for (int i=0;i<12;i++)
    {
        if (cluster[j][i]!=-1)
        cout <<cluster[j][i]+1<<"  ";
    }
        cout<<endl;
    }


    return 0;
}
