#include <bismuth/gui/guielement.hpp>
namespace bi{
    class GuiWindow : public GuiElement {

        public:
            // constructors, assignment, destructor
            GuiWindow();

            void draw() override;
            void handleMouseClick(int action, glm::vec2 position) override;

        private:
            glm::vec2 position {0,0};
            glm::vec2 size {200,200};

    };
}
