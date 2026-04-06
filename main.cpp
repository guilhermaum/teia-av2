#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <fstream>
#include <ctime>

using namespace std;

struct Lote
{
    int id;
    int quantidade;
    int tempoUnitario;
    int tempoTotal;
};

vector<Lote> lotes;
vector<pair<int, list<int>>> maquinas;

vector<pair<int, list<int>>> JobShortLpt(int numMaquinas, vector<Lote> lotes)
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

    numMaquinas = rand() % 3 + 2;
    numLotes = rand() % 8 + 8;

    lotes.clear();

    for (int i = 0; i < numLotes; i++)
    {
        Lote l;
        l.id = i + 1;
        l.quantidade = rand() % 40 + 10;
        l.tempoUnitario = rand() % 10 + 1;
        l.tempoTotal = l.quantidade * l.tempoUnitario;

        lotes.push_back(l);
    }
}

void salvarJSON()
{
    ofstream file("dados.json");

    if (!file.is_open()) {
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

            if (l == lotes.end()) continue; // segurança

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
    maquinas = JobShortLpt(numMaquinas, lotes);

    salvarJSON();

    cout << "dados.json gerado!\n";
}