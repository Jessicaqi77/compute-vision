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
    int Sizerow=256;
    int Sizecol=256;
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
    unsigned char Imagedatanew[Sizerow][Sizecol][BytesPerPixel];
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
                Imagedatanew[i][Sizecol-j-1][channel] =255-Imagedata[i][j][channel];
            }
        }
    }
    // channel 0 red
    for(int i=0;i<Sizerow;i++)
    {
        for (int j = 0; j < Sizecol; j++)
        {
            Imagedatanew[i][j][0]=36*Imagedatanew[i][j][0]/64+112;
        }
    }

    // channel1
    for(int i=0;i<Sizerow;i++)
    {
        for (int j = 0; j < Sizecol; j++)
        {
            Imagedatanew[i][j][1]=25*Imagedatanew[i][j][1]/36+28;
        }
    }
    //channel 2
    for(int i=0;i<Sizerow;i++)
    {
        for (int j = 0; j < Sizecol; j++)
        {
            Imagedatanew[i][j][2]=11*Imagedatanew[i][j][2]/18+20;
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

