
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
unsigned char Imagedatagray[321][481][1];
int Imagedatabig[323][483][1];
int Imagedatagx[321][481][1];
unsigned char Imagedatagxout[321][481][1];
int Imagedatagy[321][481][1];
unsigned char Imagedatagyout[321][481][1];
int Imagedatag[321][481][1];
unsigned char Imagedatagout[321][481][1];
int Imagedataedge[321][481][1];
unsigned char Imagedataedgeout[321][481][1];

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
    int sobelx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int sobely[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    // extension
    for (int i = 1; i < Sizerow + 1; i++) {
        for (int j = 1; j < Sizecol + 1; j++) {
            Imagedatabig[i][j][0] = (int)Imagedatagray[i - 1][j -1][0];
        }
    }
    for (int j = 0; j < Sizecol+1; j++) {
        Imagedatabig[0][j][0] = Imagedatagray[0][j][0];
        Imagedatabig[Sizerow - 1][j][0] = (int)Imagedata[Sizerow][j][0];
    }
    for (int i = 0; i < Sizerow + 1; i++) {
        Imagedatabig[i][0][0] = Imagedatagray[i][0][0];
        Imagedatabig[i][Sizecol + 1][0] = (int) Imagedatagray[i][Sizecol][0];
    }
    //gradient_x
    for (int i=1;i<Sizerow+1;i++)
    {
        for (int j=1;j<Sizecol+1;j++) {
            Imagedatagx[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * sobelx[0][0] + Imagedatabig[i - 1][j][0] * sobelx[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * sobelx[0][2] +
                    Imagedatabig[i ][j - 1][0] * sobelx[1][0] + Imagedatabig[i ][j ][0] * sobelx[1][1] +
                    Imagedatabig[i ][j + 1][0] * sobelx[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * sobelx[2][0] + Imagedatabig[i + 1][j][0] * sobelx[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * sobelx[2][2] ;
        }
    }

    //normal_x
    int b[481*321];int count1=0;
    //histogram
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            b[count1++]=Imagedatagx[i][j][0];
        }
    }
    sort(b,b+481*321);
    int minx=b[0];int maxx=b[481*321-1];int inter=maxx-minx;
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int temp;
            temp=Imagedatagx[i][j][0]-minx;
            Imagedatagx[i][j][0]=temp*255/inter;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {

            Imagedatagxout[i][j][0]= (unsigned char)Imagedatagx[i][j][0];
        }
    }
    //gradient_y
    for (int i=1;i<Sizerow+1;i++)
    {
        for (int j=1;j<Sizecol+1;j++) {
            Imagedatagy[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * sobely[0][0] + Imagedatabig[i - 1][j][0] * sobely[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * sobely[0][2] +
                    Imagedatabig[i ][j - 1][0] * sobely[1][0] + Imagedatabig[i ][j ][0] * sobely[1][1] +
                    Imagedatabig[i ][j + 1][0] * sobely[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * sobely[2][0] + Imagedatabig[i + 1][j][0] * sobely[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * sobely[2][2] ;
        }
    }
    //normal_y
    int c[481*321];int count2=0;
    //histogram
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            c[count2++]=Imagedatagy[i][j][0];
        }
    }
    sort(c,c+481*321);
    int miny=b[0];int maxy=b[481*321-1];int inter2=maxy-miny;
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int temp;
            temp=Imagedatagy[i][j][0]-miny;
            Imagedatagy[i][j][0]=temp*255/inter2;
        }
    }
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {

            Imagedatagyout[i][j][0]= (unsigned char)Imagedatagy[i][j][0];
        }
    }

    //magnitude
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++) {
            Imagedatag[i][j][0] =sqrt(pow(Imagedatagx[i][j][0],2)+pow(Imagedatagy[i][j][0],2));

        }
    }

    int a[481*321];int count=0;
    //histogram
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            a[count++]=Imagedatag[i][j][0];
        }
    }
    sort(a,a+481*321);
    //normal
    int ming=a[0];int maxg=a[481*321-1];int inter3=maxg-ming;
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int temp;
            temp=Imagedatag[i][j][0]-ming;
            Imagedatag[i][j][0]=temp*255/inter3;
        }
    }
    //find threshold
    int d[481*321];int count3=0;
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            d[count3++]=Imagedatag[i][j][0];
        }
    }
    sort(d,d+481*321);
    int num=481*321*0.9;
    int th=d[num];//10%

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            if (Imagedatag[i][j][0]>th)
                Imagedataedge[i][j][0]=0;
            else Imagedataedge[i][j][0]=255;
        }
    }
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {

            Imagedataedgeout[i][j][0]= (unsigned char)Imagedataedge[i][j][0];
        }
    }
    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {

            Imagedatagout[i][j][0]= (unsigned char)Imagedatag[i][j][0];
        }
    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedataedgeout, sizeof(unsigned char), Sizerow*Sizecol*1, file);
    fclose(file);

    return 0;
}
