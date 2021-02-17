#ifndef GLGameCore
#define GLGameCore
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
namespace gameCore {
    void SetupWindow(std::string name);
    void SetupWindow(const char* name);
    void StartGameLoop();
}
#endif
