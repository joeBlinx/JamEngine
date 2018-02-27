//
// Created by stiven on 14/12/15.
//


#include <fstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <GL/glew.h>
#include <glish/utils//log.hpp>
#include <glish/program/Program.hpp>

namespace glish {

    void Program::useProgram() {
        glUseProgram(programID);
        getError();

    }

    GLuint Program::getProgram() {
        return programID;
    }

    Program::~Program() {
        if (programID) {
            glDeleteProgram(programID);
            getError();
        }
    }

    std::string Program::extractShader(const char *path) {

        std::string shaderCode;
        std::ifstream shaderStream(path);
        std::string shader(path);
        if (!shaderStream.is_open()) {
            throw std::runtime_error("probleme ouverture fichier " + shader);
        }
        std::string read;
        while (getline(shaderStream, read)) {
            shaderCode += "\n" + read;
        }
        std::cout << "compiling shader " << shader << std::endl;
        return shaderCode;
    }

    GLuint Program::compileShader(const std::string &shader, GLenum type) {
        GLuint shaderId = glCreateShader(type);
        getError();
        char const *shaderSource = shader.c_str();
        GLint result = GL_FALSE;
        int infoLog;
        glShaderSource(shaderId, 1, &shaderSource, NULL);
        getError();
        glCompileShader(shaderId);
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        getError();
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLog);
        getError();
        if (infoLog > 0) {
            std::vector<char> VertexShaderErrorMessage(infoLog + 1);
            glGetShaderInfoLog(shaderId, infoLog, NULL, &VertexShaderErrorMessage[0]);
            getError();
            std::cout << &VertexShaderErrorMessage[0] << std::endl;
        }
        return shaderId;
    }


    void Program::compileProgram(GLuint &shader) {
        {
            glAttachShader(programID, shader);
            getError();
            glLinkProgram(programID);
            getError();
            glDetachShader(programID, shader);
            getError();
            glDeleteShader(shader);
            getError();
            GLint Result;
            int InfoLogLength;
            glGetProgramiv(programID, GL_LINK_STATUS, &Result);
            getError();
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            getError();
            if (InfoLogLength > 0) {
                std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
                glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
                printf("%s\n", &ProgramErrorMessage[0]);
                getError();
            }

        }
    }


    Program &Program::operator=(Program &&prog) {
        programID = prog.programID;
        prog.programID = 0;
        return *this;
    }

    Program::Program(Program &&prog) : programID(prog.programID) {
        prog.programID = 0;

    }

    void Program::createProgram() {
        programID = glCreateProgram();
        getError();
    }

    Program::Program() {
//        createProgram();
    }


}

