#ifndef TOOL_H
#define TOOL_H
#include <opencv2/opencv.hpp>
using namespace cv;
class Tool
{
public:
    static Mat noirEtBlanc(Mat img);
    static Mat contours(Mat img);
    static Mat flouter(Mat img);
    static Mat negatif(Mat img);
    static Mat rouge(Mat img);
    static Mat vert(Mat img);
    static Mat bleu(Mat img);
    static Mat enleverTeinte(Mat img);
    static Mat enleverSaturation(Mat img);
    static Mat enleverBrillance(Mat img);
    static Mat changement(Mat img);
    static Mat special16(Mat img);
    static Mat special64(Mat img);
    static Mat calculerGradient(Mat gx, Mat gy);
    static Mat gradient(Mat src);
    static Mat gradientRGB(Mat grad_r, Mat gradient_g, Mat gradient_b);
    void FindBlobs(Mat binary, std::vector< std::vector<Point2i> >  &blobs, int size);
};

#endif // TOOL_H
