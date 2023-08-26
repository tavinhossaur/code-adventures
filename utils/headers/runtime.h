void runCollisionDetection(CollisionBlocks collisions[], Character character, bool blockedKey[]);

void updateCharacterMovement(Character character, int frameCounter, ALLEGRO_BITMAP **movementList, bool blockedKey[], unsigned char key[]);

void drawCollision(CollisionBlocks collisions[]);
