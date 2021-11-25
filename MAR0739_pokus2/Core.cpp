#include "Core.h"
Core::Core() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    camera = new Camera();

}

void Core::setData(int width, int height, const char* windowName) {
    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Sets the key callback
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}



void Core::initCore() {
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    printf("Core Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);
}

void Core::start() {
    glActiveTexture(GL_TEXTURE0);
    GLuint textureID = SOIL_load_OGL_texture("F:\\Škola\\ZPG\\MAR0739_pokus2\\Textures\\box.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, textureID);
    while (!glfwWindowShouldClose(window)) {

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glEnable(GL_DEPTH_TEST);

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        for (ModelObject o : objects)
            o.DrawObject(model, this->camera->getView(), projection);
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we�ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Core::addObject(ModelObject object) {
    objects.push_back(object);
}