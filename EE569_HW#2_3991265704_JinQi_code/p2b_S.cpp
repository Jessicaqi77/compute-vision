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
    int T=127;

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
    int error=0;
    for (int i=0;i<Size-2;i++)
    {
        for (int j=0;j<Size-2;j++)
        {

            if (Imagedata[i][j][0]<=T)
            {
                Imagedatanew[i][j][0] = 0;
            }
            else Imagedatanew[i][j][0]=255;

            error=(Imagedata[i][j][0]-Imagedatanew[i][j][0]);

            Imagedata[i][j+1][0]=Imagedata[i][j+1][0]+(8*error)/42;
            Imagedata[i][j+2][0]=Imagedata[i][j+2][0]+(4*error)/42;

            Imagedata[i+1][j-2][0]=Imagedata[i+1][j-2][0]+(2*error)/42;
            Imagedata[i+1][j-1][0]=Imagedata[i+1][j-1][0]+(4*error)/42;
            Imagedata[i+1][j][0]=Imagedata[i+1][j][0]+(8*error)/42;
            Imagedata[i+1][j+1][0]=Imagedata[i+1][j+1][0]+(4*error)/42;
            Imagedata[i+1][j+2][0]=Imagedata[i+1][j+2][0]+(2*error)/42;

            Imagedata[i+2][j-2][0]=Imagedata[i+2][j-2][0]+(1*error)/42;
            Imagedata[i+2][j-1][0]=Imagedata[i+2][j-1][0]+(2*error)/42;
            Imagedata[i+2][j][0]=Imagedata[i+2][j][0]+(4*error)/42;
            Imagedata[i+2][j+1][0]=Imagedata[i+2][j+1][0]+(2*error)/42;
            Imagedata[i+2][j+2][0]=Imagedata[i+2][j+2][0]+(1*error)/42;
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



