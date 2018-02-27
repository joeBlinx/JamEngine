#include <vector>
#include <GL/glew.h>


namespace glish{

    template<typename T>
    Vbo::Vbo(GLuint index, const std::vector<T> &data, GLenum target ) {
        glGenBuffers(1,&vbo); getError();
        glBindBuffer(target,vbo); getError();
        glBufferData(target,data.size()*sizeof(T),data.data(),GL_STATIC_DRAW);
        getError();
        glEnableVertexAttribArray(index); getError();
        glVertexAttribPointer(
                index,
                trait<T>::size,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *)0
        );
        getError();
    }

}