#include <bismuth/iomanager.hpp>
using namespace bi;

//IOManager::IOManager(int width, int height, std::string title) {
    //this->resolution = glm::vec2(width, height);
    //this->title = title;
    //this->tileInfo = {};
//}

//IOManager::IOManager(glm::vec2 resolution, glm::vec4 tileInfo, std::string title) {
    //this->resolution = resolution;
    //this->tileInfo = tileInfo;
    //this->title = title;
//}


IOManager::IOManager() { }
IOManager::~IOManager() { }

void IOManager::construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title){
    this->window = std::make_unique<Window>(resolution.x, resolution.y, title);
    if (tileInfo.x != 0 && tileInfo.y != 0)
        this->camera = std::make_unique<Camera>(tileInfo.x * tileInfo.z, tileInfo.y * tileInfo.w);
    else
        this->camera = std::make_unique<Camera>(resolution.x, resolution.y);
    this->assetmanager = std::make_unique<AssetManager>();
    this->audioManager = std::make_unique<AudioManager>();
    this->guimanager = std::make_unique<GuiManager>(*this->window);
    this->mainFramebuffer = std::make_unique<Framebuffer>();
    this->renderer = std::make_unique<Renderer>(*this->camera);
    this->tiledManager = std::make_unique<TiledManager>();
    //shape renderer
    this->shaperenderer = std::make_unique<bi::ShapeRenderer>(*this->camera);

}

//void IOManager::init() {
    //construct(resolution, tileInfo, title);
//}

bi::IOManager& bi::ioManager() {
    return bi::IOManager::get();
}


