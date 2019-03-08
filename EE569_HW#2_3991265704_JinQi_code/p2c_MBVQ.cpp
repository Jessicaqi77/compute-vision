
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
const int Sizenew = 700;

float  Imagedatanum[Sizenew][Sizenew][3];
unsigned char Imagedatanew[Sizenew][Sizenew][3];

int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Size = 700;//Sizerow=Sizecol=Size


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
    unsigned char Imagedata[Size][Size][BytesPerPixel];
    //float  Imagedatanum[Size][Size][BytesPerPixel];
    //unsigned char Imagedatanew[Size][Size][BytesPerPixel];


    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size * Size * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    for (int channel=0;channel<3;channel++)
    {
        for (int i=0;i<Size;i++)
        {
            for (int j=0;j<Size;j++)
            {
                //Imagedata[i][j][channel]=255-Imagedata[i][j][channel];
                Imagedatanum[i][j][channel]=1-((float)Imagedata[i][j][channel])/255.0;
            }
        }
    }
    float d[8]={};
    for (int i=1;i<Size-1;i++)
    {
        for (int j=1;j<Size-1;j++)
        {

            d[0]=Imagedatanum[i][j][0]*Imagedatanum[i][j][0]+Imagedatanum[i][j][1]*Imagedatanum[i][j][1]+Imagedatanum[i][j][2]*Imagedatanum[i][j][2];

            d[1]=Imagedatanum[i][j][0]*Imagedatanum[i][j][0]+Imagedatanum[i][j][1]*Imagedatanum[i][j][1]+(Imagedatanum[i][j][2]-1)*(Imagedatanum[i][j][2]-1);

            d[2]=Imagedatanum[i][j][0]*Imagedatanum[i][j][0]+(Imagedatanum[i][j][1]-1)*(Imagedatanum[i][j][1]-1)+Imagedatanum[i][j][2]*Imagedatanum[i][j][2];

            d[3]=Imagedatanum[i][j][0]*Imagedatanum[i][j][0]+(Imagedatanum[i][j][1]-1)*(Imagedatanum[i][j][1]-1)+(Imagedatanum[i][j][2]-1)*(Imagedatanum[i][j][2]-1);

            d[4]=(Imagedatanum[i][j][0]-1)*(Imagedatanum[i][j][0]-1)+Imagedatanum[i][j][1]*Imagedatanum[i][j][1]+Imagedatanum[i][j][2]*Imagedatanum[i][j][2];

            d[5]=(Imagedatanum[i][j][0]-1)*(Imagedatanum[i][j][0]-1)+Imagedatanum[i][j][1]*Imagedatanum[i][j][1]+(Imagedatanum[i][j][2]-1)*(Imagedatanum[i][j][2]-1);

            d[6]=(Imagedatanum[i][j][0]-1)*(Imagedatanum[i][j][0]-1)+(Imagedatanum[i][j][1]-1)*(Imagedatanum[i][j][1]-1)+Imagedatanum[i][j][2]*Imagedatanum[i][j][2];

            d[7]=(Imagedatanum[i][j][0]-1)*(Imagedatanum[i][j][0]-1)+(Imagedatanum[i][j][1]-1)*(Imagedatanum[i][j][1]-1)+(Imagedatanum[i][j][2]-1)*(Imagedatanum[i][j][2]-1);

            //find min distance
            int count=0;int min=d[0];
            for (int k=1;k<8;k++)
            {
                if (d[k]<min)
                {
                    count = k;
                    min=d[k];
                }
            }
            float error;
                if (count== 0)
                {
                    Imagedatanew[i][j][0] = 0;
                    Imagedatanew[i][j][1] = 0;
                    Imagedatanew[i][j][2] = 0;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j + 1][channel] = Imagedatanum[i][j + 1][channel] + (7.0 * error )/ 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +  error/ 16.0;
                    }
                }

            else if (count==1)
                {
                    Imagedatanew[i][j][0] = 0;
                    Imagedatanew[i][j][1] = 0;
                    Imagedatanew[i][j][2] = 1;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j+1][channel] = Imagedatanum[i][j +1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +  error / 16.0;
                    }
                    Imagedatanew[i][j][2] = 255;
                }

                else if (count==2)
                {
                    Imagedatanew[i][j][0] = 0;
                    Imagedatanew[i][j][1] = 1;
                    Imagedatanew[i][j][2] = 0;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j+ 1][channel] = Imagedatanum[i][j +1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +  error/ 16.0;
                    }
                    Imagedatanew[i][j][1] = 255;
                }
                else if (count==3)
                {
                    Imagedatanew[i][j][0] = 0;
                    Imagedatanew[i][j][1] = 1;
                    Imagedatanew[i][j][2] = 1;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j +1][channel] = Imagedatanum[i][j + 1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +  error / 16.0;
                    }
                    Imagedatanew[i][j][1] = 255;Imagedatanew[i][j][2] = 255;
                }

                else if (count==4)
                {
                    Imagedatanew[i][j][0] = 1;
                    Imagedatanew[i][j][1] = 0;
                    Imagedatanew[i][j][2] = 0;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j + 1][channel] = Imagedatanum[i][j +1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] + error / 16.0;
                    }
                    Imagedatanew[i][j][0] = 255;
                }

                else if (count==5)
                {
                    Imagedatanew[i][j][0] = 1;
                    Imagedatanew[i][j][1] = 0;
                    Imagedatanew[i][j][2] = 1;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j + 1][channel] = Imagedatanum[i][j + 1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +   error / 16.0;
                    }
                    Imagedatanew[i][j][0] = 255; Imagedatanew[i][j][2] = 255;
                }

                else if (count==6)
                {
                    Imagedatanew[i][j][0] = 1;
                    Imagedatanew[i][j][1] = 1;
                    Imagedatanew[i][j][2] = 0;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j + 1][channel] = Imagedatanum[i][j + 1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] +  error/ 16.0;
                    }
                    Imagedatanew[i][j][0] = 255;Imagedatanew[i][j][1] = 255;
                }
                else if (count==7)
                {
                    Imagedatanew[i][j][0] = 1;
                    Imagedatanew[i][j][1] = 1;
                    Imagedatanew[i][j][2] = 1;
                    for (int channel = 0; channel < 3; channel++)
                    {
                        error = Imagedatanum[i][j][channel] - Imagedatanew[i][j][channel];
                        Imagedatanum[i][j + 1][channel] = Imagedatanum[i][j + 1][channel] + (7.0 * error) / 16.0;
                        Imagedatanum[i + 1][j - 1][channel] = Imagedatanum[i + 1][j - 1][channel] + (3.0 * error) / 16.0;
                        Imagedatanum[i + 1][j][channel] = Imagedatanum[i + 1][j][channel] + (5.0 * error) / 16.0;
                        Imagedatanum[i + 1][j + 1][channel] = Imagedatanum[i + 1][j + 1][channel] + error / 16.0;
                    }
                    Imagedatanew[i][j][0] = 255;Imagedatanew[i][j][1] = 255;Imagedatanew[i][j][2] = 255;
                }

        }
    }

    for (int channel=0;channel<3;channel++)
    {
        for (int i=0;i<Size;i++)
        {
            for (int j=0;j<Size;j++)
            {
                Imagedatanew[i][j][channel]=255-Imagedatanew[i][j][channel];

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
