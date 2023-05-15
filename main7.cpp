#include <opencv2/opencv.hpp>

using namespace cv;

void affine_scale(){
    Mat src = imread("rose.bmp");
    if(src.empty()) return;
    Mat dst1, dst2, dst3, dst4;
    resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
    resize(src, dst2, Size(1920, 1280));
    resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
    resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

    imshow("src", src);
    imshow("dst1", dst1(Rect(400, 500, 400, 400)));
    imshow("dst2", dst2(Rect(400, 500, 400, 400)));
    imshow("dst3", dst3(Rect(400, 500, 400, 400)));
    imshow("dst4", dst4(Rect(400, 500, 400, 400)));

    waitKey();
    destroyAllWindows();
}

void affine_rotation(){
    Mat src = imread("tekapo.bmp");
    if(src.empty()) return;

    Point2f cp(src.cols / 2.f, src.rows / 2.f);
    Mat M = getRotationMatrix2D(cp, 20, 1);
    
    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void affine_flip(){
    Mat src = imread("eastsea.bmp");
    if(src.empty()) return;

    imshow("src",src);
    Mat dst;
    int flipCode[] = { 1, 0, -1 };
    for(int i = 0; i < 3; i++){
        flip(src, dst, flipCode[i]);
        String desc = format("flipCode : %d", flipCode[i]);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);
        imshow("dst", dst);
        waitKey(); 
    }
    destroyAllWindows();
}

void perspective(){
    static Point2f srcQuad[4];
    static Point2f dstQuad[4];
    static Mat src = imread("card.bmp");
    static int count = 0;
    imshow("SRC", src);
    auto on_mouse = [](int event, int x, int y, int flags, void* userdata){
        if(event == EVENT_LBUTTONDOWN){
            if(count < 4) srcQuad[count ++] = Point2f(x, y);
            circle(src, Point(x,y), 5, Scalar(0,0,255), -1); //마우스 포인트를 점으로 표현
            imshow("SRC", src);
            if(count == 4){
                int width = 200;
                int height = 300;
                dstQuad[0] = Point2f(0, 0);
                dstQuad[1] = Point2f(width - 1, 0);
                dstQuad[2] = Point2f(width - 1, height - 1);
                dstQuad[3] = Point2f(0, height - 1);
                Mat M = getPerspectiveTransform(srcQuad, dstQuad);

                Mat dst;
                warpPerspective(src, dst, M, Size(width ,height));
                imshow("DST", dst);
                
            }
        }
        
    };
    setMouseCallback("SRC", on_mouse);
    waitKey(); 
    destroyAllWindows();
}
/*
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

Mat rc;
Point2f srcQuad[4], dstQuad[4];

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main(){
    src = imread("card.bmp");
    if(src.empty()){
        cerr << "failed" << endl;
        return -1;
    }
    namedWindow("src");
    setMouseCallback("src", on_mouse);
    imshow("src", src);
    waitKey(); 

    return 0;
}

void on_mouse(int event, int x, int y, int flags, void*){
    static int cnt = 0;
    if(event == EVENT_LBUTTONDOWN){
        if (cnt < 4){
            srcQuad[cnt++] = Point2f(x ,y);
            circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
            imshow("src", src);
            if(cnt == 4){
                int w = 200, h = 300;

                dstQuad[0] = Point2f(0, 0);
                dstQuad[1] = Point2f(w-1, 0);
                dstQuad[2] = Point2f(w-1, h-1);
                dstQuad[3] = Point2f(0, h-1);

                Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

                Mat dst;
                warpPerspective(src, dst, pers, Size(w,h));
                imshow("dst", dst)
            }
        }
    }
}
*/

void sobel_edge(){
    Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
    if(src.empty()) return;

    Mat dx, dy;
    Sobel(src, dx, CV_32FC1, 1, 0);
    Sobel(src, dy, CV_32FC1, 0, 1);
   
    imshow("src", src);
    imshow("dx", dx);
    imshow("dy", dy);

    Mat mag;
    magnitude(dx, dy, mag);
    mag.convertTo(mag, CV_8UC1);
    Mat edge = mag > 150;
    imshow("Mag", mag);
    imshow("Edge", edge);

    Mat _phase;
    phase(dx, dy, _phase);
    waitKey(); 
    destroyAllWindows();
}

void candy_edge(){ //canny_edge()
    Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);\
    if(src.empty()) return;
    Mat dst1;
    Mat dst2;

    Canny(src, dst1, 50, 100);
    Canny(src, dst2, 50, 150);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
    waitKey(); 
    destroyAllWindows();
}

void hough_lines(){
    Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    Mat edge;
    Canny(src, edge, 50, 150);

    std::vector<Vec2f> lines;
    HoughLines(edge, lines, 1, CV_PI / 180, 250);

    Mat dst;
    cvtColor(edge, dst, COLOR_GRAY2BGR);

    for (size_t i = 0; i < lines.size(); i++) {
        float r = lines[i][0], t = lines[i][1];
        double cos_t = cos(t), sin_t = sin(t);
        double x0 = r * cos_t, y0 = r * sin_t;
        double alpha = 1000;

        Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
        Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey(); 
    destroyAllWindows();
}

void hough_circles(){
    Mat src = imread("doge2.jpg", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    Mat blurred;
    blur(src, blurred, Size(3, 3));
    std::vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);
    for(Vec3f c : circles){
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey(); 
    destroyAllWindows();
}

void color_grayscale(){
    Mat src = imread("butterfly.jpg");
    if(src.empty()) return;
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);
    imshow("src",src);
    imshow("dst",dst);
    waitKey(); 
    destroyAllWindows();
}

void color_split(){
    Mat src = imread("candies.png");
    if(src.empty())  return;
    std::vector<Mat> bgr_planes;
    split(src, bgr_planes);

    imshow("src",src);
    imshow("B_Plane", bgr_planes[0]);
    imshow("G_Plane", bgr_planes[1]);
    imshow("R_Plane", bgr_planes[2]);

    waitKey(); 
    destroyAllWindows();

}
