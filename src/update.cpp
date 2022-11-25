#include "update.h"

void update_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        app.enemy[i].pos.x += 1;
        if(app.enemy[i].pos.x > 900)
            app.enemy[i].alive = false;
    }

}

void spawn_enemy(void)
{
    app.enemy[app.enemyCount].alive = true;
    app.enemy[app.enemyCount].pos = app.eSpawn.pos;
    app.enemyCount += 1;
    printf("Enemy %u spawned at Spawnpoint\n", app.enemyCount);
}
