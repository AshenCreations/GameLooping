#include "update.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ BEGIN DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void update(State *state, f64 t, f64 dt);
void spawn_enemy(void);
void move_enemy(f64 dt);
void clip_enemy(void);
void player_update(State *state, f64 dt);

Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END DECLARATIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void update(State *state, f64 t, f64 dt)
{
    spawn_enemy();
    move_enemy(dt);
    player_update(state, dt);
    clip_enemy();
}

// spawn enemies
void spawn_enemy(void)
{
    if((app.eSpawn.numberSpawned < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
    {
        app.enemy[app.eSpawn.numberSpawned].alive = true;
        app.enemy[app.eSpawn.numberSpawned].pos = app.eSpawn.pos;
        app.enemy[app.eSpawn.numberSpawned].velocity = move_down();

        app.enemy[app.eSpawn.numberSpawned].dest = WAYPOINT_1;
        
        app.eSpawn.numberSpawned += 1;
        app.eSpawn.cooldown = 120;
        app.enemyCount += 1;
    }

    app.eSpawn.cooldown -= 1;
}

// update enemy position
void move_enemy(f64 dt)
{
    // TODO redo moving enemy
    for(int i = 0; i < app.enemyCount; i++)
    {
        app.enemy[i].pos = app.enemy[i].pos + (app.enemy[i].velocity * ENEMY_VELOCITY * dt);
    }
}

// TODO fix this when we have working vector based movement! Casey reflect vectors?? HMH ep44
void clip_enemy(void)
{
    for(int i = 0; i < app.enemyCount; i++)
    {
        if(app.enemy[i].pos.y > (SCREEN_HEIGHT - app.smiley->h / 2))
        {
            app.enemy[i].pos.y = SCREEN_HEIGHT - app.smiley->h / 2.0f;
            app.enemy[i].velocity = move_up();
        }
        if(app.enemy[i].pos.y < (0 + app.smiley->h / 2))
        {
            app.enemy[i].pos.y = 0 + app.smiley->h / 2.0f;
            app.enemy[i].velocity = move_down();
        }
    }
}

Vec2 move_up(void)
{
    return {0, -1};
}

Vec2 move_down(void)
{
    return {0, 1};
}

Vec2 move_left(void)
{
    return {-1, 0};
}

Vec2 move_right(void)
{
    return {1, 0};
}

void player_update(State *state, f64 dt)
{
    state->player.pos = state->player.pos + state->player.vel * (state->player.speed * dt);
}
