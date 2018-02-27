//
// Created by unnom on 09/10/16.
//

#ifndef GLISH_TRAIT_HPP
#define GLISH_TRAIT_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
namespace glish{

template <typename T>
    struct trait;
    template <>
    struct trait<float>{
        static constexpr int size = 1;
    };
     template <>
    struct trait<int>{
        static constexpr int size = 1;
    };
     template <>
    struct trait<double>{
        static constexpr int size = 1;
    };
    template <>
    struct trait<glm::vec2>{
        static constexpr int size = 2;
    };
    template <>
    struct trait<glm::ivec2>{
        static constexpr int size = 2;
    };
    template <>
    struct trait<glm::vec3>{
        static constexpr int size = 3;
    };
    template <>
    struct trait<glm::ivec3>{
        static constexpr int size = 3;
    };
     template <>
    struct trait<glm::vec4>{
        static constexpr int size = 4;
    };
    template <>
    struct trait<glm::ivec4>{
        static constexpr int size = 4;
    };


}
#endif //GLISH_TRAIT_HPP
