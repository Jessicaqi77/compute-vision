// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Sizerow=300;
    int Sizecol=400;
    int histwidth=256;
    int cdf[3][256]={};
    int histheight[3][256]={};
    float histfre[3][256]={};
    float temp[3][256]={};
    int range=256;
    int Size;

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5){
            Size = atoi(argv[4]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[Sizerow][Sizecol][BytesPerPixel];
    int Imagedatanum[Sizerow][Sizecol][BytesPerPixel];
    unsigned char Imagedatanew [Sizerow][Sizecol][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);
    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        for(int i=0;i<Sizerow;i++)
        {
             for (int j = 0; j < Sizecol; j++)
             {
                 Imagedatanum[i][j][channel] =(int)(Imagedata[i][j][channel]);
                 histheight[channel][Imagedatanum[i][j][channel]]+=1;
             }
        }
    }

    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        for (int m = 0; m < 256; m++) {
            histfre[channel][m]=(float)histheight[channel][m]/(float)(Sizecol*Sizerow);

        }
    }

    for (int channel=0;channel<BytesPerPixel;channel++) {
        temp[channel][0]= histfre[channel][0];
        for (int k = 1; k < 256; k++) {
            temp[channel][k]=temp[channel][k-1]+ histfre[channel][k];
        }
    }

    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        for (int k = 1; k < 256; k++)
        {
            cdf[channel][k]=(int)(255.0*temp[channel][k]);
        }
    }

    for (int channel=0;channel<BytesPerPixel;channel++) {
        for (int p = 0; p < Sizerow; p++) {
            for (int q = 0; q < Sizecol; q++) {

                Imagedatanew[p][q][channel]=(unsigned char) cdf[channel][Imagedatanum[p][q][channel]];

            }
        }
    }
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedatanew, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    return 0;
}

