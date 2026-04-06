#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <fstream>
#include <ctime>

using namespace std;

#define MIN_MAQUINAS 2
#define MAX_MAQUINAS 5
#define MIN_LOTES 10
#define MAX_LOTES 30
#define MIN_SAPATOS 10
#define MAX_SAPATOS 50
#define MIN_TEMPO 1
#define MAX_TEMPO 25

struct Lote
{
    int id;
    int quantidade;
    int tempoUnitario;
    int tempoTotal;
};

vector<Lote> lotes;
vector<pair<int, list<int>>> maquinas;

vector<pair<int, list<int>>> LPT(int numMaquinas, vector<Lote> lotes)
{
    priority_queue<
        pair<int, list<int>>,
        vector<pair<int, list<int>>>,
        greater<>>
        fila;

    sort(lotes.begin(), lotes.end(), [](Lote a, Lote b)
         { return a.tempoTotal > b.tempoTotal; });

    for (int i = 0; i < numMaquinas; i++)
    {
        fila.push({0, {}});
    }

    for (auto &lote : lotes)
    {
        auto maquina = fila.top();
        fila.pop();

        maquina.first += lote.tempoTotal;
        maquina.second.push_back(lote.id);

        fila.push(maquina);
    }

    vector<pair<int, list<int>>> resultado;

    while (!fila.empty())
    {
        resultado.push_back(fila.top());
        fila.pop();
    }

    return resultado;
}

void gerarDados(int &numMaquinas, int &numLotes)
{
    srand(time(nullptr));

    numMaquinas = rand() % (MAX_MAQUINAS - MIN_MAQUINAS + 1) + MIN_MAQUINAS;
    numLotes = rand() % (MAX_LOTES - MIN_LOTES + 1) + MIN_LOTES;

    lotes.clear();

    for (int i = 0; i < numLotes; i++)
    {
        Lote l;
        l.id = i + 1;
        l.quantidade = rand() % (MAX_SAPATOS - MIN_SAPATOS + 1) + MIN_SAPATOS;
        l.tempoUnitario = rand() % (MAX_TEMPO - MIN_TEMPO + 1) + MIN_TEMPO;
        l.tempoTotal = l.quantidade * l.tempoUnitario;

        lotes.push_back(l);
    }
}

void salvarJSON()
{
    ofstream file("dados.json");

    if (!file.is_open())
    {
        cout << "Erro ao abrir arquivo\n";
        return;
    }

    file << "{";

    // LOTES
    file << "\"lotes\": [";

    for (int i = 0; i < lotes.size(); i++)
    {
        auto &l = lotes[i];

        file << "{";
        file << "\"id\":" << l.id << ",";
        file << "\"qtd\":" << l.quantidade << ",";
        file << "\"tempoUnit\":" << l.tempoUnitario << ",";
        file << "\"tempoTotal\":" << l.tempoTotal;
        file << "}";

        if (i != lotes.size() - 1)
            file << ",";
    }

    file << "],";

    // MAQUINAS
    file << "\"maquinas\": [";

    for (int i = 0; i < maquinas.size(); i++)
    {
        file << "{";
        file << "\"tempoTotal\": " << maquinas[i].first << ",";
        file << "\"lotes\": [";

        for (auto it = maquinas[i].second.begin(); it != maquinas[i].second.end(); ++it)
        {
            int id = *it;

            auto l = find_if(lotes.begin(), lotes.end(), [&](Lote lt)
                             { return lt.id == id; });

            if (l == lotes.end())
                continue; // segurança

            file << "{";
            file << "\"id\":" << l->id << ",";
            file << "\"qtd\":" << l->quantidade << ",";
            file << "\"tempoUnit\":" << l->tempoUnitario << ",";
            file << "\"tempoTotal\":" << l->tempoTotal;
            file << "}";

            if (next(it) != maquinas[i].second.end())
                file << ",";
        }

        file << "]}";

        if (i != maquinas.size() - 1)
            file << ",";
    }

    file << "]";

    file << "}";

    file.close();
}

int main()
{
    int numMaquinas, numLotes;

    gerarDados(numMaquinas, numLotes);
    maquinas = LPT(numMaquinas, lotes);

    salvarJSON();

    cout << "dados.json gerado!\n";
}