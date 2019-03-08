
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
    int Sizerow = 480;
    int Sizecol = 640;//Sizerow=Sizecol=Size
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
    unsigned char Imagedataone[Sizerow][Sizecol][BytesPerPixel];
    unsigned char Imagedatatwo[Sizerow][Sizecol][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Sizerow * Sizecol * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int pattern[58][9] = {{0, 0, 1, 0, 1, 0, 0, 0, 0},
                          {1, 0, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 0, 1},
                          {0, 0, 0, 0, 1, 1, 0, 0, 0},
                          {0, 1, 0, 0, 1, 0, 0, 0, 0},
                          {0, 0, 0, 1, 1, 0, 0, 0, 0},
                          {0, 0, 0, 0, 1, 0, 0, 1, 0},
                          {1, 0, 1, 1, 1, 1, 1, 1, 1},
                          {0, 0, 1, 0, 1, 1, 0, 0, 0},
                          {0, 1, 1, 0, 1, 0, 0, 0, 0},
                          {1, 1, 0, 0, 1, 0, 0, 0, 0},
                          {1, 0, 0, 1, 1, 0, 0, 0, 0},
                          {0, 0, 0, 1, 1, 0, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 1, 1, 0},
                          {0, 0, 0, 0, 1, 0, 0, 1, 1},
                          {0, 0, 0, 0, 1, 1, 0, 0, 1},
                          {0, 0, 1, 0, 1, 1, 0, 0, 1},
                          {1, 1, 1, 0, 1, 0, 0, 0, 0},
                          {1, 0, 0, 1, 1, 0, 1, 0, 0},
                          {0, 0, 0, 0, 1, 0, 1, 1, 1},
                          {1, 1, 0, 0, 1, 1, 0, 0, 0},
                          {0, 1, 0, 0, 1, 1, 0, 0, 1},
                          {0, 1, 1, 1, 1, 0, 0, 0, 0},
                          {0, 0, 1, 0, 1, 1, 0, 1, 0},
                          {0, 1, 1, 0, 1, 1, 0, 0, 0},
                          {1, 1, 0, 1, 1, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 0, 1, 1, 0},
                          {1, 1, 0, 1, 1, 0, 1, 1, 1},
                          {1, 0, 0, 1, 1, 1, 1, 1, 1},
                          {1, 1, 0, 1, 1, 0, 1, 0, 0},
                          {1, 0, 0, 1, 1, 0, 1, 1, 0},
                          {0, 0, 0, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 0, 1, 1, 0, 1, 1},
                          {0, 1, 1, 0, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 0, 0, 1},
                          {0, 0, 0, 1, 1, 0, 1, 1, 1},
                          {0, 0, 0, 0, 1, 1, 1, 1, 1},
                          {0, 0, 1, 0, 1, 1, 0, 1, 1},
                          {1, 1, 1, 0, 1, 1, 0, 0, 1},
                          {1, 1, 1, 1, 1, 0, 1, 0, 0},
                          {1, 0, 0, 1, 1, 0, 1, 1, 1},
                          {0, 0, 1, 0, 1, 1, 1, 1, 1},
                          {0, 1, 1, 0, 1, 1, 0, 1, 1},
                          {1, 1, 1, 1, 1, 1, 0, 0, 0},
                          {1, 1, 0, 1, 1, 0, 1, 1, 0},
                          {0, 0, 0, 1, 1, 0, 1, 1, 0},
                          {0, 0, 0, 0, 1, 1, 0, 1, 1},
                          {1, 1, 0, 0, 1, 1, 0, 0, 1},
                          {0, 1, 1, 1, 1, 0, 1, 0, 0},
                          {1, 1, 1, 0, 1, 1, 0, 0, 0},
                          {0, 1, 1, 0, 1, 1, 0, 0, 1},
                          {1, 1, 1, 1, 1, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 0, 0},
                          {0, 0, 1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 0, 1, 1, 1, 1, 1},
                          {1, 1, 1, 1, 1, 1, 1, 0, 1},
                          {1, 1, 1, 1, 1, 0, 1, 1, 1}};

    string patterntwo[320] = {"001010000", "100010000", "000010010", "000011000",
                              "001011000", "011010000", "110010000", "100110000", "000110100", "000010110", "000010011",
                              "000011001",
                              "011110000", "110011000", "010011001", "001011010", "110110000", "111111111",
                              "011010100", "001011100", "001110100", "001110110", "001010110", "110010001", "100110001",
                              "100011011", "100010011", "100011001",
                              "010111000", "110111100", "010111000", "011111001", "000111010", "001111011", "000111010",
                              "100111110",
                              "010110010", "111110010", "010110010", "010110111", "010011010", "010011111", "010011010",
                              "111011010",
                              "010011100", "110011101", "010110001", "011110101", "001110010", "101110011", "100011010",
                              "101011110",
                              "101010010", "101010011", "101010100", "101010101", "101010110", "101010111",
                              "111111010", "111111011", "111111100", "111111101", "111111110", "111111111",
                              "110111110", "110111111", "111110110", "111110111", "111111110", "111111111",
                              "100011100", "100011101", "101010100", "101010101", "101011100", "101011101",
                              "010111111", "011111111", "100111111", "101111111", "110111111", "111111111",
                              "010010101", "011010101", "100010101", "101010101", "110010101", "111010101",
                              "011111011", "011111111", "111011011", "111011111", "111111011", "111111111",
                              "001110001", "001110101", "101010001", "101010101", "101110001", "101110101",
                              "111111100", "111111101", "110110111", "110111110", "110111111", "111110110", "111110111",
                              "111111110", "111111111", "101010100",
                              "101010010", "101010110", "101010001", "101010101", "101010011", "101010111", "101011100",
                              "101011010", "101011110", "101011001",
                              "101011101", "101011011", "101011111", "111010100", "111010010", "111010110", "111010001",
                              "111010101", "111010011", "111010111",
                              "111011100", "111011010", "111011110", "111011001", "111011101", "111011011", "111011111",
                              "101110100", "101110010", "101110110",
                              "101110001", "101110101", "101110011", "101110111", "101111100", "101111010", "101111110",
                              "101111001", "101111101", "101111011",
                              "101111111", "111110100", "111110010", "111110110", "111110001", "111110101", "111110011",
                              "111110111", "111111100", "111111010",
                              "111111110", "111111001", "111111101", "111111011", "111111111", "001010101", "001110001",
                              "001110101", "101010001", "101010101",
                              "101110001", "101110101", "001011101", "001111001", "001111101", "101011001", "101011101",
                              "101111001", "101111101", "001010111",
                              "001110011", "001110111", "101010011", "101010111", "101110011", "101110111", "001011111",
                              "001111011", "001111111", "101011011",
                              "101011111", "101111011", "101111111", "011010101", "011110001", "011110101", "111010001",
                              "111010101", "111110001", "111110101",
                              "011011101", "011111001", "011111101", "111011001", "111011101", "111111001", "111111101",
                              "011010111", "011110011", "011110111",
                              "111010011", "111010111", "111110011", "111110111", "011011111", "011111011", "011111111",
                              "111011011", "111011111", "111111011",
                              "111111111", "001010101", "010010101", "011010101", "100010101", "101010101", "110010101",
                              "111010101", "001011101", "010011101",
                              "011011101", "100011101", "101011101", "110011101", "111011101", "001010111", "010010111",
                              "011010111", "100010111", "101010111",
                              "110010111", "111010111", "001011111", "010011111", "011011111", "100011111", "101011111",
                              "110011111", "111011111", "001110101",
                              "010110101", "011110101", "100110101", "101110101", "110110101", "111110101", "001111101",
                              "010111101", "011111101", "100111101",
                              "101111101", "110111101", "111111101", "001110111", "010110111", "011110111", "100110111",
                              "101110111", "110110111", "111110111",
                              "001111111", "010111111", "011111111", "100111111", "101111111", "110111111", "111111111",
                              "001110010", "001110011", "101110010",
                              "101110011", "010110001", "011110001", "010110101", "011110101", "010011100", "010011101",
                              "110011100", "110011101", "100011010",
                              "101011010", "100011110", "101011110", "110110000", "110110001", "110111000", "110111001",
                              "111110000", "111110001", "111111000",
                              "111111001", "110110010", "110110011", "110111010", "110111011", "111110010", "111110011",
                              "111111010", "111111011", "110110100",
                              "110110101", "110111100", "110111101", "111110100", "111110101", "111111100", "111111101",
                              "110110110", "110110111", "110111110"
    };

    //create binary image
    for (int i = 0; i < Sizerow; i++) {
        for (int j = 0; j < Sizecol; j++) {
            if (Imagedata[i][j][0] < 71)
                Imagedata[i][j][0] = 0;
            else Imagedata[i][j][0] = 1;
        }
    }
    int starpre[20]={};
    int star = 1;
    int N = 1;

    while (star != starpre[N-1])
    {
        N++;//iteration
        //first
        for (int i = 1; i < Sizerow - 1; i++)//scan pixel
        {
            for (int j = 1; j < Sizecol - 1; j++) {
                if (Imagedata[i][j][0] == 1) {

                    int temp[9];
                    int count = 0;
                    temp[0] = Imagedata[i - 1][j - 1][0];
                    temp[1] = Imagedata[i - 1][j][0];
                    temp[2] = Imagedata[i - 1][j + 1][0];
                    temp[3] = Imagedata[i][j - 1][0];
                    temp[4] = Imagedata[i][j][0];
                    temp[5] = Imagedata[i][j + 1][0];
                    temp[6] = Imagedata[i + 1][j - 1][0];
                    temp[7] = Imagedata[i + 1][j][0];
                    temp[8] = Imagedata[i + 1][j + 1][0];
                    bool key = false;
                    for (int p = 0; p < 58; p++) {
                        count = 0;
                        for (int q = 0; q < 9; q++) {
                            if (temp[q] == pattern[p][q])// compare
                                count++;
                        }
                        if (count == 9)//hit
                        {
                            Imagedataone[i][j][0] = 1;
                            key = true;

                        }

                    }
                    if (!key) {
                        Imagedataone[i][j][0] = 0;
                    }
                } else { Imagedataone[i][j][0] = Imagedata[i][j][0]; }
            }
        }
        // second
        for (int l = 1; l < Sizerow - 1; l++) {
            for (int m = 1; m < Sizecol - 1; m++) {
                if (Imagedataone[l][m][0] == 1) {

                    int temp2[9];
                    int count2 = 0;
                    temp2[0] = Imagedataone[l - 1][m - 1][0];
                    temp2[1] = Imagedataone[l - 1][m][0];
                    temp2[2] = Imagedataone[l - 1][m + 1][0];
                    temp2[3] = Imagedataone[l][m - 1][0];
                    temp2[4] = Imagedataone[l][m][0];
                    temp2[5] = Imagedataone[l][m + 1][0];
                    temp2[6] = Imagedataone[l + 1][m - 1][0];
                    temp2[7] = Imagedataone[l + 1][m][0];
                    temp2[8] = Imagedataone[l + 1][m + 1][0];
                    for (int k = 0; k < 320; k++) {
                        string s1;
                        for (int h = 0; h < 9; h++) {
                            if (temp2[h] == 0) { s1.append("0"); }
                            else { s1.append("1"); }
                        }
                        if (s1 == patterntwo[k])//hit
                        {
                            count2++;
                        }
                    }
                    if (count2 != 0)
                        Imagedatatwo[l][m][0] = Imagedata[l][m][0];
                    else Imagedatatwo[l][m][0] = 0;

                } else { Imagedatatwo[l][m][0] = Imagedata[l][m][0]; }
            }
        }

        for (int u = 1; u < Sizerow - 1; u++)//update
        {
            for (int v = 1; v < Sizecol - 1; v++) {
                Imagedata[u][v][0] = Imagedatatwo[u][v][0];
            }
        }
        //counting
        star = 0;
        for (int e = 0; e < Sizerow; e++) {
            for (int r = 0; r < Sizecol; r++) {
                if (Imagedata[e][r][0] == 1) {
                    ++star;
                    //Imagedata[e][r][0] = 255;
                }
            }
            starpre [N]= star;
        }
    }

    for (int i=0;i<Sizerow;i++)
    {
        for (int j=0;j<Sizecol;j++)
        {
            if (Imagedata[i][j][0] == 1) {
                Imagedata[i][j][0] = 255;
            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Sizerow*Sizecol*BytesPerPixel, file);
    fclose(file);
     cout<<"the number of stars"<<" : "<<star<<endl;
     cout<<"the iteration time is : "<<N-2<<endl;
    return 0;
}

