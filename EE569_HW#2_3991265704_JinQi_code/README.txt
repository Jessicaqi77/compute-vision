#EE569 Homework Assignment #2
#Date February 24,2018
#Name: Jin Qi
#ID: 3991265704
#EMAIL: jinqi@usc.edu

Compiled on OS X10.10.5 CLION platform using C++ language with g++
Running format：g++ Filename.cpp -o Filename
                ./ filename parameter_1  parameter_2  parameter_3

The parameter_1 is the input image, parameter_2 is the output image,parameter_3 is number of BytesPerPixel
Before running any project, we need change the variable 'Sizecol''Sizerow' to be consistent with the input image size of parameter_1.

Problem1_a_1:
Filename: p1a_warping
Input parameters:puppy.raw p1a_puppy.raw 3
                 tiger.raw p1a_tiger.raw 3
                 panda.raw p1a_panda.raw 3
Running format: g++ p1a_warping.cpp -o p1a_warping
                ./ p1a_warping puppy.raw p1a_puppy.raw 3

Function:Do the image warping transformation to make a disk-like image

Problem1_a_2:
Filename: p1a_reverse
Input parameters:p1a_puppy.raw  p1a_puppyreverse.raw 3
                 p1a_tiger.raw  p1a_tigerreverse.raw 3
                 p1a_panda.raw  p1a_pandareverse.raw 3
Running format: g++ p1a_reverse.cpp -o p1a_reverse
                ./ p1a_reverse p1a_puppy.raw  p1a_puppyreverse.raw 3

Function:Do image reverse transformation to get the original image from warping one

Problem1_b:
Filename:p1b_homo
Input parameters:left.raw middle.raw right.raw homo.raw 3
Running format: g++ p1b_homo.cpp -o p1b_homo
                ./ p1b_homo left.raw middle.raw right.raw homo.raw 3
Function:Do image homographic transformation and image stitching to get panorama image


Problem2_a_1:
Filename:p2a_fixed
Input parameters:colorchecker.raw fixed.raw 1
Running format:g++ p2a_fixed.cpp -o p2a_fixed
               ./ p2a_fixed colorchecker.raw fixed.raw 1
Function: Get half-toning image by fixed threshold

Problem2_a_2:
Filename:p2a_random
Input parameters:colorchecker.raw random.raw 1
Running format:g++ p2a_random.cpp -o p2a_random
               ./ p2a_random colorchecker.raw random.raw 1
Function: Get half-toning image by random threshold


Problem2_a_3:
Filename:p2a_m2
Input parameters:colorchecker.raw p2a_matrix2.raw 1
Running format:g++ p2a_m2.cpp -o p2a_m2
               ./ p2a_m2 colorchecker.raw p2a_matrix2.raw 1
Function: Get half-toning image by bayer matrix I=2

Problem2_a_4:
Filename:p2a_m4
Input parameters:colorchecker.raw p2a_matrix4.raw 1
Running format:g++ p2a_m4.cpp -o p2a_m4
               ./ p2a_m4 colorchecker.raw p2a_matrix4.raw 1
Function: Get half-toning image by bayer matrix I=4

Problem2_a_5:
Filename:p2a_m8
Input parameters:colorchecker.raw p2a_matrix8.raw 1
Running format:g++ p2a_m8.cpp -o p2a_m8
               ./ p2a_m8 colorchecker.raw p2a_matrix8.raw 1
Function: Get half-toning image by bayer matrix I=8

Problem2_a_6:
Filename:p2a_val4
Input parameters:colorchecker.raw 4value.raw 1
Running format:g++ p2a_val4.cpp -o p2a_val4
               ./ p2a_val4 colorchecker.raw 4value.raw 1
Function: Get 4 intensity level image by bayer matrix I=8 dithering method

Problem2_b_1:
Filename:p2b_FS
Input parameters:colorchecker.raw p2b_errorFS.raw 1
Running format:g++ p2b_FS.cpp -o p2b_FS
               ./ p2b_FS colorchecker.raw p2b_errorFS.raw 1
Function: Get half-toning image by error diffusion FS matrix

Problem2_b_2:
Filename:p2b_JJN
Input parameters:colorchecker.raw p2b_errorJJN.raw 1
Running format:g++ p2b_JJN.cpp -o p2b_JJN
               ./ p2b_JJN colorchecker.raw p2b_errorJJN.raw 1
Function: Get half-toning image by error diffusion JJN matrix

Problem2_b_3:
Filename:p2b_S
Input parameters:colorchecker.raw p2b_errorS.raw 1
Running format:g++ p2b_S.cpp -o p2b_S
               ./ p2b_S colorchecker.raw p2b_errorS.raw 1
Function: Get half-toning image by error diffusion Stucki matrix

Problem2_c_1:
Filename:p2c_separate
Input parameters:colorchecker.raw separate.raw 3
Running format:g++ p2c_separate.cpp -o p2c_separate
               ./ p2c_separate colorchecker.raw separate.raw 3
Function: Get colore half-toning image by separate error diffusion

Problem2_c_2:
Filename:p2c_MBVQ
Input parameters:colorchecker.raw MBVQ.raw 3
Running format:g++ p2c_MBVQ.cpp -o p2c_MBVQ
               ./ p2c_MBVQ colorchecker.raw MBVQ.raw 3
Function: Get colore half-toning image by MBVQ method


Problem3_a:
Filename:p3a_countingstar
Input parameters:stars.raw p3a_star.raw 1
Running format:g++ p3a_countingstar.cpp -o p3a_countingstar
               ./ p3a_countingstar stars.raw p3a_star.raw 1
Function: Do image object shrinking and count object number


Problem3_b:
Filename:p3b_thinning
Input parameters:jigsaw_1.raw thinning.raw 1
Running format:g++ p3b_thinning.cpp -o p3b_thinning
               ./ p3b_thinning jigsaw_1.raw thinning.raw 1
Function: Do image object thinning

Problem3_c:
Filename:p3c_ske
Input parameters:jigsaw_2.raw ske.raw 1
Running format:g++ p3c_ske.cpp -o p3c_ske
               ./ p3c_ske jigsaw_2.raw ske.raw 1
Function: Do image object skeletonizing

Problem3_d_1:
Filename:p3d_counting
Input parameters:board.raw result.raw 1
Running format:g++ p3d_counting.cpp -o p3d_counting
               ./ p3d_counting board.raw result.raw 1
Function: Get the object number by connectivity component analysis

Problem3_d_2:
Filename:p3d_countingunique
Input parameters:board.raw result.raw 1
Running format:g++ p3d_countingunique.cpp -o p3d_counting
               ./ p3d_countingunique board.raw result.raw 1
Function: Get the unique object number
