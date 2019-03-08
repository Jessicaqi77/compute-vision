#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <stdlib.h>
using namespace std;
using namespace cv;
using namespace cv::ximgproc;
using namespace cv::xfeatures2d;

int g_nOctaveLayers = 0;
int g_ncontrastThreshold = 0;
extern int g_nOctaves=0;
void merge(Mat & dst,Mat &src1,Mat &src2)
{
    int rows = max(src1.rows,src2.rows);
    int cols = src1.cols+5+src2.cols;
    CV_Assert(src1.type () == src2.type ());
    dst.create (rows,cols,src1.type ());
    src1.copyTo (dst(Rect(0,0,src1.cols,src1.rows)));
    src2.copyTo (dst(Rect(src1.cols+5,0,src2.cols,src2.rows)));
}
int main()
{
    Mat img_21 = imread("/Users/qijin/Desktop/clion/Optimus_Prime.jpg", 1);//load image
    Mat img_11 = imread("/Users/qijin/Desktop/clion/bumblebee.jpg", 1);
    Mat img_1, img_2;
    cvtColor(img_11, img_1, CV_BGR2GRAY);//convert to gray
    cvtColor(img_21, img_2, CV_BGR2GRAY);

    int type;
    cout << "Input the method type: 1. SIFT 2. SURF: ";
    cin >> type;Mat outimg;
    if (type == 1)//SIFT
    {
        int bar;
        cout << " choose track bar: 1.yes 2.no: ";
        cin >> bar;

        if (bar == 1)//choose the track bar
        {

            namedWindow("parameter bar", 0);
            createTrackbar("Octave Layers:", "parameter bar", &g_nOctaveLayers, 10, 0);
            createTrackbar("Contrast Threshold:", "parameter bar", &g_ncontrastThreshold, 10, 0);

            char key;
            while(1)
            {
                Mat img21,img11;
                img21.release();img11.release();
                cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, g_nOctaveLayers + 1, (double) (g_ncontrastThreshold / 100.0), 10, 1.6);
                std::vector<KeyPoint> keypoints_1, keypoints_2;
                f2d->detect(img_1, keypoints_1);
                f2d->detect(img_2, keypoints_2);
                Mat descriptors_1, descriptors_2;
                f2d->compute(img_1, keypoints_1, descriptors_1);
                f2d->compute(img_1, keypoints_2, descriptors_2);
                cv::drawKeypoints(img_21, keypoints_1, img21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                cv::drawKeypoints(img_11, keypoints_1, img11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                merge (outimg,img21,img11);
                imshow("Result window", outimg);//imshow("bumblebee window", img110);
                key=waitKey(0);
                if (key == 27)break;//use 'esc'key to break out from the code.
            }
            destroyWindow("Optimus window"); //destroyWindow("bumblebee window");
        }
        //not use the track bar

            cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, 2, 0.18, 10, 1.6);
            std::vector<KeyPoint> keypoints_1, keypoints_2;
            f2d->detect(img_1, keypoints_1);
            f2d->detect(img_2, keypoints_2);

            Mat descriptors_1, descriptors_2;
            f2d->compute(img_1, keypoints_1, descriptors_1);
            f2d->compute(img_2, keypoints_2, descriptors_2);

            cv::drawKeypoints(img_11, keypoints_1, img_11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
            cv::drawKeypoints(img_21, keypoints_2, img_21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

            imwrite("/Users/qijin/Desktop/clion/Optimus_out.jpg", img_21);
            imwrite("/Users/qijin/Desktop/clion /bumblebee_out.jpg", img_11);

    }
    else//SURF
    {
        int bar;
        cout << "If do the choose bar: 1)yes 2)no: ";
        cin >> bar;

        if (bar == 1)
        {
            namedWindow("parameter bar", 0);
            createTrackbar("Octave Layers:", "parameter bar", &g_nOctaveLayers, 10, 0);
            createTrackbar("Contrast Threshold:", "parameter bar", &g_ncontrastThreshold, 10, 0);
            char key;

            while(1)
            {
                Mat img21,img11;
                cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create(100, g_nOctaves + 1, g_nOctaveLayers + 1);
                std::vector<KeyPoint> keypoints_1;std::vector<KeyPoint> keypoints_2;
                f2d->detect(img_1, keypoints_1);f2d->detect(img_2, keypoints_2);
                Mat descriptors_1;Mat descriptors_2;
                f2d->compute(img_1, keypoints_1, descriptors_1);f2d->compute(img_2, keypoints_2, descriptors_2);
                cv::drawKeypoints(img_11, keypoints_1, img11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                cv::drawKeypoints(img_21, keypoints_2, img21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
                merge (outimg,img21,img11);
                imshow("Result window", outimg);//imshow("bumblebee window", img110);
                key=waitKey(0);
                if (key == 27)break;//use 'esc'key to break out from the code.
            }

        }

            cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create();
            std::vector<KeyPoint> keypoints_1, keypoints_2;
            f2d->detect(img_1, keypoints_1);
            f2d->detect(img_2, keypoints_2);

            Mat descriptors_1, descriptors_2;
            f2d->compute(img_1, keypoints_1, descriptors_1);
            f2d->compute(img_2, keypoints_2, descriptors_2);

            cv::drawKeypoints(img_11, keypoints_1, img_11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
            cv::drawKeypoints(img_21, keypoints_2, img_21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
            imwrite("/Users/qijin/Desktop/clion/Optimus_surf_out.jpg", img_21);
            imwrite("/Users/qijin/Desktop/clion/bumblebee_surf_out.jpg", img_11);

    }

    system("pause");

}