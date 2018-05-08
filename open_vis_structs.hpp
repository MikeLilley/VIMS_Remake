#ifndef VIMSSTRUCTS_H
#define VIMSSTRUCTS_H

#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"

/* Structs, Enumerations */

//Defines supported camera connection types.
enum cameraType {Static, USB, Ethernet, WiFi, Serial};

//Defines a generic structure to store x-y values for anything that uses cartesian coordinates.
struct CartesianCoordinates
{
    unsigned short xCoordinate;
    unsigned short yCoordinate;
};

//Defines a structure to store data about a camera.
struct Camera
{
    std::string cameraName; //Variable to store name of camera.
    cameraType connection;  //Enumerated variable to store connection type.
    unsigned short cameraPort;  //Variable to store port ID if connection type is Wireless.
    unsigned short cameraID;    //Variable to store the ID of a camera.
    CartesianCoordinates defaultResolution;   //CartesianCoordinates variable to store resolution of video stream.
	unsigned short cameraFPS;	//Variable to store the default FPS of a camera stream.
};

//Defines a generic structure to be used for coloring certain elements of the overlay.
struct rgbColor
{
    unsigned short redValue;
    unsigned short greenValue;
    unsigned short blueValue;
};

//Defines a structure to store on-off states of certain overlay elements.
struct uiElements
{
    bool displayHUD;    //If true, turn on the overlay.
    bool trackingMode;   //If true, the object's coordinates are tracked and surrounded by a contour.
    bool displayFpsCounter;    //If true, display FPS counter in overlay.
    bool displayTimeAndDate;   //If true, display time and date in overlay.
    bool displayVideoResolution;    //If true, display the video resolution in overlay.
    rgbColor defaultColorScheme;    //rgbColor variable to store default color of HUD.
};

//Defines the structure for a profile.
struct Profile
{
    std::string name;   //Name of profile.
    uiElements defaultUiSettings;   //Default UI settings for profile.
    std::vector<Camera> cameraList; //Vector of Cameras to store list of cameras associated with profile.
};

#endif // VIMSSTRUCTS_H
