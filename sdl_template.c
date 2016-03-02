#define GLEW_STATIC
#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#undef main

void createWindow(SDL_Window **window);
void createContext(SDL_Window *window, SDL_GLContext *context);
void draw();
int  shutDown(SDL_GLContext* context);
const char *vertShader = "#version 150\nin vec2 position;\nvoid main() {\ngl_Position = vec4(position, 0.0, 1.0);\n}\n";
const char *fragShader = "#version 150\nout vec4 outColor;\nvoid main() {\noutColor = vec4(1.0, 1.0, 1.0, 1.0);\n}\n";

int main(int argc, char *argv[]) {
    SDL_Window    *window = NULL;
    SDL_GLContext context = NULL;

    createWindow(&window);
    createContext(window, &context);

    SDL_Event windowEvent;
    for(;;) {
        draw();
        SDL_GL_SwapWindow(window);
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
            if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE) {
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

void createContext(SDL_Window *window, SDL_GLContext *context) {
    *context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    float vertices[] = {
             0.0f,  0.5f, // Vertex 1 (X,Y)
             0.5f, -0.5f, // Vertex 2 (X,Y)
            -0.5f,  0.5f  // Vertex 3 (X,Y)
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

int shutDown(SDL_GLContext *context) {
    SDL_GL_DeleteContext(*context);
    SDL_Quit();
    return 0;
}

void draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
