#include <SDL_main.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <regex>

struct Bola
{
    SDL_Rect forma;
    SDL_Color cor;

    Bola(int raio, const SDL_Color& cor, int x, int y)
    {
        forma = { x - raio, y - raio, raio * 2, raio * 2 };
        this->cor = cor;
    }
};

static int ready_archive()
{
    int ball_quantity = 0;

    std::ifstream arquivo("virus_selection.txt");

    if (arquivo.is_open())
    {
        arquivo >> ball_quantity;
        arquivo.close();
        std::cout << "Valor lido do arquivo: " << ball_quantity << std::endl;
        return ball_quantity;
    }
    else
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 0;
    }
}

static SDL_Color gerarCorAleatoria()
{
    Uint8 red = std::rand() % 256;
    Uint8 green = std::rand() % 256;
    Uint8 blue = std::rand() % 256;

    return { red, green, blue, 255 };
}

int main(int argc, char* argv[])
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int selectionVirus = ready_archive();
    float interval = 0;
    int bolinhasPorVez{};
    int days = 0;

    if (selectionVirus == 1)
    {
        interval = 2.0f;
        bolinhasPorVez = 60;
    }
    if (selectionVirus == 2)
    {
        interval = 2.0f;
        bolinhasPorVez = 180;
    }
    if (selectionVirus == 3)
    {
        interval = 2.0f;
        bolinhasPorVez = 144;
    }
    if (selectionVirus == 4)
    {
        interval = 2.0f;
        bolinhasPorVez = 180;
    }
    if (selectionVirus == 5)
    {
        interval = 2.0f;
        bolinhasPorVez = 144;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (TTF_Init() != 0)
    {
        std::cerr << "Erro ao inicializar o SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Virus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::vector<Bola> bolas;

    SDL_Color textColor = { 255, 255, 255, 255 };
    TTF_Font* font = TTF_OpenFont("font.otf", 30);

    if (!font)
    {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Surface* virusesTextSurface = nullptr;
    SDL_Surface* daysTextSurface = nullptr;
    SDL_Texture* virusesTextTexture = nullptr;
    SDL_Texture* daysTextTexture = nullptr;
    SDL_Rect virusesTextRect = { 0, 0, 0, 0 };
    SDL_Rect daysTextRect = { 0, 0, 0, 0 };

    // Loop principal
    bool quit = false;
    Uint32 lastBallCreationTime = SDL_GetTicks();  // Armazena o tempo da última criação de bola

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                // Mantém a mesma escala mesmo quando a janela é redimensionada
                SDL_Rect viewportRect = { 0, 0, static_cast<int>(event.window.data1), static_cast<int>(event.window.data2) };
                SDL_RenderSetViewport(renderer, &viewportRect);
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastBallCreationTime) / 1000.0f;  // Calcula a diferença em segundos

        if (deltaTime >= interval)
        {
            for (int i = 0; i < bolinhasPorVez; ++i)
            {
                int raio = 10;
                int x = std::rand() % (800 - raio * 2) + raio;
                int y = std::rand() % (600 - raio * 2) + raio;

                SDL_Color cor = gerarCorAleatoria();
                Bola bola(raio, cor, x, y);
                bolas.push_back(bola);
            }

            days++;
            lastBallCreationTime = currentTime;
        }

        // Atualiza o texto de informações
        std::string virusesText = "Approximation of Produced Viruses: " + std::to_string(bolas.size());
        std::string daysText = "Days gone by: " + std::to_string(days);

        virusesTextSurface = TTF_RenderText_Solid(font, virusesText.c_str(), textColor);
        daysTextSurface = TTF_RenderText_Solid(font, daysText.c_str(), textColor);

        virusesTextTexture = SDL_CreateTextureFromSurface(renderer, virusesTextSurface);
        daysTextTexture = SDL_CreateTextureFromSurface(renderer, daysTextSurface);

        virusesTextRect.x = 10;
        virusesTextRect.y = 10;
        virusesTextRect.w = virusesTextSurface->w;
        virusesTextRect.h = virusesTextSurface->h;

        daysTextRect.x = 10;
        daysTextRect.y = 10 + virusesTextRect.h;
        daysTextRect.w = daysTextSurface->w;
        daysTextRect.h = daysTextSurface->h;

        // Limpa a janela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Desenha todas as bolas no vetor
        for (const auto& bola : bolas)
        {
            SDL_SetRenderDrawColor(renderer, bola.cor.r, bola.cor.g, bola.cor.b, bola.cor.a);
            SDL_RenderFillRect(renderer, &bola.forma);
        }

        // Desenha o texto de informações
        SDL_RenderCopy(renderer, virusesTextTexture, nullptr, &virusesTextRect);
        SDL_RenderCopy(renderer, daysTextTexture, nullptr, &daysTextRect);

        // Mostra tudo na janela
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(virusesTextTexture);
    SDL_DestroyTexture(daysTextTexture);
    SDL_FreeSurface(virusesTextSurface);
    SDL_FreeSurface(daysTextSurface);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
