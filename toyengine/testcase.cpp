#include "GameObject.hpp"
#include "GraphicsProgram.hpp"
#include "Shader.hpp"
#include "TriRenderComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

const int SCR_WIDTH = 1600;
const int SCR_HEIGHT = 900;

class Triangle : public GameObject {
public:
    Triangle(glm::vec3 position, glm::vec3 size)
        : GameObject(position, size, 0)
    {
        Shader triShader("shader-test.vert", "shader-test.frag");
        setRenderCompenent(std::make_shared<TriRenderComponent>(*this, triShader));
    }
};

int main(int argc, char** argv)
{
    std::shared_ptr<Level> level = std::make_shared<Level>(SCR_WIDTH, SCR_HEIGHT);
    GraphicsProgram program(level);
	

    auto center = glm::vec3(SCR_WIDTH / 2, SCR_WIDTH / 2, 0);
    auto size = glm::vec3(1, 1, 1);
    auto triangle = std::make_shared<Triangle>(center, size);
    
    level->addObject(triangle);
	
    program.loop();
    return 0;
}
