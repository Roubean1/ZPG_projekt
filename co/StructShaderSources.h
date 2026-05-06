#pragma once
#include <string>

struct ShaderPair {
    std::string vertex;
    std::string fragment;
};

namespace ShaderSources {
    extern const ShaderPair Constant;
    extern const ShaderPair Lamb;
    extern const ShaderPair Phong;
    extern const ShaderPair Blinn;
    extern const ShaderPair Skybox;
}