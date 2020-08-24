
//#ifndef __EMSCRIPTEN__
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//#else
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
//#endif
#include <bismuth/logging.hpp>
#include <bismuth/glhelper.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



unsigned int bi::glhelper::compileVertexShader(std::string& shaderSrc) {
    unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    // Pass the shader to GPU
    const char* vertexCode = shaderSrc.c_str();
    glShaderSource(vertexId, 1, &vertexCode, NULL);
    glCompileShader(vertexId);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
        bi::log("glHelper vertexShader ", infoLog);
        throw std::runtime_error("Failed to compile vertexShader");
    }
    return vertexId;
}

unsigned int bi::glhelper::compileFragmentShader(std::string& shaderSrc) {
    unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    // Pass the shader to GPU
    const char* fragmentCode = shaderSrc.c_str();
    glShaderSource(fragmentId, 1, &fragmentCode, NULL);
    glCompileShader(fragmentId);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
        bi::log("glHelper fragmentShader ", infoLog);
        throw std::runtime_error("Failed to compile fragmentShader");
    }
    return fragmentId;

}

unsigned int bi::glhelper::linkShaders(unsigned int vertexId, unsigned int fragmentId) {
    char infoLog[512];
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexId);
    glAttachShader(shaderProgram, fragmentId);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        bi::log("glHelper ", infoLog);
    }
    return shaderProgram;
}

void bi::glhelper::uploadUniformMat3(int shaderProgramId, std::string varName, glm::mat3& mat3) {
    unsigned int varLocationId = glGetUniformLocation(shaderProgramId, varName.c_str());
    glUniformMatrix3fv(varLocationId, 1, GL_FALSE, glm::value_ptr(mat3));
}

void bi::glhelper::uploadUniformMat4(int shaderProgramId, std::string varName, glm::mat4 mat4) {
    unsigned int varLocationId = glGetUniformLocation(shaderProgramId, varName.c_str());
    glUniformMatrix4fv(varLocationId, 1, GL_FALSE, glm::value_ptr(mat4));
}

void bi::glhelper::uploadUniformVec3(int shaderProgramId, std::string varName, glm::vec3& vec3) {
    glUniform3f(glGetUniformLocation(shaderProgramId, varName.c_str()), vec3.x, vec3.y, vec3.z);
}

void bi::glhelper::uploadUniformVec2(int shaderProgramId, std::string varName, glm::vec2& vec2) {
    glUniform2f(glGetUniformLocation(shaderProgramId, varName.c_str()), vec2.x, vec2.y);
}

void bi::glhelper::uploadUniformFloat(int shaderProgramId, std::string varName, float value) {
    glUniform1f(glGetUniformLocation(shaderProgramId, varName.c_str()), value);
}

void bi::glhelper::uploadUniformInt(int shaderProgramId, std::string varName, int value) {
    glUniform1i(glGetUniformLocation(shaderProgramId, varName.c_str()), value);
}

void bi::glhelper::uploadUniformIntArray(int shaderProgramId, std::string varName, int size, const int* location) {
    glUniform1iv(glGetUniformLocation(shaderProgramId, varName.c_str()), size, location);
}


void bi::glhelper::uploadUniformIntArray(int shaderProgramId, std::string varName, int size, int* location) {
    glUniform1iv(glGetUniformLocation(shaderProgramId, varName.c_str()), size, location);
}

void bi::glhelper::uploadUniformIntArray2(int shaderProgramId, std::string varName, int size, int location[]) {
    glUniform1iv(glGetUniformLocation(shaderProgramId, varName.c_str()), size, location);
}

bi::glhelper::TextureInfo bi::glhelper::generateTexture(std::string filepath) {
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        throw std::runtime_error("No image data");
    }

    if (nrChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else if (nrChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        throw std::runtime_error("Error unknown number of channels");
    }

    stbi_image_free(data);
    return TextureInfo{textureId, width, height};
}

