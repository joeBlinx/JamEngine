//
// Created by stiven on 18/03/16.
//

namespace glish {

    template <typename T>
    void Uniform<T>::operator=(const int value){
        static_assert(std::is_same<type, int>::value, "Uniform's type is not int");
        glProgramUniform1i(prog->getProgram(), uni, value);
        getError();
    }
    template <typename T>
    void Uniform<T>::operator=(const float value){
        static_assert(std::is_same<type, float>::value, "Uniform's type is not float");
        glProgramUniform1f(prog->getProgram(), uni, value);
        getError();
    }
    template <typename T>
    void Uniform<T>::operator=(const double value){
        static_assert(std::is_same<type, double>::value, "Uniform's type is not double");
        glProgramUniform1d(prog->getProgram(), uni, value);
        getError();
    }
    template <typename T>
    void Uniform<T>::operator=(const glm::vec2 &value) {
        static_assert(std::is_same<type, glm::vec2>::value, "Uniform's type is not glm::vec2");

        glProgramUniform2fv(prog->getProgram(), uni, 1, glm::value_ptr(value));
        getError();
    }

    template <typename T>
    void Uniform<T>::operator=(const glm::vec3 &value) {
        static_assert(std::is_same<type, glm::vec3>::value, "Uniform's type is not glm::vec3");
        glProgramUniform3fv(prog->getProgram(), uni, 1, glm::value_ptr(value));
        getError();
    }

    template <typename T>
    void Uniform<T>::operator=(const glm::mat3 &value) {
        static_assert(std::is_same<type, glm::mat3>::value, "Uniform's type is not glm::mat3");
        glProgramUniformMatrix3fv(prog->getProgram(), uni, 1, GL_FALSE, glm::value_ptr(value));
        getError();
    }

    template <typename T>
    void Uniform<T>::operator=(const glm::mat4 &value) {
        static_assert(std::is_same<type, glm::mat4>::value, "Uniform's type is not glm::mat4");
        glProgramUniformMatrix4fv(prog->getProgram(), uni, 1, GL_FALSE, glm::value_ptr(value));
        getError();

    }

    template <typename T>
    void Uniform<T>::operator=(const bool value) {
        static_assert(std::is_same<type, bool>::value, "Uniform's type is not bool");
        glProgramUniform1i(prog->getProgram(), uni, value);
        getError();
    }

    template <typename T>
    void Uniform<T>::operator=(const glm::mat2 &value) {
        static_assert(std::is_same<type, glm::mat2>::value, "Uniform's type is not glm::mat2");
        glProgramUniformMatrix2fv(prog->getProgram(), uni, 1, GL_FALSE, glm::value_ptr(value));
        getError();

    }

    template <typename T>
    void Uniform<T>::operator=(const glm::vec4 &value) {
        static_assert(std::is_same<type, glm::vec4>::value, "Uniform's type is not glm::vec4");
        glProgramUniform4fv(prog->getProgram(), uni, 1, glm::value_ptr(value));


    }


}

