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

        /* Profile Modifiers */
        void addProfile()
        {
            Profile tempProfile;
            //Signal Code from UI to assign instance data to profile.
            //After "Add" has been hit:
            profileList.push_back(tempProfile);
        }

        void removeProfile()
        {
            short indexToRemove;
            //List profiles contained in profileList in combo box, select which one to remove.
            //After "Remove" has been hit:
            profileList.erase(myVector.begin + indexToRemove);
        }

        void AddNewCamera()
        {

        }

        ~VideoProcessing();

    signals:

    public slots:
};

#endif // VIDEOPROCESSING_H
