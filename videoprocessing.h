#ifndef VIDEOPROCESSING_H
#define VIDEOPROCESSING_H

#include <vector>
#include <fstream>
#include <thread>

#include "vimsstructs.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#define PROFILEDATALINECOUNT 5

class VideoProcessing  //Class to filter and produce video.
{
    private:
        /* Instance Variables */
        std::vector<Profile> profileList;   //Vector to store all recorded profiles.
        cv::VideoCapture *currentCameraView;   //VideoCapture variable to specify the current camera being used.
        cv::Mat *currentFrameMatrix;  //Pointer to matrix used to store each individual frame coming from the video feed.
        CartesianCoordinates objectLocation;    //CartesianCoordinates variable to store coordinates of a tracked object.
		std::fstream profileData;	//String variable to specify the name of text file in which all the profile data is stored.

    public:
		void setcurrentCameraView()
		{
			if (currentCameraView != nullptr)
			{
				delete currentCameraView;
				currentCameraView = nullptr;
			}

			currentCameraView = new cv::VideoCapture;
			currentCameraView->open(0);
		}

        void setcurrentCameraView(Camera &newCamera)
        {
            currentCameraView->open(newCamera.cameraID);
        }

        short clearFrameMatrix()
        {
            if (currentFrameMatrix == nullptr)
            {
                delete currentFrameMatrix;
                currentFrameMatrix = nullptr;
                return 0;
            }

            else return -1;
        }

        short setFrameMatrix(cv::Mat &newFrameMatrix)
        {
            if (currentFrameMatrix != nullptr)
            {
                delete currentFrameMatrix;
                currentFrameMatrix = nullptr;
            }

            currentFrameMatrix = &newFrameMatrix;
            return 0;
        }

        short setFrameMatrix(CartesianCoordinates matrixSize, int type)
        {
            if (currentFrameMatrix != nullptr)
            {
                delete currentFrameMatrix;
                currentFrameMatrix = nullptr;
            }

            currentFrameMatrix = new cv::Mat(matrixSize.xCoordinate, matrixSize.yCoordinate, type);
            return 0;
        }

        short setFrameMatrix(CartesianCoordinates matrixSize, int type, cv::Scalar initialValue)
        {
            if (currentFrameMatrix != nullptr)
            {
                delete currentFrameMatrix;
                currentFrameMatrix = nullptr;
            }

            currentFrameMatrix = new cv::Mat(matrixSize.xCoordinate, matrixSize.yCoordinate, type, initialValue);
            return 0;
        }

        void setCartesianCoordinates_X(CartesianCoordinates &inputCoordinates, unsigned short newXCoordinate)
        {
            inputCoordinates.xCoordinate = newXCoordinate;
        }

        void setCartesianCoordinates_Y(CartesianCoordinates &inputCoordinates, unsigned short newYCoordinate)
        {
            inputCoordinates.yCoordinate = newYCoordinate;
        }

        void setCartesianCoordinates (CartesianCoordinates &inputCoordinates,unsigned short newXCoordinate, unsigned short newYCoordinate)
        {
            inputCoordinates.xCoordinate = newXCoordinate;
            inputCoordinates.yCoordinate = newYCoordinate;
        }

        void setCartesianCoordinates (CartesianCoordinates &inputCoordinates, CartesianCoordinates newCoordinates)
        {
            inputCoordinates.xCoordinate = newCoordinates.xCoordinate;
            inputCoordinates.yCoordinate = newCoordinates.yCoordinate;
        }

        /* Profile Mutators and Accessors */

        //Function to check if a profile exists based on its index within the profileList vector.
        bool profileExists(unsigned short profileIndex)
        {
            if (profileIndex < profileList.size())
                return true;

            else return false;
        }

        //Subroutine to add a profile to the profileList vector.
        void addProfile(Profile &tempProfile)
        {
            profileList.push_back(tempProfile);
        }

        //Function to remove a profile contained within the profileList vector.
        short removeProfile(unsigned short &profileIndex)
        {
            if (profileExists(profileIndex))
            {
                profileList.erase(profileList.begin() + profileIndex);
                return 0;
            }

            else return -1;
        }

        //Function to set the name of a profile contained within the profileList vector.
        short setProfileName(unsigned short &profileIndex, std::string &newProfileName)
        {
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).name = newProfileName;
                return 0;
            }

            else return -1;
        }

        /* Camera Mutators and Accessors */

        //Adds a new camera to the profileList vector.
        short addNewCamera(unsigned short profileIndex, Camera &newCamera)
        {
            //After "Add" has been hit:
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).cameraList.push_back(newCamera);
                return 0;
            }

            else return -1;
        }

        //Removes a camera from the profileList vector;
        short removeCamera(unsigned short profileIndex, unsigned short cameraID)
        {
            //List cameras contained in cameraList of inputProfile in combo box, select which one to remove.
            //After "Remove" has been hit:
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).cameraList.erase(profileList.at(profileIndex).cameraList.begin() + cameraID);
                return 0;
            }

            else return -1;
        }

        //Function to set a camera's name within the cameraList vector contained in a profile.
        short setCameraName(unsigned short profileIndex, unsigned short cameraID, std::string &newCameraName)
        {
            //List cameras contained in cameraList of inputProfile in combo box, select which one to remove.
            //After "Remove" has been hit:
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).cameraList.at(cameraID).cameraName = newCameraName;
                return 0;
            }

            return -1;
        }

        //Function to return a camera's name within the cameraList vector contained in a profile.
        std::string getCameraName(unsigned short profileIndex, unsigned short cameraID)
        {
            if (profileExists(profileIndex))
                return profileList.at(profileIndex).cameraList.at(cameraID).cameraName;

            else return "-1";
        }

        //Function to set a camera's type of connection within the cameraList vector contained in a profile.
        short setCameraConnection(unsigned short profileIndex, unsigned short cameraID, std::string newCameraType)
        {
            if (profileExists(profileIndex))
            {
                if (cameraID < profileList.at(profileIndex).cameraList.size())
                {
                    if (newCameraType == "Static")
                    {
                        profileList.at(profileIndex).cameraList.at(cameraID).connection = Static;
                        return 0;
                    }

                    else if (newCameraType == "USB")
                    {
                        profileList.at(profileIndex).cameraList.at(cameraID).connection = USB;
                        return 0;
                    }

                    else if (newCameraType == "Ethernet")
                    {
                        profileList.at(profileIndex).cameraList.at(cameraID).connection = Ethernet;
                        return 0;
                    }


                    else if (newCameraType == "WiFi")
                    {
                        profileList.at(profileIndex).cameraList.at(cameraID).connection = WiFi;
                        return 0;
                    }

                    else if (newCameraType == "Serial")
                    {
                        profileList.at(profileIndex).cameraList.at(cameraID).connection = Serial;
                        return 0;
                    }

                    else return -1;
                }

                else return -1;
            }

            else return -1;
        }

        //Function to set a camera's port within the cameraList vector contained in a profile.
        short setCameraPort(unsigned short profileIndex, unsigned short newCameraPort, unsigned short cameraID)
        {
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).cameraList.at(cameraID).cameraPort = newCameraPort;
                return 0;
            }

            else return -1;
        }

        //Function to grab a new frame and place it into frameMatrix.
        short grabFrame()
        {
            if (currentCameraView->isOpened())
            {
                currentCameraView->grab();   //Grabs the next frame from the camera as a pointer.
                *currentCameraView >> *currentFrameMatrix;    //Read, decode, and pass the next frame into frameMatrix.
            }

            else return -1;
        }

        short readVideoStream()
        {
            if (currentCameraView->isOpened())
            {
                while (currentCameraView->isOpened())
                {
                    grabFrame();
                    cv::imshow("Video Stream Test", *currentFrameMatrix);   //Display the image within an OpenCV GUI window.
					if (cv::waitKey(30) >= 0) break; //TODO: 30 millisecond delay with boost (refresh rate).
                }

                return 0;
            }

            else return -1;
        }

		/* File Verification Functions */
		
		//Check if file exists in same directory as executable.
		bool fileExistsInDirectory(std::string fileName)
		{
			return boost::filesystem::exists(boost::filesystem::current_path().string() + "\\" + fileName);
		}

        /* Constructors and Destructors */

        //Default Constructor
        VideoProcessing()
        {
			if (fileExistsInDirectory("OpenVISData.txt"))
			{
				std::ifstream dataFile("OpenVISData.txt");
				std::string dataFileLineTemp;
				//TODO: Verify Data, then parse it.
				dataFile.seekg(dataFile.beg);
				while (!dataFile.eof())
				{
					for (int i = 0; i < PROFILEDATALINECOUNT; i++)
					{
						Profile tempProfile;
						std::getline(dataFile, dataFileLineTemp);	//Skip first line.
						std::getline(dataFile, dataFileLineTemp);	//Read in second line.
						

					}
				}

				
			}
			
			else
			{
				std::ofstream defaultOutputFile("OpenVISData.txt");
				defaultOutputFile.close();
			}

			setcurrentCameraView();

            /* frameMatrix will point to a new matrix that has the size of 640*480,
             * with a default type of an 8-bit scalar of unsigned char types and
             * a channel length of 3. The default value of each channel is 0. */
            if (currentFrameMatrix != nullptr)
                delete currentFrameMatrix;

            currentFrameMatrix = nullptr;
            currentFrameMatrix = new cv::Mat(640, 480, CV_8UC3, cv::Scalar(0, 0, 0));

            //Sets the default X and Y values of objectLocation to 0.
            objectLocation.xCoordinate = 0; objectLocation.yCoordinate = 0;
        }

        //Constructor that sets the size of the matrix its type.
        VideoProcessing(CartesianCoordinates matrixSize, int type)
        {
            //Verify that currentCameraView is not attached to any video feed.
            if(currentCameraView->isOpened())
                currentCameraView->release();

            /* frameMatrix will point to a new matrix that has the size of matrixSize, with a
             * default type of the user-defined type. The default value of each channel is 0. */
            if (currentFrameMatrix != nullptr)
                delete currentFrameMatrix;

            currentFrameMatrix = nullptr;
            currentFrameMatrix = new cv::Mat(matrixSize.xCoordinate, matrixSize.yCoordinate, type, cv::Scalar(0, 0, 0));

            //Sets the default X and Y values of objectLocation to 0.
            objectLocation.xCoordinate = 0; objectLocation.yCoordinate = 0;
        }

        //Constructor that sets the size of the matrix, its type, and each channel's initial value.
        VideoProcessing(CartesianCoordinates matrixSize, int type, cv::Scalar initialValue)
        {
            //Verify that currentCameraView is not attached to any video feed.
            if(currentCameraView->isOpened())
                currentCameraView->release();

            /* frameMatrix will point to a new matrix that has the size of matrixSize, with a default
             * type of the user-defined type. The default value of each channel is initialValue. */
            if (currentFrameMatrix != nullptr)
                delete currentFrameMatrix;

            currentFrameMatrix = nullptr;
            currentFrameMatrix = new cv::Mat(matrixSize.xCoordinate, matrixSize.yCoordinate, type, initialValue);

            //Sets the default X and Y values of objectLocation to 0.
            objectLocation.xCoordinate = 0; objectLocation.yCoordinate = 0;
        }

        //Destructor to deallocate heap memory.
        ~VideoProcessing()
        {
            delete currentFrameMatrix; //Deallocates the matrix object that frameMatrix is pointing to in heap memory.
            currentFrameMatrix = nullptr;
        }
};

#endif // VIDEOPROCESSING_H
