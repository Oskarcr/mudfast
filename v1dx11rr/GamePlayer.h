#pragma once

#include "Packages/miniaudio/miniaudio.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class GamePlayer {
private:
    ma_engine engine = {};
    ma_sound theme = {};
    bool themeLoaded = false;

    vector<ma_sound*> sounds;

    void play(ma_sound* snd, string name, float localVolume);

    bool isPlaying(ma_sound* snd);

    void release(ma_sound* snd);

public:
    // El volumen del reproductor.
    float volume = 1.0f;

    GamePlayer();

    // Establece un tema ambiental.
    // El name debe ser el nombre del archivo .mp3 que este en la carpeta "Assets/Audio"
    void setTheme(string name, float localVolume = 1.0f);

    // Reproduce un sonido.
    // El name debe ser el nombre del archivo .mp3 que este en la carpeta "Assets/Audio"
    void playSound(string name, float localVolume = 1.0f);

    // Limpia los sonidos que han terminado.
    void clean();

    // Pausa todos los sonidos, menos el tema.
    void stopSounds();

    ~GamePlayer();
};