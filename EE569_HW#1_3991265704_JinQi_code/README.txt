#EE569 Homework Assignment #1
#Date February 2,2018
#Name: Jin Qi
#ID: 3991265704
#EMAIL: jinqi@usc.edu

Compiled on OS X10.10.5 CLION platform using C++ language with g++
Running format：g++ Filename.cpp -o Filename
                ./ filename parameter_1  parameter_2  parameter_3

The parameter_1 is the input image, parameter_2 is the output image,parameter_3 is number of BytesPerPixel
Before running any project, we need change the variable 'Sizecol''Sizerow' to be consistent with the input image size of parameter_1.

Problem1_a1_1:
File name:P1_gray1.cpp
Input parameters:Tiffany.raw P1_Tiffany1.raw 3
Function:Change color space from RGB to grayscale using lightness method

Problem1_a1_2:
File name:P1_gray2.cpp
Input parameters:Tiffany.raw P1_Tiffany2.raw 3
Function:Change color space from RGB to grayscale using average method


Problem1_a1_3:
File name:P1_gray3.cpp
Input parameters:Tiffany.raw P1_Tiffany3.raw 3
Function:Change color space from RGB to grayscale using luminosity method


Problem1_a2:
File name:P1_CMY.cpp
Input parameters:(1) Bear.raw  P1_bearout.raw 3
(2)Dance.raw P1_danceout.raw 3
Function:Change color space from RGB to CMY(K)

Problem1_b:
File name:P1_resize.cpp
Input parameters:Airplane.raw P1_Airplaneout 3
Function:Resize an image using bilinear interpolation method

Problem2_a_11:
File name:P2_transferfunction.cpp
Input parameters:Desk.raw P2_TF.raw 3
Function:Histogram equalization using transfer function method

Problem2_a_2:
File name:P2_CPF.cpp
Input parameters:Desk.raw P2_CPF.raw 3
Function: Histogram equalization using cumulative-probability-based method

Problem2_b_1:
File name:P2_64value.cpp
Input parameters:(1)Trojans.raw P2_Trojans64.raw 3
(2)Star_Wars.raw P2_Starwars64value.raw 3
Function: Quantize an image to 64-color

Problem2_b_2:
File name:P2_oil.cpp
Input parameters:(1)Trojans.raw output.raw 3
(2Star_Wars.raw output.raw 3
Function: Create oil effect, and we can change window size to get different visual effect

Problem2_b_3:
File name:P2_512value.cpp
Input parameters:(1)Trojans.raw output.raw 3
(2)Star_Wars.raw output.raw 3
Function: Quantize an image to 512-color and oil effect

Problem2_c:
File name:P2_film.cpp
Input parameters:Girl.raw P2_girl.raw 3
Function: Create film effect

Problem3_a_1:
File name:P3_Median.cpp
Input parameters:Lena_mixed.raw P3_denosingmedian_N=3.raw 3
Function: Noise remove by Median , and in the project we can change window size 'windowsize' to get different window mask and performance


Problem3_a_2:
File name:P3_Gaussian.cpp
Input parameters:Lena_mixed.raw output.raw 3
Function: Noise remove by Gaussian filter

Problem3_performance:
File name:P3_psnr.cpp
Input parameters:(1)Lena.raw P3_denosingmedian_N=3 3
(2) House.raw P3_house_parta 1
Function:Calculate PSNR, and the parameter_1 is the original image, the parameter_2 can be the image that has already be de-noising from the original one
