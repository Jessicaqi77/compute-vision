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
    int Sizerow =256;
    int Sizecol=256;
    double mse[3]={};
    double psnr[3]={};
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
    if (!(file=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedatanew, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);
    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        double sum=0;
        for(int i=0;i<Sizerow;i++)
        {
            for (int j = 0; j < Sizecol; j++)
            {
                double temp;
                temp=Imagedatanew[i][j][channel]-Imagedata[i][j][channel];
                sum=sum+temp*temp;
            }
        }
        mse[channel]=sum/(Sizerow*Sizecol);
        psnr[channel]=10*log10(255*255/mse[channel]);
    }
    float ava=(psnr[0]+psnr[1]+psnr[2])/3;
    cout<<psnr[0]<<endl;
    cout<<psnr[1]<<endl;
    cout<<psnr[2]<<endl;
    cout<<ava<<endl;
    return 0;
}
