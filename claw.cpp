#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "formas.h"
#include "braco.h"
#include "camera.h"

const int   SCREEN_WIDTH = 800;
const int   SCREEN_HEIGHT = 600;

GLfloat ambiente[4];
GLfloat difusao[3][4];  // degradê
GLfloat especular[3][4]; // brilho
GLfloat posicaoLuz[3][4];

void iluminacao() {
    ambiente[0] = 0.2;
    ambiente[1] = 0.2;
    ambiente[2] = 0.2;
    ambiente[3] = 1.0;

    difusao[0][0] = 0.7;
    difusao[0][1] = 0.7;
    difusao[0][2] = 0.7;
    difusao[0][3] = 1.0;

    especular[0][0] = 0.8;
    especular[0][1] = 0.8;
    especular[0][2] = 0.8;
    especular[0][3] = 0.0;

    posicaoLuz[0][0] = 50.0f;
    posicaoLuz[0][1] = 50.0f;
    posicaoLuz[0][2] = 50.0f;
    posicaoLuz[0][3] = 1.0;

    difusao[1][0] = 0.7;
    difusao[1][1] = 0.7;
    difusao[1][2] = 0.7;
    difusao[1][3] = 1.0;

    especular[1][0] = 0.8;
    especular[1][1] = 0.8;
    especular[1][2] = 0.8;
    especular[1][3] = 1.0;

    posicaoLuz[1][0] = -50.0;
    posicaoLuz[1][1] = 50.0;
    posicaoLuz[1][2] = -50.0;
    posicaoLuz[1][3] = 1.0;

    posicaoLuz[2][0] = 0;
    posicaoLuz[2][1] = 90.0;
    posicaoLuz[2][2] = 0;
    posicaoLuz[2][3] = 1.0;
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 30); // componente especular do material

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiente);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusao[0]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, especular[0]);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz[0]);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, difusao[1]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, especular[1]);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz[1]);


    glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, difusao[1]);
    glLightfv(GL_LIGHT2, GL_SPECULAR, especular[1]);
    glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz[2]);
}

int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO |
                SDL_INIT_AUDIO |
                SDL_INIT_EVENTS |
                SDL_INIT_TIMER) < 0) {
        printf("Erro de inicialização do SDL: %s\n",
                SDL_GetError());
    } else {
        window = SDL_CreateWindow(
                "The Claw",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_OPENGL);

        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        SDL_Event e;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING); // liga a luz
        glEnable(GL_LIGHT0); // define a luz 0
        glEnable(GL_LIGHT1); // define a luz 1
        glEnable(GL_LIGHT2); // define a luz 1


        bool quit;

        Uint32 tempoAtual, tempoPassado;
        float dt;

        tempoAtual = SDL_GetTicks();

        quit = false;

        const Uint8* keys = NULL;
        keys = SDL_GetKeyboardState(NULL);

        Camera* camera = new Camera();
        Braco* braco = new Braco();

        while(!quit) {
            tempoPassado = tempoAtual;
            tempoAtual = SDL_GetTicks();
            dt = (tempoAtual - tempoPassado) / 1000.0f;

            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            if(!keys[SDL_SCANCODE_C]) {
                                braco->selecionarJunta(1);
                            }
                            break;
                        case SDLK_DOWN:
                            if(!keys[SDL_SCANCODE_C]) {
                                braco->selecionarJunta(-1);
                            }
                            break;
                        case SDLK_x:
                            camera->alterarProjecao();
                            break;
                        default:
                            break;
                    }
                } else if(e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            if(keys[SDL_SCANCODE_C]) {
                if(keys[SDL_SCANCODE_UP]) {
                    camera->alterarDirecao(0, 1);
                }
                if(keys[SDL_SCANCODE_DOWN]) {
                    camera->alterarDirecao(0, -1);
                }
                if(keys[SDL_SCANCODE_LEFT]) {
                    camera->alterarDirecao(1, 0);
                }
                if(keys[SDL_SCANCODE_RIGHT]) {
                    camera->alterarDirecao(-1, 0);
                }
            } else {
                if(keys[SDL_SCANCODE_LEFT]) {
                    braco->rotacionarSelecao(1);
                }

                if(keys[SDL_SCANCODE_RIGHT]) {
                    braco->rotacionarSelecao(-1);
                }
            }

            camera->atualizar(dt);
            braco->atualizar(dt);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            camera->posicionar();

            iluminacao();

            Formas::grade(300.0f, 10.0f);
            Formas::xyz(100.0f, 1.0f);
            Formas::base();

            braco->renderizar();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            camera->projetar();

            glFlush();

            SDL_GL_SwapWindow(window);
        }

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return 0;
}
