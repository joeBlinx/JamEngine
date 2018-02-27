//
// Created by stiven on 17-10-31.
//

#include <glish/program/programPipeline.hpp>
#include <glish/program/separableProgram.hpp>
#include <GL/glu.h>
#include <GL/gl.h>

namespace  glish {
    ProgramPipeline::ProgramPipeline() {
        glCreateProgramPipelines(1, &pipeline);
        getError();
        bind();
    }


    ProgramPipeline::~ProgramPipeline() {
        glDeleteProgramPipelines(1, &pipeline);
        getError();

    }

    void ProgramPipeline::use(const SeparableProgram &program) {
        glUseProgramStages(pipeline, program.getTypeShader(), program);
        glish::getError();

    }

    void ProgramPipeline::bind() {
        glUseProgram(0);
        glBindProgramPipeline(pipeline);
        getError();
    }
}