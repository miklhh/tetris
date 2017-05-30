# Tetris
A tetris replica written in C++ for Windows and Linux.

### Prerequisites
This application is written with and requires SDL2. For Windows builders, Visual Studio 2017 is required to build the application. See links for more information.

* [SDL - Simple Directmedia Layer](https://www.libsdl.org/) - Multimedia library used.
* [Microsoft Visual Studio 2017](https://www.visualstudio.com/) - Development tool for Windows users.


### Build
***Linux*** users build the application by running the make-script in the repository top folder. On running the make-script a new directory *build* will be created and the output file *tetris* can be found and run from the folder. To run the make-script type *make* whils standing in the tetris top folder. For the build to work on a Linux machines, SDL2 must be installed to its standard path.

***Windows*** users have to manually add their *Include directory* and *Library directory* to their solution to build the application. If you are uncertain how this is done, you can follow __step 3 - 9__ in [this guide](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php) (hyperlink).

## Authors
* **Mikael Henriksson** - *Code and multimedia* - [https://github.com/miklhh](https://github.com/miklhh)
