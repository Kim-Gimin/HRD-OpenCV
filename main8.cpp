#include <opencv2/opencv.hpp>

void using_threshold(){
    cv::Mat src {cv::imread("neutrophils.png", cv::IMREAD_GRAYSCALE)};
    if(src.empty()) return;
    cv::namedWindow("Source");
    cv::namedWindow("Destination");
    cv::imshow("Source",src);
    auto on_thread = [](int position,void* user_data){
        cv::Mat src {*static_cast<cv::Mat*>(user_data)};
        cv::Mat dst;
        cv::threshold(src, dst, position, 255.0, cv::THRESH_BINARY);
        cv::imshow("Destination", dst);
    };
    cv::createTrackbar("Threshold", "Destination", 0, 255, on_thread, (void*)&src);
    cv::setTrackbarPos("Threshold", "Destination", 128);
    cv::waitKey(); 
    cv::destroyAllWindows();

}

static void on_trackbar(int pos, void* userdata){
    cv::Mat src = {*static_cast<cv::Mat*>(userdata)};
    int block_size = pos;
    if(pos % 2 == 0) --block_size;
    if(block_size < 3) block_size = 3;
    cv::Mat dst;
    cv::adaptiveThreshold(src, dst, 255.0, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, block_size, 5.0);
    cv::imshow("DST", dst);
}
void adaptive_threshold(){
    cv::Mat src = cv::imread("sudoku.jpg", cv::IMREAD_GRAYSCALE);
    if(src.empty()) return;
    cv::imshow("SRC",src);
    cv::namedWindow("DST");
    cv::createTrackbar("BlockSize", "DST", nullptr, 200, on_trackbar, (void*)&src);
    cv::setTrackbarPos("BlockSize", "DST", 11);
    cv::waitKey();
    cv::destroyAllWindows();
}
using namespace cv;
void erode_dilate(){
    Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat dst1, dst2;
    erode(bin, dst1, Mat());
    dilate(bin, dst2, Mat());

    imshow("src", src);
    imshow("bin", bin);
    imshow("erode", dst1);
    imshow("dilate", dst2);
    waitKey();
    destroyAllWindows();
}

void open_close(){
    Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat dst1, dst2;
    morphologyEx(bin, dst1, MORPH_OPEN, Mat());
    morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

    imshow("src", src);
    imshow("bin", bin);
    imshow("opening", dst1);
    imshow("closing", dst2);
    waitKey();
    destroyAllWindows();
}
void labeling_basic(){
    uchar data[] = {
        0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    Mat src = Mat(8, 8, CV_8UC1, data) * 255;
    Mat labels;
    int cnt = connectedComponents(src, labels);
    std::cout << "src:\n" << src << std::endl;
    std::cout << "labels:\n" << labels << std::endl;
    std::cout << "number of labels : " << cnt << std::endl;
}
void labeling_stats(){
    Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);
    if(src.empty()) return;
    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

    Mat dst;
    CvtColor(src, dst, COLOR_GRAY2BGR);
    for(int i = 1; i < cnt; i++){
        int* p = stats.ptr<int>(i);
        if(p[4] < 20) continue;
        rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();
}

