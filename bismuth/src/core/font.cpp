#include "bismuth/primitives.hpp"
#include "glm/fwd.hpp"
#include <array>
#include <bismuth/font.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <string>

using namespace bi;

Font::~Font() {

}

void Font::init() {
    if (FT_Init_FreeType(&ft)) {
        log("Failed to init FreeType Library");
        throw std::runtime_error("Failed to init FreeType Library");
    }

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
        //log("Texture id char: " + std::to_string(texture));
    }
    FT_Done_Face(face);
    log("Done initializing font " + mfontFilePath);
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

std::array<float, 100> Font::getTextureIds(std::string text) {
    std::array<float, 100> textureIds;
    for (int i = 0; i < text.length(); i ++) {
        textureIds[i] = characters.at(i).texId;
    }
    return textureIds;
}


