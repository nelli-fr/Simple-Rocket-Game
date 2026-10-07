#include <CSFML/Audio.h>
#include <CSFML/Graphics.h>

typedef struct Player {
    const sfTexture* texture;
    sfSprite* sprite;
    sfVector2f position;
    sfVector2f velocity;
} Player;

void loadPlayer(sfRenderWindow* window, Player* p) {
    p->texture = sfTexture_createFromFile("assets/player.png", NULL);
    if(!p->texture) {
        sfRenderWindow_destroy(window);
    }
    p->sprite = sfSprite_create(p->texture);

    p->position = (sfVector2f){0, 0};
    p->velocity = (sfVector2f){0, 0};
}

void unloadPlayer(sfRenderWindow* window, Player* p) {
    sfSprite_destroy(p->sprite);
    sfTexture_destroy(p->texture);
}

void playerController(Player* p, sfEvent e) {
    if(sfKeyboard_isKeyPressed(sfKeyA)) p->position.x+=1;
}

void updatePlayer(sfRenderWindow* window, Player* p) {
    p->position.x += p->velocity.x;
    p->position.y += p->velocity.y;
}

void drawPlayer(sfRenderWindow* window, Player* p) {
    sfSprite_setPosition(p->sprite, p->position);
    sfRenderWindow_drawSprite(window, p->sprite, NULL);
}

int main() {
    const sfVideoMode mode = {{600, 400}, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "test", sfResize|sfClose, sfWindowed, NULL);
    if(!window) return EXIT_FAILURE;

    Player player;
    loadPlayer(window, &player);

    sfEvent event;
    while(sfRenderWindow_isOpen(window)) {
        while(sfRenderWindow_pollEvent(window, &event)) {
            if(event.type == sfEvtClosed) sfRenderWindow_close(window);

            playerController(&player, event);
        }

        sfRenderWindow_clear(window, sfBlack);
        drawPlayer(window, &player);

        sfRenderWindow_display(window);
    }
    unloadPlayer(window, &player);
    sfRenderWindow_destroy(window);
    return 0;
}