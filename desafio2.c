#include "raylib.h"

#define LARGURA      800
#define ALTURA       450
#define RAIO_INICIAL 30
#define RAIO_MIN     5
#define RAIO_MAX     100
#define PASSO_RAIO   5
#define MAX_TINTAS   500

typedef struct {
    Vector2 pos;
    float raio;
    Color cor;
} Pincelada;

// ---------- logica (atualizar): muda o estado, nao desenha ----------
Color corAleatoria(void) {
    return (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255),
                    GetRandomValue(0, 255), 255 };
}

void atualizaPincel(Pincelada *p) {
    p->pos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))     // um clique, uma troca
        p->cor = corAleatoria();

    p->raio += GetMouseWheelMove() * PASSO_RAIO;     // roda muda o raio
    if (p->raio < RAIO_MIN) p->raio = RAIO_MIN;
    if (p->raio > RAIO_MAX) p->raio = RAIO_MAX;
}

void pinta(Pincelada tintas[], int *n, Pincelada p) {
    if (*n < MAX_TINTAS) {                           // vetor cheio: ignora
        tintas[*n] = p;
        (*n)++;
    }
}

// ---------- desenho: so le o estado ----------
void desenhaTintas(const Pincelada tintas[], int n) {
    for (int i = 0; i < n; i++)
        DrawCircleV(tintas[i].pos, tintas[i].raio, tintas[i].cor);
}

void desenhaPincel(Pincelada p) {
    DrawCircleV(p.pos, p.raio, p.cor);
    DrawCircleLines((int)p.pos.x, (int)p.pos.y, p.raio, DARKGRAY);
}

void desenhaInterface(Pincelada p, int n) {
    DrawText(TextFormat("Raio: %.0f", p.raio), 20, 20, 30, DARKGRAY);
    DrawText(TextFormat("Pinceladas: %d/%d", n, MAX_TINTAS), 20, 55, 20, GRAY);
    DrawText("Esq: troca cor | Roda: raio | Dir: pinta | C: limpa",
             20, ALTURA - 30, 20, GRAY);
}

int main(void) {
    InitWindow(LARGURA, ALTURA, "Desafio 2 - Pincel do mouse");
    SetTargetFPS(60);

    Pincelada pincel = { { LARGURA/2, ALTURA/2 }, RAIO_INICIAL, RED };
    Pincelada tintas[MAX_TINTAS];
    int n = 0;                                       // quantas pinceladas existem

    while (!WindowShouldClose()) {
        // 1. ENTRADA + 2. ATUALIZAR
        atualizaPincel(&pincel);

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))   // Down: pinta enquanto segura
            pinta(tintas, &n, pincel);

        if (IsKeyPressed(KEY_C))                     // Pressed: limpa uma vez
            n = 0;

        // 3. DESENHAR (a ordem importa: fundo, tintas, cursor, texto)
        BeginDrawing();
            ClearBackground(RAYWHITE);
            desenhaTintas(tintas, n);
            desenhaPincel(pincel);
            desenhaInterface(pincel, n);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}