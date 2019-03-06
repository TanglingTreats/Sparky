#include "window.h"

namespace sparky { namespace graphics {

    void windowResize(GLFWwindow* window, int width, int height);

    Window::Window(const char* title, int width, int height)
    {
        m_Title = title;
        m_Width = width;
        m_Height = height;

        if (!init())
            glfwTerminate();
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::init()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialse GLFW!" << std::endl;

            return false;
        }
        else
        {
            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window)
            {
                glfwTerminate();
                std::cout << "GLFW window failed to create!" << std::endl;

                return false;
            }
        }

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, windowResize);
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
        glfwSetCursorPosCallback(m_Window, cursor_position_callback);

        if (glewInit() != GLEW_OK)
        {
            std::cout << "GLEW could not be initialized!" << std::endl;
            return false;
        }

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

        return true;
    }

    bool Window::isKeyPressed(unsigned int keycode) const
    {
        //TODO: Logging system
        if (keycode >= MAX_KEYS)
        {
            return false;
        }

        return m_Keys[keycode];
    }

    bool Window::isMouseButtonPressed(unsigned int button) const
    {
        //TODO: Log message
        if (button >= MAX_BUTTONS)
        {
            return false;
        }

        return m_MouseButtons[button];
    }

    void Window::getCursorPosition(double& x, double& y) const
    {
        x = mx;
        y = my;
    }

    void Window::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update()
    {
        glfwSwapBuffers(m_Window);
        //glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
        glfwPollEvents();
    }

    bool Window::closed() const
    {
        return glfwWindowShouldClose(m_Window) == 1;
    }

    void windowResize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* win = (Window*) glfwGetWindowUserPointer(window);
        win->m_Keys[key] = action != GLFW_RELEASE;
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->m_MouseButtons[button] = action != GLFW_RELEASE;
    }

    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->mx = xpos;
        win->my = ypos;
    }
} }
