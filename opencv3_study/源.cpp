#include <iostream>  

#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>

#define PIC1 "Z:/Sai/Bangumi/paint/back2.jpg"
#define VID1 "D:/Cocoa/2016-1月番/OVA/【minori】EdenOP.mp4"

int First_Test_IMG_IMREAD(const std::string &path) {

	cv::Mat img = cv::imread(path);
	if (!img.empty()) {
		cv::namedWindow("Test", cv::WINDOW_NORMAL);
		cv::imshow("Test", img);
		cv::waitKey(0);

		cv::destroyWindow("Test");



	}
	else {
		return -1;
	}

	return 0;
}


int First_Test_Video(const std::string &path) {
	cv::namedWindow("tx", cv::WINDOW_NORMAL);
	cv::VideoCapture cap;
	cap.open(path);

	cv::Mat frame;
	for (;;)
	{
		cap >> frame;
		if (frame.empty())break;
		cv::imshow("tx", frame);

		if (cv::waitKey(17) >= 0) {
			cv::destroyAllWindows();
			break;
		}

	}
	return 0;
}
namespace First_Video_Bar {

	//由于无法使用捕获造就的回调函数,只能声明成为全局变量
	int g_slider_position = 0;
	int g_run = 1, g_dontset = 0;
	cv::VideoCapture cap;

	void onTrackBarSlide(int pos, void * ) {
		//std::cout << "OOOOO\n";
		cap.set(cv::CAP_PROP_POS_FRAMES, pos);

		if (!g_dontset) {
			g_run = 1;
		}
		g_dontset = 0;
	}
	int First_Test_Video_Hard(const std::string &path) {
		//int g_slider_position = 0;
		//int g_run = 1, g_dontset = 0;
		//cv::VideoCapture cap;

		cv::namedWindow("t", cv::WINDOW_NORMAL);

		cap.open(path);

		int frames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
		int tmpw = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
		int tmph = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

		std::cout << "Frams = " << frames
			<< "\nw = " << tmpw
			<< "\nh = " << tmph << std::endl;

		//[注意]经测试,在OPENCV3中无法使用lambda或std::bind完成对回调函数的调用[只要捕获了其他变量]

		//auto call = std::bind(onTrackBarSlide, std::placeholders::_1, std::placeholders::_2, std::ref(cap), std::ref(g_run), std::ref(g_dontset));
		//cv::createTrackbar("position", "t", &g_slider_position, frames,
		//	call);

		//cv::createTrackbar("position", "t", &g_slider_position, frames,
		//	[](int pos, void *) {
		//	//ok
		//});

		cv::createTrackbar("position", "t", &g_slider_position, frames, onTrackBarSlide);


		cv::Mat frame;
		for (;;)
		{
			if (g_run != 0) {
				cap >> frame;

				if(frame.empty())
					break;

				int current_pos = (int)cap.get(cv::CAP_PROP_POS_FRAMES);
				g_dontset = 1;
				
				cv::setTrackbarPos("position", "t", current_pos);

				cv::imshow("t", frame);

				g_run -= 1;
			}
			char c = (char)cv::waitKey(10);
			if (c == 's')
			{
				g_run = 1;
				std::cout << "Single Step, run = " << g_run << std::endl;

			}
			if (c == 'r') {
				g_run = -1;
				std::cout << "Run mode, run = " << g_run << std::endl;

			}
			if (c == 27) {
				break;
			}

		}
		cv::destroyWindow("t");
		return 0;
	}
}
int Smooth_Pic_Test(const std::string & path) {
	cv::Mat in_mat;
	cv::Mat out_mat;

	in_mat = cv::imread(path, -1);

	cv::namedWindow("in", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

	cv::GaussianBlur(in_mat, out_mat, cv::Size(5, 5), 3, 3);

	cv::imshow("in", in_mat);
	cv::imshow("out", out_mat);

	cv::waitKey(0);
	return 0;
}
int main()
{
	//First_Test_IMG_IMREAD(PIC1);
	//First_Test_Video(VID1);
	//First_Video_Bar::First_Test_Video_Hard(VID1);
	Smooth_Pic_Test(PIC1);
	system("pause");
}
