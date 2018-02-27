//
// Created by stiven on 17-11-03.
//

#include "glish/program/separableProgram.hpp"

GLuint glish::SeparableProgram::getTypeShader() const {

    return typeShader;

}

GLenum glish::SeparableProgram::chooseTypeShaderBit(GLenum type) {

    switch (type) {
        case GL_VERTEX_SHADER:
            return GL_VERTEX_SHADER_BIT;
        case GL_GEOMETRY_SHADER:
            return GL_GEOMETRY_SHADER_BIT;
        case GL_FRAGMENT_SHADER:
            return GL_FRAGMENT_SHADER_BIT;
        case GL_COMPUTE_SHADER:
            return GL_COMPUTE_SHADER_BIT;
        case GL_TESS_EVALUATION_SHADER:
            return GL_TESS_EVALUATION_SHADER_BIT;
        case GL_TESS_CONTROL_SHADER:
            return GL_TESS_CONTROL_SHADER_BIT;
        default:
            return 0;
    }


}
