#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
//bumblebee.jpg Optimus_Prime.jpg ferrari1.jpg ferrari_2.jpg
using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void readme();
double *histo(Mat des1, Mat dictionary);
double* d_array(int length) {double *arr = new double[length];	for (int i = 0; i < length; i++) {		arr[i] = 0;	}	return arr;}

/** @function main */
int main(int argc, char** argv)
{

    Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);//bumblebee
    Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);//optimus
    Mat img_3 = imread(argv[3], IMREAD_GRAYSCALE);//ferrali
    Mat img_4 = imread(argv[4], IMREAD_GRAYSCALE);//ferrali_2

    if (!img_1.data || !img_2.data || !img_3.data || !img_4.data)
    {
        std::cout << " --(!) Error reading images " << std::endl; return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 3000;
    //int minHessian1 = 9000;
    Ptr<SIFT> detector = SIFT::create(minHessian);
    Ptr<SURF> detector1 = SURF::create(minHessian);

    std::vector<KeyPoint> keypoints_sift1, keypoints_sift2, keypoints_surf1, keypoints_surf2, keypoints_sift3, keypoints_sift4, kp_surfc1, kp_surfc2;
    Mat des1;
    Mat des2;
    Mat des3;
    Mat des4;

    detector->detect(img_1, keypoints_sift1);
    detector->detect(img_2, keypoints_sift2);
    detector->detect(img_3, keypoints_sift3);
    detector->detect(img_4, keypoints_sift4);

    detector->compute(img_1, keypoints_sift1,des1);
    detector->compute(img_2, keypoints_sift2,des2);
    detector->compute(img_3, keypoints_sift3,des3);
    detector->compute(img_4, keypoints_sift4,des4);

    //-- Draw keypoints
    Mat img_keypoints_sift1; Mat img_keypoints_sift2;
    Mat img_keypoints_sift3; Mat img_keypoints_sift4;

    drawKeypoints(img_1, keypoints_sift1, img_keypoints_sift1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    drawKeypoints(img_2, keypoints_sift2, img_keypoints_sift2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    drawKeypoints(img_3, keypoints_sift3, img_keypoints_sift3, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    drawKeypoints(img_4, keypoints_sift4, img_keypoints_sift4, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    //-- Show detected (drawn) keypoints
    imshow("Keypoints SIFT Bumblbee", img_keypoints_sift1); imwrite("/Users/qijin/Desktop/clion/3_c_Bumblbee.jpg",img_keypoints_sift1);
    imshow("Keypoints SIFT Optimus", img_keypoints_sift2);imwrite("/Users/qijin/Desktop/clion/3_c_Optimus.jpg",img_keypoints_sift2);
    imshow("Keypoints SIFT Ferrari", img_keypoints_sift3);imwrite("/Users/qijin/Desktop/clion/3_c_Ferrari.jpg",img_keypoints_sift3);
    imshow("Keypoints SIFT Ferrari_2", img_keypoints_sift4);imwrite("/Users/qijin/Desktop/clion/3_c_Ferrari_2.jpg",img_keypoints_sift4);

    BFMatcher sift_1(NORM_L2);
    std::vector<DMatch>siftmatch_1;
    sift_1.match(des1, des2, siftmatch_1);
    Mat sift_m1;
    drawMatches(img_1, keypoints_sift1, img_2, keypoints_sift2, siftmatch_1, sift_m1);
    imshow("SIFT match Bumblebee and Optimus", sift_m1);
    imwrite("/Users/hangdong/CLionProjects/project3/EE569_hw3_images/3_c_sift_1.jpg",sift_m1);

    BFMatcher sift_2(NORM_L2);
    std::vector<DMatch>siftmatch_2;
    sift_2.match(des1, des3, siftmatch_2);
    Mat sift_m2;
    drawMatches(img_1, keypoints_sift1, img_3, keypoints_sift3, siftmatch_2, sift_m2);
    imshow("SIFT match Bumblebee and Ferrari1", sift_m2);
    imwrite("/Users/hangdong/CLionProjects/project3/EE569_hw3_images/3_c_sift_2.jpg",sift_m2);

    BFMatcher sift_3(NORM_L2);
    std::vector<DMatch>siftmatch_3;
    sift_3.match(des2, des3, siftmatch_3);
    Mat sift_m3;
    drawMatches(img_2, keypoints_sift2, img_3, keypoints_sift3, siftmatch_3, sift_m3);
    imshow("SIFT match Optimus and Ferrari1", sift_m3);
    imwrite("/Users/hangdong/CLionProjects/project3/EE569_hw3_images/3_c_sift_3.jpg",sift_m3);

    // Bag of Words


    BOWKMeansTrainer BagOfWords(8);

    BagOfWords.add(des1);
    BagOfWords.add(des2);
    BagOfWords.add(des3);
    Mat dictionary = BagOfWords.cluster();
    //cout << dictionary << endl;
    double *bag_1 = d_array(8);
    double *bag_2 = d_array(8);
    double *bag_3 = d_array(8);
    double *bag_4 = d_array(8);
    bag_1 = histo(des1, dictionary);
    bag_2 = histo(des2, dictionary);
    bag_3 = histo(des3, dictionary);
    bag_4 = histo(des4, dictionary);
    cout << "Feature Histogram of Bumblebee" << endl;
    for (int i = 0; i < 8; i++) {
        cout << bag_1[i]<<" " ;
    }  cout<<endl;
    cout << "Feature Histogram of Optimus" << endl;
    for (int i = 0; i < 8; i++) {
        cout << bag_2[i]<<" ";
    }  cout<<endl;
    cout << "Feature Histogram of Ferrari" << endl;
    for (int i = 0; i < 8; i++) {
        cout << bag_3[i]<<" ";
    }cout<<endl;
    cout << "Feature Histogram of testing image" << endl;
    for (int i = 0; i < 8; i++) {
        cout << bag_4[i]<<" ";
    }cout<<endl;

    double bag1=0, bag2=0, bag3=0;
    for (int i = 0; i < 8; i++) {
        bag1 += abs(bag_1[i] - bag_4[i]);
        bag2 += abs(bag_2[i] - bag_4[i]);
        bag3 += abs(bag_3[i] - bag_4[i]);
    }

    if (bag1 < bag2 && bag1 < bag3) {
        cout << "It Belongs to BUMBLEBEE" << endl;
    }
    else if (bag2 < bag1 && bag2 < bag3) {
        cout << "It Belongs to Optimus" << endl;
    }
    else if (bag3 <= bag1 && bag3 < bag2) {
        cout << "It Belongs to Ferrari" << endl;
    }

    waitKey(0);

    return 0;
}

double *histo(Mat des1, Mat dictionary) {
    double *a = d_array(des1.rows);
    double *b = d_array(des1.rows);
    double *c = d_array(des1.rows);
    double *d = d_array(des1.rows);
    double *e = d_array(des1.rows);
    double *f = d_array(des1.rows);
    double *g = d_array(des1.rows);
    double *h = d_array(des1.rows);
    for (int i = 0; i < des1.rows; i++) {
        for (int j = 0; j < des1.cols; j++) {
            a[i] += pow((dictionary.at<float>(0, j) - des1.at<float>(i, j)), 2);			b[i] += pow((dictionary.at<float>(1, j) - des1.at<float>(i, j)), 2);			c[i] += pow((dictionary.at<float>(2, j) - des1.at<float>(i, j)), 2);			d[i] += pow((dictionary.at<float>(3, j) - des1.at<float>(i, j)), 2);
            e[i] += pow((dictionary.at<float>(4, j) - des1.at<float>(i, j)), 2);			f[i] += pow((dictionary.at<float>(5, j) - des1.at<float>(i, j)), 2);			g[i] += pow((dictionary.at<float>(6, j) - des1.at<float>(i, j)), 2);			h[i] += pow((dictionary.at<float>(7, j) - des1.at<float>(i, j)), 2);
        }
        a[i] = sqrt(a[i]);		b[i] = sqrt(b[i]);		c[i] = sqrt(c[i]);		d[i] = sqrt(d[i]);
        e[i] = sqrt(e[i]);		f[i] = sqrt(f[i]);		g[i] = sqrt(g[i]);		h[i] = sqrt(h[i]);
    }

    double *bag = d_array(8);

    for (int i = 0; i < des1.rows; i++) {
        if (a[i] < b[i] && a[i] < c[i] && a[i] < d[i] && a[i] < e[i] && a[i] < f[i] && a[i] < g[i] && a[i] < h[i]) {
            bag[0] += 1;
        }
        else if (b[i] < a[i] && b[i] < c[i] && b[i] < d[i] && b[i] < e[i] && b[i] < f[i] && b[i] < g[i] && b[i] < h[i]) {
            bag[1] += 1;
        }
        else if (c[i] < b[i] && c[i] < a[i] && c[i] < d[i] && c[i] < e[i] && c[i] < f[i] && c[i] < g[i] && c[i] < h[i]) {
            bag[2] += 1;
        }
        else if (d[i] < b[i] && d[i] < c[i] && d[i] < a[i] && d[i] < e[i] && d[i] < f[i] && d[i] < g[i] && d[i] < h[i]) {
            bag[3] += 1;
        }
        else if (e[i] < b[i] && e[i] < c[i] && e[i] < d[i] && e[i] < a[i] && e[i] < f[i] && e[i] < g[i] && e[i] < h[i]) {
            bag[4] += 1;
        }
        else if (f[i] < b[i] && f[i] < c[i] && f[i] < d[i] && f[i] < e[i] && f[i] < a[i] && f[i] < g[i] && f[i] < h[i]) {
            bag[5] += 1;
        }
        else if (g[i] < b[i] && g[i] < c[i] && g[i] < d[i] && g[i] < e[i] && g[i] < f[i] && g[i] < a[i] && g[i] < h[i]) {
            bag[6] += 1;
        }
        else if (h[i] < b[i] && h[i] < c[i] && h[i] < d[i] && h[i] < e[i] && h[i] < f[i] && h[i] < g[i] && h[i] < a[i]) {
            bag[7] += 1;
        }
    }
    return bag;
}