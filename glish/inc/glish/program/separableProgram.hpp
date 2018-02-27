//
// Created by stiven on 17-11-03.
//

#ifndef ALLPROJECT_SEPARABLEPROGRAM_HPP
#define ALLPROJECT_SEPARABLEPROGRAM_HPP

#include "Program.hpp"
#include <GL/glu.h>
#define addBit(type) type ## _BIT
namespace glish {
    class SeparableProgram : public Program {
        GLenum typeShader = 0;

        template<class ...Shaders, class OneShader>
                void whichShader(OneShader const & shader, Shaders const & ...shaders){
            typeShader = typeShader | chooseTypeShaderBit(shader.shaderType);
            if constexpr (sizeof...(shaders)){
                whichShader(shaders...);
            }
        }

        GLenum chooseTypeShaderBit(GLenum type);
    public:
        template <class ... Shader>
                SeparableProgram(Shader && ... shaders){
            createProgram();
            glProgramParameteri(getProgram(), GL_PROGRAM_SEPARABLE, GL_TRUE);
            glish::getError();

            whichShader(shaders...);
            initProgram(std::forward<Shader>(shaders)...);
        }

        GLuint getTypeShader() const;
    };
}


#endif //ALLPROJECT_SEPARABLEPROGRAM_HPP
