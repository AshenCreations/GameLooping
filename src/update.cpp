#include "update.h"

void update(void);
void update_enemy(void);
void spawn_enemy(void);
void move_up(void);
void move_down(void);
void move_left(void);
void move_right(void);


void update(void)
{
    spawn_enemy();
    update_enemy();
}

// spawn enemies
void spawn_enemy(void)
{
    if((app.eSpawn.numberSpawned < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
    {
        app.enemy[app.eSpawn.numberSpawned].alive = true;
        app.enemy[app.eSpawn.numberSpawned].pos = app.eSpawn.pos;
        app.enemy[app.eSpawn.numberSpawned].dPos = MOVE_RIGHT;
        app.enemy[app.eSpawn.numberSpawned].dPos *= ENEMY_SPEED;

        app.eSpawn.numberSpawned += 1;
        app.eSpawn.cooldown = MS_PER_UPDATE * 30;
        app.enemyCount += 1;
    }
    app.eSpawn.cooldown -= 1;
}

// update enemy position
void update_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        if(app.enemy[i].pos.x > 900)
        {
            app.enemy[i].dPos = MOVE_LEFT;
            app.enemy[i].dPos *= ENEMY_SPEED;
        }
        if(app.enemy[i].pos.x < 200)
        {
            app.enemy[i].dPos = MOVE_RIGHT;
            app.enemy[i].dPos *= ENEMY_SPEED;
        }

        app.enemy[i].pos += app.enemy[i].dPos;
    }
}

void move_up(void)
{
    app.player.dPos = {0, -1};
}

void move_down(void)
{
    app.player.dPos = {0, 1};
}

void move_left(void)
{
    app.player.dPos = {-1, 0};
}

void move_right(void)
{
    app.player.dPos = {1, 0};
}
