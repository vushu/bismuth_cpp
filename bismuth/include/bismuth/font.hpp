#pragma once
#include <array>
#include <bismuth/primitives.hpp>
#include <glm/glm.hpp>
#include <map>
//#include <ft2build.h>
#include <vector>
//#include FT_FREETYPE_H
#include <string>

namespace bi {
    struct FontInfo {
        std::string face;
        unsigned int size;
        bool bold, italic;
        unsigned int lineHeight, base, scaleW, scaleH, pages, packed;
        std::string file;

    };
    struct Character {
        int charId;
        int x,y, width, height, xoffset, yoofset, xadvance, page, chnl;
    };
    //struct Character {
    //unsigned int texId; //Id handle of the glyph texture
    //glm::ivec2 size; // Size of glyph
    //glm::ivec2 bearing; // Offset from baseline to left/top of glyph
    //unsigned int advanceOffset; // Offset to advance to next glyph
    //};


    class Font {

        public:
            // constructors, asssignment, destructor
            //Font(std::string fontFilePath, float fontSize) :  mfontFilePath(fontFilePath), mfontSize(fontSize) {}
            Font();
            void loadFnt(std::string filePath);
            ~Font();
            void updateBuffers(std::string text, glm::vec2 position, QuadVertex*& quadVertex, glm::vec4 color, float scale, float renderTexId);
            //void updateBuffers(std::array<char,256> text, glm::vec2 position, QuadVertex*& quadVertex, int renderTexId);
            unsigned int textureId;
            std::vector<Character> getCharacters(std::string text);

        private:
            FontInfo fontInfo;
            std::string face;
            //FT_Library ft;
            std::string mfontFilePath;
            float mfontSize;
            //FT_Face face;
            std::map<char, Character> characters;
            std::vector<std::string> split(std::string str, std::string sep);
            int getDigit(std::string text);
            std::string getInQuotes(std::string text);

    };
}
