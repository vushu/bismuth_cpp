#include "bismuth/assetmanager.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/editors/asseteditor.hpp>
#include <imgui/imgui.h>
using namespace bi;

AssetEditor::AssetEditor() { }
AssetEditor::~AssetEditor() { }

void AssetEditor::update(float dt) {
    getRenderer().clear(0,0,0,0);
    getGuiManager().beginDraw();

    ImGui::SetNextWindowSize(ImVec2(400, 300));
    ImGui::SetNextWindowPos(ImVec2(getWindow().width - 410, 60));
    ImGui::Begin("Assets loaded");

    for (const auto& tex : bi::assetManager().getTextures()){
        if (ImGui::Button((std::to_string(tex->textureId) + ":" + tex->filepath).c_str())) {
            currentTexture = tex;
        }
    }

    ImGui::SetNextWindowPos(ImVec2(getWindow().width - 210, getWindow().height/2));
    ImGui::SetNextWindowSize(ImVec2(200, 100));
    ImGui::Begin("Zoom");
    ImGui::SliderFloat("Scale", &scale, 1, maxScale);
    ImGui::End();
    ImGui::End();

    if (currentTexture) {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(currentTexture->width * scale + 50, currentTexture->height * scale + 50));
        ImGui::Begin(currentTexture->filepath.c_str(), &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Image((void*)(currentTexture->textureId), ImVec2(currentTexture->width * scale, currentTexture->height * scale));

        ImGui::End();
    }
    bi::log("Scroll Y", (float)bi::mouseInput().scrollY);

    if(bi::mouseInput().scrollY == 1.0f){
        bi::mouseInput().scrollY = 0.0f;
        scale++;
        if (scale >= maxScale) {
            scale = maxScale;
        }
    }

    if(bi::mouseInput().scrollY == -1.0f){
        bi::mouseInput().scrollY = 0.0f;
        scale--;
        if (scale < 2) {
            scale = 1;
        }
    }
    getGuiManager().endDraw();
}

void AssetEditor::init() {
    getGuiManager().init();
}

void AssetEditor::start() {
}

void AssetEditor::close() {

}
