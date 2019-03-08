
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

unsigned char Imagedata[321][481][3];
unsigned char Imagedatagray[321][481][3];
int Imagedatabig[325][485][3];
int Imagedatafilter[321][481][3];
float  Imagedatanormal[321][481][3];
float Imagedatatri[321][481][3];
unsigned char Imagedataedgeout[321][481][1];
unsigned char Imagedatanormalout[321][481][1];
int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int Sizerow=321;
    int Sizecol=481;

    // Allocate image data array
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizecol*Sizerow*3, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //convert gray
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            Imagedatagray[i][j][0]=(Imagedata[i][j][0]+Imagedata[i][j][1]+Imagedata[i][j][2])/3;
        }
    }
    int log[5][5]={{0,0,-1,0,0},{0,-1,-2,-1,0},{-1,-2,16,-2,-1},{0,-1,-2,-1,0},{0,0,-1,0,0}};
    // extension
    for (int i = 2; i < Sizerow + 2; i++) {
        for (int j = 2; j < Sizecol + 2; j++) {
            Imagedatabig[i][j][0] = (int)Imagedatagray[i - 2][j - 2][0];
        }
    }
    for (int j = 0; j < Sizecol+2; j++) {
        Imagedatabig[0][j][0] = (int)Imagedatagray[0][j][0];
        Imagedatabig[1][j][0] = (int)Imagedatagray[0][j][0];
        Imagedatabig[Sizerow - 2][j][0] = (int)Imagedatagray[Sizerow][j][0];
        Imagedatabig[Sizerow - 1][j][0] = (int)Imagedatagray[Sizerow][j][0];
    }
    for (int i = 0; i < Sizerow + 2; i++) {
        Imagedatabig[i][0][0] = (int)Imagedatagray[i][0][0];
        Imagedatabig[i][1][0] = (int)Imagedatagray[i][1][0];
        Imagedatabig[i][Sizecol + 1][0] = (int)Imagedatagray[i][Sizecol][0];
        Imagedatabig[i][Sizecol + 2][0] = (int)Imagedatagray[i][Sizecol][0];
    }

    //filter
    for (int i=2;i<Sizerow+2;i++)
    {
        for (int j=2;j<Sizecol+2;j++) {
            Imagedatafilter[i-2][j-2][0] =Imagedatabig[i - 2][j - 2][0] * log[0][0] + Imagedatabig[i - 2][j - 1][0] * log[0][1] +
                                          Imagedatabig[i - 2][j][0] * log[0][2] + Imagedatabig[i - 2][j + 1][0] * log[0][3] +
                                          Imagedatabig[i - 2][j + 2][0] * log[0][4] +
                                          Imagedatabig[i - 1][j - 2][0] * log[1][0] + Imagedatabig[i - 1][j - 1][0] * log[1][1] +
                                          Imagedatabig[i - 1][j][0] * log[1][2] + Imagedatabig[i - 1][j + 1][0] * log[1][3] +
                                          Imagedatabig[i - 1][j + 2][0] * log[1][4] +
                                          Imagedatabig[i][j - 2][0] * log[2][0] + Imagedatabig[i][j - 1][0] * log[2][1] +
                                          Imagedatabig[i][j][0] * log[2][2] + Imagedatabig[i][j + 1][0] * log[2][3] +
                                          Imagedatabig[i][j + 2][0] * log[2][4] +
                                          Imagedatabig[i + 1][j - 2][0] * log[3][0] + Imagedatabig[i + 1][j - 1][0] * log[3][1] +
                                          Imagedatabig[i + 1][j][0] * log[3][2] + Imagedatabig[i + 1][j + 1][0] * log[3][3] +
                                          Imagedatabig[i + 1][j + 2][0] * log[3][4] +
                                          Imagedatabig[i + 2][j - 2][0] * log[4][0] + Imagedatabig[i + 2][j - 1][0] * log[4][1] +
                                          Imagedatabig[i + 2][j][0] * log[4][2] + Imagedatabig[i + 2][j + 1][0] * log[4][3] +
                                          Imagedatabig[i + 2][j + 2][0] * log[4][4];

        }
    }
    //normal
    int a[481*321]={};int count=0;int min=0; int max=0;int inter=0;
    for (int i=0;i<Sizerow;i++) {
        for (int j = 0; j < Sizecol; j++) {
            a[count++] = abs(Imagedatafilter[i][j][0]);
        }
    }
    sort(a,a+481*321);
    min=a[0];max=a[481*321-1]; inter=max-min;float th=0; float th2=0;

    for (int i=0;i<Sizerow;i++) {
        for (int j = 0; j < Sizecol; j++) {
            int temp=0;
            temp=abs(Imagedatafilter[i][j][0])-0;
            Imagedatanormal[i][j][0]=temp*255.0/max;
        }
    }

    float b[481*321]={};int count1=0;
    for (int i=0;i<Sizerow;i++) {
        for (int j = 0; j < Sizecol; j++) {
            b[count1++] = Imagedatanormal[i][j][0];
        }
    }
    sort(b,b+481*321);
    int num=481*321*0.9;
    th=b[num];
    th2=(int)th*max/255.0;

    for (int i=0;i<Sizerow;i++) {
        for (int j = 0; j < Sizecol; j++) {
            if(Imagedatafilter[i][j][0]<=((-1)*th2))
                Imagedatatri[i][j][0]=-1;
            else if (Imagedatafilter[i][j][0]>=th2)
                Imagedatatri[i][j][0]=1;
            else if ((Imagedatafilter[i][j][0]<th2)&&(Imagedatafilter[i][j][0]>((-1)*th2)))
                Imagedatatri[i][j][0]=0;

        }
    }
    for (int i=1;i<Sizerow-1;i++)
    {
        for (int j=1;j<Sizecol-1;j++)
        {
            if (Imagedatatri[i][j][0]==0)
            {
                int g=Imagedatatri[i-1][j][0]*Imagedatatri[i+1][j][0];
                int f=Imagedatatri[i][j-1][0]*Imagedatatri[i][j+1][0];
                int z=Imagedatatri[i-1][j-1][0]*Imagedatatri[i+1][j+1][0];
                int x=Imagedatatri[i+1][j-1][0]*Imagedatatri[i-1][j+1][0];
                if((g==-1)||(f==-1)||(z==-1)||(x==-1))
                    Imagedatatri[i][j][0]=0;
                //else Imagedatatri[i][j][0]=255;
            }

        }
    }
    for (int i=1;i<Sizerow-1;i++)
    {
        for (int j=1;j<Sizecol-1;j++)
        {
            if(Imagedatatri[i][j][0]!=0)
            {
                Imagedatatri[i][j][0]=255;
            }

        }
    }
    for (int i=1;i<Sizerow-1;i++)
    {
        for (int j=1;j<Sizecol-1;j++)
        {
            Imagedataedgeout[i][j][0]=255-(unsigned char)Imagedatatri[i][j][0];
        }
    }
    for (int i=1;i<Sizerow-1;i++)
    {
        for (int j=1;j<Sizecol-1;j++)
        {
            Imagedatanormalout[i][j][0]=(unsigned char)Imagedatanormal[i][j][0];
        }
    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedatanormalout, sizeof(unsigned char), Sizerow*Sizecol*1, file);
    fclose(file);

    return 0;
}
