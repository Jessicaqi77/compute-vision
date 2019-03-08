


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

unsigned char Imagedata[450][600][1];
unsigned char Imagedataout[450][600][1];


int main(int argc, char *argv[])
{
// Define file pointer and variables
    FILE *file;
    int BytesPerPixel=1;
    int Sizerow =450;
    int Sizecol=600;

// Check for proper syntax
// Check if image is grayscale or color
// Check if size is specified
// Allocate image data array
//int E[3] = {-1, -2, 0, 2, 1};
//int S[3] = {-1, 0, 2, 0, -1};

    int windowsize=51;
    int x=windowsize/2;
// Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow * Sizecol* BytesPerPixel, file);
    fclose(file);

///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

for (int i=0;i<Sizerow;i++)
{
    for (int j=0;j<Sizecol;j++)
    {
        int count[6]={}; int val[6]={0,51,102,153,204,255};
        for (int p=i-x;p<i+x;p++)
        {
            for (int q=j-x;q<j+x;q++)
            {
                if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                {
                    if (Imagedata[p][q][0]==0)
                        count[0]++;
                    else if  (Imagedata[p][q][0]==51)
                        count[1]++;
                    else if  (Imagedata[p][q][0]==102)
                        count[2]++;
                    else if  (Imagedata[p][q][0]==153)
                        count[3]++;
                    else if  (Imagedata[p][q][0]==204)
                        count[4]++;
                    else if  (Imagedata[p][q][0]==255)
                        count[5]++;
                }

            }

        }
        int max=count[0];int key=0;
        for (int l=1;l<6;l++)
        {
            if (count[l]>max){
                max=count[l];
                key=l;
            }

        }
        Imagedataout[i][j][1]= val[key];

    }
    }

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedataout, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    return 0;

}
