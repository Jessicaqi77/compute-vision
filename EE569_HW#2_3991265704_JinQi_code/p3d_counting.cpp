
// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<string>

#include<sstream>
using namespace std;
//using std::string;
int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Sizerow = 372;
    int Sizecol = 372;//Sizerow=Sizecol=Size
    int Size = 0;

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

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow * Sizecol * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    //create binary image

    for (int i = 0; i < Sizerow; i++) {
        for (int j = 0; j < Sizecol; j++) {
            if (Imagedata[i][j][0] < 71)
                Imagedata[i][j][0] = 1;
            else Imagedata[i][j][0] = 0;
        }
    };
    //first scan
    int lab[100]={};
    int val=2;

        for (int i = 1; i < Sizerow - 1; i++)//scan pixel
        {
            for (int j = 1; j < Sizecol - 1; j++) {
                if (Imagedata[i][j][0]!=0) {

                    int temp[8];
                    temp[0] = Imagedata[i - 1][j - 1][0];
                    temp[1] = Imagedata[i - 1][j][0];
                    temp[2] = Imagedata[i - 1][j + 1][0];
                    temp[3] = Imagedata[i][j - 1][0];
                    temp[4] = Imagedata[i][j + 1][0];
                    temp[5] = Imagedata[i + 1][j - 1][0];
                    temp[6] = Imagedata[i + 1][j][0];
                    temp[7] = Imagedata[i + 1][j + 1][0];
                    if ((temp[0]==0)&& (temp[1] ==0)&& (temp[2] ==0)&& (temp[3]==0))
                        Imagedata[i][j][0] = val++;//first
                    else {
                        int min;
                        for(int p=0;p<8;p++)// nonzero and non-one
                        {
                           if (temp[p]>1)
                               min=temp[p];
                        }
                        for(int p=0;p<8;p++)//first nonzero
                        {
                            if ((temp[p]>1)&&(temp[p]<min))
                                min=temp[p];
                        }

                        Imagedata[i][j][0] = min;
                    }
                }
            }
        }
    //second scan
    for(int i=Sizerow-1;i>0;i--)
    {
        for(int j=Sizecol-1;j>0;j--){
            if (Imagedata[i][j][0] !=0)
            {

                int temp[8];
                temp[0] = Imagedata[i - 1][j - 1][0];
                temp[1] = Imagedata[i - 1][j][0];
                temp[2] = Imagedata[i - 1][j + 1][0];
                temp[3] = Imagedata[i][j - 1][0];
                temp[4] = Imagedata[i][j + 1][0];
                temp[5] = Imagedata[i + 1][j - 1][0];
                temp[6] = Imagedata[i + 1][j][0];
                temp[7] = Imagedata[i + 1][j + 1][0];
                int min;
                for(int p=0;p<8;p++)// nonzero
                {
                    if (temp[p]>1)
                        min=temp[p];
                }
                for(int p=0;p<8;p++)//first nonzero
                {
                    if ((temp[p]>1)&&(temp[p]<min))
                        min=temp[p];
                }

                Imagedata[i][j][0] = min;
            }
        }
    }
    //third scan
    for(int i=1;i<Sizecol-1;i++)
    {
        for(int j=1;j<Sizerow-1;j++){
            if (Imagedata[i][j][0] !=0)
            {

                int temp[8];
                temp[0] = Imagedata[i - 1][j - 1][0];
                temp[1] = Imagedata[i - 1][j][0];
                temp[2] = Imagedata[i - 1][j + 1][0];
                temp[3] = Imagedata[i][j - 1][0];
                temp[4] = Imagedata[i][j + 1][0];
                temp[5] = Imagedata[i + 1][j - 1][0];
                temp[6] = Imagedata[i + 1][j][0];
                temp[7] = Imagedata[i + 1][j + 1][0];
                int min;
                for(int p=0;p<8;p++)//nonzero
                {
                    if (temp[p]>1)
                        min=temp[p];
                }
                for(int p=0;p<8;p++)
                {
                    if ((temp[p]>1)&&(temp[p]<min))
                        min=temp[p];
                }

                Imagedata[i][j][0] = min;
            }
        }
    }

    for (int i=0;i<Sizerow;i++){
     for (int j=0;j<Sizecol;j++){
         if (Imagedata[i][j][0] >1)
         {
             lab[Imagedata[i][j][0]]+=1;
             Imagedata[i][j][0] =255;
         }
    }
    }
    //counting
    int count=0;
    for(int i=0;i<100;i++)
    {
        if (lab[i]!=0)
        {
            count++;
        }
    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);
    cout<<"the number of jigsaws: "<<count<<endl;
    return 0;
}


