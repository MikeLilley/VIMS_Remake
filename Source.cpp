#include <opencv2/core.hpp>
#include "video_processing.hpp"

int main()
{
	VideoProcessing videoInstance;

	videoInstance.fileExistsInDirectory("testFile.txt");
	//videoInstance.readVideoStream();
	
	return 0;
}