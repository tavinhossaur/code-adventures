#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "../headers/dependencies.h"

#define ANIMATION_DELAY 10

/*
* Função que atualiza a posição do personagem e faz a alteração do bitmap de movimento com base
* na direção em que o personagem está ou estava andando, verificando também se essa tecla
* não esta bloqueada devido a uma colisão.
*
* O uso do ANIMATION_DELAY é para fazer uma troca mais devagar das sprites de movimento do personagem.
*
* obs: precisam ser todos "if" ao invés de "else if" para que a movimentação diagonal seja possível.
*/
void updateCharacterMovement(Character *character, int frameCounter, ALLEGRO_BITMAP **movementList, bool blockedKey[], unsigned char key[])
{
    if (key[ALLEGRO_KEY_W] && !blockedKey[W])
    {
        character -> posY--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_UP_1] : movementList[WALKING_UP_2];
        character -> lastDirection = W;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_A] && !blockedKey[A])
    {
        character -> posX--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_LEFT_1] : movementList[WALKING_LEFT_2];
        character -> lastDirection = A;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_S] && !blockedKey[S])
    {
        character -> posY++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_DOWN_1] : movementList[WALKING_DOWN_2];
        character -> lastDirection = S;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_D] && !blockedKey[D])
    {
        character -> posX++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_RIGHT_1] : movementList[WALKING_RIGHT_2];
        character -> lastDirection = D;
        character -> isMoving = true;
    }

    if(!character -> isMoving)
    {
        switch (character -> lastDirection)
        {
        case W:
            character -> currentMovementBitmap = movementList[STANDBY_UP];
            break;
        case A:
            character -> currentMovementBitmap = movementList[STANDBY_LEFT];
            break;
        case S:
            character -> currentMovementBitmap = movementList[STANDBY_DOWN];
            break;
        case D:
            character -> currentMovementBitmap = movementList[STANDBY_RIGHT];
            break;
        }
    }

    blockedKey[W] = false;
    blockedKey[A] = false;
    blockedKey[S] = false;
    blockedKey[D] = false;
    character -> isMoving = false;
}

/*
* Função que carrega todas as colisões do jogo no loop principal. Recebendo a lista de colisões,
* o personagem e o array booleano para controlar o bloqueio do movimento do personagem.
*/
void runCollisionDetection(CollisionBlock collisions[], Character character, bool blockedKey[])
{
    // Colisões externas
    if(character.posX <= 1) blockedKey[A] = true;

    if(character.posX >= DISPLAY_WIDTH - 1) blockedKey[D] = true;

    if(character.posY <= 1) blockedKey[W] = true;

    if(character.posY >= DISPLAY_HEIGHT - 1) blockedKey[S] = true;

    int i;

    for (i = 0; i < MAX_COLLISIONS; ++i)
    {
        if (character.posX >= collisions[i].topLeftX && character.posX <= collisions[i].bottomRightX && character.posY >= collisions[i].topLeftY && character.posY <= collisions[i].bottomRightY)
        {
            if(character.posX >= collisions[i].topLeftX - 1 && character.posX <= collisions[i].topLeftX) blockedKey[D] = true;

            if(character.posY >= collisions[i].topLeftY - 1 && character.posY <= collisions[i].topLeftY) blockedKey[S] = true;

            if(character.posX <= collisions[i].bottomRightX + 1 && character.posX >= collisions[i].bottomRightX) blockedKey[A] = true;

            if(character.posY <= collisions[i].bottomRightY + 1 && character.posY >= collisions[i].bottomRightY) blockedKey[W] = true;

            // Permite pular os limites de terra (morros)
            if(character.posY >= collisions[18].topLeftY - 1 && character.posY <= collisions[18].topLeftY) blockedKey[S] = false;
            if(character.posY >= collisions[19].topLeftY - 1 && character.posY <= collisions[19].topLeftY) blockedKey[S] = false;
            if(character.posY >= collisions[20].topLeftY - 1 && character.posY <= collisions[20].topLeftY) blockedKey[S] = false;
        }
    }
}

void drawCollision(CollisionBlock collisions[])
{
    int i;

    for(i = 0; i < MAX_COLLISIONS; i++)
    {
        al_draw_filled_rectangle(collisions[i].topLeftX, collisions[i].topLeftY, collisions[i].bottomRightX, collisions[i].bottomRightY, al_map_rgb(5,5,5));
    }
}

void createDialogBar(){

    ALLEGRO_BITMAP* dialogBar = al_load_bitmap("res/sprites/interface/dialog_bar.png");
}
