#include <opencv2/opencv.hpp>
extern void matop();
extern void matop2();
extern void matop3();
extern void matop4();
extern auto matop5() -> void;
extern void matop6();
extern void drawLines();
extern void drawPolys();
extern void keyboard_event();

extern void camera_in();
extern void video_in();
extern void video_out();

extern void mouse_event();

extern void trackbar_event();
extern void mask_setTo();
extern void mask_copyTo();

extern void brightness1();
extern void brightness3();
extern void brightness4();
extern void show_hist();
extern void histogram_streching();
extern void arithmetic();
extern void logical();
extern void filter_embossing();
extern void bluring_mean();
extern void blurring_gaussian();
extern void unsharp_mask();
extern void noise_gaussian();
extern void filter_median();
extern void affine_transforn();
extern void affine_translation();

extern void affine_scale();
extern void affine_rotation();
extern void affine_flip();
extern void perspective();
extern void sobel_edge();
extern void candy_edge();
extern void hough_lines();
extern void hough_circles();
extern void color_grayscale();
extern void color_split();
extern void on_threshold();
extern void using_threshold();
extern void on_trackbar();
extern void adaptive_threshold();
extern void erode_dilate();
extern void open_close();

extern void labeling_basic();
extern void labeling_stats();

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
//	video_out();
//	drawLines();
//	drawPolys();
//	keyboard_event();
//	mouse_event();
//	trackbar_event();
//	(*::mask_setTo)();
//	mask_copyTo();
//	brightness1();
//	brightness3();
//	brightness4();
//	show_hist();
//	histogram_streching();
//	arithmetic();
//	logical();
//	filter_embossing();
//	bluring_mean();
//	blurring_gaussian();
//	unsharp_mask();
//	noise_gaussian();
//	filter_median();
//	affine_transforn();
//	affine_translation();
//	affine_scale();
//	affine_rotation();
//	affine_flip();
//	perspective();
//	sobel_edge();
//	candy_edge();
//	hough_lines();
//	hough_circles();
//	color_grayscale();
//	color_split();
//	using_threshold();
//	on_trackbar();
//	adaptive_threshold();
//	erode_dilate();
//	open_close();
//	labeling_basic();
	labeling_stats();
	return 0;
}


