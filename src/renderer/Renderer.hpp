#ifndef EGEN_RENDERER_H
#define EGEN_RENDERER_H

#include "window/Window.hpp"

namespace egen::renderer
{

class Renderer
{
public:
    Renderer(window::Window& window);
    
    void update();

    void add_triangle();

private:
    window::Window& m_window;

    const char *m_vertex_shader_source = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

    const char* m_fragment_shader_source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";
};

}


#endif //EGEN_RENDERER_H
