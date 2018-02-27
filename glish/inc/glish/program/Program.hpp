//
// Created by stiven aigle on 14/12/15.
//

#ifndef OPENGL_PROGRAM_HPP
#define OPENGL_PROGRAM_HPP

#include <GL/glew.h>
#include <string>
#include <vector>
#include <glish/utils//log.hpp>
#include <array>
#include <utility>

namespace glish {
    /*! \class Program
     * \brief Crée un program OpenGL
 *
 *
 * */
enum class compileType{
    FILE, STRING
};
    struct shaderFile{
        GLenum shaderType;
        const char * path;
        static constexpr compileType type = compileType ::FILE;
    };

    struct shaderString{
        GLenum shaderType;
        const char * path;
        static constexpr compileType type = compileType::STRING;

    };

    class Program {

        template<class Enum, class ...T >
        friend class ProgramGL;
        template<class T>
        friend class Uniform;
        friend  class ProgramPipeline;
        /*! \var  programID
        * identifiant du program*/
        GLuint programID;
        public:

        static std::string extractShader(const char * path);
        static GLuint compileShader(const std::string &shader, GLenum type);

        void compileProgram(GLuint &shader) ;

        template<class ... Is>
        void compileProgram(GLuint &first, Is &...next) {
            glAttachShader(programID, first);
            getError();
            compileProgram(next...);
            glDetachShader(programID, first);
            getError();

        }
        template <size_t size>
                void compileProgram(std::array<GLuint, size>  & shadersId){
            for(unsigned i = 0 ; i < size-1; i++){
                glAttachShader(programID, shadersId[i]);
            }
            compileProgram( shadersId.back());
            for(unsigned i = 0 ; i < size-1; i++){
                glDetachShader(programID, shadersId[i]);
                glDeleteShader(shadersId[i]);
            }
        }


        /*!
         * \param  vertexShader: path vers le Vertex shader
         * \param fragmentShader: path vers le Fragment shader
          *
         */
        template < size_t size, class shaderSetting, class ...shader>
        void init (std::array<GLuint, size> & shadersId, shaderSetting && oneShader, shader && ... shaders){
            auto constexpr n = size - 1 - sizeof...(shaders);
            std::string file = oneShader.path;
            if(shaderSetting::type == compileType::FILE){
                file = extractShader(oneShader.path);
            }
            shadersId[n] = compileShader(file, oneShader.shaderType);
            getError();
            if constexpr (n < size -1)
            {
                init(shadersId, std::forward<shader>(shaders)...);
            }
        }

        template <class ... Shader>
        void initProgram(Shader && ... shaders){

            std::array<GLuint, sizeof...(Shader)> shadersId;
            init(shadersId, std::forward<Shader>(shaders)...);
            compileProgram(shadersId);
        }

        void createProgram();
        template <class ...shader>
        Program(shader &&... shaders){
            createProgram();
            initProgram(std::forward<shader>(shaders)...) ;

        }
      /*  Program(char const *vertexShader, char const *fragmentShader);
        Program(char const *vertexShader, char const * fragmentShader, char const* geometryShader);*/
       /* void init(char const *vertexShader, char const *fragmentShader);
        void init(char const *vertexShader, char const * fragmentShader, char const* geometryShader);*/



        Program();

        /*!
         * \brief Le constructeur de copie a été détruit pour éviter les copies inutiles*/
        Program(Program const &) = delete;
        Program &operator=(Program const &) = delete;

        Program(Program && prog ) ;
        Program &operator=(Program && prog) ;

        /*!
        * \brief Permet de recuperer l'identifiant du program OpenGL*/
        GLuint getProgram();


        operator unsigned () const{ return  programID;};
        /*!
         * \brief Permet de spécifier à OpenGL que c'est ce program qu'on utilise
         * A utiliser avant chaque appel de fonction modidifiant les uniforms
         * associer a ce program*/
        void useProgram();



    protected:

        ~Program();

    };
}
#endif //OPENGL_PROGRAM_HPP
