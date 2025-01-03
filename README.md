# Audio Spectrum Visualizer

Este projeto implementa um visualizador de espectro de áudio em tempo real utilizando a linguagem de programação **C++**. O código foi desenvolvido no editor de texto **Visual Studio Code (VSCode)**, conectado ao **Windows Subsystem for Linux (WSL)** com a distribuição **Ubuntu**.

## Funcionalidades
- Leitura de arquivos de áudio no formato **.wav**.
- Análise do espectro de frequência utilizando a biblioteca **FFTW**.
- Visualização do espectro com gráficos em tempo real utilizando a biblioteca **SFML**.
- Exibição do progresso da reprodução e informações sobre a música.

---

## Requisitos
Antes de compilar e executar o programa, certifique-se de ter as seguintes bibliotecas instaladas no seu ambiente Linux (Ubuntu):

- **SFML** (Simple and Fast Multimedia Library):
  ```bash
  sudo apt-get install libsfml-dev
  ```

- **FFTW** (Fastest Fourier Transform in the West):
  ```bash
  sudo apt-get install libfftw3-dev
  ```

---

## Compilação
Utilize o comando abaixo para compilar o programa:

```bash
g++ main.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfftw3
```

### Descrição do comando:
- **g++ main.cpp**: Compila o arquivo principal do código.
- **-o app**: Define o nome do executável gerado como `app`.
- **-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio**: Linka as bibliotecas da SFML necessárias para gráficos, janelas, sistema e áudio.
- **-lfftw3**: Linka a biblioteca FFTW para análise do espectro de frequência.

---

## Execução
Para executar o programa, use o comando abaixo:

```bash
./app [nome_da_musica.wav]
```

- Substitua `[nome_da_musica.wav]` pelo caminho e nome do arquivo de áudio que deseja analisar.
- Certifique-se de que o arquivo de áudio esteja no formato **.wav**.

### Exemplo:
```bash
./app exemplo.wav
```

---

## Observações
- Certifique-se de que os arquivos necessários (como imagens ou fontes mencionados no código) estejam no mesmo diretório do executável ou no caminho correto especificado no código.
- Caso encontre problemas durante a execução, verifique se todas as dependências estão instaladas corretamente e se os arquivos de entrada estão no formato suportado.

---

## Referências
- [Documentação da SFML](https://www.sfml-dev.org/documentation/2.5.1/)
- [Documentação da FFTW](http://www.fftw.org/)
