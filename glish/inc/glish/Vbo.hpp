//
// Created by stiven chouette on 27/01/16.
//

#ifndef OPENGL_VBO_HPP
#define OPENGL_VBO_HPP



#include <vector>
#include <GL/glew.h>
#include <glish/utils//log.hpp>
#include <glish/utils/trait.hpp>

namespace glish {
    /*! \class Vbo
     * \brief génere un identifiant pour un Vertex Array Buffer, \n
     * c'est une suite de valeur envoyé à la carte graphique*/
    class Vbo {

        GLuint vbo;
        GLenum target;
        mutable  bool hasBeenCopied = false;
        template<unsigned nbVbo>
        friend class Vao;
        /* template<typename T>
        Vbo(GLuint index, GLint size, const std::vector<T> &data);*/
        template<typename T>
        Vbo(GLuint index, const std::vector<T> &data, GLenum target = GL_ARRAY_BUFFER);

        Vbo(std::vector<int> const & elements);
        /*!
         * \brief destruction du constructeur de copie
         */

        /*!
         * \brief redéfinition du constructeur de déplacement
         */
        /*!
         * \brief detruit le vbo
         */
        void deleteBuffer();

        /*!
         * \brief retourne l'identifiant du vbo
         * \return identifiant du vbo
         */
        GLuint getVbo();
        /*!
         * \brief redefinition de l'opérateur d'affectation\n
         * et destruction de orig
         * \param orig: Vbo que l'on utilise pour le réaffecter
         *
         */


        void bind()const;

       operator bool() const;
    public:
        /*!
         * \param index :identifiant qui sera utilisé dans le vertex shader pour récuperer les valeurs contenu dans le vbo
         * \param size :  nombre de valeur qui coresponde a un seul paramètre
         * \tparam T : type de valeur stockée dans le vector qui sera stockée dans le vbo
         * \param data : donnée stockée dans le vector*/

        Vbo();
        ~Vbo();
        Vbo(Vbo const & vbo) ;
        Vbo& operator=(Vbo const & vbo);
        Vbo &operator=(Vbo &&orig);
        Vbo(Vbo &&orig);



    };
}
//TODO : a changer ne permet pas d'utiliser des VBO plus complexes
#include <glish/Vbo.tpp>


#endif //OPENGL_VBO_HPP
