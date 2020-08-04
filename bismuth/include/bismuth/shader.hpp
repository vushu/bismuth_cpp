#pragma once
#include <glm/fwd.hpp>
#include <string>
#include <vector>
namespace bi {

    class Shader
    {
        public:
            Shader (std::string filepath);
            ~Shader ();
            void compile();
            unsigned int vertexId;
            unsigned int fragmentId;
            unsigned int shaderProgramId;
            void use();
            void detach();
            void uploadUniformMat3(std::string varName, glm::mat3& mat3);
            void uploadUniformMat4(std::string varName, glm::mat4& mat4);
            void uploadUniformVec3(std::string varName, glm::vec3& vec3);
            void uploadUniformVec2(std::string varName, glm::vec2& vec2);
            void uploadUniformFloat(std::string varName, float value);
            void uploadUniformInt(std::string varName, int value);

        private:
            std::string vertexSource;
            std::string fragmentSource;
            std::string filepath;
            bool isUsed;
            void parseShader(std::string source);
            void setSource(const std::string& pattern, const std::string& source);
            std::vector<std::string> split(const std::string& str, const std::string& regex);
            std::string trim(const std::string& str);
    };

}
