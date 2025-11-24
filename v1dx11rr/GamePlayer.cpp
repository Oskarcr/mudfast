#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
    ma_engine_init(NULL, &engine);
}

void GamePlayer::play(ma_sound* snd, string name, float localVolume)
{
    string path = "Assets/Audio/" + name + ".mp3";
    ifstream inputFile(path.c_str());
    if (!inputFile.good()) throw "No se pudo iniciar la musica.";
    ma_result result = ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_DECODE, 0, 0, snd);
    if (result != MA_SUCCESS) throw "Error al cargar archivo de audio.";
    float finalVolume = localVolume * volume;
    ma_sound_set_volume(snd, finalVolume);
    ma_sound_start(snd);
}

bool GamePlayer::isPlaying(ma_sound* snd)
{
    return ma_sound_is_playing(snd);
}

void GamePlayer::release(ma_sound* snd)
{
    ma_sound_stop(snd);
    ma_sound_uninit(snd);
    delete snd;
}

void GamePlayer::setTheme(string name, float localVolume)
{
    if (themeLoaded) ma_sound_stop(&theme);

    if (!themeLoaded) {
        string path = "Assets/Audio/" + name + ".mp3";
        ma_result result = ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_DECODE, 0, 0, &theme);
        if (result == MA_SUCCESS) themeLoaded = true;
    }
    else {
        play(&theme, name, localVolume);
        return;
    }
    ma_sound_set_volume(&theme, localVolume * volume);
    ma_sound_set_looping(&theme, MA_TRUE);
    ma_sound_start(&theme);
}

void GamePlayer::playSound(string name, float localVolume)
{
    ma_sound* snd = new ma_sound();
    play(snd, name, localVolume);
    sounds.push_back(snd);
}

void GamePlayer::clean()
{
    auto it = remove_if(sounds.begin(), sounds.end(), [this](ma_sound* snd) {
        if (isPlaying(snd)) return false;
        release(snd);
        return true;
    });
    sounds.erase(it, sounds.end());
}

void GamePlayer::stopSounds()
{
    for (auto snd : sounds) release(snd);
    sounds.clear();
}

GamePlayer::~GamePlayer()
{
    if (themeLoaded) ma_sound_uninit(&theme);
    stopSounds();
    ma_engine_uninit(&engine);
}