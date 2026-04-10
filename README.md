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

## Tecnologias Utilizadas

- **C++**
- **HTML/CSS/JavaScript**
- **JSON**

## Como executar

1. Compile o arquivo `main.cpp`, correspondente ao código do algoritmo (C++):

```bash
g++ main.cpp -o algoritmo
```

2. Execute o algoritmo:

```bash
./algoritmo
```
Será gerado o arquivo `output/dados.json`, contendo os dados que foram gerados aleatoriamente para os lotes e máquinas.

3. Inicie o servidor local:

```bash
python -m http.server 8000
```

4. Acesse no navegador:

```bash
http://localhost:8000
```

## Equipe 04:

- João Felype Morais Vieira
- Luís Guilherme Ferreira da Costa
- Maria Eduarda Araujo Sales
- Maria Luiza Pereira Sousa
