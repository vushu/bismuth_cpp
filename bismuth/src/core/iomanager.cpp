#include <bismuth/iomanager.hpp>
using namespace bi;

IOManager::IOManager(int width, int height, std::string title) {
    this->window = std::make_unique<Window>(width, height, title);
    this->camera = std::make_unique<Camera>();
    this->assetmanager = std::make_unique<AssetManager>();
    //this->renderer = std::make_unique<Renderer>(this->window, this->camera, *this->assetmanager);
    this->audioManager = std::make_unique<AudioManager>();
    this->guimanager = std::make_unique<GuiManager>(*this->window);
    this->mainFramebuffer = std::make_unique<Framebuffer>();
    //this->textrenderer = std::make_unique<TextRenderer>();
    this->renderer = std::make_unique<Renderer>(*this->camera);

}

IOManager::~IOManager() { }

void IOManager::init() {

}



