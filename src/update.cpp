#include "update.h"

void update(void);
void update_enemy(void);
void spawn_enemy(void);


void update(void)
{
    spawn_enemy();
    update_enemy();
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
    if((app.enemyCount < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
    {
        app.enemy[app.enemyCount].alive = true;
        app.enemy[app.enemyCount].pos = app.eSpawn.pos;
        app.enemyCount += 1;
        printf("Enemy %u spawned.\n", app.enemyCount);
        app.eSpawn.cooldown = 75;
    }
    app.eSpawn.cooldown -= 1;
}
