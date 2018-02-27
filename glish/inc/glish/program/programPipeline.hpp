//
// Created by stiven on 17-10-31.
//

#ifndef ALLPROJECT_PROGRAMPIPELINE_H
#define ALLPROJECT_PROGRAMPIPELINE_H

#include <GL/glew.h>

namespace glish{
    class  SeparableProgram;
    class ProgramPipeline {
        GLuint pipeline;
    public:

        ProgramPipeline();

        void use(const SeparableProgram &program);
        void bind();

        ~ProgramPipeline();

    };
}
#endif //ALLPROJECT_PROGRAMPIPELINE_H
