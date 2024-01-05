#include "utils.h"
#include "Terminal.h"
#include "Interacao.h"
using namespace term;
using namespace std;


void print_size(Terminal& t) {
        std::ostringstream o;
        o << "tamanho do terminal: " << std::setw(7) << t.getNumCols() << "x" << t.getNumRows();
        std::string str = o.str();
        t.clear();
        t << set_color(0) << move_to(t.getNumCols()-str.length(), t.getNumRows()-1) << str;
    }

    void printZona(std::vector<Window*>& zonas, int x, int y, const std::string& mensagem) {
        // Calcula o índice da janela com base nas coordenadas x e y
        int indice = x * 4 + y;

        // Verifica se o índice é válido
        if (indice >= 0 && indice < zonas.size()) {
            // Utiliza os métodos reais da classe Window
            *zonas[indice] << move_to(0, 0) << set_color(1) << mensagem;
        } else {
            std::cout << "Índice inválido!" << std::endl;
        }
    }


    int main() {

    Terminal &t = Terminal::instance();
    for(int i=1;i<20;i++)t.init_color(i,i,0);
    Interacao a;
    a.leComando();
    return 0;

    }