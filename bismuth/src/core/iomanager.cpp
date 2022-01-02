#include <bismuth/iomanager.hpp>
using namespace bi;

IOManager::IOManager() { }
IOManager::~IOManager()
{
    bi::log("IOManager destroyed");
}

void IOManager::destroy()
{
    window->destroy();
}

void IOManager::construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title)
{

    this->window = std::make_unique<Window>(resolution.x, resolution.y, title);
    this->tiledManager = std::make_unique<TiledManager>();

    if (tileInfo.x != 0 && tileInfo.y != 0) {
        this->camera = std::make_unique<Camera>(tileInfo.x * tileInfo.z, tileInfo.y * tileInfo.w);
        this->tiledManager->tileScreenDimension = tileInfo;
    } else
        this->camera = std::make_unique<Camera>(resolution.x, resolution.y);

    this->assetmanager = std::make_unique<AssetManager>();

    this->cursor = std::make_unique<Cursor>("resources/assets/textures/cursor/pointer.png", "resources/assets/textures/cursor/hand.png");

    this->audioManager = std::make_unique<AudioManager>();
    this->mainFramebuffer = std::make_unique<Framebuffer>();
    this->renderer = std::make_unique<Renderer>(*this->camera);
    //shape renderer
    this->shaperenderer = std::make_unique<bi::ShapeRenderer>(*this->camera);
}

bi::IOManager& bi::ioManager()
{
    return bi::IOManager::get();
}
