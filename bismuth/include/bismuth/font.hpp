#pragma once
#include <array>
#include <bismuth/primitives.hpp>
#include <glm/glm.hpp>
#include <map>
#include <ft2build.h>
#include <vector>
#include FT_FREETYPE_H
#include <string>

namespace bi {
    struct Character {
        unsigned int texId; //Id handle of the glyph texture
        glm::ivec2 size; // Size of glyph
        glm::ivec2 bearing; // Offset from baseline to left/top of glyph
        unsigned int advanceOffset; // Offset to advance to next glyph
    };


    class Font {

        public:
            // constructors, asssignment, destructor
            //Font(std::string fontFilePath, float fontSize) :  mfontFilePath(fontFilePath), mfontSize(fontSize) {}
            Font();
            void loadFnt(std::string filePath);
            void init();
            ~Font();
            void updateBuffers(std::string text, glm::vec2 position, QuadVertex*& quadVertex);
            unsigned int textureId;
            std::array<float,100> getTextureIds(std::string text);

        private:
            std::string face;
            //FT_Library ft;
            std::string mfontFilePath;
            float mfontSize;
            //FT_Face face;
            std::map<char, Character> characters;
            void generateChars();
            std::vector<std::string> split(std::string str, std::string sep);
            int getDigit(std::string text);
            std::string getInQuotes(std::string text);

    };
}
