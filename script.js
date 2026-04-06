let dataGlobal;
let passo = 0;
let intervalo = null;
let rodando = false;

const container = document.getElementById("maquinas-container");
const lotesContainer = document.getElementById("lotes-container");

fetch("output/dados.json")
  .then(res => res.json())
  .then(data => {
    dataGlobal = data;

    lotesContainer.innerHTML = "";

    data.lotes.forEach(lote => {
      const div = document.createElement("div");
      div.className = "card lote";

      div.innerHTML = `
        <img src="shoes.png" class="sapatos-img">
        <div><strong>Lote ${lote.id}</strong></div>
        <div>Quantidade de sapatos: ${lote.qtd}</div>
        <div>Tempo por unidade: ${lote.tempoUnit}</div>
        <div>Tempo total de colagem: ${lote.tempoTotal}</div>
      `;

      lotesContainer.appendChild(div);
    });

    render(dataGlobal.iteracoes[0]);
  });


function render(iteracao) {
  container.innerHTML = "";

  iteracao.maquinas.forEach((maq, i) => {

    const maqDiv = document.createElement("div");
    maqDiv.className = "maquina";

    // INFO DA MÁQUINA
    const info = document.createElement("div");
    info.className = "maquina-info";

    info.innerHTML = `
      <img src="machine.png" class="maquina-img">
      <div>Máquina ${i + 1}</div>
      <div>Tempo de processamento: ${maq.tempo}</div>
    `;

    maqDiv.appendChild(info);

    // LOTES
    maq.lotes.forEach(id => {

      const lote = dataGlobal.lotes.find(l => l.id === id);

      const loteDiv = document.createElement("div");
      loteDiv.className = "lote-maquina";

      loteDiv.innerHTML = `
        <img src="shoes.png" class="sapatos-img-mini">
        <div><strong>Lote ${lote.id}</strong></div>
        <div>Tempo total do lote: ${lote.tempoTotal}</div>
      `;

      maqDiv.appendChild(loteDiv);
    });

    container.appendChild(maqDiv);
  });
}


function play() {
  if (rodando) return;

  rodando = true;

  intervalo = setInterval(() => {
    if (passo >= dataGlobal.iteracoes.length) {
      clearInterval(intervalo);
      rodando = false;
      return;
    }

    render(dataGlobal.iteracoes[passo]);
    passo++;

  }, 400);
}


function pause() {
  clearInterval(intervalo);
  rodando = false;
}


function reset() {
  pause();
  passo = 0;

  if (dataGlobal) {
    render(dataGlobal.iteracoes[0]);
  }
}