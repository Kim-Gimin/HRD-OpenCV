#include <opencv2/opencv.hpp>
extern void matop();
extern void matop2();
extern void matop3();
extern void matop4();
extern auto matop5() -> void;
extern void matop6();

extern void camera_in();
extern void video_in();
extern void video_out();
int main()
{
	std::cout << CV_VERSION << std::endl;

	//matop();
	//matop2();
	//matop3();
	//matop4();
	//matop5();
	//matop6();
	//camera_in();
	//video_in();
	video_out();
	return 0;
}


