#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
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
void updateCharacterMovement(Character *character, int frameCounter, ALLEGRO_BITMAP **movementList, bool blockedKey[], unsigned char key[]) {
    if (key[ALLEGRO_KEY_W] && !blockedKey[KEY_W]) {
        character -> posY--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_UP_1] : movementList[WALKING_UP_2];
        character -> lastDirection = KEY_W;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_A] && !blockedKey[KEY_A]) {
        character -> posX--;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_LEFT_1] : movementList[WALKING_LEFT_2];
        character -> lastDirection = KEY_A;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_S] && !blockedKey[KEY_S]) {
        character -> posY++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_DOWN_1] : movementList[WALKING_DOWN_2];
        character -> lastDirection = KEY_S;
        character -> isMoving = true;
    }

    if (key[ALLEGRO_KEY_D] && !blockedKey[KEY_D]) {
        character -> posX++;
        character -> currentMovementBitmap = (frameCounter / ANIMATION_DELAY % 2 == 0) ? movementList[WALKING_RIGHT_1] : movementList[WALKING_RIGHT_2];
        character -> lastDirection = KEY_D;
        character -> isMoving = true;
    }

    if(!character -> isMoving) {
        switch (character -> lastDirection) {
        case KEY_W:
            character -> currentMovementBitmap = movementList[STANDBY_UP];
            break;
        case KEY_A:
            character -> currentMovementBitmap = movementList[STANDBY_LEFT];
            break;
        case KEY_S:
            character -> currentMovementBitmap = movementList[STANDBY_DOWN];
            break;
        case KEY_D:
            character -> currentMovementBitmap = movementList[STANDBY_RIGHT];
            break;
        }
    }

    blockedKey[KEY_W] = false;
    blockedKey[KEY_A] = false;
    blockedKey[KEY_S] = false;
    blockedKey[KEY_D] = false;
    character -> isMoving = false;
}

/*
* Função que carrega todas as colisões do jogo no loop principal. Recebendo a lista de colisões,
* o personagem e o array booleano para controlar o bloqueio do movimento do personagem.
*/
void runCollisionDetection(CollisionBlock collisions[], Character character, bool blockedKey[]) {
    // Colisões externas
    if(character.posX <= 1) blockedKey[KEY_A] = true;

    if(character.posX >= DISPLAY_WIDTH - 1) blockedKey[KEY_D] = true;

    if(character.posY <= 1) blockedKey[KEY_W] = true;

    if(character.posY >= DISPLAY_HEIGHT - 1) blockedKey[KEY_S] = true;

    int i;

    for (i = 0; i < MAX_COLLISIONS; ++i) {
        if (character.posX >= collisions[i].topLeftX && character.posX <= collisions[i].bottomRightX && character.posY >= collisions[i].topLeftY && character.posY <= collisions[i].bottomRightY) {
            if(character.posX >= collisions[i].topLeftX - 1 && character.posX <= collisions[i].topLeftX) blockedKey[KEY_D] = true;

            if(character.posY >= collisions[i].topLeftY - 1 && character.posY <= collisions[i].topLeftY) blockedKey[KEY_S] = true;

            if(character.posX <= collisions[i].bottomRightX + 1 && character.posX >= collisions[i].bottomRightX) blockedKey[KEY_A] = true;

            if(character.posY <= collisions[i].bottomRightY + 1 && character.posY >= collisions[i].bottomRightY) blockedKey[KEY_W] = true;

            // Permite pular os limites de terra (morros)
            if(character.posY >= collisions[18].topLeftY - 1 && character.posY <= collisions[18].topLeftY) blockedKey[KEY_S] = false;
            if(character.posY >= collisions[19].topLeftY - 1 && character.posY <= collisions[19].topLeftY) blockedKey[KEY_S] = false;
            if(character.posY >= collisions[20].topLeftY - 1 && character.posY <= collisions[20].topLeftY) blockedKey[KEY_S] = false;
        }
    }
}

void drawCollision(CollisionBlock collisions[]) {
    int i;

    for(i = 0; i < MAX_COLLISIONS; i++) {
        al_draw_filled_rectangle(collisions[i].topLeftX, collisions[i].topLeftY, collisions[i].bottomRightX, collisions[i].bottomRightY, al_map_rgb(5,5,5));
    }
}

/*
* Função que verifica qual alternativa o jogador escolheu, e, dependendo de qual, um valor é atribuído a uma variável
* que representa a escolha do usuário, após isso, uma verificação entre a resposta do usuário e a resposta correta atrelada ao desafio
* em questão, é feita, retornando um valor booleano dessa comparação.
*
* returns -> um valor booleano que representa se o jogador acertou ou não a questão
*/
bool isAnswerCorrect(int mouseClickPositionX, int mouseClickPositionY, Challenge * challengeList, int index) {

    int playerAnswer;

    if (mouseClickPositionX >= 315 && mouseClickPositionX <= 750 && mouseClickPositionY >= 55 && mouseClickPositionY <= 135){
        playerAnswer = A;
    }

    if (mouseClickPositionX >= 315 && mouseClickPositionX <= 750 && mouseClickPositionY >= 150 && mouseClickPositionY <= 230){
        playerAnswer = B;
    }

    if (mouseClickPositionX >= 315 && mouseClickPositionX <= 750 && mouseClickPositionY >= 240 && mouseClickPositionY <= 320){
        playerAnswer = C;
    }

    if (mouseClickPositionX >= 315 && mouseClickPositionX <= 750 && mouseClickPositionY >= 335 && mouseClickPositionY <= 410){
        playerAnswer = D;
    }

    mouseClickPositionX = 0;
    mouseClickPositionY = 0;

    return playerAnswer == challengeList[index].correctAnswer;
}

/*
* Função de utilidade que seta os valores dos cliques do jogador durante a execução do jogo para 0, dessa forma, repetimos menos código
* ao longo da lógica do loop principal do jogo, reutilizando as mesmas variáveis em certos momentos.
*/
void clearMouseClickPositions(int * mouseClickPositionX, int * mouseClickPositionY) {
    *mouseClickPositionX = 0;
    *mouseClickPositionY = 0;
    printf("\n- [GAME_RUNTIME] -> | mouseClickPositionX limpo.");
    printf("\n- [GAME_RUNTIME] -> | mouseClickPositionY limpo.");
}

/*
* Função temporária que retorna um nome que será exibido como o nome do jogador.
*
* returns - uma string com o nome do jogador.
*/
char * getUserName() {
    return "Ash";
}
