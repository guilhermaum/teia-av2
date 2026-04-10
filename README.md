# Sistema de Alocação de Máquinas

## Descrição

Este projeto foi desenvolvido para a disciplina de **Tópicos Especiais em Inteligência Artificial** e tem como objetivo resolver um problema de **alocação de recursos**, no qual diferentes tarefas devem ser distribuídas entre máquinas de forma eficiente.

O sistema busca distribuir lotes de produção entre máquinas industriais de forma eficiente, minimizando o tempo total de execução (**makespan**) e equilibrando a carga de trabalho.

Foram implementados dois algoritmos: **LPT (Longest Processing Time)** e **Simulated Annealing (SA)**.

Cada algoritmo está disponível em uma branch separada:

- `LPT`
- `SA`

## Problema

Uma fábrica de calçados possui um setor responsável pela colagem de solas, realizado por máquinas industriais.

Durante um turno de produção:

- Existem entre **2 e 5 máquinas**
- São processados entre **10 e 30 lotes**
- Cada lote contém entre **10 e 50 sapatos**
- O tempo de colagem varia entre **1 e 25 segundos por sapato**

### Restrições

- Cada máquina processa **um lote por vez**
- Um lote deve ser completamente finalizado antes do próximo

### Objetivo

Distribuir os lotes entre as máquinas de forma que:

- O trabalho fique **balanceado**
- O tempo total de produção (**makespan**) seja **minimizado**

## Modelagem

### Representação Computacional

- **Lote**
  - ID
  - Quantidade de sapatos
  - Tempo de colagem de cada sapato
  - Tempo total

- **Máquina**
  - Tempo total de processamento
  - Lista de lotes atribuídos

## Função de Avaliação

O desempenho de uma solução é medido pelo:

**Makespan**: maior tempo entre todas as máquinas

```
minimizar max(tempo_maquina)
```

## Algoritmos

### LPT (Longest Processing Time)

Algoritmo guloso que ordena os lotes por tempo total (decrescente) e atribui cada lote à máquina com menor carga.

#### Vantagens

- Simples
- Rápido
- Boa solução inicial

#### Limitações

- Não garante solução ótima

---

### Simulated Annealing

Metaheurística baseada em busca local com aceitação probabilística.

#### Etapas

1. Geração de solução inicial aleatória
2. Geração de vizinhos:
   - Troca de lotes
   - Realocação entre máquinas

3. Avaliação (makespan)
4. Critério de aceitação:
   - Melhor solução → sempre aceita
   - Pior solução → aceita com probabilidade

5. Redução gradual da temperatura

#### Vantagens

- Escapa de mínimos locais
- Melhor qualidade de solução

#### Limitações

- Mais lento
- Dependente de parâmetros

## Tecnologias

- **C++** → algoritmos
- **HTML/CSS/JavaScript** → interface
- **JSON** → comunicação

## Execução

O sistema funciona em duas etapas principais:

1. **Execução do algoritmo**
2. **Visualização dos resultados na interface web**

### 1. Executar o algoritmo (C++)

Primeiramente, é necessário compilar e executar o arquivo `main.cpp`.  
Essa etapa é responsável por:

- Gerar os dados aleatórios (lotes e máquinas)
- Executar o algoritmo (LPT ou Simulated Annealing)
- Gerar o arquivo `dados.json` com os resultados

#### Compilação

```bash
g++ main.cpp -o algoritmo
```

#### Execução

```bash
./algoritmo
```

Após a execução, será gerado o arquivo:

```bash
output/dados.json
```

### 2. Executar a visualização

Para evitar problemas com o carregamento do JSON, é recomendado utilizar um servidor local.

#### Usando Python:

```bash
python -m http.server 8000
```

Acesse no navegador:
```
http://localhost:8000
```

## Visualização

A interface permite acompanhar de forma visual como os lotes são distribuídos entre as máquinas, facilitando a compreensão do funcionamento dos algoritmos.

### LPT

O processo guloso de distribuição dos lotes é apresentado da seguinte forma:

- Lotes gerados
- Lotes ordenados
- Distribuição final entre as máquinas

### Simulated Annealing

A visualização mostra a evolução da solução ao longo das iterações do algoritmo:

- Lotes iniciais
- Evolução das soluções
- Controles:
  - Iniciar
  - Pausar
  - Resetar

## Conclusão

O projeto demonstra diferentes abordagens para a resolução de um problema clássico de escalonamento, evidenciando as vantagens de cada estratégia. Enquanto o LPT fornece uma solução rápida e eficiente, o Simulated Annealing permite melhorar a qualidade da solução ao explorar de forma mais ampla o espaço de busca. Dessa forma, ambos podem ser utilizados de maneira complementar.

## Equipe 04:

- João Felype Morais Vieira
- Luís Guilherme Ferreira da Costa
- Maria Eduarda Araujo Sales
- Maria Luiza Pereira Sousa
