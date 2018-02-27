//
// Created by darkblinx on 01/08/17.
//

#ifndef GLENGINE_PROGRAMGL_HPP
#define GLENGINE_PROGRAMGL_HPP

#include <glish/program/Program.hpp>
#include <glish/Uniform.hpp>
#include <utility>
#include <optional>
#include <utils/type_trait.h>
#include <utils/templateUtils.h>

namespace glish {
    template<class Enum, class ...T >
    class ProgramGL {
        template<class = std::enable_if_t<std::is_enum<Enum>::value>>
        struct test;
        template <class First, class ...U>
        struct uniforms{
            Uniform<First> uni;
            uniforms<U...> next;
            template <class ... Args>
                    void init(Program * program, std::string && first, Args &&...args)
            {
                uni.init(program, std::move(first));
                next.init (program, std::forward<Args>(args)...);
            }

            template <Enum uniform>
                    auto & get(){
                constexpr auto num = static_cast<int>(uniform);
                if constexpr (num == 0){
                    return uni;
                }else{
                    return next.template get<static_cast<Enum>(num-1)>();
                }
            }
            template <Enum uniform, class V>
                void set(V && value){
                constexpr auto num = static_cast<int>(uniform);
                if constexpr (num == 0){
                    uni = std::forward<V>(value);
                }else{
                    next.template set<static_cast<Enum>(num-1)>(std::forward<V>(value));
                }
            }

        };
        template <class End>
        struct uniforms<End>{
            Uniform<End> uni;
            void init (Program * program, std::string && first) {
                uni.init(program, std::move(first));
            }

            template <Enum uniform>
            auto & get(){
                constexpr auto num = static_cast<int>(uniform);
                if constexpr (num == 0){
                    return uni;
                }else{
                    static_assert(num != 0, "too deep in recursion, uniform doesn't exist");
                }
            }
            template <Enum uniform, class V>
            void set(V && value){
                constexpr auto num = static_cast<int>(uniform);
                if constexpr (num == 0){
                    uni = std::forward<V>(value);
                }else{
                    static_assert(num != 0, "too deep in recursion, uniform doesn't exist");
                }
            }
        };
        Program program;
        uniforms<T...> allUniforms;
        bool initialized = false;
    public:
        template <class ...Args>
        ProgramGL(Args && ...args):program(std::forward<Args>(args)...){}
        /**
         *
         * @tparam PathShader
         * @param path vertex, fragment, geometry
         */
        template <class ... UniformName>
                void init (UniformName &&... path){
            if(initialized){
                throw std::runtime_error("Uniform already initialized");
            }
            static_assert(sizeof...(path) == sizeof...(T), "not same number for uniform and path to it");
            initialized = true;
            allUniforms.init(&program, std::forward<UniformName>(path)...);
        }

        template <Enum uniform>
                auto & get(){
            if(!initialized){
                throw std::runtime_error("Uniform not initialized");
            }
            return allUniforms.template get<uniform>();
        }



        template <Enum uniform, class V>
        void set(V && value) {
            if (!initialized) {
                throw std::runtime_error("Uniform not initialized");
            }
            if constexpr (utils::is_optional<V>::value){
                if(!value){
                    return;
                }
                return allUniforms.template set<uniform>(std::forward<decltype(*value)>(*value));

            }else{
                return allUniforms.template set<uniform>(std::forward<V>(value));
            }
        }

        void use(){
            program.useProgram();
        }
    };

}

#endif //GLENGINE_PROGRAMGL_HPP
