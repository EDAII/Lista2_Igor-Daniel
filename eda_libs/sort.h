#ifndef SORTVIEW_H
#define SORTVIEW_H

#include <SFML/Graphics.hpp>
#include "base.h"

#include <queue>
#include <sstream>
#include <vector>

class SortView{
private:
    int _begin;
    int _end;
    enum ViewOption{BAR, DOT};
    ViewOption _voption;
    float _thick{7.0};
    float _delta{10.0};
    float xbegin{50};
    float ybegin{550};
    sf::RenderTexture painel;
public:
    SortView()
    {
        _begin = 0;
        _end = 0;
        _voption = BAR;
        painel.create(800, 600);
    }


    void set_faixa(int begin, int end){
        _begin = begin;
        _end = end;
    }

    void set_bar_view(){
        _voption = BAR;
    }

    void set_dot_view(){
        _voption = DOT;
    }

    void plot(float x, float size, sf::Color cor_linha){
        float ydown = 0;
        if(_voption == DOT)
            ydown = -size + 5;

        painel.draw(dsLine(sf::Vector2f(_delta * x + xbegin, ybegin + ydown),
                           sf::Vector2f(_delta * x + xbegin, ybegin - size),
                           _thick, cor_linha));
    }

    void show(const std::vector<int> &vet, std::vector<int> pos = {}, std::string cores = ""){
        if(my_window->isOpen() == false)
            return;

        painel.clear();
        ColorMap * cmap = ColorMap::get_instance();
        int tam = vet.size();
        for(int x = 0; x < tam; x++){
            sf::Color cor_linha = sf::Color::White;
            for(int k = 0; k < (int)pos.size(); k++){
                if(x == pos[k]){
                    cor_linha = cmap->get(cores[k]);
                }
            }
            plot(x, vet[x], cor_linha);
        }
        painel.draw(dsLine(sf::Vector2f(_delta * _begin - 3 + xbegin, ybegin + 5),
                           sf::Vector2f(_delta * _end + 3   + xbegin, ybegin + 5),
                                        _thick, sf::Color::Yellow));

        painel.display();
        my_player->_push(painel.getTexture());
    }
};

static SortView sview;

//versão cpp
void view_show(std::vector<int> &vet, std::vector<int> pos = {}, std::string cores = ""){
    sview.show(vet, pos, cores);
}

void view_set_bar(){
    sview.set_bar_view();
}

void view_set_dot(){
    sview.set_dot_view();
}

void view_set_faixa(int begin, int end){
    sview.set_faixa(begin, end);
}

void view_lock(){
    my_player->wait();
}



#endif