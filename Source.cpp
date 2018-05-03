#include <opencv2\core.hpp>
#include "videoprocessing.h"

int main()
{
	VideoProcessing videoInstance;

	videoInstance.fileExistsInDirectory("testFile.txt");
	//videoInstance.readVideoStream();
	

	return 0;
}