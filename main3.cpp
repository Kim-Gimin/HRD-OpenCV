#include <opencv2/opencv.hpp>

void camera_in(){
    cv::VideoCapture cap(-1);
    if(!cap.isOpened()) {
        std::cerr << "Camera is not opened..." << std::endl;
        return;
    }
	std::cout << "Height : " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;
	std::cout << "WIDTH : " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
    cv::Mat frame;
    while(true){
        cap >> frame;
        if(frame.empty()) break;
        cv::imshow("Camera", ~frame);
        if(cv::waitKey(10) == 27) break; //ESC 27
    }

    cv::destroyAllWindows();
}
void video_in(){
    cv::VideoCapture cap("stopwatch.avi");
    if(!cap.isOpened()) {
        std::cerr << "Camera is not opened..." << std::endl;
        return;
    }
	std::cout << "Height : " << cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) << std::endl;
	std::cout << "WIDTH : " << cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH)) << std::endl;
	//Camera FPS
	std::cout << "Count : " << cvRound(cap.get(cv::CAP_PROP_FRAME_COUNT)) << std::endl;
	double fps = cap.get(cv::CAP_PROP_FPS);
	int delay = cvRound(1000/fps);
    cv::Mat frame;
	cv::Mat inversed;
    while(true){

        cap >> frame;
		inversed = ~frame;
        if(frame.empty()) break;
        cv::imshow("Camera", frame);
		cv::imshow("INVERSED", inversed);
        if(cv::waitKey(delay) == 27) break; //ESC 27
    }

    cv::destroyAllWindows();
}
void video_out(){
    cv::VideoCapture cap(-1);
    if(!cap.isOpened()) {
        std::cerr << "Camera is not opened..." << std::endl;
        return;
    }
	int h = cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	int w = cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	std::cout << "Height : " << h << std::endl;
	std::cout << "WIDTH : " << w << std::endl;
	//Camera FPS
	std::cout << "Count : " << cvRound(cap.get(cv::CAP_PROP_FRAME_COUNT)) << std::endl;
	double fps = cap.get(cv::CAP_PROP_FPS);
	int delay = cvRound(1000/fps);
    cv::Mat frame;
	cv::Mat inversed;
	int fourcc = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');
	cv::VideoWriter output("output.avi", fourcc, fps, cv::Size(w, h));
	if(!output.isOpened()){
		std::cerr << "Rile is not opened" << std::endl;
		return;
	}
	while(true){
		cap >> frame;
		if(frame.empty()){
			std::cerr << "Frame is not opened" << std::endl;
			break;
		}
		inversed = ~frame;
		output << frame;

		cv::imshow("Camera", frame);
		cv::imshow("INVERSED", inversed);
		if(cv::waitKey(delay) == 27) break;
	}
    cv::destroyAllWindows();
}
