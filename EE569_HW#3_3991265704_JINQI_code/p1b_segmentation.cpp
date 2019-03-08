

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
float Imagedatabig[452][602][1];
float Imagedata1[450][600][1];
float Imagedata2[450][600][1];
float Imagedata3[450][600][1];
float Imagedata4[450][600][1];
float Imagedata5[450][600][1];
float Imagedata6[450][600][1];
float Imagedata7[450][600][1];
float Imagedata8[450][600][1];
float Imagedata9[450][600][1];
unsigned char Imagedataout[450][600][1];
float featurevector[270000][9]={};

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
//int L[3] = {-1, 2, 0, -2, 1};
    int ES[3][3] = {{1,-2,1},{0,0,0},{-1,2,-1}};
    int SE[3][3] = {{1,0,-1},{-2,0,2},{1,0,-1}};
    int EL[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    int LE[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int SL[3][3] = {{-1,-2,-1},{2,4,2},{-1,-2,-1}};
    int LS[3][3] = {{-1,2,-1},{-2,4,-2},{-1,2,-1}};
    int EE[3][3] = {{1,0,-1},{0,0,0},{-1,0,1}};
    int SS[3][3] = {{1,-2,1},{-2,4,-2},{1,-2,1}};
    int LL[3][3] = {{1,2,1},{2,4,2},{1,2,1}};

    int windowsize=21;
    int x=windowsize/2;
    
// Read image (filename specified by first argument) into image data matrix
        if (!(file = fopen(argv[1], "rb"))) {
            cout << "Cannot open file: " << argv[1] << endl;
            exit(1);
        }
        fread(Imagedata, sizeof(unsigned char), Sizerow * Sizecol* BytesPerPixel, file);
        fclose(file);

///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

//extension
        for (int i = 1; i < Sizerow + 1; i++) {
            for (int j = 1; j < Sizecol + 1; j++) {
                Imagedatabig[i][j][0] = (float)Imagedata[i - 1][j - 1][0];
            }
        }
        for (int j = 0; j < Sizecol+1; j++) {
            Imagedatabig[0][j][0] = (float)Imagedata[0][j][0];
            Imagedatabig[Sizerow - 1][j][0] = (float)Imagedata[Sizerow][j][0];
        }
        for (int i = 0; i < Sizerow + 1; i++) {
            Imagedatabig[i][0][0] = (float)Imagedata[i][0][0];
            Imagedatabig[i][Sizecol + 1][0] = (float)Imagedata[i][Sizecol][0]; 
        }


//ES
        int count0=0;
        for (int i = 1; i < Sizerow+1; i++) {
            for (int j = 1; j < Sizecol+1; j++) {
                Imagedata1[i-1][j-1][0] =
                        Imagedatabig[i - 1][j - 1][0] * ES[0][0] + Imagedatabig[i - 1][j][0] * ES[0][1] +
                        Imagedatabig[i - 1][j + 1][0] * ES[0][2] +
                        Imagedatabig[i ][j - 1][0] * ES[1][0] + Imagedatabig[i ][j ][0] * ES[1][1] +
                        Imagedatabig[i ][j + 1][0] * ES[1][2] +
                        Imagedatabig[i + 1][j - 1][0] * ES[2][0] + Imagedatabig[i + 1][j][0] * ES[2][1] +
                        Imagedatabig[i + 1][j + 1][0] * ES[2][2] ;
            }
        }
        for (int i=0;i<Sizerow;i++){
            for (int j=0;j<Sizecol;j++){
                Imagedata1[i][j][0]=Imagedata1[i][j][0]/8.0;
            }
        }
        for (int i=0;i<Sizerow;i++)
        {
            for (int j=0;j<Sizecol;j++)
            {
                int count=0;int sum=0;
                for (int p=i-x;p<i+x;p++)
                {
                    for (int q=j-x;q<j+x;q++)
                    {
                        if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                        {
                            sum+=Imagedata1[p][q][0];
                            count++;
                        }

                    }
                }
               featurevector[count0++][0]=sum/count;
            }
        }
//SE
    int count1=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata2[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * SE[0][0] + Imagedatabig[i - 1][j][0] * SE[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * SE[0][2] +
                    Imagedatabig[i ][j - 1][0] * SE[1][0] + Imagedatabig[i ][j ][0] * SE[1][1] +
                    Imagedatabig[i ][j + 1][0] * SE[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * SE[2][0] + Imagedatabig[i + 1][j][0] * SE[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * SE[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata2[i][j][0]=Imagedata2[i][j][0]/8.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata2[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count1++][1]=sum/count;
        }
    }
//EL
    int count2=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata3[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * EL[0][0] + Imagedatabig[i - 1][j][0] * EL[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * EL[0][2] +
                    Imagedatabig[i ][j - 1][0] * EL[1][0] + Imagedatabig[i ][j ][0] * EL[1][1] +
                    Imagedatabig[i ][j + 1][0] * EL[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * EL[2][0] + Imagedatabig[i + 1][j][0] * EL[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * EL[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata3[i][j][0]=Imagedata3[i][j][0]/8.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata3[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count2++][2]=sum/count;
        }
    }
//LE
    int count3=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata4[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * LE[0][0] + Imagedatabig[i - 1][j][0] * LE[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * LE[0][2] +
                    Imagedatabig[i ][j - 1][0] * LE[1][0] + Imagedatabig[i ][j ][0] * LE[1][1] +
                    Imagedatabig[i ][j + 1][0] * LE[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * LE[2][0] + Imagedatabig[i + 1][j][0] * LE[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * LE[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata4[i][j][0]=Imagedata4[i][j][0]/8.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata4[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count3++][3]=sum/count;
        }
    }
//SL
    int count4=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata5[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * SL[0][0] + Imagedatabig[i - 1][j][0] * SL[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * SL[0][2] +
                    Imagedatabig[i ][j - 1][0] * SL[1][0] + Imagedatabig[i ][j ][0] * SL[1][1] +
                    Imagedatabig[i ][j + 1][0] * SL[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * SL[2][0] + Imagedatabig[i + 1][j][0] * SL[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * SL[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata5[i][j][0]=Imagedata5[i][j][0]/16.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata5[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count4++][4]=sum/count;
        }
    }
//LS
    int count5=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata6[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * LS[0][0] + Imagedatabig[i - 1][j][0] * LS[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * LS[0][2] +
                    Imagedatabig[i ][j - 1][0] * LS[1][0] + Imagedatabig[i ][j ][0] * LS[1][1] +
                    Imagedatabig[i ][j + 1][0] * LS[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * LS[2][0] + Imagedatabig[i + 1][j][0] * LS[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * LS[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata6[i][j][0]=Imagedata6[i][j][0]/16.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata6[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count5++][5]=sum/count;
        }
    }
//EE
    int count6=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata7[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * EE[0][0] + Imagedatabig[i - 1][j][0] * EE[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * EE[0][2] +
                    Imagedatabig[i ][j - 1][0] * EE[1][0] + Imagedatabig[i ][j ][0] * EE[1][1] +
                    Imagedatabig[i ][j + 1][0] * EE[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * EE[2][0] + Imagedatabig[i + 1][j][0] * EE[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * EE[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata7[i][j][0]=Imagedata7[i][j][0]/4.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata7[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count6++][6]=sum/count;
        }
    }
//SS
    int count7=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata8[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * SS[0][0] + Imagedatabig[i - 1][j][0] * SS[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * SS[0][2] +
                    Imagedatabig[i ][j - 1][0] * SS[1][0] + Imagedatabig[i ][j ][0] * SS[1][1] +
                    Imagedatabig[i ][j + 1][0] * SS[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * SS[2][0] + Imagedatabig[i + 1][j][0] * SS[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * SS[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata8[i][j][0]=Imagedata8[i][j][0]/16.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata8[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count7++][7]=sum/count;
        }
    }
//LL
    int count8=0;
    for (int i = 1; i < Sizerow+1; i++) {
        for (int j = 1; j < Sizecol+1; j++) {
            Imagedata9[i-1][j-1][0] =
                    Imagedatabig[i - 1][j - 1][0] * LL[0][0] + Imagedatabig[i - 1][j][0] * LL[0][1] +
                    Imagedatabig[i - 1][j + 1][0] * LL[0][2] +
                    Imagedatabig[i ][j - 1][0] * LL[1][0] + Imagedatabig[i ][j ][0] * LL[1][1] +
                    Imagedatabig[i ][j + 1][0] * LL[1][2] +
                    Imagedatabig[i + 1][j - 1][0] * LL[2][0] + Imagedatabig[i + 1][j][0] * LL[2][1] +
                    Imagedatabig[i + 1][j + 1][0] * LL[2][2] ;
        }
    }
    for (int i=0;i<Sizerow;i++){
        for (int j=0;j<Sizecol;j++){
            Imagedata9[i][j][0]=Imagedata9[i][j][0]/16.0;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            int count=0;int sum=0;
            for (int p=i-x;p<i+x;p++)
            {
                for (int q=j-x;q<j+x;q++)
                {
                    if ((p>0)&&(p<Sizerow)&&(q>0)&&(q<Sizecol))
                    {
                        sum+=Imagedata9[p][q][0];
                        count++;
                    }

                }
            }
            featurevector[count8++][8]=sum/count;
        }
    }


    //KMEAN

    //initial
    int k = 6;
    int num[6] = {};
    int cluster[6][300*450] ;
    for(int i=0;i<k;i++){
        for (int j=0;j<135000;j++)
            cluster[i][j]=-1;
    }
    int center[6][9] = {};
    for(int i=0;i<k;i++){
        for (int j=0;j<9;j++)
            center[i][j]=0;
    }

    for (int i=0;i<9;i++) {
        center[0][i] = featurevector[0][i];
    }
    cluster[0][0] = 0;
    num[0] = 0;

    for (int i=0;i<9;i++) {
        center[1][i] = featurevector[14208][i];
    }
    cluster[1][0] = 14208;
    num[1] = 0;

    for (int i=0;i<9;i++) {
        center[2][i] = featurevector[40000][i];
    }
    cluster[2][0] = 40000;
    num[2] = 0;

    for (int i=0;i<9;i++) {
        center[3][i] = featurevector[35000][i];
    }
    cluster[3][0] =35000 ;
    num[3] = 0;
    
    for (int i=0;i<9;i++) {
        center[4][i] = featurevector[183600][i];
    }
    cluster[4][0] = 183600;
    num[4] = 0;

    for (int i=0;i<9;i++) {
        center[5][i] = featurevector[62752][i];
    }
    cluster[5][0] =62752 ;
    num[5] = 0;
    

    int errornew[6] = {};
    int errorold[6] = {};
    int iter=0;

    do{
        for (int b =0; b < 450*600; b++) {
            int d[6] = {};
            d[0] = sqrt(pow((featurevector[b][0] - center[0][0]), 2) + pow((featurevector[b][1] - center[0][1]), 2) +
                        pow((featurevector[b][2] - center[0][2]), 2) + pow((featurevector[b][3] - center[0][3]), 2) +
                        pow((featurevector[b][4] - center[0][4]), 2) + pow((featurevector[b][5] - center[0][5]), 2) +
                        pow((featurevector[b][6] - center[0][6]), 2) + pow((featurevector[b][7] - center[0][7]), 2) +
                        pow((featurevector[b][8] - center[0][8]), 2));
            d[1] = sqrt(pow((featurevector[b][0] - center[1][0]), 2) + pow((featurevector[b][1] - center[1][1]), 2) +
                        pow((featurevector[b][2] - center[1][2]), 2) + pow((featurevector[b][3] - center[1][3]), 2) +
                        pow((featurevector[b][4] - center[1][4]), 2) + pow((featurevector[b][5] - center[1][5]), 2) +
                        pow((featurevector[b][6] - center[1][6]), 2) + pow((featurevector[b][7] - center[1][7]), 2) +
                        pow((featurevector[b][8] - center[1][8]), 2));
            d[2] = sqrt(pow((featurevector[b][0] - center[2][0]), 2) + pow((featurevector[b][1] - center[2][1]), 2) +
                        pow((featurevector[b][2] - center[2][2]), 2) + pow((featurevector[b][3] - center[2][3]), 2) +
                        pow((featurevector[b][4] - center[2][4]), 2) + pow((featurevector[b][5] - center[2][5]), 2) +
                        pow((featurevector[b][6] - center[2][6]), 2) + pow((featurevector[b][7] - center[2][7]), 2) +
                        pow((featurevector[b][8] - center[2][8]), 2));
            d[3] = sqrt(pow((featurevector[b][0] - center[3][0]), 2) + pow((featurevector[b][1] - center[3][1]), 2) +
                        pow((featurevector[b][2] - center[3][2]), 2) + pow((featurevector[b][3] - center[3][3]), 2) +
                        pow((featurevector[b][4] - center[3][4]), 2) + pow((featurevector[b][5] - center[3][5]), 2) +
                        pow((featurevector[b][6] - center[3][6]), 2) + pow((featurevector[b][7] - center[3][7]), 2) +
                        pow((featurevector[b][8] - center[3][8]), 2));
            d[4] = sqrt(pow((featurevector[b][0] - center[4][0]), 2) + pow((featurevector[b][1] - center[4][1]), 2) +
                        pow((featurevector[b][2] - center[4][2]), 2) + pow((featurevector[b][3] - center[4][3]), 2) +
                        pow((featurevector[b][4] - center[4][4]), 2) + pow((featurevector[b][5] - center[4][5]), 2) +
                        pow((featurevector[b][6] - center[4][6]), 2) + pow((featurevector[b][7] - center[4][7]), 2) +
                        pow((featurevector[b][8] - center[4][8]), 2));
            d[5] = sqrt(pow((featurevector[b][0] - center[5][0]), 2) + pow((featurevector[b][1] - center[5][1]), 2) +
                        pow((featurevector[b][2] - center[5][2]), 2) + pow((featurevector[b][3] - center[5][3]), 2) +
                        pow((featurevector[b][4] - center[5][4]), 2) + pow((featurevector[b][5] - center[5][5]), 2) +
                        pow((featurevector[b][6] - center[5][6]), 2) + pow((featurevector[b][7] - center[5][7]), 2) +
                        pow((featurevector[b][8] - center[5][8]), 2));
            //find min distance
            int min = d[0];
            int key = 0;
            for (int j = 1; j < k; j++) {
                if (d[j] < min) {
                    min = d[j];
                    key = j;
                }
            }
            int o=0;
            for (int i=0;i<450*300;i++)
            {
                if (cluster[key][i]==b)
                    o++;
            }
            if (o==0)
            {
                num[key]++;
                cluster[key][num[key]] = b;
            }
        }

        //error

        for (int p = 0; p < k; p++) {
            int distance=0;
            for (int l = 0; l < num[p]+1; l++) {
                int d=0;
                for (int i = 0; i < 9; i++) {
                    d=d+pow((featurevector[cluster[p][l]][i] - center[p][i]), 2);
                }
                distance+=d;
            }
            errorold[p]=distance ;
        }

        //recenter
        for (int p = 0; p < k; p++) {
            int sum[9] = {};
            for (int i = 0; i < 9; i++) {
                for (int l = 0; l < num[p]+1; l++) {
                    sum[i] = sum[i] + featurevector[cluster[p][l]][i];
                }
                center[p][i] = sum[i] / (num[p]+1);
            }
        }
        //error

        for (int p = 0; p < k; p++) {
            int distance=0;
            for (int l = 0; l < num[p]+1; l++) {
                int d = 0;
                for (int i = 0; i < 9; i++) {
                    d = d+pow((featurevector[cluster[p][l]][i] - center[p][i]), 2);
                }
                distance+= d;
            }
            errornew[p]=distance;
        }
        iter++;
    } while(((errorold[0]-errornew[0])+(errorold[1]-errornew[1])+(errorold[2]-errornew[2])+(errorold[3]-errornew[3])+(errorold[4]-errornew[4])+(errorold[5]-errornew[5])>1));


    // Write image data (filename specified by second argument) from image data matrix

    for (int i=0;i<=num[0];i++) {

            int row = floor(cluster[0][i] / 600);
            int col = cluster[0][i] % 600;
            Imagedataout[row][col][0] = 0;

    }
    for (int i=0;i<=num[1];i++) {

            int row = floor(cluster[1][i]/ 600);
            int col = cluster[1][i] % 600;
            Imagedataout[row][col][0] = 51;

    }
    for (int i=0;i<=num[2];i++) {

            int row= floor(cluster[2][i]/600);
            int col=cluster[2][i]%600;
        Imagedataout[row][col][0]=102;
    }
    for (int i=0;i<=num[3];i++) {

            int row= floor(cluster[3][i]/600);int col=cluster[3][i]%600;
        Imagedataout[row][col][0]=153;
    }
    for (int i=0;i<=num[4];i++) {

            int row= floor(cluster[4][i]/600);int col=cluster[4][i]%600;
        Imagedataout[row][col][0]=204;
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
             if ((Imagedataout[i][j][0]!=0)&&(Imagedataout[i][j][0]!=51)&&(Imagedataout[i][j][0]!=102)&&(Imagedataout[i][j][0]!=153)&&(Imagedataout[i][j][0]!=204))
                 Imagedataout[i][j][0]=255;
        }
    }
    /*for (int i=0;i<450*600;i++) {
        if (cluster[5][i] != -1){
            int row= floor(cluster[5][i]/450);int col=cluster[5][i]%450;
        Imagedataout[row][col][0]=255;}
    }*/

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedataout, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    return 0;

}
