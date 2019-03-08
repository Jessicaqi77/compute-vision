


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
    int Size =700;//Sizerow=Sizecol=Size
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
    for (int channel=0;channel<3;channel++) {
        for (int i = 0; i < Size - 1; i++) {
            if (i % 2 == 0)
            {
                for (int j = 1; j < Size - 1; j++)
                {
                    if (Imagedata[i][j][channel] < T)
                    {
                        Imagedatanew[i][j][channel] = (unsigned) 0;
                    }
                    else Imagedatanew[i][j][channel] = (unsigned) 255;

                    error = (Imagedata[i][j][channel] - Imagedatanew[i][j][channel]);

                    Imagedata[i][j + 1][channel] = Imagedata[i][j+1][channel] + (7 * error) / 16;
                    Imagedata[i + 1][j - 1][channel] = Imagedata[i + 1][j - 1][channel] + (3 * error) / 16;
                    Imagedata[i + 1][j][channel] = Imagedata[i + 1][j][channel] + (5 * error) / 16;
                    Imagedata[i + 1][j + 1][channel] = Imagedata[i + 1][j + 1][channel] + (1 * error) / 16;
                }

            }
            if (i % 2 == 1)
            {
                for (int j = Size - 1; j>0 ; j--)
                {
                    if (Imagedata[i][j][channel] < T)
                    {
                        Imagedatanew[i][j][channel] = (unsigned) 0;
                    }
                    else Imagedatanew[i][j][channel] = (unsigned) 255;

                    error = (Imagedata[i][j][channel] - Imagedatanew[i][j][channel]);

                    Imagedata[i][j -1][channel] = Imagedata[i][j - 1][channel] + (7 * error) / 16;
                    Imagedata[i + 1][j - 1][channel] = Imagedata[i + 1][j - 1][channel] + (3 * error) / 16;
                    Imagedata[i + 1][j][channel] = Imagedata[i + 1][j][channel] + (5 * error) / 16;
                    Imagedata[i + 1][j + 1][channel] = Imagedata[i + 1][j + 1][channel] + (1 * error) / 16;
                }

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
