#include <bismuth/guimanager.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace bi;

GuiManager::~GuiManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void GuiManager::init() {
    const char* glslVersion = "#version 300 es";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

}

void GuiManager::beginDraw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

//Must between beginDraw and endDraw
void GuiManager::showFPS() {

    ImGui::Begin("FPS");
    //ImGui::Text("Quads: %s", std::to_string(this->getRenderer().getRenderStats().quadCount).c_str());
    //ImGui::Text("DrawCount: %s", std::to_string(this->getRenderer().getRenderStats().drawCount).c_str());
    ImGui::Text("Average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();

}

void GuiManager::endDraw()  {
    //bool show = true;

    //ImGui::ShowDemoWindow(&show);

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
