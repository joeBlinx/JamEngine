//
// Created by darkblinx on 27/06/17.
//

#include <stdexcept>
#include <window.hpp>
#include <windowSettings.hpp>
#include <GL/glew.h>
#include <glish/utils//log.hpp>


namespace JamEngine {
    Window::~Window() {
        SDL_GL_DeleteContext(m_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    Window::Window(windowSettings const & settings) {
        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            throw std::runtime_error("error while initialize SDL2 " + std::string{SDL_GetError()});
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.majorVersion);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minorVersion);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settings.doubleBuffer);

        m_window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.width, settings.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if(!m_window){
            std::string erreur {SDL_GetError()};
            SDL_Quit();
            throw std::runtime_error("error while initialize window "+erreur);
        }

        m_context = SDL_GL_CreateContext(m_window);
	    glewExperimental = GL_TRUE;
	    auto err = glewInit();
	    if(err!= GLEW_OK){
		    std::cerr << glewGetErrorString(err) << std::endl;
		    throw std::runtime_error("error while initialize glew" );
	    }
	    glGetError();
	    glClearColor(0.5, 0.5, 0.5, 1);
	    glGetError();
		glEnable (GL_BLEND);
		glGetError();
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glGetError();

	}

    SDL_Window *Window::getWindow() {
        return m_window;
    }




}