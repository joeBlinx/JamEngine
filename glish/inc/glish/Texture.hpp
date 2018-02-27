//
// Created by stiven on 14/12/15.
//

#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP
#include <GL/glew.h>
#include <string>
#include <array>
namespace glish {

//use PNG
    /*! \class Texture
     * \brief génere un identifiant de texture OpenGL
     */
    class Texture {
    private:
        GLuint text = 0;
        GLenum target;
        mutable bool hasBeenCopied = false;


	    void loadTexture(std::string const &path, GLenum target);
	    Texture(GLenum target);
    public:
	    Texture();
        /*!\param image: chemin vers l'image (en PNG) à texturer
         *
         */
        Texture(GLuint texture, GLenum target);
	    Texture(std::string const &image, GLenum target = GL_TEXTURE_2D)  ;

        Texture(const Texture &);

        Texture(Texture && texture);

        /*!
         * \brief bind la texture, spécifie que c'est celle ci que l'on utilisera
         */
        void bindTexture(int number) const ;
        Texture & operator=(Texture && texture)  ;
        Texture &operator=(Texture const & oldTexture);




        /*!
         * \brief permet de récuperer l'identifiant de la Texture
         */
        GLuint get() const;
        static Texture makeDepthTexture(int width, int height);
        static Texture makeEmptyTexture();
        static Texture makeTextureCubeMap(std::array<std::string, 6> const & pathImage);
        ~Texture();


    };
}
#endif //OPENGL_TEXTURE_HPP
