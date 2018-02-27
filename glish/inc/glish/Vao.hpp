//
// Created by darkblinx on 01/08/17.
//

#ifndef GLENGINE_VAO_HPP
#define GLENGINE_VAO_HPP

#include "Vbo.hpp"
#include <utility>
#include <array>
namespace glish {

    template<unsigned nbVbo>
    class Vao {
        GLuint vao;
        std::array<Vbo, nbVbo> vbos;
        int i = 0;
        Vbo elements ;
        mutable bool hasBeenCopied = false;
    public:

        Vao();

        Vao(Vao const & a);

        Vao& operator=(Vao const &);

        Vao(Vao &&vao);

        Vao& operator=(Vao && vao);
        template<class  T>
        void addVbo(GLuint index, const std::vector<T> &data, GLenum target = GL_ARRAY_BUFFER);

        ~Vao();

        /*!\brief permet de récuperer l'identifiant du VAO*/
        const GLuint &getName() const;

        /*!\brief permet de bind le vao, spécifie que c'est ce vao sur lequel on travaille
         */
        void bind() const;

        void unbind() const;

        void addIndices(std::vector<int> const & indices);

    };

    template<unsigned nbVbo>
    Vao<nbVbo>::Vao(Vao const & vao):vao(vao.vao), vbos(vao.vbos), elements(vao.elements){
        vao.hasBeenCopied  = true;
    }
    template<unsigned nbVbo>
    Vao<nbVbo>::Vao() {
        glGenVertexArrays(1, &vao);
        getError();

    }

    template<unsigned nbVbo>
    Vao<nbVbo>::~Vao() {
        if(!hasBeenCopied) {
            glDeleteVertexArrays(1, &vao);
            getError();

        }

    }

    template<unsigned nbVbo>
    Vao<nbVbo>::Vao(Vao &&vao) :vao(vao.vao), vbos(vao.vbos), elements(std::move(vao.elements)) {
        vao.vao = 0;
    }

    template<unsigned nbVbo>
    const GLuint &Vao<nbVbo>::getName() const {
        return vao;
    }

    template<unsigned nbVbo>
    void Vao<nbVbo>::bind() const {
        glBindVertexArray(vao);
        getError();
        if(elements){
            elements.bind();
            getError();
        }
    }

    template <unsigned nbVbo>
    template <class T>
    void Vao<nbVbo>::addVbo(GLuint index, const std::vector<T> &data, GLenum target){
        if(i == nbVbo){
            throw std::runtime_error("too many Vbo added to vao " + std::to_string(nbVbo));
        }
        bind();
        vbos[i++] = Vbo(index, data, target);

    }
    template <unsigned nbVbo>
    void Vao<nbVbo>::addIndices(std::vector<int> const &indices) {
        bind();
        elements = Vbo(indices);

    }
    template <unsigned nbVbo>
    void Vao<nbVbo>::unbind() const {
        glBindVertexArray(0);

    }

    template <unsigned nbVbo>
    Vao<nbVbo> &Vao<nbVbo>::operator=(Vao &&vao) {
        this->vao = vao.vao;
        vbos = vao.vbos;
        elements = std::move(vao.elements);
        vao.vao = 0;
        return *this;
    }
    template <unsigned nbVbo>
    Vao<nbVbo> &Vao<nbVbo>::operator=(Vao const & vao) {
        vao.hasBeenCopied = true;
        this->vao = vao.vao;
        vbos = vao.vbos;
        elements = vao.elements;
        return *this;
    }
}
#endif //GLENGINE_VAO_HPP
