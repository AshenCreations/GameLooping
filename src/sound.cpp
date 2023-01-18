#include "sound.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ declarations BEGIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Mix_Music* load_music(const char* file);
Mix_Chunk* load_sound(const char* file);
void play_music(Mix_Music *music);
void play_sound(Mix_Chunk *sound, bool flag);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ declarations END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Mix_Music* load_music(const char* file)
{
    Mix_Music *music = Mix_LoadMUS(file);
    if(music == NULL)
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    return music;
}

Mix_Chunk* load_sound(const char* file)
{
    Mix_Chunk *chunk = Mix_LoadWAV(file);
    if(chunk == NULL)
        printf("Failed to load chunk! SDL_mixer Error: %s\n", Mix_GetError());
    return chunk;
}

void play_music(Mix_Music *music)
{
    Mix_PlayMusic(music, 0);
}

void play_sound(Mix_Chunk *sound, bool flag)
{
    if(flag)
    {
        if(Mix_Playing(-1))
        {
            // Mix_FadeOutChannel(-1, 125);
            // Mix_HaltChannel(-1);
        }
    }

    Mix_PlayChannel(-1, sound, 0);
}
