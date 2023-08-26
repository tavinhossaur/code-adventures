#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "../headers/dependencies.h"

#define ANIMATION_DELAY 10

/*
* Função que atualiza a posição do personagem e faz a alteração do bitmap de movimento com base
* na direção em que o personagem está andando, utilizando um "delay" para fazer uma
* animação de movimentação do personagem.
*/
void updateCharacterMovement(Character *character, int frameCounter, ALLEGRO_BITMAP **movementList, bool blockedKey[], unsigned char key[])
{
    if (key[ALLEGRO_KEY_W] && !blockedKey[W])
    {
        character -> posY--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_UP_1] : movementList[WALKING_UP_2];
    }

    if (key[ALLEGRO_KEY_A] && !blockedKey[A])
    {
        character -> posX--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_LEFT_1] : movementList[WALKING_LEFT_2];
    }

    if (key[ALLEGRO_KEY_S] && !blockedKey[S])
    {
        character -> posY++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_DOWN_1] : movementList[WALKING_DOWN_2];
    }

    if (key[ALLEGRO_KEY_D] && !blockedKey[D])
    {
        character -> posX++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_RIGHT_1] : movementList[WALKING_RIGHT_2];
    }

    blockedKey[W] = false;
    blockedKey[A] = false;
    blockedKey[S] = false;
    blockedKey[D] = false;
}

/*
* Função que carrega todas as colisões do jogo no loop principal. Recebendo a lista de colisões,
* o personagem e o array booleano para controlar o bloqueio do movimento do personagem.
*/
void runCollisionDetection(CollisionBlock collisions[], Character character, bool blockedKey[])
{
    for (int i = 0; i < MAX_COLLISIONS; ++i)
    {
        if (character.posX >= collisions[i].topLeftX && character.posX <= collisions[i].bottomRightX && character.posY >= collisions[i].topLeftY && character.posY <= collisions[i].bottomRightY)
        {
            if(character.posX >= collisions[i].topLeftX - 1 && character.posX <= collisions[i].topLeftX) blockedKey[D] = true;

            if(character.posY >= collisions[i].topLeftY - 1 && character.posY <= collisions[i].topLeftY) blockedKey[S] = true;

            if(character.posX <= collisions[i].bottomRightX + 1 && character.posX >= collisions[i].bottomRightX) blockedKey[A] = true;

            if(character.posY <= collisions[i].bottomRightY + 1 && character.posY >= collisions[i].bottomRightY) blockedKey[W] = true;
        }
    }
}

void drawCollision(CollisionBlock collisions[])
{
    int i;

    for(i = 0; i < 52; i++)
    {
        al_draw_filled_rectangle(collisions[i].topLeftX, collisions[i].topLeftY, collisions[i].bottomRightX, collisions[i].bottomRightY, al_map_rgb(5,5,5));
    }
}
