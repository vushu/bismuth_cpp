#include <bismuth/textrenderer.hpp>
#include <bismuth/logging.hpp>
#include <stdexcept>

#include <bismuth/font.hpp>
#ifndef __EMSCRIPTEN__
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#endif

using namespace bi;

TextRenderer::TextRenderer() {}

TextRenderer::~TextRenderer() {
    log("Destroyed TextRenderer");
    FT_Done_FreeType(ft);
}

void TextRenderer::init() {
    if (FT_Init_FreeType(&ft)) {
        log("Failed to init FreeType Library");
        throw std::runtime_error("Failed to init FreeType Library");
    }
    log("TextRenderer initialized");
}

void TextRenderer::addFont(std::string fontFilePath, float fontSize) {
    //Font f(ft, fontFilePath, fontSize);
    //f.init();
    //this->fonts.push_back(f);
    //return fonts.at(fonts.size() - 1);

}

void TextRenderer::render() {

    for (auto& f : fonts) {
        f.render();
    }
}

