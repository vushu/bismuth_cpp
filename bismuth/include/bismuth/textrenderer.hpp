#pragma once
#include <glm/glm.hpp>
#include <string>
#include <bismuth/font.hpp>
#include <vector>
#include <bismuth/font.hpp>
#ifndef __EMSCRIPTEN__
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#else
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#endif


namespace bi {

    class TextRenderer{
        public:
            // constructors, asssignment, destructor
            TextRenderer();
            ~TextRenderer();

            void init();
            //void displayText(std::string text);
            Font& addFont(std::string fontFilePath, float fontSize);
            void render();

        private:
            std::vector<Font> fonts;
            FT_Library ft;

    };
}
