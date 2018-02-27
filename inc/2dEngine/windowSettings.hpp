//
// Created by darkblinx on 29/06/17.
//

#ifndef JAMENGINE_WINDOWSETTINGS_HPP
#define JAMENGINE_WINDOWSETTINGS_HPP

#include <string>
namespace JamEngine {

    struct windowSettings{

        std::string title{"no title"};
        int width = 800;
        int height = 600;
	    unsigned majorVersion = 3;
	    unsigned minorVersion = 3;
        bool doubleBuffer = true;
        unsigned depthBits = 8;
        unsigned stencilBits = 1;


    };
}
#endif //GLENGINE_WINDOWSETTINGS_HPP
