
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
    int Size =512;//Sizerow=Sizecol=Size

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
    unsigned char Imagedata[Size][Size][BytesPerPixel];
    unsigned char Imagedatanew[Size][Size][BytesPerPixel];


    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    for (int channel=0; channel<3;channel++)
    {
        Imagedatanew[Size/2][0][channel] = Imagedata[Size /2][0][channel];
        Imagedatanew[Size/2][Size/2][channel] = Imagedata[Size /2][Size/2][channel];
    }
    for (int channel=0; channel<3;channel++)
    {
        for(int i=1;i<Size/2;i++)
        {
                int x=ceil(sqrt(Size*Size/4-pow(Size/2-i,2)));
                for (int p=1;p<x+1;p++)
                {
                    float r=(float)2*x/(float)Size;
                    float original=float(p)/r;
                    int a=int(original);
                    float v=original-a;
                    int value=(1-v)*Imagedata[i][a][channel]+v*Imagedata[i][a+1][channel];
                    Imagedatanew[i][p+Size/2-x][channel]=value;
                }
            }

    }

       for (int channel=0; channel<3;channel++)
    {
        for(int i=Size/2;i<Size;i++)
        {

                int x=ceil(sqrt(Size*Size/4-pow(i-Size/2,2)));
                for (int p=1;p<x;p++)
                {
                    float r=(float)2*x/(float)Size;
                    float original=float(p)/r;
                    int a=floor(original);
                    float v=original-a;
                    int value=(1-v)*Imagedata[i][a][channel]+v*Imagedata[i][a+1][channel];
                    Imagedatanew[i][p+Size/2-x][channel]=value;
                }
            }

    }

    for (int channel=0; channel<3;channel++)
    {
        for(int i=1;i<Size/2;i++)
        {
                int x=ceil(sqrt(Size*Size/4-pow(Size/2-i,2)));
                for (int p=1;p<x;p++)
                {
                    float r=(float)2*x/(float)Size;
                    float original=float(p)/r;
                    int a=int(original);
                    float v=original-a;
                    int value=(1-v)*Imagedata[i][a+Size/2][channel]+v*Imagedata[i][a+Size/2+1][channel];
                    Imagedatanew[i][p+Size/2][channel]=value;
                }

        }
    }

    for (int channel=0; channel<3;channel++)
    {
        for(int i=Size/2;i<Size;i++)
        {
                int x=ceil(sqrt(Size*Size/4-pow(i-Size/2,2)));
                for (int p=0;p<x;p++)
                {
                    float r=(float)2*x/(float)Size;
                    float original=float(p)/r;
                    int a=int(original);
                    float v=original-a;
                    int value=(1-v)*Imagedata[i][a+Size/2][channel]+v*Imagedata[i][a+Size/2+1][channel];
                    Imagedatanew[i][p+Size/2][channel]=value;
                }
        }
    }





    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedatanew, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    return 0;
}
