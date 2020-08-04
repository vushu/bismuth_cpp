#pragma once
#include "bismuth/logging.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <stdexcept>
#include <string>
#include <vector>
namespace bi {
    namespace glhelper {

        struct TextureInfo {
            unsigned int textureId;
            int width, height;
        };

        unsigned int compileVertexShader(std::string& shaderSrc);
        unsigned int compileFragmentShader(std::string& shaderSrc);
        unsigned int linkShaders(unsigned int vertexId, unsigned int fragmentId);
        void uploadUniformMat3(int shaderProgramId, std::string varName, glm::mat3& mat3);
        void uploadUniformMat4(int shaderProgramId, std::string varName, glm::mat4& mat4);
        void uploadUniformVec3(int shaderProgramId, std::string varName, glm::vec3& vec3);
        void uploadUniformVec2(int shaderProgramId, std::string varName, glm::vec2& vec2);
        void uploadUniformFloat(int shaderProgramId, std::string varName, float value);
        void uploadUniformInt(int shaderProgramId, std::string varName, int value);
        void uploadUniformIntArray(int shaderProgramId, std::string varName, int arr[]);
        TextureInfo generateTexture(std::string filepath);
    }
}
