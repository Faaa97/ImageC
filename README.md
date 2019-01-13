# ImageC

ImageC is a image processing program, taking ImageJ as a base.
It's built using wxWidgets and C++.

## What it can do
* Open and save image files.
* See image related info.
* See accumulative and absolute histogram.
* Convert to grayscale.
* Threshold.
* Resizing image.
* Rotation (90º).
* Lineal Transformation
* Lineal brightness and contrast fit.
* Histogram Equalizer.
* Histogram especification.
* Gamma correction
* Image difference.

## RoadMap
This is the planned work and scope of the project.
There are 3 types of tasks:
* TODO
* BUG
* UNDONE
TODO is obligatory work, it must be 100% functional. Normal priority.
BUG is highlighting some bugs that must be taken care of before release. Normal priority.
UNDONE is optional work, should be addressed if there is spare time. Low priority.

### TODO

* Region of Interest
* Horizontal and vertical flip.
* Transpose of an image.
* Image scaling
* Image Rotation (any angle)

### UNDONE

* Show entropy in image info
* Image-Cross Section
* Image digitalization simulation
* 
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

You'll need:
* Visual Studio 2017 or later
* wxWidgets-3.0.4 or later

### Installing

For easy installing wxwidgets, get windows installer here: [wxWidgets](https://www.wxwidgets.org/downloads/)
Then go to ImageC.sln and ImageC.vcxproj and replace every "c:\wxWidgets-3.0.4\ ..." with your wxwdigets folder.

Then open ImageC.sln with Visual Studio and you are ready to build in Debug mode.

## Built With

* [wxWidgets](https://www.wxwidgets.org/downloads/) - Library for GUI
* [Visual Studio Community 2017](https://visualstudio.microsoft.com/es/) - IDE

## Contributing

No contributing, pull requests are blocked.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/Faaa97/ImageC/tags). 

## Authors

* Felipe Álvarez Avaria - [Faaa97](https://github.com/Faaa97)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [ImageJ](https://imagej.nih.gov/ij/)
* [Principles of Digital Image Processing](https://doi.org/10.1007/978-1-84800-191-6)

