//
// Created by stiven aigle on 27/01/16.
//

#include <glish/Vbo.hpp>

namespace glish {

    Vbo::Vbo(Vbo &&orig) : vbo(orig.vbo), target(orig.target) {
        orig.vbo = 0;
    }

    Vbo&  Vbo::operator=(Vbo &&orig) {
        if (&orig != this) {
            deleteBuffer();
            vbo = orig.vbo;
            orig.vbo = 0;
            target  = orig.target;
        }
        return *this;
    }

    Vbo::~Vbo() {
       deleteBuffer();
    }

    void Vbo::deleteBuffer() {
        if(!hasBeenCopied) {
            glDeleteBuffers(1, &vbo);
            getError();
        }
    }


    GLuint Vbo::getVbo() {
        return vbo;
    }

    Vbo::Vbo():vbo(0) {

    }

    Vbo::Vbo(std::vector<int> const &elements):target(GL_ELEMENT_ARRAY_BUFFER) {

        glGenBuffers(1, &vbo);getError();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);getError();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*elements.size(), elements.data(), GL_STATIC_DRAW);getError();


    }

    void Vbo::bind() const {
        glBindBuffer(target, vbo);
    }

    Vbo::operator bool() const{
        return vbo != 0;
    }

    Vbo::Vbo(Vbo const &vbo):vbo(vbo.vbo), target(vbo.target) {
        vbo.hasBeenCopied = true;

    }

    Vbo &Vbo::operator=(Vbo const &vbo) {
        this->vbo = vbo.vbo;
        this->target = vbo.target;

        vbo.hasBeenCopied = true;
        return *this;
    }
}