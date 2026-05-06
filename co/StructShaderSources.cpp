#include "StructShaderSources.h"

const ShaderPair ShaderSources::Constant = { "ShaderSource/standard.vert", "ShaderSource/constant.frag" };
const ShaderPair ShaderSources::Lamb = { "ShaderSource/standard.vert",     "ShaderSource/lamb.frag" };
const ShaderPair ShaderSources::Phong = { "ShaderSource/standard.vert",    "ShaderSource/phongMultiLight.frag" };
const ShaderPair ShaderSources::Blinn = { "ShaderSource/standard.vert",    "ShaderSource/blinn.frag" };
const ShaderPair ShaderSources::Skybox = { "ShaderSource/skybox.vert", "ShaderSource/skybox.frag" };