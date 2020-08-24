#include "bismuth/primitives.hpp"
#include "glm/fwd.hpp"
#include <array>
#include <bismuth/font.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>


using namespace bi;

Font::Font() {

}
Font::~Font() {

}

void Font::init() {
    //generateChars();
}

void Font::generateChars() {
}

void Font::updateBuffers(std::string text, glm::vec2 position, QuadVertex*& quadVertex) {
    std::string::const_iterator c;
    float scale = 1.5f;
    float texId = 0.0f;

    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];
        glm::vec2 pos (position.x + ch.bearing.x * scale, position.y - (ch.size.y - ch.bearing.y) * scale);
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        quadVertex->position = {pos.x + w, pos.y + h, 0.0f};
        quadVertex->color = {1,1,1,0};
        quadVertex->texId = texId;
        quadVertex->texcoords = {1.0f, 1.0f};
        quadVertex++;

        quadVertex->position = {pos.x + w, pos.y, 0.0f};
        quadVertex->color = {1,1,1,0};
        quadVertex->texId = texId;
        quadVertex->texcoords = {1.0f, 0.0f};
        quadVertex++;

        quadVertex->position = {pos.x, pos.y, 0.0f};
        quadVertex->color = {1,1,1,0};
        quadVertex->texId = texId;
        quadVertex->texcoords = {0.0f, 0.0f};
        quadVertex++;

        quadVertex->position = {pos.x, pos.y + h, 0.0f};
        quadVertex->color = {1,1,1,0};
        quadVertex->texId = texId;
        quadVertex->texcoords = {0.0f, 1.0f};
        quadVertex++;

        texId++;
        position.x = (ch.advanceOffset >> 6) * scale;
    }
}
std::vector<std::string> Font::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

void Font::loadFnt(std::string filePath) {
    std::ifstream file(filePath);
    std::string line, line2;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    //std::regex rgx(R"(face=\"(.*?)\" size=(\d+) bold=(\d+) padding=(.,.,.,.?) ")");
    std::smatch match;
    std::string delimiter = "=";

    std::string faceLine = lines.at(0);
    size_t pos = 0;
    std::string token;

    face = getInQuotes(faceLine);
    log("face: " + face);

    bool first = true;
    while ((pos = faceLine.find(delimiter)) != std::string::npos) {
        if (first){
            token = faceLine.substr(0, pos);
            first = false;
        }
        else
            token = split(faceLine.substr(0, pos), " ")[0];
        std::cout << token << std::endl;
        faceLine.erase(0, pos + delimiter.length());
    }


    // last line isnt needed

    for (int i = 3; i < lines.size() - 1; i++) {
        std::vector<std::string> l = split(lines.at(i), "=");
        for (int j = 0; j < l.size(); j++) {
            getDigit(l[j]);
        }
    }

}

//log("hej file");

std::array<float, 100> Font::getTextureIds(std::string text) {
    std::array<float, 100> textureIds;
    for (int i = 0; i < text.length(); i ++) {
        textureIds[i] = characters.at(i).texId;
    }
    return textureIds;
}

int Font::getDigit(std::string text){
    std::regex rgx("([0-9]+)");
    std::smatch match;

    if (std::regex_search(text, match, rgx))
    {

        std::cout << match[1] << std::endl;
        return std::stoi(match[1]);
    }

    return 1;
}
std::string Font::getInQuotes(std::string text) {

    std::regex rgx("\"(.*?)\"");
    std::smatch match;

    if (std::regex_search(text, match, rgx))
    {
        return match[1];
    }
    return text;
}


