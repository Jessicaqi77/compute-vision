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

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Sizerow=300;//image size
    int Sizecol=400;
    int size=Sizerow*Sizecol;
    int Size;
    int num=ceil((float)size/(float)256);

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
    unsigned char Imagedataout[Sizerow][Sizecol][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix

    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);
    int x[Sizerow*Sizecol];
    int y[Sizecol*Sizerow];

    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        //initialize
        for (int w = 0; w < size ; w++)
        {
            x[w]=0;y[w]=0;
        }

        int m=0;
        for (int i=0;i<256;i++)
        {
            for (int p=0;p<Sizerow;p++)
            {
               for (int q=0;q<Sizecol;q++)
               {
                   if (Imagedata[p][q][channel]==i)
                   {
                       x[m]=p;
                       y[m]=q;
                       m++;
                   }
               }
            }
        }

        for(int value=0;value<256;value++) {
            for (int v = 0; v < num; v++) {
                if(num* value + v<size)
                {
                    Imagedataout[x[num * value + v]][y[num * value + v]][channel] = value;
                }
                else
                {
                    continue;
                }
            }
        }
    }



    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedataout, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    return 0;
}



