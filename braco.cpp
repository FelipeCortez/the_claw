#include "braco.h"
#include "Load.h"

Braco::Braco() {
    modeloBase = Load::loadObject("modelos/base.obj");

    juntaSelecionada = 0;

    juntas.push_back(new BaseTorcional());
    juntas.push_back(new JuntaRotacional1());
    juntas.push_back(new JuntaRotacional2());
    juntas.push_back(new JuntaRotacional3());
    juntas.push_back(new JuntaTorcional());
}

void Braco::atualizar(float dt) {
    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        (*it)->atualizar(dt);
    }
}

void Braco::renderizar() {
    glTranslatef(0.0f, 0.0f, 0.0f);

    glCallList(modeloBase);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f, 1.0f, 0.0f);

    std::vector<Junta*>::iterator it;
    for(it = juntas.begin(); it != juntas.end(); ++it) {
        if((it - juntas.begin()) == juntaSelecionada) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 1.0f, 0.0f);
        }

        (*it)->renderizar();
    }

    glDisable(GL_COLOR_MATERIAL);
}

void Braco::selecionarJunta(int i) {
    if(i == -1 && juntaSelecionada > 0) {
        juntaSelecionada--;
    } else if(i == 1 && juntaSelecionada < juntas.size() - 1) {
        juntaSelecionada++;
    }
}

void Braco::rotacionarSelecao(int i) {
    juntas.at(juntaSelecionada)->rotacionar(i);
}
