#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <cmath>
#include <ctime>
#include <fstream>
#include <unordered_map>

#define MIN_MAQUINAS 2
#define MAX_MAQUINAS 5
#define MIN_LOTES 10
#define MAX_LOTES 30
#define MIN_SAPATOS 10
#define MAX_SAPATOS 50
#define MIN_TEMPO 1
#define MAX_TEMPO 25

#define TEMP_INICIAL 400.0
#define REDUCAO_TEMP 0.95
#define TEMP_MINIMA 1.0

using namespace std;

// STRUCT 
struct Lote {
    int id;
    int qtd;
    int tempoUnit;
    int tempoTotal;
};

// ================= GERAR VIZINHO =================
vector<pair<int, list<int>>> gerarVizinho(
    int numMaquinas,
    vector<pair<int, list<int>>> maquinas,
    unordered_map<int, Lote> &mapaLotes)
{
    int rand_int = rand() % 2 + 1;

    int m1 = rand() % numMaquinas;
    int m2 = rand() % numMaquinas;

    if (maquinas[m1].second.empty())
        return maquinas;

    if (rand_int == 1 && !maquinas[m2].second.empty())
    {
        int lote_m1 = rand() % maquinas[m1].second.size();
        int lote_m2 = rand() % maquinas[m2].second.size();

        auto it_m1 = maquinas[m1].second.begin();
        auto it_m2 = maquinas[m2].second.begin();

        advance(it_m1, lote_m1);
        advance(it_m2, lote_m2);

        int t1 = mapaLotes[*it_m1].tempoTotal;
        int t2 = mapaLotes[*it_m2].tempoTotal;

        swap(*it_m1, *it_m2);

        maquinas[m1].first += (t2 - t1);
        maquinas[m2].first += (t1 - t2);
    }
    else
    {
        int idx = rand() % maquinas[m1].second.size();

        auto it = maquinas[m1].second.begin();
        advance(it, idx);

        int tempo = mapaLotes[*it].tempoTotal;

        maquinas[m2].second.push_back(*it);
        maquinas[m1].second.erase(it);

        maquinas[m1].first -= tempo;
        maquinas[m2].first += tempo;
    }

    return maquinas;
}

// ================= SA =================
vector<pair<int, list<int>>> JobShortSimulatedAnnealing(
    int numMaquinas,
    vector<pair<int, list<int>>> maquinas,
    unordered_map<int, Lote> &mapaLotes,
    vector<vector<pair<int, list<int>>>> &historico)
{
    vector<pair<int, list<int>>> maquinas_atual = maquinas;

    int melhor = (*max_element(maquinas.begin(), maquinas.end())).first;
    int atual = melhor;

    double temp = TEMP_INICIAL;

    historico.push_back(maquinas);

    while (temp >= TEMP_MINIMA)
    {
        auto vizinho = gerarVizinho(numMaquinas, maquinas_atual, mapaLotes);

        int custoVizinho = (*max_element(vizinho.begin(), vizinho.end())).first;

        if (custoVizinho < melhor)
        {
            melhor = custoVizinho;
            maquinas = vizinho;
        }

        if (custoVizinho < atual)
        {
            atual = custoVizinho;
            maquinas_atual = vizinho;
        }
        else
        {
            double prob = exp(-(custoVizinho - atual) / temp);

            if (prob > ((double)rand() / RAND_MAX))
            {
                atual = custoVizinho;
                maquinas_atual = vizinho;
            }
        }

        historico.push_back(maquinas_atual);
        temp *= REDUCAO_TEMP;
    }

    return maquinas;
}

// ================= DADOS =================
void definicaoAleatoriaSimulatedAnnealing(
    int &numMaquinas,
    int &numLotes,
    vector<Lote> &lotes)
{
    srand(time(nullptr));

    numMaquinas = rand() % (MAX_MAQUINAS - MIN_MAQUINAS + 1) + MIN_MAQUINAS;
    numLotes = rand() % (MAX_LOTES - MIN_LOTES + 1) + MIN_LOTES;

    lotes.resize(numLotes);

    for (int i = 0; i < numLotes; i++)
    {
        int sapatos = rand() % (MAX_SAPATOS - MIN_SAPATOS + 1) + MIN_SAPATOS;
        int tempoSapato = rand() % (MAX_TEMPO - MIN_TEMPO + 1) + MIN_TEMPO;

        lotes[i] = { i + 1, sapatos, tempoSapato, sapatos * tempoSapato };
    }
}

// ================= SOLUÇÃO INICIAL =================
vector<pair<int, list<int>>> solucaoInicialAleatoria(
    int numMaquinas,
    vector<Lote> lotes)
{
    vector<pair<int, list<int>>> maquinas(numMaquinas);

    shuffle(lotes.begin(), lotes.end(), default_random_engine(time(nullptr)));

    for (int i = 0; i < lotes.size(); i++)
    {
        maquinas[i % numMaquinas].second.push_back(lotes[i].id);
        maquinas[i % numMaquinas].first += lotes[i].tempoTotal;
    }

    return maquinas;
}

// ================= JSON =================
void salvarJSON(
    vector<Lote> lotes,
    vector<vector<pair<int, list<int>>>> historico)
{
    ofstream file("dados.json");

    file << "{\n";

    file << "\"lotes\": [\n";
    for (int i = 0; i < lotes.size(); i++)
    {
        file << "{ \"id\": " << lotes[i].id
             << ", \"qtd\": " << lotes[i].qtd
             << ", \"tempoUnit\": " << lotes[i].tempoUnit
             << ", \"tempoTotal\": " << lotes[i].tempoTotal << "}";

        if (i < lotes.size() - 1) file << ",";
        file << "\n";
    }
    file << "],\n";

    file << "\"iteracoes\": [\n";

    for (int h = 0; h < historico.size(); h++)
    {
        file << "{ \"maquinas\": [";

        for (int i = 0; i < historico[h].size(); i++)
        {
            file << "{ \"tempo\": " << historico[h][i].first << ", \"lotes\": [";

            int count = 0;
            for (int l : historico[h][i].second)
            {
                file << l;
                if (count < historico[h][i].second.size() - 1)
                    file << ",";
                count++;
            }

            file << "] }";

            if (i < historico[h].size() - 1)
                file << ",";
        }

        file << "] }";

        if (h < historico.size() - 1)
            file << ",";
        file << "\n";
    }

    file << "]\n}\n";
}

// ================= MAIN =================
int main()
{
    int numMaquinas, numLotes;

    vector<Lote> lotes;
    vector<vector<pair<int, list<int>>>> historico;

    definicaoAleatoriaSimulatedAnnealing(numMaquinas, numLotes, lotes);

    // MAPA DE LOTES (ESSENCIAL)
    unordered_map<int, Lote> mapaLotes;
    for (auto &l : lotes)
        mapaLotes[l.id] = l;

    auto maquinas = solucaoInicialAleatoria(numMaquinas, lotes);

    auto resultado = JobShortSimulatedAnnealing(
        numMaquinas,
        maquinas,
        mapaLotes,
        historico
    );

    salvarJSON(lotes, historico);

    cout << "OK - JSON GERADO\n";

    return 0;
}