#include <bismuth/font.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>

using namespace bi;

Font::~Font() {

}

void Font::init() {

    if (FT_New_Face(ft, "resources/assets/fonts/Ready.ttf", 0, &face)) {
        log("Failed to init load font");
        throw std::runtime_error("Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, this->mfontSize);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        log("ERROR::FREETYTPE: Failed to load Glyph");
        throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
    }
    log("Font: " + this->mfontFilePath + " initialized");

    generateChars();
}

void Font::generateChars() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            log("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    log("Done initializing font " + mfontFilePath);
}

void Font::render() {

}

