#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace sf;

struct Bola
{
    CircleShape forma;

    Bola(float raio, const Color &cor, float x, float y)
    {
        forma = CircleShape(raio);
        forma.setFillColor(cor);
        forma.setPosition(x, y);
    }
};

int ready_archive()
{
    int ball_quantity = 0;

    std::ifstream arquivo("output/virus_selection.txt");

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

Color gerarCorAleatoria()
{
    // Gera valores aleatórios para os componentes de cor (RGB)
    Uint8 red = std::rand() % 256;
    Uint8 green = std::rand() % 256;
    Uint8 blue = std::rand() % 256;

    return Color(red, green, blue);
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int selectionVirus = ready_archive();
    float interval;
    int bolinhasPorVez;
    int days = 0;

    if (selectionVirus == 1)
    {                        // Escolha de qual é o tipo de vírus
        interval = 2.0f;     // Intervalo em segundos entre cada multiplicação
        bolinhasPorVez = 60; // Quantidade de bolinhas que aparecerão a cada intervalo
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

    RenderWindow window(VideoMode(800, 600), "Virus");

    std::vector<Bola> bolas;

    Clock clock;
    float tempoPassado = 0.0f;

    Font font;
    if (!font.loadFromFile("pricedown.bl-regular.otf")) // Certifique-se de que o arquivo "pricedown.bl-regular.otf" está no mesmo diretório do seu executável
    {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        return -1;
    }

    Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(30);
    infoText.setFillColor(Color::White);

    // Configura uma View fixa para a janela
    View view(FloatRect(0, 0, 800, 600));
    window.setView(view);

    // Loop principal
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::Resized)
            {
                // Mantém a mesma escala mesmo quando a janela é redimensionada
                view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(view);
            }
        }

        // Adiciona bolas ao vetor com posições e cores aleatórias em intervalos de tempo
        tempoPassado += clock.restart().asSeconds();
        // if (tempoPassado >= interval && bolas.size() < selectionVirus)
        if (tempoPassado >= interval)
        {
            for (int i = 0; i < bolinhasPorVez; ++i)
            {
                float raio = 10.0f;
                float x = static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(raio) * 2) + static_cast<int>(raio));
                float y = static_cast<float>(std::rand() % (window.getSize().y - static_cast<int>(raio) * 2) + static_cast<int>(raio));

                Color cor = gerarCorAleatoria();
                Bola bola(raio, cor, x, y);
                bolas.push_back(bola);
            }

            tempoPassado = 0.0f;
            days++;
        }

        // Atualiza o texto de informações
        // infoText.setString("Day: " + std::to_string(days) + "\nViruses produced: " + std::to_string(bolas.size()));
        infoText.setString("Approximation of Produced Viruses: " + std::to_string(bolas.size()) + "\nDays gone by: " + std::to_string(days));

        // Limpa a janela
        window.clear();

        // Desenha todas as bolas no vetor
        for (const auto &bola : bolas)
        {
            window.draw(bola.forma);
        }

        // Desenha o texto de informações
        window.draw(infoText);

        // Mostra tudo na janela
        window.display();
    }

    return 0;
}
