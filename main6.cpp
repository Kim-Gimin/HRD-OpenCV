#include <opencv2/opencv.hpp>
void arithmetic(){
    cv::Mat src1 = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
    cv::Mat src2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);
    if(src1.empty() or src2.empty()) return;
    cv::imshow("SRC1", src1);
    cv::imshow("SRC2", src2);
    cv::Mat dst;
    cv::add(src1, src2, dst);
    cv::imshow("ADD", dst);
    cv::Mat dst2;
    cv::addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
    cv::imshow("ADDWEIGHTED", dst2);
    cv::Mat dst3;
    cv::subtract(src1, src2, dst3);
    cv::imshow("SUBTRACT", dst3);

    cv::Mat dst4;
    cv::absdiff(src1, src2, dst4);
    cv::imshow("ABSDIFF", dst4);
    cv::waitKey();
    cv::destroyAllWindows();

}

void logical(){
    cv::Mat src1 = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
    cv::Mat src2 = cv::imread("square.bmp", cv::IMREAD_GRAYSCALE);

    if(src1.empty() or src2.empty()) return;
    cv::imshow("SRC1", src1);
    cv::imshow("SRC2", src2);

    cv::Mat dst;
    cv::bitwise_and(src1, src2, dst);
    cv::imshow("BITWISE_AND", dst);

    cv::Mat dst2;
    cv::bitwise_or(src1, src2, dst2);
    cv::imshow("BITWISE_OR", dst2);

    cv::Mat dst3;
    cv::bitwise_xor(src1, src2, dst3);
    cv::imshow("BITWISE_XOR", dst3);

    cv::Mat dst4;
    cv::bitwise_not(src1, dst4);
    cv::imshow("BITWSIE_NOT", dst4);

    cv::waitKey();
    cv::destroyAllWindows(); 
}

void filter_embossing(){
    cv::Mat src = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr << "no file" << std::endl;
        return;
    }
    float filter_data[] = {-1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    cv::Mat emboss(3, 3, CV_32FC1, filter_data);
    cv::Mat dst;
    cv::filter2D(src, dst, -1, emboss, cv::Point(-1, -1), 128);

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows(); 
}

void bluring_mean(){
    cv::Mat src = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr << "no file" << std::endl;
        return;
    }
    //float filter_data[] = {-1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    //cv::Mat emboss(3, 3, CV_32FC1, filter_data);
    cv::Mat dst;
    cv::imshow("SRC", src);
    for(int ksize = 3; ksize <= 7; ksize += 2){
        cv::blur(src, dst, cv::Size(ksize, ksize));

        cv::String desc = cv::format("Mean : %dx%d", ksize, ksize);
        putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
        imshow("dst", dst);
        cv::waitKey();
    }
    cv::destroyAllWindows(); 
    //cv::filter2D(src, dst, -1, emboss, cv::Point(-1, -1), 128);

}

void blurring_gaussian(){
    cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr << "Image loa failed!" << std::endl;
        return;
    }
    cv::imshow("src", src);
    cv::Mat dst;
    for(int sigma = 1; sigma <= 5; ++sigma){
        cv::GaussianBlur(src, dst, cv::Size(), static_cast<double>(sigma));
        cv::String text = cv::format("sigma = %d", sigma);
        cv::putText(dst, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
        cv::imshow(text, dst);
        cv::waitKey();
    }
    cv::destroyAllWindows(); 
}


void unsharp_mask(){
    cv::Mat src = cv::imread("rose.bmp", cv::IMREAD_GRAYSCALE);
    if(src.empty()){
        std::cerr << "Image failed" << std::endl;
        return;
    }
    cv::imshow("src",src);
    for(int sigma = 1; sigma <= 5; sigma++){
        cv::Mat blurred;
        cv::GaussianBlur(src, blurred, cv::Size(), sigma);

        float alpha = 1.f;
        cv::Mat dst = (1 + alpha) * src - alpha * blurred;

        cv::String desc = cv::format("sigam : %d", sigma);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);

        cv::imshow("dst", dst);
        cv::waitKey();
    }
    cv::destroyAllWindows(); 
}

void noise_gaussian(){
    cv::Mat src = imread("lenna.bmp", cv::IMREAD_GRAYSCALE);

    if(src.empty()) return;
    cv::imshow("Lenna",src);
    for(int stddev = 10; stddev <= 10; stddev +=10){
        cv::Mat noise(src.size(), CV_32SC1);
        cv:: randn(noise, 0, stddev);

        cv:: Mat dst;
        cv:: add(src, noise, dst, cv::Mat(), CV_8U);

        cv::String desc = cv::format("stddev = %d", stddev);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
        cv::imshow("dst",dst);
        cv::waitKey();
    }
    cv::destroyAllWindows(); 
}
void filter_median(){
    cv::Mat src = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
    if(src.empty()) return;
    int num = (int)(src.total() * 0.1);
    for(int i = 0; i < num; i++){
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        src.at<uchar>(y, x) = (i % 2) * 255;
    }
    cv::Mat dst1;
    cv::GaussianBlur(src, dst1, cv::Size(), 1);
    cv::Mat dst2;
    cv::medianBlur(src, dst2, 3);

    cv::imshow("src", src);
    cv::imshow("dst", dst1);
    cv::imshow("dst2", dst2);

    cv::waitKey();
    cv::destroyAllWindows(); 

}


void affine_transforn(){
    cv::Mat src = cv::imread("tekapo.bmp");
    if(src.empty())return;
    cv::Point2f srcPts[3];
    cv::Point2f dstPts[3];

    srcPts[0] = cv::Point2f(0,0);
    srcPts[1] = cv::Point2f(src.cols - 1.0);
    srcPts[2] = cv::Point2f(src.cols - 1, src.rows - 1);
    dstPts[0] = cv::Point2f(50, 50);
    dstPts[1] = cv::Point2f(src.cols - 100, 100);
    dstPts[2] = cv::Point2f(src.cols - 50, src.rows - 50);

    cv::Mat M = cv::getAffineTransform(srcPts, dstPts);

    cv::Mat dst;
    cv::warpAffine(src, dst, M, cv::Size());

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows(); 
}

void affine_translation(){
    cv::Mat src = cv::imread("tekapo.bmp");
    if(src.empty()) return;
    cv::Mat M = cv::Mat_<float>({2, 3}, { 1, 0, 150, 0, 1, 100 });

    cv::Mat dst;
    cv::warpAffine(src, dst, M, cv::Size());
    cv::imshow("SRC",src);
    cv::imshow("DST",dst);
    cv::waitKey();
    cv::destroyAllWindows();
}
