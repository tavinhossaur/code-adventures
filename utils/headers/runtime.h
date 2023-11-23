void runCollisionDetection(CollisionBlock collisions[], Character character, bool blockedKey[], int challengeIndex, ALLEGRO_BITMAP* snorlax);

void updateSnorlaxRoadblocksCollisions(int challengeIndex, CollisionBlock collisions[], Character character, bool blockedKey[]);

void updateCharacterMovement(Character *character, int frameCounter, ALLEGRO_BITMAP **movementList, bool blockedKey[], unsigned char key[]);

void drawCollision(CollisionBlock collisions[]);

bool isAnswerCorrect(int mouseClickPositionX, int mouseClickPositionY, Challenge * challengeList, int index);

void clearMouseClickPositions(int * mouseClickPositionX, int * mouseClickPositionY);
