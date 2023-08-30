#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>

#include "../headers/dependencies.h"

#define COLLISION_DATABASE "res/database/collision_data.csv"

#define MAX_LENGTH 50
#define MAX_VALUES 4

/*
* Função que lê todos os valores das posições dos blocos de colisões do mapa por meio
* da função "fopen" para acessar o .csv com os valores.
*
* returns -> um ponteiro para CollisionBlock (um array de CollisionBlock)
*/
CollisionBlock * getCollisionBlocks()
{
    static CollisionBlock list[MAX_COLLISIONS];

    FILE *file = fopen(COLLISION_DATABASE, "r");

    if (file == NULL)
    {
        perror("\nERRO: Ocorreu um erro ao acessar banco de colisoes\n");
        return 1;
    }

    char line[MAX_LENGTH];
    int collisionIndex = 0;

    while (fgets(line, sizeof(line), file))
    {
        // Divide os valores por "tokens" separados por vírgula
        char *token = strtok(line, ",");
        int values[MAX_VALUES];
        int i = 0;

        while (token != NULL && i < MAX_VALUES)
        {
            values[i] = atoi(token); // Converte o valor lido para int
            token = strtok(NULL, ",");
            i++;
        }

        if (i == MAX_VALUES)
        {
            // Adiciona as coordenadas dos pontos do bloco de colisão
            list[collisionIndex].topLeftX = values[0];
            list[collisionIndex].topLeftY = values[1];
            list[collisionIndex].bottomRightX = values[2];
            list[collisionIndex].bottomRightY = values[3];

            // Vai para o próximo bloco de colisão
            collisionIndex++;

            if (collisionIndex >= MAX_COLLISIONS)
            {
                break; // Interrompe a leitura do banco se já atingiu a quantidade de colisões pré-definidas do mapa
            }
        }
    }

    fclose(file);

    return list;
}

/*
* Função que faz o carregamento de todos os bitmaps de movimento do personagem
* utilizando uma string dinâmica que é construída com base no gênero escolhido
* e no movimento da lista.
*
* returns -> um ponteiro para um ponteiro de ALLEGRO_BITMAP (uma lista de ALLEGRO_BITMAPs)
*/
ALLEGRO_BITMAP ** getCharacterMovementSprites(char *gender)
{
    static ALLEGRO_BITMAP* list[MAX_MOVEMENTS];

    // String do caminho do arquivo
    char path[MAX_LENGTH];

    char *movementNames[] =
    {
        "standby_up", "walking_up_1", "walking_up_2",
        "standby_left", "walking_left_1", "walking_left_2",
        "standby_down", "walking_down_1", "walking_down_2",
        "standby_right", "walking_right_1", "walking_right_2"
    };

    for (int i = 0; i < MAX_MOVEMENTS; i++)
    {
        // Construção da string
        snprintf(path, sizeof(path), "res/sprites/%s/%s_%s.png", gender, gender, movementNames[i]);
        list[i] = al_load_bitmap(path);

        if (!list[i])
        {
            printf("\nERRO: Ocorreu um erro ao carregar a imagem: %s\n", path);
            return 1;
        }
    }

    return list;
}
