#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "../headers/dependencies.h"

#define COLLISION_DATABASE "res/database/collision_data.csv"

#define MAX_LENGTH 50
#define MAX_VALUES 4
#define MAX_CHARACTERS 55

/*
* Função que lê todos os valores das posições dos blocos de colisões do mapa por meio
* da função "fopen" para acessar o .csv com os valores.
*
* returns -> um ponteiro para CollisionBlock (um array de CollisionBlock)
*/
CollisionBlock * getCollisionBlocks() {
    static CollisionBlock list[MAX_COLLISIONS];

    FILE *file = fopen(COLLISION_DATABASE, "r");

    if (file == NULL) {
        perror("\n- [BUILDING_ERROR]\t -> | ERRO: Ocorreu um erro ao acessar banco de colisoes\n");
        return 1;
    }

    char line[MAX_LENGTH];
    int collisionIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        // Divide os valores por "tokens" separados por vírgula
        char *token = strtok(line, ",");
        int values[MAX_VALUES];
        int i = 0;

        while (token != NULL && i < MAX_VALUES) {
            values[i] = atoi(token); // Converte o valor lido para int
            token = strtok(NULL, ",");
            i++;
        }

        if (i == MAX_VALUES) {
            // Adiciona as coordenadas dos pontos do bloco de colisão
            list[collisionIndex].topLeftX = values[0];
            list[collisionIndex].topLeftY = values[1];
            list[collisionIndex].bottomRightX = values[2];
            list[collisionIndex].bottomRightY = values[3];

            // Vai para o próximo bloco de colisão
            collisionIndex++;

            if (collisionIndex >= MAX_COLLISIONS) {
                break; // Interrompe a leitura do banco se já atingiu a quantidade de colisões pré-definidas do mapa
            }
        }
    }

    fclose(file);

    printf("\n- [BUILDING]\t -> | Banco de colisoes carregado com sucesso.");

    return list;
}

/*
* Função que faz o carregamento de todos os bitmaps de movimento do personagem
* utilizando uma string dinâmica que é construída com base no gênero escolhido
* e no movimento da lista.
*
* returns -> um ponteiro para um ponteiro de ALLEGRO_BITMAP (uma lista de ALLEGRO_BITMAPs)
*/
ALLEGRO_BITMAP ** getCharacterMovementSprites(int gender) {
    static ALLEGRO_BITMAP* list[MAX_MOVEMENTS];

    char *strGender = gender == BOY ? "boy" : "girl";

    // String do caminho do arquivo
    char path[MAX_LENGTH];

    char *movementNames[] = {
        "standby_up", "walking_up_1", "walking_up_2",
        "standby_left", "walking_left_1", "walking_left_2",
        "standby_down", "walking_down_1", "walking_down_2",
        "standby_right", "walking_right_1", "walking_right_2"
    };
    int i;
    for (i = 0; i < MAX_MOVEMENTS; i++) {
        // Construção da string
        snprintf(path, sizeof(path), "res/sprites/%s/%s_%s.png", strGender, strGender, movementNames[i]);
        list[i] = al_load_bitmap(path);

        if (!list[i]) {
            printf("\n- [BUILDING]\t -> | ERRO: Ocorreu um erro ao carregar a imagem: %s\n", path);
            return 1;
        }
    }

    printf("\n- [BUILDING]\t -> | Bitmaps de movimento do personagem carregados com sucesso.");

    return list;
}

/*
* Função que faz o carregamento de todos os desafios do jogo, populando
* uma lista de objetos da struct Challenge.
*
* returns -> uma lista de Challenges
*/
Challenge * getChallenges() {
    Challenge* list = malloc(MAX_QUESTIONS * sizeof(Challenge));

    list[0].questionText[0] = "Olá, %s!";
    list[0].questionText[1] = "Estamos com uma grande quantidade de caixas de pokebólas para enviar para Johto!";
    list[0].questionText[2] = "Precisamos decompor o valor total em numeração decimal para fazermos o envio para transportadora.";
    list[0].questionText[3] = "Poderia nos ajudar? A quantidade total de pokebólas é 135.";
    list[0].questionText[4] = "";

    list[0].alternatives[0] = "12 dezenas e 5 unidades";
    list[0].alternatives[1] = "13 dezenas e 5 unidades";
    list[0].alternatives[2] = "12 dezenas e 10 unidades";
    list[0].alternatives[3] = "13 dezenas e 1 unidade";

    list[0].correctAnswer = B;

    list[1].questionText[0] = "%s, sua próxima jornada está prestes a começar!";
    list[1].questionText[1] = "Você está em Pallet Town e deseja calcular a diferença de tempo entre diferentes meios de locomoção até a próxima cidade, Pewter City.";
    list[1].questionText[2] = "Normalmente, levaria 5 horas a pé, mas você tem um amigo Pokémon!";
    list[1].questionText[3] = "Um Rapidash! Que pode levá-lo lá muito mais rápido, a uma média de 220 km/h.";
    list[1].questionText[4] = "Que horas você aproximadamente chegaria em Pewter City, saindo de Pallet Town às 14:00 horas, montado no seu confiável Rapidash?";
    list[1].questionText[5] = "";

    list[1].alternatives[0] = "16:35";
    list[1].alternatives[1] = "14:20";
    list[1].alternatives[2] = "14:01";
    list[1].alternatives[3] = "19:15";

    list[1].correctAnswer = C;

    list[2].questionText[0] = "Olá, treinador %s!";
    list[2].questionText[1] = "Você está em uma batalha Pokémon contra um adversário habilidoso.";
    list[2].questionText[2] = "Para vencer, você precisa prestar muita atenção aos padrões.";
    list[2].questionText[3] = "Após uma sequência de pokémons um padrão é revelado:";
    list[2].questionText[4] = "Charmander - Pikachu - Squirtle - Bulbassaur - Jigglypuff - Charmander - Pikachu...";
    list[2].questionText[5] = "Quantos Squirtles terão na 6ª parte dessa sequência?";

    list[2].alternatives[0] = "1";
    list[2].alternatives[1] = "5";
    list[2].alternatives[2] = "3";
    list[2].alternatives[3] = "6";

    list[2].correctAnswer = A;

    list[3].questionText[0] = "Treinador %s!";
    list[3].questionText[1] = "Precisamos criar um algoritmo para a pokedéx que determine a probabilidade de encontrar um Pokémon lendário em cada região que visitarmos!";
    list[3].questionText[2] = "As probabilidades variam de acordo com a região, portanto, precisamos considerar dois fatores:";
    list[3].questionText[3] = "Total de Pokémons Lendários da Região e Total de Pokémons da Região.";
    list[3].questionText[4] = "Qual algoritmo é o melhor para representar essa probabilidade em porcentagem (%%)?";
    list[3].questionText[5] = "";

    list[3].alternatives[0] = "(lendários / totais) x 100";
    list[3].alternatives[1] = "(lendários + 100) / totais";
    list[3].alternatives[2] = "(totais + lendarios) / 100";
    list[3].alternatives[3] = "(lendarios x totais) x 100";

    list[3].correctAnswer = A;

    list[4].questionText[0] = "Treinador!";
    list[4].questionText[1] = "Estamos partindo em uma missão para encontrar as partes de um antigo artefato Pokémon que estão espalhadas dentro da caverna de Mt. Moon.";
    list[4].questionText[2] = "Precisamos dividir essa missão em etapas menores. Aqui está a missão decomposta em etapas:";
    list[4].questionText[3] = "1. Voltar e estudar as peças encontradas. - 2. Preparar uma equipe Pokémon e partir - 3. Chegar ao Mt. Moon em segurança - 4. Encontrar todas as peças";
    list[4].questionText[4] = "Qual é a ordem correta das etapas?";
    list[4].questionText[5] = "";

    list[4].alternatives[0] = "1, 2, 3, 4";
    list[4].alternatives[1] = "2, 3, 4, 1";
    list[4].alternatives[2] = "1, 3, 4, 2";
    list[4].alternatives[3] = "4, 2, 1, 3";

    list[4].correctAnswer = B;

    list[5].questionText[0] = "Olá, %s! Lembra do algoritmo que criamos?";
    list[5].questionText[1] = "Parece que estão acontecendo alguns bugs na pokedéx e o algoritmo está apresentando a probabilidade errada!";
    list[5].questionText[2] = "Precisamos realizar um teste de mesa do Profº Naves para ter certeza de que o algoritmo está correto!";
    list[5].questionText[3] = "Aplique o algoritmo sabendo que a região de Kanto possuí:";
    list[5].questionText[4] = "5 Pokémons lendários e um total de 151 Pokémons em toda a região.";
    list[5].questionText[5] = "";

    list[5].alternatives[0] = "4.29%";
    list[5].alternatives[1] = "2.73%";
    list[5].alternatives[2] = "5.14%";
    list[5].alternatives[3] = "3.31%";

    list[5].correctAnswer = D;

    list[6].questionText[0] = "Está na hora de uma batalha Pokémon, %s!";
    list[6].questionText[1] = "Gary está usando um Pokémon do tipo Água.";
    list[6].questionText[2] = "Você precisa escolher o melhor Pokémon para enfrentá-lo.";
    list[6].questionText[3] = "Pokémons do tipo Planta são super efetivos e resistentes contra os Pokémons do tipo Água.";
    list[6].questionText[4] = "Qual Pokémon você escolherá com base na abstração da situação?";
    list[6].questionText[5] = "";

    list[6].alternatives[0] = "Charmander (Fogo)";
    list[6].alternatives[1] = "Bulbassaur (Planta/Venenoso)";
    list[6].alternatives[2] = "Pikachu (Elétrico)";
    list[6].alternatives[3] = "Jigglypuff (Normal/Fada)";

    list[6].correctAnswer = B;

    list[7].questionText[0] = "Precisamos arrumar uma base de dados sobre as vitórias dos treinadores desse semestre no Ginásio!";
    list[7].questionText[1] = "Um Slowpoke safado fez nosso programador preencher os dados erroneamente!";
    list[7].questionText[2] = "Veja se consegue identificar um padrão nos dados para arrumarmos o problema:";
    list[7].questionText[3] = "Ash: 3 vitórias - Brock: 5 vitórias - Misty: 5 vitórias - Gary: 4 vitórias - May: 3 vitórias";
    list[7].questionText[4] = "Quantas vitórias o Slowpoke fez o nosso programador colocar para o treinador %s?";
    list[7].questionText[5] = "";

    list[7].alternatives[0] = "4 vitórias";
    list[7].alternatives[1] = "1 vitória";
    list[7].alternatives[2] = "%i vitórias";
    list[7].alternatives[3] = "5 vitórias";

    list[7].correctAnswer = C;

    list[8].questionText[0] = "Treinador %s! O fim da jornada se aproxima!";
    list[8].questionText[1] = "Como último desafio, você deve desvendar o mistério das lendas de...";
    list[8].questionText[2] = "Arceus, O Primeiro Pokémon!";
    list[8].questionText[3] = "A entrada está protegida por um enigma complexo.";
    list[8].questionText[4] = "Para acessar a caverna, você deve desvendar o número misterioso do enigma.";
    list[8].questionText[5] = "";

    list[8].alternatives[0] = "";
    list[8].alternatives[1] = "";
    list[8].alternatives[2] = "";
    list[8].alternatives[3] = "";

    list[8].correctAnswer = B;

    list[9].questionText[0] = "'No coração de Kanto, sob o sol escaldante,";
    list[9].questionText[1] = "Nas entranhas da região, há um número intrigante.";
    list[9].questionText[2] = "Se trata do primeiro múltiplo de 5 que possui o mesmo resto por 2 que a quantidade total de Pokémons de Kanto,";
    list[9].questionText[3] = "Adicionado ao dobro da quantidade de Pokémons Lendários que nos traz tanto encanto.";
    list[9].questionText[4] = "E ao adicionar o número de letras em 'Pikachu',";
    list[9].questionText[5] = "E subtrair o número de letras em 'Squirtle',";
    list[9].questionText[6] = "Você chegará à suprema resposta final,";
    list[9].questionText[7] = "E encontrará a chave para abrir esta entrada especial.'";

    list[9].alternatives[0] = "5";
    list[9].alternatives[1] = "14";
    list[9].alternatives[2] = "8";
    list[9].alternatives[3] = "15";

    list[9].correctAnswer = B;
    int i;
    for (i = 0; i < sizeof(list); i++) list[i].isChallengeCompleted = false;

    printf("\n- [BUILDING]\t -> | Lista de desafios carregada com sucesso.");

    return list;
}

/*
* Função que faz o carregamento da localização de todas as portas das casas que são
* acessíveis no jogo, também definindo "false" para o atributo "alreadyEntered" inicialmente.
*
* returns -> uma lista de HouseDoor
*/
HouseDoor * getHouses(){

    static HouseDoor houses[] =
    {
        {161, 185, 194, 198, false},
        {270, 285, 194, 198, false},
        {480, 505, 192, 198, false},
        {242, 256, 287, 290, false},
        {350, 370, 319, 323, false},
        {495, 514, 346, 350, false},
        {203, 241, 464, 470, false},
        {369, 382, 463, 469, false},
        {465, 479, 463, 469, false},
        {12, 33, 194, 212, false}
    };

    printf("\n- [BUILDING]\t -> | Casas acessiveis carregadas com sucesso.");

    return houses;
}

/*
* Função de utilidade que identifica quando um texto atinge o máximo de caracteres permitido por linha
* e faz uma quebra na mesma, jogando o texto que execederia a tela para a linha de baixo. A função também
* é capaz de identificar se uma palavra está sendo cortada ao meio, e também joga ela para linha de baixo.
*/
void splitText(int textLength, char* questionText, ALLEGRO_FONT* font) {
    const int maxLineLength = MAX_CHARACTERS;
    int start = 0;
    int end = 0;
    int partIndex = 0;
    char textParts[10][maxLineLength + 1]; // +1 para o caractere nulo
    bool wordCutoff = false;

    int i;
    for (i = 0; i < textLength; i++) {
        if (i - start >= maxLineLength) {
            // Verifica se a palavra está sendo cortada
            if (wordCutoff) {
                // Se a palavra estiver sendo cortada, volte para o último espaço
                i = end;
            } else {
                // Caso contrário, vá até o próximo espaço
                i = end;
            }

            wordCutoff = false;

            // Copia a parte do texto para a matriz
            strncpy(textParts[partIndex], &questionText[start], i - start);
            textParts[partIndex][i - start] = '\0'; // Certifique-se de que a string esteja terminada corretamente

            // Remove espaços em branco no início da parte
            int len = strlen(textParts[partIndex]);
            while (len > 0 && textParts[partIndex][0] == ' ') {
                memmove(textParts[partIndex], textParts[partIndex] + 1, len);
                len = strlen(textParts[partIndex]);
            }

            partIndex++;
            start = i;
            start = i;
        } else if (questionText[i] == ' ') {
            end = i; // Marca o último espaço
        } else if (questionText[i] == '\n') {
            // Adiciona uma nova linha diretamente
            strncpy(textParts[partIndex], &questionText[start], i - start);
            textParts[partIndex][i - start] = '\0';

            // Remove espaços em branco no início da parte
            int len = strlen(textParts[partIndex]);
            while (len > 0 && textParts[partIndex][0] == ' ') {
                memmove(textParts[partIndex], textParts[partIndex] + 1, len);
                len = strlen(textParts[partIndex]);
            }

            partIndex++;
            start = i + 1;
            end = i + 1;
        }

        // Verifica se a palavra está sendo cortada
        if (i - start >= maxLineLength) {
            wordCutoff = true;
        }
    }

    // Copia a última parte do texto
    strncpy(textParts[partIndex], &questionText[start], textLength - start);
    textParts[partIndex][textLength - start] = '\0';

    // Remove espaços em branco no início da parte
    int len = strlen(textParts[partIndex]);
    while (len > 0 && textParts[partIndex][0] == ' ') {
        memmove(textParts[partIndex], textParts[partIndex] + 1, len);
        len = strlen(textParts[partIndex]);
    }

    partIndex++;

    // Itera e desenha as partes
    for (i = 0; i < partIndex; i++) {
        al_draw_text(font, al_map_rgb(255, 255, 255), 35, 545 + i * 20, 0, textParts[i]);
    }
}
