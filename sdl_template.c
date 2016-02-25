#define GLEW_STATIC
#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#undef main

void createWindow(SDL_Window **window);
void createContext(SDL_Window *window, SDL_GLContext *context);
int  shutDown(SDL_GLContext* context);
//char *vertShader = "#version 150\nin vec2 position;\nvoid main() {\ngl_Position = vec4(position, 0.0, 1.0);\n}";
//char *fragShader = "#version 150\nout vec4 outColor;\nvoid main() {\noutColor = vec4(1.0, 1.0, 1.0, 1.0);\n}"
const char *fragShader = SIMPLE_FRAG;
const char *vertShader = SIMPLE_VERT;

int main(int argc, char *argv[]) {
    SDL_Window    *window = NULL;
    SDL_GLContext context = NULL;
    createWindow(&window);
    createContext(window, &context);

    SDL_Event windowEvent;
    for(;;) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }
    }
    return shutDown(&context);
}

void createWindow(SDL_Window **window) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    *window  = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
}
float vertices[] = {
        0.0f,  0.5f, // Vertex 1 (X,Y)
        0.5f, -0.5f, // Vertex 2 (X,Y)
        -0.5f,  0.5f  // Vertex 3 (X,Y)
};
void createContext(SDL_Window *window, SDL_GLContext *context) {
    *context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint  vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);



}

int shutDown(SDL_GLContext *context) {
    SDL_GL_DeleteContext(*context);
    SDL_Quit();
    return 0;
}

void draw() {

}