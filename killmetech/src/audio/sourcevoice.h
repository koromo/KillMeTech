#ifndef _KILLME_SOURCEVOICE_H_
#define _KILLME_SOURCEVOICE_H_

#include "xaudiosupport.h"
#include "../resource/resource.h"
#include <xaudio2.h>
#include <memory>

namespace killme
{
    class AudioClip;

    extern const int AUDIO_LOOP_INFINITE;

    /** Transmit the audio data to the audio device */
    class SourceVoice
    {
    private:
        struct VoiceCallback : public IXAudio2VoiceCallback
        {
            void CALLBACK OnBufferEnd(void* context);
            void CALLBACK OnBufferStart(void*) {}
            void CALLBACK OnLoopEnd(void*) {}
            void CALLBACK OnStreamEnd() {}
            void CALLBACK OnVoiceError(void* context, HRESULT hr);
            void CALLBACK OnVoiceProcessingPassEnd() {}
            void CALLBACK OnVoiceProcessingPassStart(unsigned) {}
        };

        VoiceUniquePtr<IXAudio2SourceVoice> sourceVoice_;
        Resource<AudioClip> clip_;
        VoiceCallback callBack_;
        bool isPlaying_;

    public:
        /** Constructs with an audio clip */
        SourceVoice(IXAudio2* xAudio, const Resource<AudioClip>& clip);

        /** Destructs */
        ~SourceVoice();

        /** Plays the audio */
        void play(size_t numLoops);

        /** Stops the audio */
        void stop();

        /** Pauses the audio */
        void pause();

        /** Returns true if the audio is playing now */
        bool isPlaying() const;

        /** Applies the frequency ratio */
        void applyFrequencyRatio(float ratio);

        /** Applies the output matrix */
        void applyOutputMatrix(size_t numSrcChannels, size_t numDestChannels, const float* levelMatrix);
    };
}

#endif