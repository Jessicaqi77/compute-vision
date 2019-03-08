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

const int Sizerownew=2000;
const int Sizecolnew=480*3;
unsigned char Imagedatanew[Sizerownew][Sizecolnew][3];

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int Sizerow =640;
    int Sizecol=480;
    int BytesPerPixel;
    int Size=0;
    // Check for proper syntax
    if (argc < 5){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 6){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[5]);
        // Check if size is specified
        if (argc >= 7){
            Size = atoi(argv[4]);
        }
    }

    // Allocate image data array
    unsigned char Imagedataleft[Sizerow][Sizecol][BytesPerPixel];
    unsigned char Imagedatamiddle[Sizerow][Sizecol][BytesPerPixel];
    unsigned char Imagedataright[Sizerow][Sizecol][BytesPerPixel];



    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedataleft, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    if (!(file=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedatamiddle, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    if (!(file=fopen(argv[3],"rb"))) {
        cout << "Cannot open file: " << argv[3] <<endl;
        exit(1);
    }
    fread(Imagedataright, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int mov_val=600;
    //middle
    for(int channel=0;channel<3;channel++)
    {
        for (int i=0;i<Sizerow;i++)
        {
            for(int j=0;j<Sizecol;j++)
            {
                Imagedatanew[i+mov_val][j+mov_val][channel]= Imagedatamiddle[i][j][channel];
            }
        }
    }
    float H[3][3]={{1.8348,0.0716,227.5733},{0.6812,1.3598,508.0607},{0.00076025,0.00006915,1}};
    int data=0;
    // left

    for(int channel=0;channel<3;channel++)
    {
        for (int i=0;i<Sizerow;i++)
        {
            for(int j=0;j<Sizecol;j++)
            {
                int X,Y;
                data=Imagedataleft[i][j][channel];
                X=(j*H[0][0]+i*H[0][1]+H[0][2])/(j*H[2][0]+i*H[2][1]+H[2][2]);
                Y=(j*H[1][0]+i*H[1][1]+H[1][2])/(j*H[2][0]+i*H[2][1]+H[2][2]);
                Imagedatanew[Y][X+1][channel]=data;
                Imagedatanew[Y][X-1][channel]=data;
                Imagedatanew[Y+1][X][channel]=data;
                Imagedatanew[Y-1][X][channel]=data;
            }
        }

    }

    float P[3][3]={{0.8062,-0.0380,809.9586},{-0.0611,0.9094,617.9524},{-0.000077926,-0.000036524,1}};
    // right
    for(int channel=0;channel<3;channel++)
    {
        for (int i=0;i<Sizerow;i++)
        {
            for(int j=0;j<Sizecol;j++)
            {
                int X,Y;
                data=Imagedataright[i][j][channel];
                X=(j*P[0][0]+i*P[0][1]+P[0][2])/(j*P[2][0]+i*P[2][1]+P[2][2]);
                Y=(j*P[1][0]+i*P[1][1]+P[1][2])/(j*P[2][0]+i*P[2][1]+P[2][2]);
                Imagedatanew[Y][X+1][channel]=data;
                Imagedatanew[Y][X-1][channel]=data;
                Imagedatanew[Y+1][X][channel]=data;
                Imagedatanew[Y-1][X][channel]=data;

            }
        }

    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[4],"wb"))) {
        cout << "Cannot open file: " << argv[4] << endl;
        exit(1);
    }
    fwrite(Imagedatanew, sizeof(unsigned char), Sizerownew*Sizecolnew*BytesPerPixel, file);
    fclose(file);

    return 0;
}
