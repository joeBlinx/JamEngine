//
// Created by stiven on 14/12/15.
//


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glish/Texture.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utils/log.hpp>
#include <stringUtil.h>
#include <array>

namespace glish {

    GLuint Texture::get() const {
        return text;
    }

    void Texture::bindTexture(int number) const {
        if (text != 0) {
            glActiveTexture(GL_TEXTURE0 + number);
            getError();
            glBindTexture(target, text);
            getError();
        }else{
            std::cerr << "Texture is not initialized" << std::endl;
        }

    }
    Texture::Texture(std::string const & image, GLenum target):target(target) {

        glGenTextures(1, &text);
        getError();
        glBindTexture(target, text);
        getError();

	    loadTexture(image, target);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        getError();
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        getError();
        glBindTexture(target, 0);
        getError();


    }

    Texture::Texture(GLuint texture, GLenum target):text(texture), target(target) {

    }

    Texture::Texture(Texture &&texture):text(texture.text), target(texture.target) {
        texture.text = 0;
    }

    Texture::Texture() {


    }

	Texture::Texture(GLenum target) :target(target){
		glGenTextures(1, &text);
		getError();
		glBindTexture(target, text);
		getError();
	}

	void Texture::loadTexture(std::string const &path, GLenum target) {
		SDL_Surface *surface = IMG_Load(path.c_str());
		if(!surface){
			throw std::runtime_error(IMG_GetError());
		}
		std::string extension = utils::extractExtension(path);
		if(extension == ".tga"){
			glTexImage2D(target, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
		}else if (extension == ".bmp"){
			glTexImage2D(target, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
		}else if (extension == ".png"){
			glTexImage2D(target, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		}else if (extension ==".jpg" || extension == ".jpeg"){
			glTexImage2D(target, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

		}
		getError();

		SDL_FreeSurface(surface);

	}

    Texture &Texture::operator=(Texture &&texture) {
        text = texture.text;
        target = texture.target;
        texture.text = 0;
        return *this;
    }

    Texture::~Texture() {
        if(text != 0 && !hasBeenCopied) {
            glDeleteTextures(1, &text);
            getError();
        }
    }

    Texture Texture::makeDepthTexture(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glBindTexture(GL_TEXTURE_2D, 0);
        return Texture(texture, GL_TEXTURE_2D);
    }

    Texture Texture::makeEmptyTexture() {
        GLuint texture;
        GLfloat empty[] ={128, 128, 128, 255};
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0 ,GL_RGBA, GL_FLOAT, empty);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glBindTexture(GL_TEXTURE_2D, 0);
        return Texture(texture, GL_TEXTURE_2D);
    }

    Texture::Texture(const Texture & oldTexture): text(oldTexture.text), target(oldTexture.target) {
        oldTexture.hasBeenCopied = true;
    }

    Texture &Texture::operator=(Texture const &oldTexture) {
        text = oldTexture.text;
        target = oldTexture.target;
        oldTexture.hasBeenCopied = true;
        return *this;
    }

    Texture Texture::makeTextureCubeMap(const std::array<std::string, 6> &pathImage) {
	    Texture texture(GL_TEXTURE_CUBE_MAP);

	    for(int i = 0; i < pathImage.size() ; i++){
		    texture.loadTexture(pathImage[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X +i);
	    }

	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	    return texture;
    }
}