#pragma once
#include <glm/glm.hpp>
#include <map>
#ifndef __EMSCRIPTEN__
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#endif

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
            Font(FT_Library& ftLibrary, std::string fontFilePath, float fontSize) : ft(ftLibrary),  mfontFilePath(fontFilePath), mfontSize(fontSize) {}
            void init();
            ~Font();
            void render();

        private:
            FT_Library& ft;
            std::string mfontFilePath;
            float mfontSize;
            FT_Face face;
            std::map<char, Character> characters;
            void generateChars();

    };
}
