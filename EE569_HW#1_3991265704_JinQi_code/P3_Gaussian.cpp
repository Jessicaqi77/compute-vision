// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Sizecol = 256;
    int Sizerow =256;
    int windowsize = 3;
    int window[9] = {};
    int position = (windowsize - 1) / 2;
    int mid=0;
    int Size;
    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4) {
        BytesPerPixel = 1; // default is grey image
    } else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
            Size = atoi(argv[4]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[Sizerow][Sizecol][BytesPerPixel];
    unsigned char Imagedatanew[Sizerow+1][Sizecol+1][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow * Sizecol * BytesPerPixel, file);
    fclose(file);
    //extension
    for (int channel=0;channel<BytesPerPixel;channel++)
    {

        for(int i=0;i<Sizerow;i++)
        {
            for (int j = 0; j < Sizecol; j++)
            {
                Imagedatanew[i+1][j+1][channel] =(Imagedata[i][j][channel]);
                Imagedatanew[0][j][channel] =(Imagedata[0][j][channel]);
                Imagedatanew[i][0][channel] =(Imagedata[i][0][channel]);
            }
        }
    }


    for (int c = 0; c < BytesPerPixel; c++)
    {
        for (int i = 1; i < Sizerow+1 ; i++)
        {
            for (int j = 1; j< Sizecol+1; j++)
            {
                int winpos = 0;
                for (int m = -1; m < windowsize - position; m++)
                {
                    for (int n = -1; n < windowsize - position; n++)
                    {
                        window[winpos++] = Imagedatanew[m+i][n+j][c];
                    }
                }
                int sum=0;
                sum=(window[0]+window[2]+window[6]+window[8])+2*(window[1]+window[3]+window[5]+window[7])+4*window[4];
                Imagedata[i-1][j-1][c]=sum/16;
            }
        }

    }

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    return 0;
}



