//
// Created by stiven on 17-10-28.
//
#include <utils/log.hpp>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glu.h>

namespace glish{
    void getError(){
        GLenum error = glGetError();
        if (error) {
            std::cout << gluErrorString(error) << std::endl;
            assert(false);
        }
    }
}