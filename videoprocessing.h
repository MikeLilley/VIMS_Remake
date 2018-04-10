#ifndef VIDEOPROCESSING_H
#define VIDEOPROCESSING_H

#include <vector>
#include "QObject"
#include "vimsstructs.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

class VideoProcessing : public QObject  //Class to filter and produce video.
{
    Q_OBJECT

    private:
        /* Instance Variables */
        std::vector<Profile> profileList;   //Vector to store all recorded profiles.
        cv::VideoCapture cap();   //VideoCapture variable to specify the current camera being used.
        CartesianCoordinates objectLocation;    //CartesianCoordinates variable to store coordinates of a tracked object.

    public:
        explicit VideoProcessing(QObject *parent = nullptr);

        /* Profile Mutators and Accessors */

        //Function to check if a profile exists based on its index within the profileList vector.
        bool profileExists(unsigned short &profileIndex)
        {
            if (profileIndex < profileList.size())
                return true;

            else return false;
        }

        //Subroutine to add a profile to the profileList vector.
        void addProfile(Profile &tempProfile) { profileList.push_back(tempProfile); }

        //Function to remove a profile contained within the profileList vector.
        int removeProfile(unsigned short &profileIndex)
        {
            //List profiles contained in profileList in combo box, select which one to remove.
            //After "Remove" has been hit:
            if (profileExists(profileIndex))
            {
                profileList.erase(profileList.begin() + profileIndex);
                return 0;
            }

            else return -1;
        }

        //Function to set the name of a profile contained within the profileList vector.
        int setProfileName(unsigned short &profileIndex, std::string &newProfileName)
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
        int addNewCamera(unsigned short &profileIndex, Camera &newCamera)
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
        int removeCamera(unsigned short &profileIndex, unsigned short &cameraID)
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
        int setCameraName(unsigned short &profileIndex, unsigned short &cameraID, std::string &newCameraName)
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
        std::string getCameraName(unsigned short &profileIndex, unsigned short &cameraID)
        {
            if (profileExists(profileIndex))
                return profileList.at(profileIndex).cameraList.at(cameraID).cameraName;

            else return "-1";
        }

        //Function to set a camera's type of connection within the cameraList vector contained in a profile.
        int setCameraConnection(unsigned short &profileIndex, unsigned short &cameraID, std::string &newCameraType)
        {
            if (profileExists(profileIndex))
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

        //Function to set a camera's port within the cameraList vector contained in a profile.
        int setCameraPort(unsigned short &profileIndex, unsigned short &newCameraPort, unsigned short &cameraID)
        {
            if (profileExists(profileIndex))
            {
                profileList.at(profileIndex).cameraList.at(cameraID).cameraPort = newCameraPort;
                return 0;
            }

            else return -1;
        }

        //~VideoProcessing();   TODO: Create Destrutor

    signals:

    public slots:
};

#endif // VIDEOPROCESSING_H
