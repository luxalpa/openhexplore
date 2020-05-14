//
// Created by Smaug on 2020-05-01.
//

#include <cstdio>
#include "sound.h"
#include "dsound.h"
#include "globals.h"
#include "global_fns.h"
#include "files.h"

// @ 421860
void initDirectSound(int a1, int maxAudioBufferSize) {
    if (gDirectSound != nullptr)
        return;

    if (maxAudioBufferSize)
        gMaxAudioBufferSize = maxAudioBufferSize;

    gAudioBufferPos = 0;

    for (int i = 0; i < NUM_SOUNDBANKS; i++) {
        gSBKInfos[i].fileDesc = -1;
    }

    for (int i = 0; i < NUM_SOUNDTEMPLATES; i++) {
        SoundTemplate &info = gSoundTemplateCache[i];
        info.soundBuffer = nullptr;
        info.numActive = 0;
        info.sampleID = -1;
    }

    for (int i = 0; i < NUM_SOUNDINSTANCES; i++) {
        gSoundInstanceCache[i].soundBuffer = nullptr;
        gSoundInstanceCache[i].soundID = -1;
    }

    for (int i = 0; i < 8; i++) {
        gVolumes[i] = 100;
    }

    if (createDSound(&gDirectSound, a1) != DS_OK)
        return;

    gDirectSound->SetCooperativeLevel(gHWnd, DSSCL_EXCLUSIVE);

    DSBUFFERDESC dsbufferdesc = {
            .dwSize = sizeof(DSBUFFERDESC),
            .dwFlags = DSBCAPS_PRIMARYBUFFER,
            .dwBufferBytes = 0,
            .dwReserved = 0,
            .lpwfxFormat = nullptr,
    };

    if (!gDirectSound->CreateSoundBuffer(&dsbufferdesc, &gDirectSoundBuffer, 0)) {
        WAVEFORMATEX waveformat = {
                .wFormatTag = WAVE_FORMAT_PCM,
                .nChannels = 2,
                .nSamplesPerSec = 11025,
                .nAvgBytesPerSec = 44100,
                .nBlockAlign = 4,
                .wBitsPerSample = 16,
                .cbSize = 0,
        };

        if (gDirectSoundBuffer->SetFormat(&waveformat)) {
            gDirectSound->Release();
            gDirectSound = nullptr;
        }
    }
}

// @ 4219D0
HRESULT createDSound(LPDIRECTSOUND *ppDs, int a2) {
    if (!a2)
        return DirectSoundCreate(nullptr, ppDs, nullptr);

    DirectSoundEnumerateA((LPDSENUMCALLBACKA) sub_421A30, &a2);
    *ppDs = nullptr;
    return DSERR_INVALIDPARAM;
}

// @ 421B30
int loadSBK(const char *filename) {
    char drive[4];
    char dir[256];

    int pos = 0;

    for (; pos < 2; pos++) {
        if (gSBKInfos[pos].fileDesc == -1)
            break;
    }

    if (pos == 2)
        return -1;

    _splitpath(filename, drive, dir, nullptr, nullptr);

    lstrcpyA(gSampleDir, drive);
    lstrcatA(gSampleDir, dir);

    int fd = Files::open(filename, Files::OpenMode::ReadOnly);

    if (fd == -1) return -1;

    SBKInfo &info = gSBKInfos[pos];

    info.fileDesc = fd;
    lstrcpyA(info.filename, filename);

    Files::read(fd, &info.containsSamples, 4);
    Files::read(fd, &info.numSamples, 4);

    int *data = (int *) allocFile(4 * info.numSamples, 0x8002);
    info.pSampleOffsets = data;

    if (data != nullptr) {
        Files::read(fd, data, 4 * info.numSamples);
        if (info.containsSamples == 0)
            Files::close(fd);
        return pos;
    } else {
        Files::close(fd);
        return -1;
    }
}

// @ 421CD0
int createSmpInfo(SmpBinEntry *data, unsigned int dataSize, int smpBankPos) {
    if (!data || !dataSize || smpBankPos == -1)
        return -1;

    int i;
    for (i = 0; i < 25; i++) {
        if (gSmpInfos[i].pData == nullptr) {
            break;
        }
    }
    if (i == 25) {
        return -1;
    }

    gSmpInfos[i] = SmpInfo{
            .pData = data,
            .numSounds = dataSize / 16,
            .smpBank = smpBankPos
    };

    return i;
}

// @ 421D70
int randomRange(int min, int max) {
    if (max == min)
        return min;
    else
        return min + rand() % (max - min + 1);
}

// @ 421DA0
int playSound(int sndBnk, unsigned int snd, int volume) {
    static int nextSoundID = 0;

    bool bSomeFlag = false;
    if ((snd & 0x80000000) != 0) {
        bSomeFlag = true;
        snd &= 0x7FFFFFFFu;
    }

    if (!gDirectSound || sndBnk == -1)
        return -1;

    if (gSmpInfos[sndBnk].numSounds <= snd)
        return -1;

    const int soundInstance = getNextFreeSoundInstance();
    if (soundInstance == -1)
        return -1;

    SoundInstance &curSndInfo = gSoundInstanceCache[soundInstance];

    SmpBinEntry *sndEntry = &gSmpInfos[sndBnk].pData[snd];
    const int soundTemplateID = loadSample(sndEntry->sampleID, gSmpInfos[sndBnk].smpBank);
    if (soundTemplateID == -1)
        return -1;

    SoundTemplate &curSndInfo2 = gSoundTemplateCache[soundTemplateID];

    int result = gDirectSound->DuplicateSoundBuffer(
            curSndInfo2.soundBuffer,
            &curSndInfo.soundBuffer);
    if (result != DS_OK) {
        // TODO: This error is not actually being displayed.
        char v24[0xFC];
        sprintf(v24, "Unable to duplicate buffer\ncode=%d %x %x", result, (unsigned int) gDirectSound,
                (unsigned int) curSndInfo2.soundBuffer);
        return -1;
    }

    if (volume < 0)
        volume = 0;
    if (volume > 100)
        volume = 100;

    unsigned char volumeIdx = volume * sndEntry->volume * gVolumes[sndEntry->volumeMod & 0x7F] / 10000;
    curSndInfo.volumeLevelIdx = volumeIdx;
    curSndInfo.soundBuffer->SetVolume(dword_4D5E28[100 - volumeIdx]);

    if (sndEntry->panMode) {
        int panRelative = 0;

        switch (sndEntry->panMode) {
            case 1u:
            case 5u:
                panRelative = -100;
                break;
            case 2u:
            case 6u:
                panRelative = 100;
                break;
            case 3u:
                panRelative = 100 * randomRange(-1, 1);
                break;
            case 4u:
                panRelative = randomRange(-100, 100);
                break;
            default:
                panRelative = 0;
                break;
        }

        int pan = panRelative <= 0 ? -dword_4D5E28[-panRelative] : dword_4D5E28[panRelative];
        curSndInfo.soundBuffer->SetPan(pan);
    }

    unsigned int frequency;

    if (sndEntry->minRandFrequency > 0 || sndEntry->maxRandFrequency > 0) {
        frequency = randomRange(sndEntry->minRandFrequency, sndEntry->maxRandFrequency);
        curSndInfo.soundBuffer->SetFrequency(frequency);
    } else {
        frequency = curSndInfo2.frequency;
    }

    if (curSndInfo.soundBuffer->Play(0, 0, (sndEntry->volumeMod & 0x80) ? DSBPLAY_LOOPING : 0) != DS_OK)
        return -1;

    curSndInfo2.timePlayed = GetTickCount();
    curSndInfo2.numPlayed++;
    curSndInfo2.numActive++;

    curSndInfo.numPlayed = curSndInfo2.numPlayed;
    curSndInfo.soundTemplateID = soundTemplateID;
    curSndInfo.timePlayed = GetTickCount();
    curSndInfo.timeEnd = curSndInfo.timePlayed + 1000 * curSndInfo2.duration / frequency;
    curSndInfo.panMode = sndEntry->panMode;
    curSndInfo.volume = sndEntry->volume;
    curSndInfo.soundID = nextSoundID;
    curSndInfo.volumeMod = sndEntry->volumeMod;
    curSndInfo.field_1D = bSomeFlag;
    nextSoundID++;

    if (nextSoundID == -1)
        nextSoundID = 0;

    return curSndInfo.soundID;
}

// @ 422190
void releaseAllSoundBuffers() {
    unsigned long status;

    for (int i = 0; i < NUM_SOUNDINSTANCES; i++) {
        SoundInstance &instance = gSoundInstanceCache[i];
        if (instance.soundBuffer != nullptr
            && instance.soundBuffer->GetStatus(&status) == DS_OK
            && status & DSBSTATUS_PLAYING
            && instance.soundBuffer->Release() == DS_OK) {
            instance.soundBuffer = nullptr;
            instance.soundID = -1;
            gSoundTemplateCache[instance.soundTemplateID].numActive--;
        }
    }
}

// @ 4220D0
int getNextFreeSoundInstance() {
    releaseAllSoundBuffers();

    int instanceID = -1;

    for (int i = 0; i < NUM_SOUNDINSTANCES; i++) {
        if (gSoundInstanceCache[i].soundBuffer == nullptr) {
            instanceID = i;
        }
    }

    if (instanceID == -1) {
        int maxNumPlayed = -1;

        // get the sound Instance with the highest numPlayed
        for (int i = 0; i < NUM_SOUNDINSTANCES; i++) {
            SoundInstance &instance = gSoundInstanceCache[i];
            int numPlayed = instance.volumeMod & 0x80 ? 0 : instance.numPlayed;
            if (numPlayed > maxNumPlayed) {
                maxNumPlayed = instance.numPlayed;
                instanceID = i;
            }
        }

        SoundInstance &instance = gSoundInstanceCache[instanceID];

        if (instance.soundBuffer->Stop() == DS_OK && instance.soundBuffer->Release() == DS_OK) {
            instance.soundBuffer = nullptr;
            instance.soundID = -1;
            gSoundTemplateCache[instance.soundTemplateID].numActive--;
        } else {
            return -1;
        }
    }
    return instanceID;
}

// Returns index for sound template ID
// @ 422200
int loadSample(int sampleID, int smpBank) {
    int emptySoundBufferLocation = -1;

    for (int i = 0; i < NUM_SOUNDTEMPLATES; i++) {
        SoundTemplate &soundTemplate = gSoundTemplateCache[i];
        if (soundTemplate.sampleID == sampleID) {
            return i;
        }
        if (soundTemplate.soundBuffer == nullptr) {
            emptySoundBufferLocation = i;
        }
    }

    if (emptySoundBufferLocation != -1) {
        return loadSampleFromDisk(sampleID, emptySoundBufferLocation, smpBank);
    }

    return loadSampleFromDisk(sampleID, getNextFreeSoundTemplate(), smpBank);
}

// Get next free soundTemplate position in the cache. If there is no more space in the cache, it will release the sound with the lowest duration.
// @ 422260
int getNextFreeSoundTemplate() {
    unsigned int minDuration = MAXDWORD32;
    int idx = 0;

    // Find the sound with the shortest duration and release it.
    for (int i = 0; i < NUM_SOUNDTEMPLATES; i++) {
        SoundTemplate *curSoundTemplate = &gSoundTemplateCache[i];
        if (curSoundTemplate->soundBuffer == nullptr) {
            return i;
        }

        if (curSoundTemplate->numActive == 0 && curSoundTemplate->duration < minDuration) {
            minDuration = curSoundTemplate->duration;
            idx = i;
        }
    }

    SoundTemplate *soundTemplate = &gSoundTemplateCache[idx];

    if (minDuration == MAXDWORD32)
        return -1;

    if (soundTemplate->soundBuffer->Release() != DS_OK)
        return -1;

    soundTemplate->soundBuffer = 0;
    soundTemplate->sampleID = -1;
    gAudioBufferPos -= soundTemplate->duration;
    return idx;
}

// @ 422300
int loadSampleFromDisk(int sampleID, int soundTemplateID, int iSampleBank) {
    if (soundTemplateID == -1)
        return -1;

    SBKInfo &sbkInfo = gSBKInfos[iSampleBank];

    int fd = sbkInfo.fileDesc;
    if (fd == -1 || sbkInfo.numSamples <= sampleID)
        return -1;

    if (!sbkInfo.containsSamples) {
        fd = Files::open(sbkInfo.filename, Files::OpenMode::ReadOnly);
        if (fd == -1)
            return -1;
    }

    Files::seek(fd, sbkInfo.pSampleOffsets[sampleID], 0);

    unsigned int audioBufferSize = 0;

    WAVEFORMATEX waveformatex;
    int fdSampleFile;

    if (sbkInfo.containsSamples) {
        Files::read(fd, &waveformatex, sizeof(WAVEFORMATEX));
        Files::read(fd, &audioBufferSize, sizeof(int));
        fdSampleFile = -1;
    } else {
        char filepath[200];
        char filename[200];

        Files::read(fd, filename, sizeof(filename));

        lstrcpyA(filepath, gSampleDir);
        lstrcatA(filepath, filename);

        fdSampleFile = Files::open(filepath, Files::OpenMode::ReadOnly);
        if (fdSampleFile == -1)
            return -1;

        waveformatex = {
                .wFormatTag = 0,
                .nChannels = 0,
                .nSamplesPerSec = 0,
                .nAvgBytesPerSec = 0,
                .nBlockAlign = 0,
                .wBitsPerSample = 0,
                .cbSize = 0,
        };

        int format;
        Files::read(fdSampleFile, &format, 4u);

        if (format == 'FFIR') {
            unsigned int buffer;
            Files::read(fdSampleFile, &buffer, 4u);

            unsigned int audioFormat;
            Files::read(fdSampleFile, &audioFormat, 4u);

            if (audioFormat == 'EVAW') {
                int cancelLoop = 0;
                while (!cancelLoop) {
                    unsigned int section;
                    unsigned int waveFormatExSize;

                    Files::read(fdSampleFile, &section, 4u);
                    Files::read(fdSampleFile, &waveFormatExSize, 4u);

                    if (section == ' tmf') {
                        if (waveFormatExSize > sizeof(WAVEFORMATEX))
                            cancelLoop = 2;

                        Files::read(fdSampleFile, &waveformatex, waveFormatExSize);
                        waveformatex.cbSize = 0;
                    } else if (section == 'atad') {
                        cancelLoop = 1;
                    } else {
                        Files::seek(fdSampleFile, waveFormatExSize, 1);
                    }
                }
            }
        }
        Files::close(fd);
    }

    if (!audioBufferSize) return -1;

    int soundBufferIdx = -1;

    if (reserveAudioBuffer(audioBufferSize)) {
        DSBUFFERDESC dsbufferdesc = {
                .dwSize = sizeof(DSBUFFERDESC),
                .dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_LOCSOFTWARE |
                           DSBCAPS_STATIC,
                .dwBufferBytes = audioBufferSize,
                .dwReserved = 0,
                .lpwfxFormat = &waveformatex,
        };

        IDirectSoundBuffer *pSoundBuffer = nullptr;

        if (!gDirectSound->CreateSoundBuffer(&dsbufferdesc, &pSoundBuffer, nullptr)) {
            void *pvAudioPtr1;
            unsigned long ptr1Size;

            void *pvAudioPtr2;
            unsigned long ptr2Size;

            if (pSoundBuffer->Lock(0, audioBufferSize, &pvAudioPtr1, &ptr1Size, &pvAudioPtr2, &ptr2Size, 0) ==
                DS_OK) {
                if (ptr1Size == audioBufferSize) {
                    if (sbkInfo.containsSamples)
                        Files::read(fd, pvAudioPtr1, audioBufferSize);
                    else
                        Files::read(fdSampleFile, pvAudioPtr1, audioBufferSize);
                }

                if (pSoundBuffer->Unlock(pvAudioPtr1, audioBufferSize, pvAudioPtr2, 0) == DS_OK) {
                    gSoundTemplateCache[soundTemplateID] = {
                            .numPlayed = 0,
                            .soundBuffer = pSoundBuffer,
                            .duration = static_cast<int>(audioBufferSize),
                            .frequency = static_cast<int>(waveformatex.nSamplesPerSec),
                            .sampleID = sampleID,
                    };
                    soundBufferIdx = soundTemplateID;
                }
            }
            gAudioBufferPos += audioBufferSize;
        }
    }

    if (!sbkInfo.containsSamples)
        Files::close(fdSampleFile);
    return soundBufferIdx;
}

// Releases stuff from the audio buffer until there's enough space again
// @ 4226D0
int reserveAudioBuffer(unsigned int audioBufferSize) {
    if (gMaxAudioBufferSize - gAudioBufferPos >= audioBufferSize)
        return true;

    while (1) {
        unsigned int timePlayed = -1;
        int i;

        SoundTemplate *info = nullptr;

        for (i = 0; i < 73; i++) {
            SoundTemplate &soundInfo2 = gSoundTemplateCache[i];
            if (soundInfo2.soundBuffer != nullptr && soundInfo2.numActive && soundInfo2.timePlayed < timePlayed) {
                info = &soundInfo2;
                timePlayed = soundInfo2.timePlayed;
            }
        }

        if (timePlayed == -1)
            break;

        if (info->soundBuffer->Release()) {
            return false;
        }

        info->soundBuffer = nullptr;
        info->sampleID = -1;

        gAudioBufferPos -= info->duration;
        if (gMaxAudioBufferSize - gAudioBufferPos >= audioBufferSize)
            return true;
    }
    return false;
}

// @ 4227B0
int playSoundAtFullVolume(int sndBnk, int snd) {
    return playSound(sndBnk, snd, 100);
}

// @ 422C00
HRESULT initSoundBuffer(unsigned int soundBufferSize) {
    if (!gDirectSound || gDirectSoundBuffer2 != nullptr)
        return -1;

    gSoundBufferSize = soundBufferSize;

    WAVEFORMATEX waveformat{
            .wFormatTag = WAVE_FORMAT_PCM,
            .nChannels = 1,
            .nSamplesPerSec = 11025,
            .nAvgBytesPerSec = 22050,
            .nBlockAlign = 2,
            .wBitsPerSample = 16,
            .cbSize = sizeof(WAVEFORMATEX),
    };

    DSBUFFERDESC dsbufferdesc{
            .dwSize = sizeof(DSBUFFERDESC),
            .dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_LOCSOFTWARE |
                       DSBCAPS_STATIC,
            .dwBufferBytes = soundBufferSize,
            .dwReserved = 0,
            .lpwfxFormat = &waveformat,
    };

    return gDirectSound->CreateSoundBuffer(&dsbufferdesc, &gDirectSoundBuffer2, 0);
}