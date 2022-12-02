#include "update.h"

void update(void);
void update_enemy(void);
void spawn_enemy(void);


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
        app.eSpawn.cooldown = 75;
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

// void move_player(void)
// {
//     app.player.pos += app.player.dPos;
// }
