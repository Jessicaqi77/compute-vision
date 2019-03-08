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
    int Sizenew=650;
    int newsize=650;
    int Sizeold=512;//Sizerow=Sizecol=Sizenold
    float r=(float)Sizenew/(float)Sizeold;
    int Size;

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
    unsigned char Imagedataold[Sizeold][Sizeold][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedataold, sizeof(unsigned char), Sizeold*Sizeold*BytesPerPixel, file);
    fclose(file);
    unsigned char Imagedatanew[newsize][newsize][BytesPerPixel];
    for(int i=0;i<Sizenew-1;i++) {
        for (int j = 0; j < Sizenew-1; j++) {
            float a=i/r,b=j/r;
            int x=int(a),y=int(b);
            float u=a-x,v=b-y;
            Imagedatanew[i][j][0] =(1-u)*(1-v)*Imagedataold[x][y][0]+(1-u)*v*Imagedataold[x][y+1][0]+u*(1-v)*Imagedataold[x+1][y][0]+u*v*Imagedataold[x+1][y+1][0];
            Imagedatanew[i][j][1] =(1-u)*(1-v)*Imagedataold[x][y][1]+(1-u)*v*Imagedataold[x][y+1][1]+u*(1-v)*Imagedataold[x+1][y][1]+u*v*Imagedataold[x+1][y+1][1];
            Imagedatanew[i][j][2] =(1-u)*(1-v)*Imagedataold[x][y][2]+(1-u)*v*Imagedataold[x][y+1][2]+u*(1-v)*Imagedataold[x+1][y][2]+u*v*Imagedataold[x+1][y+1][2];
        }
    }
    Imagedatanew[Sizenew-1][Sizenew-1][0]=Imagedataold[Sizeold-1][Sizeold-1][0];
    Imagedatanew[Sizenew-1][Sizenew-1][1]=Imagedataold[Sizeold-1][Sizeold-1][1];
    Imagedatanew[Sizenew-1][Sizenew-1][2]=Imagedataold[Sizeold-1][Sizeold-1][2];
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedatanew, sizeof(unsigned char), Sizenew*Sizenew*BytesPerPixel, file);
    fclose(file);

    return 0;
}

