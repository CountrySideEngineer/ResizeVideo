// ResizeVideo.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

int main(int argc, TCHAR** argv)
{
	_tprintf(_T("Start program\r\n"));

	//Check number of argument.
	if (argc < 3) {
		_tprintf(_T("Number of arguments is not enough.\r\n"));

		return 0;
	}

	argv++;
	TCHAR* InputFileName = *argv;
	argv++;
	TCHAR* OutputFileName = *argv;

	cv::VideoCapture Capture = cv::VideoCapture();
	Capture.open(cv::String(InputFileName));
	if (!Capture.isOpened()) {
		_tprintf(_T("Can not open %s\r\n"), InputFileName);

		return 0;
	}

	double ImageFps = Capture.get(cv::CAP_PROP_FPS);	//Same that of source data.
	cv::Size NewImageSize = cv::Size(640, 480);
	cv::VideoWriter Writer = cv::VideoWriter();
	Writer.open(cv::String(OutputFileName),
		cv::VideoWriter::fourcc('X', 'V', 'I', 'D'),	//AVI format.
		ImageFps, NewImageSize);

	cv::Mat SrcFrame;
	cv::Mat DstFrame;
	int FrameNum = (int)Capture.get(cv::CAP_PROP_FRAME_COUNT);
	for (int index = 0; index < FrameNum; index++) {
		Capture >> SrcFrame;

		if (SrcFrame.empty()) {
			_tprintf(_T("Source frame is empty.\r\n"));

			break;
		}

		cv::resize(SrcFrame, DstFrame, NewImageSize);
		Writer << DstFrame;
		cv::imshow("Resized image", DstFrame);

		cv::waitKey((int)(1000/ImageFps));
	}

	Capture.release();
	Writer.release();

	cv::destroyAllWindows();

    return 0;
}

