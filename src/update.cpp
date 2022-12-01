#include "update.h"

void update(void);
void update_enemy(void);
void spawn_enemy(void);


void update(void)
{
    spawn_enemy();
    update_enemy();
}

// update player position
void move_player(void)
{
    app.player.pos += app.player.dPos;
}

// update enemy position
void update_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        // move enemy on x-axis
        app.enemy[i].pos.x += ENEMY_SPEED;
        
        // TODO enemy should die somehow

    }
}

// spawn enemies
void spawn_enemy(void)
{
    if((app.eSpawn.numberSpawned < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
    {
        app.enemy[app.eSpawn.numberSpawned].alive = true;
        app.enemy[app.eSpawn.numberSpawned].pos = app.eSpawn.pos;

        app.eSpawn.numberSpawned += 1;
        app.eSpawn.cooldown = 75;
        app.enemyCount += 1;
    }
    app.eSpawn.cooldown -= 1;
}
