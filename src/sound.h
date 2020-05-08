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

struct SoundInfo {
    int field_4;
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

struct SoundInfo2 {
    int numPlayed;
    IDirectSoundBuffer *soundBuffer;
    int timePlayed;
    int duration;
    int frequency;
    int numPlayed2;
    int sampleID;
};


void initDirectSound(int a1, int maxAudioBufferSize);

HRESULT createDSound(LPDIRECTSOUND *ppDs, int a2);

int loadSBK(LPCSTR filename);

int createSmpInfo(SmpBinEntry *data, unsigned int dataSize, int smpBankPos);

int randomRange(int min, int max);

int sub_421DA0(int sndBnk, unsigned int snd, int volume);

int sub_422200(int sampleID, int smpBank);

int sub_422300(int sampleID, int iSoundBufferLoc, int iSampleBank);

signed int __cdecl reserveAudioBuffer(unsigned int audioBufferSize);

int sub_4227B0(int sndBnk, int snd);

HRESULT initSoundBuffer(unsigned int soundBufferSize);

#endif //OPENHEXPLORE_SOUND_H
