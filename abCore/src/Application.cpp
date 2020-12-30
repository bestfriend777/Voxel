#include "VoxelGL.h"
#include "Renderer.h"
#include "imgui/ImIncluded.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

struct CONTEXTDATA
{
    const unsigned int VER_MAJOR = 4;
    const unsigned int VER_MINOR = 5;
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;
    const char* TITLE = "CORE REBUILD";
};
CONTEXTDATA CONTEXT;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT.VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT.VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(CONTEXT.WIDTH, CONTEXT.HEIGHT, CONTEXT.TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    std::cout << glGetString(GL_VERSION) << "\n" << std::endl;

    const char* glsl_version = "#version 450";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init(glsl_version);
    //ImGui_ImplOpenGL3_Init((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    ///////////////////////////////////     INIT END  ///////////////////////////

    float vertices[]{
        -0.5, -0.5, 0.0,  1.0, 0.0, 0.0, 1.0,  // BOTTOM LEFT
         0.5, -0.5, 0.0,  0.0, 1.0, 0.0, 1.0,  // BOTTOM RIGHT
         0.5,  0.5, 0.0,  0.0, 0.0, 1.0, 1.0,  // TOP RIGHT
        -0.5,  0.5, 0.0,  1.0, 1.0, 1.0, 1.0,  // TOP LEFT
    };

    unsigned int index[]{
        0, 1, 2,
        2, 3, 0, 
    };

    Shader shade("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl");
    Shader* shader = new Shader("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl");
   
    VertexBuffer vbo(vertices, sizeof(vertices)); // Send by reference?
    //VertexBuffer vbo(nullptr, sizeof(float) * 256); // Send by reference?
    //vbo.AddSubData(trivert, sizeof(float) * 21, 0);

    IndexBuffer ibo(index, sizeof(index));
    std::cout << "IBO COUNT: " << ibo.GetCount() << "\n" << std::endl;

    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(4);

    VertexArray vao(vbo, vbl); // investigate vertex offset cast: (GLvoid*) vs &
    //vao.AddBuffer(vbo, vbl); // investigate vertex offset cast: (GLvoid*) vs &
    vao.PrintAttribData(vbl);

    Renderer renderer;
    renderer.Init();

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h); // move dis to window class
        
        ////////////////////// RENDER /////////////////////////
        renderer.Clear(0.0f, 0.3f, 0.3f, 0.5f);
        renderer.Draw(vao, ibo, *shader);

        //IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static float f = 0.0f;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // END IMGUI

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}