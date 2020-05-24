//
// Created by Smaug on 2020-05-01.
//

#ifndef OPENHEXPLORE_SOUND_H
#define OPENHEXPLORE_SOUND_H

#include <windows.h>
#include <dsound.h>

struct SBKInfo {
    char filename[200];
    int fileDesc;
    int *pSampleOffsets;
    int numSamples;
    int containsSamples;
};

struct SmpBinEntry {
    int minRandFrequency;
    int maxRandFrequency;
    int sampleID;
    unsigned char volume;
    char volumeMod;
    unsigned char panMode;
    char reserved;
};

struct SmpInfo {
    SmpBinEntry *pData;
    unsigned int numSounds;
    int unk;
    int smpBank;
};

struct SoundInstance {
    int soundTemplateID;
    int numPlayed;
    IDirectSoundBuffer *soundBuffer;
    int timePlayed;
    int timeEnd;
    int panMode;
    int soundID;
    char volumeMod;
    bool field_1D;
    char volume;
    char volumeLevelIdx;
};

struct SoundTemplate {
    int numPlayed;
    IDirectSoundBuffer *soundBuffer;
    int timePlayed;
    int duration;
    int frequency;
    int numActive;
    int sampleID;
};

void sub_4214F0(int numElements);

void sub_421580(int pos, int a2, int a3, int a4, int a5, int a6);

void initDirectSound(int a1, int maxAudioBufferSize);

HRESULT createDSound(LPDIRECTSOUND *ppDs, int a2);

int loadSBK(LPCSTR filename);

int createSmpInfo(SmpBinEntry *data, unsigned int dataSize, int smpBankPos);

int randomRange(int min, int max);

int playSound(int sndBnk, unsigned int snd, int volume);

void releaseAllSoundBuffers();

int getNextFreeSoundInstance();

int loadSample(int sampleID, int smpBank);

int getNextFreeSoundTemplate();

int loadSampleFromDisk(int sampleID, int soundTemplateID, int iSampleBank);

signed int __cdecl reserveAudioBuffer(unsigned int audioBufferSize);

int playSoundAtFullVolume(int sndBnk, int snd);

HRESULT initSoundBuffer(unsigned int soundBufferSize);

#endif //OPENHEXPLORE_SOUND_H
