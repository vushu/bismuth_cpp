#include "bismuth/iomanager.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/editors/asseteditor.hpp>
#include <imgui/imgui.h>
using namespace bi;

AssetEditor::AssetEditor() { }
AssetEditor::~AssetEditor() { }

void AssetEditor::update(float dt)
{
    getRenderer().clear(0, 0, 0, 0);
    getGuiManager().beginDraw();

    ImGui::SetNextWindowSize(ImVec2(400, getWindow().height - 10));
    ImGui::SetNextWindowPos(ImVec2(getWindow().width - 405, 10));
    ImGui::Begin("Assets loaded");

    for (const auto& tex : bi::ioManager().assetmanager->getTextures()) {
        if (ImGui::Button((std::to_string(tex->textureId) + ":" + tex->filepath).c_str())) {
            currentTexture = tex;
        }
    }
    ImGui::End();

    if (currentTexture) {

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(currentTexture->width * scale + 50, currentTexture->height * scale + 50));
        ImGui::Begin(currentTexture->filepath.c_str(), &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::Button("Close")) {
            currentTexture = nullptr;
        }

        ImGui::SameLine();

        ImGui::SliderFloat("Scale", &scale, 1, maxScale);
        if (currentTexture) {

            std::string size = "Size: " + std::to_string(currentTexture->width) + "x" + std::to_string(currentTexture->height);
            ImGui::Text("%s", size.c_str());
        }

        if (currentTexture != nullptr)
            ImGui::Image((void*)(currentTexture->textureId), ImVec2(currentTexture->width * scale, currentTexture->height * scale));

        ImGui::End();
    }

    if (bi::mouseInput().scrollY == 1.0f) {
        bi::mouseInput().scrollY = 0.0f;
        scale++;
        if (scale >= maxScale) {
            scale = maxScale;
        }
    }

    if (bi::mouseInput().scrollY == -1.0f) {
        bi::mouseInput().scrollY = 0.0f;
        scale--;
        if (scale < 2) {
            scale = 1;
        }
    }
    getGuiManager().endDraw();

    getShapeRenderer().beginBatch();
    drawGrid();
    getShapeRenderer().endFlushBegin();
}

void AssetEditor::init()
{
    getGuiManager().init();
}

void AssetEditor::drawGrid()
{
    float tileCountX = bi::ioManager().tiledManager->tileScreenDimension.x;
    float tileW = bi::ioManager().tiledManager->tileScreenDimension.z;

    float tileCountY = bi::ioManager().tiledManager->tileScreenDimension.y;
    float tileH = bi::ioManager().tiledManager->tileScreenDimension.w;

    for (int i = 0; i <= tileCountX; i++) {
        bi::ioManager().shaperenderer->drawLine({ i * tileW, 0 }, { i * tileW, tileCountY * tileW }, {1,1,0, 0.5f});
    }

    for (int i = 0; i <= tileCountY; i++) {
        bi::ioManager().shaperenderer->drawLine({ 0, i * tileH }, { tileCountY * tileH, i * tileH }, {1,1,0, 0.5f});
    }
}

void AssetEditor::start()
{
}

void AssetEditor::close()
{
}
