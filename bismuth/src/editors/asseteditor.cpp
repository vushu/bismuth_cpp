#include <bismuth/editors/asseteditor.hpp>
#include <imgui/imgui.h>
using namespace bi;

AssetEditor::AssetEditor() { }
AssetEditor::~AssetEditor() { }

void AssetEditor::update(float dt) {
    getGuiManager().beginDraw();
    ImGui::Begin("Assets loaded");
    ImGui::Text("My assets");
    ImGui::End();
    getGuiManager().endDraw();
}

void AssetEditor::init() {
    getGuiManager().init();
}

void AssetEditor::start() {
}

void AssetEditor::close() {

}
