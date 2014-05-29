#ifndef JUNTA_H
#define JUNTA_H

#include <SDL_opengl.h>

class Junta {
    public:
        Junta(GLfloat rotacaoMax = 45.0f,
              GLfloat atrito = 0.85f,
              GLfloat acelMax = 5.00f);
        void atualizar(float dt);
        void rotacionar(int i);
        virtual void renderizar(int braco) = 0;

    protected:
        // Constantes
        GLfloat rotacaoMax;
        GLfloat acelMax;
        GLfloat atrito;
        // Variáveis
        GLfloat acel;
        GLfloat vel;
        GLfloat rotacao;
};

class JuntaPrismatica : public Junta {
    public:
        JuntaPrismatica() : Junta() {}
        void renderizar(int braco);
};

class JuntaRotacional : public Junta {
    public:
        JuntaRotacional() : Junta() {}
        void renderizar(int braco);
};

class JuntaTorcional : public Junta {
    public:
        JuntaTorcional() : Junta() {}
        void renderizar(int braco);
};

class JuntaRevolvente : public Junta {
    public:
        JuntaRevolvente() : Junta() {}
        void renderizar(int braco);
};

#endif
