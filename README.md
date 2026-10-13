# CursorPaint

Jogo simples de pintura feito em C com [raylib](https://www.raylib.com/), desenvolvido para o **Desafio 2 — Pincel do mouse**.

Este README separa duas situações:

- **Cliente (quem quer jogar):** só precisa baixar e abrir o jogo.
- **Projetista/desenvolvedor (quem quer modificar ou compilar o código):** encontra as instruções técnicas na seção separada, mais abaixo.

## Para jogar — cliente

### Requisitos

- Um computador com Windows 10 ou 11.
- O executável do CursorPaint (`desafio2.exe`).

**Você não precisa instalar Git, VS Code, GCC, Make ou raylib para jogar**, desde que esteja usando uma versão já compilada do jogo.

### Baixar e abrir

1. Acesse a página do repositório: [github.com/bielabs/CursorPaint](https://github.com/bielabs/CursorPaint).
2. Procure a seção **Releases** do GitHub e baixe o arquivo executável disponibilizado pelo projetista.
3. Se o arquivo vier em um `.zip`, extraia todo o conteúdo para uma pasta de sua preferência.
4. Dê dois cliques em `desafio2.exe` para abrir o jogo.

> **Atenção:** o repositório pode conter apenas o código-fonte. Se não houver um executável disponível na seção **Releases**, o projetista ainda precisa publicar uma versão compilada para que o cliente possa jogar sem preparar um ambiente de desenvolvimento. Baixar apenas os arquivos `.c` não é suficiente para executar o jogo diretamente.

### Controles do jogo

| Ação | Controle |
|---|---|
| Mudar a cor do pincel | Clique no botão esquerdo do mouse |
| Aumentar ou diminuir o tamanho do pincel | Role a roda do mouse |
| Desenhar | Segure o botão direito e mova o mouse |
| Limpar a tela | Pressione `C` |
| Fechar o jogo | Feche a janela ou pressione `Esc` |

### Como funciona

- O pincel acompanha o cursor do mouse.
- A cor muda aleatoriamente ao clicar com o botão esquerdo.
- O tamanho do pincel varia entre `5` e `100`.
- A tela mostra o raio atual e a quantidade de pinceladas.
- O jogo guarda até **500 pinceladas**. Ao atingir esse limite, limpe a tela com `C` para começar novamente.

---

## Para o projetista/desenvolvedor

Esta seção é destinada a quem mantém o repositório, altera o código ou precisa gerar uma nova versão executável. **Se você só quer jogar, não precisa seguir estes passos.**

### Tecnologias utilizadas

- Linguagem C (padrão C99)
- [raylib](https://www.raylib.com/)
- GCC
- GNU Make

### Preparar o ambiente no Windows

As instruções a seguir descrevem o ambiente Windows usado no desenvolvimento.

1. Instale a [raylib para Windows](https://www.raylib.com/) e siga as instruções do pacote escolhido.
2. Este projeto espera, por padrão, encontrar os arquivos da raylib em `C:/raylib/raylib/src` e o compilador em `C:/raylib/w64devkit/bin/gcc.exe`.
3. Instale o [Git](https://git-scm.com/downloads) caso ainda não esteja disponível.
4. Clone o repositório e entre na pasta do projeto:

   ```bash
   git clone https://github.com/bielabs/CursorPaint.git
   cd CursorPaint
   ```

5. Abra o terminal do w64devkit ou outro terminal em que `gcc` e `make` estejam disponíveis. Confira a instalação:

   ```bash
   gcc --version
   make --version
   ```

Se a raylib estiver em outro local, ajuste o caminho da variável `RAYLIB` no `Makefile` antes de compilar.

### Compilar e executar

Na pasta do projeto, execute:

```bash
make desafio2
```

Depois, execute o jogo:

```bash
./desafio2.exe
```

Se a compilação terminar sem erros, a janela **Desafio 2 - Pincel do mouse** deverá abrir.

Para gerar uma nova versão depois de modificar o código, feche o jogo e execute novamente `make desafio2`. O executável gerado é `desafio2.exe`.

### Arquivos principais

```text
CursorPaint/
├── .gitignore
├── Makefile
├── README.md
├── desafio2.c
└── .vscode/
    └── c_cpp_properties.json   # opcional, para IntelliSense no VS Code
```

- `desafio2.c`: código-fonte do jogo.
- `Makefile`: instruções de compilação.
- `.vscode/c_cpp_properties.json`: configuração opcional do IntelliSense no VS Code.

### Configuração opcional do VS Code

Se `#include "raylib.h"` aparecer sublinhado em vermelho no VS Code, mas o programa compilar, pode ser apenas um problema de configuração do IntelliSense.

Crie `.vscode/c_cpp_properties.json` na raiz do projeto:

```json
{
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "${workspaceFolder}/**",
        "C:/raylib/raylib/src"
      ],
      "compilerPath": "C:/raylib/w64devkit/bin/gcc.exe",
      "cStandard": "c99",
      "intelliSenseMode": "windows-gcc-x64"
    }
  ],
  "version": 4
}
```

Se a raylib estiver instalada em outro diretório, atualize `includePath` e `compilerPath`.

### Solução de problemas de compilação

- **`make: command not found`:** abra o terminal fornecido pelo w64devkit ou configure um terminal que tenha o GNU Make no `PATH`.
- **`make: Nothing to be done for 'desafio2.c'`:** use `make desafio2`, sem a extensão `.c`.
- **`undefined reference to WinMain`:** confira se `desafio2.c` contém o código completo e foi salvo, e se o `Makefile` está preenchido e na pasta correta.
- **`raylib.h: No such file or directory`:** confirme se o caminho dos cabeçalhos da raylib está correto na variável `RAYLIB`.
- **Erros como `undefined reference to InitWindow`:** confira se o `Makefile` está sendo usado e se os parâmetros de link da raylib estão corretos.
- **`No rule to make target 'clean'`:** confira se o arquivo `Makefile` está presente, salvo com esse nome exato e não como `Makefile.txt`.
- **`missing separator`:** confira se as linhas de comandos no `Makefile` começam com um caractere TAB quando exigido pelo Make.

### Publicar uma versão para os clientes

Para permitir que alguém jogue sem instalar ferramentas de desenvolvimento:

1. Compile o projeto no ambiente compatível com o sistema de destino.
2. Teste o executável em um ambiente Windows semelhante ao do usuário final.
3. Empacote `desafio2.exe` e quaisquer arquivos adicionais de que a versão compilada precise em um `.zip`.
4. No GitHub, crie uma publicação em **Releases** e anexe o `.zip`.
5. Atualize as instruções da seção **Para jogar — cliente** se o nome do arquivo ou o processo de instalação mudar.

Não é necessário incluir arquivos temporários de compilação no repositório de código. O `.gitignore` deve ignorar executáveis e outros artefatos gerados, conforme a organização do projeto.

## Referências

- [raylib — site oficial](https://www.raylib.com/)
- [raylib — cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [Repositório de referência da aula](https://github.com/0x03c1/Raylib)
- [Repositório CursorPaint](https://github.com/bielabs/CursorPaint)

---

Projeto desenvolvido para fins de estudo.

---

## Alunos:
- Antonio Sandes
- Gabriel Araujo
- Heitor Torres
- Isabelly Ribeiro
- Rafael de Andrade
- Rubens Sousa
