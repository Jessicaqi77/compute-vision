


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
    float Imagedatanum[512][512][1];
    unsigned char Imagedatanew[Size][Size][BytesPerPixel];


    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //threshold
    int N=4;
    int M=8;
    int I[2][2]={{1,2},{3,0}};
    int B[4][4]={};
    int C[8][8]={};
    for (int i=0;i<N/2;i++)
    {
        for (int j=0;j<N/2;j++)
        {

            B[i][j]=4*I[i][j]+1;
        }
    }
    for (int i=0;i<N/2;i++)
    {
        for (int j=N/2;j<N;j++)
        {

            B[i][j]=4*I[i][j%(N/2)]+2;
        }
    }
    for (int i=N/2;i<N;i++)
    {
        for (int j=0;j<N/2;j++)
        {

            B[i][j]=4*I[i%(N/2)][j]+3;
        }
    }
    for (int i=N/2;i<N;i++)
    {
        for (int j=N/2;j<N;j++)
        {

            B[i][j]=4*I[i%(N/2)][j%(N/2)];
        }
    }


    for (int i=0;i<M/2;i++)
    {
        for (int j=0;j<M/2;j++)
        {

            C[i][j]=4*B[i][j]+1;
        }
    }
    for (int i=0;i<M/2;i++)
    {
        for (int j=M/2;j<M;j++)
        {

            C[i][j]=4*B[i][j%(M/2)]+2;
        }
    }
    for (int i=M/2;i<M;i++)
    {
        for (int j=0;j<M/2;j++)
        {

            C[i][j]=4*B[i%(M/2)][j]+3;
        }
    }
    for (int i=M/2;i<M;i++)
    {
        for (int j=M/2;j<M;j++)
        {

            C[i][j]=4*B[i%(M/2)][j%(M/2)];
        }
    }

    float T[8][8]={};
    for (int m=0;m<M;m++)
    {
        for(int n=0;n<M;n++)
        {
            T[m][n]=(C[m][n]+0.5)/(M*M);
        }
    }
    // binary
    for (int i=0;i<Size;i++)
    {
        for (int j = 0; j < Size; j++)
        {
            Imagedatanum[i][j][0]=((float)(Imagedata[i][j][0]))/255;
        }
    }
    // compare
    for (int i=0;i<Size;i++)
    {
        for (int j=0;j<Size;j++)
        {

            int a=i%M; int b=j%M;
            if (Imagedatanum[i][j][0]<=T[a][b])
            {
                Imagedatanew[i][j][0]=0;
            }
            else Imagedatanew[i][j][0]=255;
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


