#include <iostream>
#include <ctime>
#include <cstdlib> //rand
#include "eda_libs/sort.h"

using namespace std;

//cores rgbcymkw
//red, green, blue, cyan, yellow, magenta, black, white

void selection_sort(vector<int>& vet){
    for(int i = 0; i < (int) vet.size() - 1; i++){
        int imenor = i;
        view_set_faixa(i, vet.size() - 1);
        for(int j = i + 1; j < (int) vet.size(); j++){
            view_show(vet, {i, j, imenor}, "ygr");
            if(vet[j] < vet[imenor]){
                imenor = j;
                view_show(vet, {i, j, imenor}, "ygr");
            }
        }
        std::swap(vet[imenor], vet[i]);
    }
}

void bubble_sort(vector<int>& vet){
    for(int i = vet.size(); i > 0; i--){
        for(int j = 0; j < i - 1; j++){
            view_show(vet, {i, j, j + 1}, "rgy");
            if(vet[j] > vet[j + 1]){
                std::swap(vet[j], vet[j + 1]);
                view_show(vet, {i, j, j + 1}, "rgy");
            }
        }

    }
}

void insertion_sort(vector<int>& vet){
    for(int i = 1; i < (int) vet.size(); i++){
        for(int j = i; j > 0; j--){
            view_show(vet, {i, j, j - 1}, "rgy");
            if(vet[j] < vet[j - 1]){
                std::swap(vet[j], vet[j - 1]);
                view_show(vet, {i, j, j - 1}, "ryg");
            }else{
                break;
            }
        }

    }
}

//intervalos fechados [C, F]
#define qshow view_show(vet, {C, F, i, j}, "rgby")

void merge(vector<int>& vet, int a, int b, int c){
    int i = a;
    int j = b;
    vector<int> vaux;
    vaux.reserve(c - a);
    while((i < b) && (j < c)){ //comparar particoes
        if(vet[i] < vet[j])
            vaux.push_back(vet[i++]);
        else
            vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(i < b){
        vaux.push_back(vet[i++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(j < c){
        vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    for(int i = 0; i < (int) vaux.size(); i++){
        vet[a + i] = vaux[i];
        view_show(vet, {a + i}, "r");
    }
}

//particao [C, F[
void mergesort(vector<int>& vet, int a, int c){
    if(c == a + 1)
        return;
    int b = (a + c)/2;
    mergesort(vet, a, b);
    mergesort(vet, b, c);
    merge(vet, a, b, c);
}

void test_sort(vector<int>& vet){
    for(int i = 0; i < (int) vet.size() - 1; i++){
        if(vet[i] <= vet[i + 1])
            view_show(vet, {i, i + 1}, "gg");
        else{
            view_show(vet, {i, i + 1}, "rr");
            view_lock();
        }
    }
}

int main(){
    srand(time(NULL));

    const int qtd = 70;
    vector<int> vet(qtd, 0);

    int min = 10;
    int max = 400;

    for(int i = 0; i < qtd; i++)
        vet[i] = (rand() % (max - min + 1) + min);

    //view_set_dot();
    view_set_bar();
    view_set_faixa(0, qtd - 1);

    //selection_sort(vet);
    //bubble_sort(vet);
    //insertion_sort(vet);
    mergesort(vet, 0, vet.size());

    test_sort(vet);
    view_lock();
    return 0;
}