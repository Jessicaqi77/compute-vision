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
    cout<<"work"<<endl;
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Sizerow=338;///change image size
    int Sizecol=600;
    int size=Sizerow*Sizecol;
    int rep[3][8]={};
    int Size;
    int windowsize = 3;
    int position = (windowsize - 1) / 2;
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
    unsigned char Imagedata1[Sizerow+1][Sizecol+1][BytesPerPixel];
    unsigned char Imagedatanew[Sizerow][Sizecol][BytesPerPixel];
    //int Imagedatanum[Sizerow][Sizecol][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix

    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);

    int* b=(int*)malloc(sizeof(int)*size*3);
    // 8 values representation
    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        int n=0;
        for(int i=0;i<Sizerow;i++)
        {
            for (int j = 0; j< Sizecol; j++)
            {
                *(b+n*3+channel)=Imagedata[i][j][channel];
                n++;
            }
        }
        int value_b[size];//current channel pixel value prepare for rank
        for(int bb=0;bb<size;bb++) {
            value_b[bb] = *(b+bb*3+channel);
        }
        sort(value_b,value_b+size);
        for(int cc=0;cc<size;cc++) {
            *(b+cc*3+channel) = value_b[cc];
        }
        for(int nn=0;nn<8;nn++)
        {
            int sum=0;
            for (int m=nn*size/8;m<(nn+1)*size/8;m++)
            {
                sum=sum+value_b[m];
            }
            rep[channel][nn]=sum/(size/8);
        }

    }
    // map grey scale value
    for (int channel=0;channel<BytesPerPixel;channel++)
    {
        int one=*(b+(size/8)*3+channel);
        int two=*(b+(size/4)*3+channel);
        int three=*(b+(3*size/8)*3+channel);
        int four=*(b+(size/2)*3+channel);
        int five=*(b+(5*size/8)*3+channel);
        int six=*(b+(3*size/4)*3+channel);
        int seven=*(b+(7*size/8)*3+channel);
        for (int p = 0; p < Sizerow; p++)
        {
            for (int q = 0; q < Sizecol; q++)
            {
                if (Imagedata[p][q][channel]<=one)
                {
                    Imagedatanew[p][q][channel] = 0;
                    Imagedataout[p][q][channel] = rep[channel][0];
                }
                if (Imagedata[p][q][channel]>one&&Imagedata[p][q][channel]<=two)
                {
                    Imagedatanew[p][q][channel]=1;
                    Imagedataout[p][q][channel]=rep[channel][1];
                }
                if (Imagedata[p][q][channel]>two&&Imagedata[p][q][channel]<=three)
                {
                    Imagedatanew[p][q][channel] = 2;
                    Imagedataout[p][q][channel] = rep[channel][2];
                }
                if (Imagedata[p][q][channel]>three&&Imagedata[p][q][channel]<=four)
                {
                    Imagedatanew[p][q][channel]=3;
                    Imagedataout[p][q][channel]=rep[channel][3];
                }
                if (Imagedata[p][q][channel]>four&&Imagedata[p][q][channel]<=five)
                {
                    Imagedatanew[p][q][channel] = 4;
                    Imagedataout[p][q][channel] = rep[channel][4];
                }
                if (Imagedata[p][q][channel]>five&&Imagedata[p][q][channel]<=six)
                {
                    Imagedatanew[p][q][channel] = 5;
                    Imagedataout[p][q][channel] = rep[channel][5];
                }
                if (Imagedata[p][q][channel]>six&&Imagedata[p][q][channel]<=seven)
                {
                    Imagedatanew[p][q][channel] = 6;
                    Imagedataout[p][q][channel] = rep[channel][6];
                }
                if (Imagedata[p][q][channel]>seven)
                {
                    Imagedatanew[p][q][channel] = 7;
                    Imagedataout[p][q][channel] = rep[channel][7];
                }


            }
        }
    }
    free(b);


// extension
    for (int channel=0;channel<BytesPerPixel;channel++)
    {

        for(int i=0;i<Sizerow;i++)
        {
            for (int j = 0; j < Sizecol; j++)
            {
                Imagedata1[i+1][j+1][channel] =(Imagedatanew[i][j][channel]);
                Imagedata1[0][j][channel] =(Imagedatanew[0][j][channel]);
                Imagedata1[i][0][channel] =(Imagedatanew[i][0][channel]);
            }
        }
    }

//replace the center value
    for (int i = 1; i < Sizerow+1 ; i++)
    {
        for (int j = 1; j< Sizecol+1;j++)
        {
            int color[8][8][8]={};
            for (int m = -1; m < windowsize - position; m++)
            {
                for (int n = -1; n < windowsize - position; n++)
                {

                    color[Imagedatanew[m+i][n+j][0]][Imagedatanew[m+i][n+j][1]][Imagedatanew[m+i][n+j][2]]+=1;
                }

            }

            int local1=Imagedatanew[i][j][0],local2=Imagedatanew[i][j][1],local3=Imagedatanew[i][j][2];
            int max=1;
            for (int o=0;o<8;o++ )
            {
                for (int p=0;p<8;p++ )
                {
                    for (int q=0;q<8;q++)
                    {
                        if (color[o][p][q]>max)
                        {
                            max=color[o][p][q];
                            local1=o;
                            local2=p;
                            local3=q;
                        }
                    }
                }
            }
            Imagedataout[i][j][0]=rep[0][local1];
            Imagedataout[i][j][1]=rep[1][local2];
            Imagedataout[i][j][2]=rep[2][local3];
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
    cout<<rep[0][0]<<" "<<rep[0][1]<<" "<<rep[0][2]<<" "<<rep[0][3]<<rep[0][4]<<" "<<rep[0][5]<<" "<<rep[0][6]<<" "<<rep[0][7]<<" "<<endl;
    cout<<rep[1][0]<<" "<<rep[1][1]<<" "<<rep[1][2]<<" "<<rep[1][3]<<rep[1][4]<<" "<<rep[1][5]<<" "<<rep[1][6]<<" "<<rep[1][7]<<" "<<endl;
    cout<<rep[2][0]<<" "<<rep[2][1]<<" "<<rep[2][2]<<" "<<rep[2][3]<<rep[2][4]<<" "<<rep[2][5]<<" "<<rep[2][6]<<" "<<rep[2][7]<<" "<<endl;
    return 0;
}




