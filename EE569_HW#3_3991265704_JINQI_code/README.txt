#EE569 Homework Assignment #3
#Date March 24,2018
#Name: Jin Qi
#ID: 3991265704
#EMAIL: jinqi@usc.edu

Compiled on OS X10.10.5 CLION platform using C++ language with g++
Running format：g++ Filename.cpp -o Filename
                ./ filename parameter

Before running any project, we need change the variable 'Sizecol''Sizerow' to be consistent with the input image size.

Problem1_a:
Filename:p1a_class
Input parameters:texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.raw 1
Running format: g++ p1a_class.cpp -o p1a_class
                ./ p1a_class texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.raw 1
Function:Make a classification of 12 texture images into 4 groups

Problem1_b:
Filename:p1b_segmentation
Input parameters:comb.raw p1b_seg.raw 1
Running format:g++ p1b_segmentation.cpp -o p1b_segmentation
               ./ p1b_segmentation comb.raw p1b_seg.raw 1
Function:Make a segmentation on a texture image into 6 regions

Problem1_c:
Filename:p1c_advanced
Input parameters:p1b_seg.raw p1_c.raw 1
Running format:g++ p1c_advanced.cpp -o p1c_advanced
               ./ p1c_advanced p1b_seg.raw p1_c.raw 1
Function:Improve the segmentation performance

Problem2_a_1:
Filename:p2a_1
Input parameters:Boat.raw p2a_sobel.raw
                 Boat_noisy.raw p2a_sobelnoisy.raw
Running format:g++ p2a_1.cpp -o p2a_1
               ./ p2a_1 Boat.raw p2a_sobel.raw
               g++ p2a_1.cpp -o p2a_1
               ./ p2a_1 Boat_noisy.raw p2a_sobelnoisy.raw
Function:Get the edge detection result by sobel operator
And if we we to get the X or Y direction normalized image, we need change the code  of the output part into 'Imagedatagxout' or'Imagedatagyout'

Problem2_a_2:
Filename:p2a_2
Input parameters:Boat.raw p2a_LOG.raw
                 Boat_noisy.raw p2a_LOGnoisy.raw
Running format:g++ p2a_2.cpp -o p2a_2
               ./ p2a_2 Boat.raw p2a_LOG.raw
               g++ p2a_2.cpp -o p2a_2
               ./ p2a_2 Boat_noisy.raw p2a_LOGnoisy.raw
Function:Get the edge detection result by LoG operator


Problem3_a:
Filename:p3a
Running format:g++ p3a.cpp -o p3a
               ./ p3a
Function:Find the feature points by SIFT or SURF

Problem3_b:
Filename:p3b
Running format:g++ p3b.cpp -o p3b
               ./ p3b
Function:Match two images using SIFT or SURF

Problem3_c:
Filename:p3c
Input parameters:bumblebee.jpg Optimus_Prime.jpg ferrari1.jpg ferrari_2.jpg
Running format:g++ p3c.cpp -o p3c
               ./ p3c bumblebee.jpg Optimus_Prime.jpg ferrari1.jpg ferrari_2.jpg
Function:Match the input image with other provided images using bag of word method
