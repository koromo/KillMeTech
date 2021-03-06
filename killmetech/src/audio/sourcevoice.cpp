#include "sourcevoice.h"
#include "audioclip.h"
#include "../core/exception.h"
#include <cassert>

namespace killme
{
    const int AUDIO_LOOP_INFINITE = XAUDIO2_LOOP_INFINITE + 1;

    void CALLBACK SourceVoice::VoiceCallback::OnBufferEnd(void* context)
    {
        // Down the audio playing flag
        const auto p = static_cast<SourceVoice*>(context);
        p->isPlaying_ = false;
    }

    void CALLBACK SourceVoice::VoiceCallback::OnVoiceError(void*, HRESULT)
    {
        throw XAudioException("Any error occurred in source buffer.");
    }

    SourceVoice::SourceVoice(const std::weak_ptr<IXAudio2>& xAudio, const Resource<AudioClip>& clip)
        : xAudio_(xAudio)
        , sourceVoice_()
        , clip_(clip)
        , callBack_()
        , isPlaying_(false)
    {
        const auto format = clip_.access()->getFormat();
        IXAudio2SourceVoice* voice;
        enforce<XAudioException>(
            SUCCEEDED(xAudio_.lock()->CreateSourceVoice(&voice, &format, 0, 2, &callBack_)),
            "Failed to create IXAudio2SourceVoice."
            );
        sourceVoice_ = makeVoiceUnique(voice);
    }

    SourceVoice::~SourceVoice()
    {
        if (xAudio_.expired())
        {
            sourceVoice_.release();
        }
    }

    void SourceVoice::submit(size_t numLoops)
    {
        assert(numLoops > 0 && "You need numLoops > 0.");

        if (numLoops > AUDIO_LOOP_INFINITE)
        {
            numLoops = AUDIO_LOOP_INFINITE;
        }

        XAUDIO2_BUFFER buffer;
        ZeroMemory(&buffer, sizeof(buffer));
        buffer.Flags = XAUDIO2_END_OF_STREAM;
        buffer.AudioBytes = static_cast<UINT32>(clip_.access()->getSize());
        buffer.pAudioData = clip_.access()->getData();
        buffer.PlayBegin = 0;
        buffer.PlayLength = 0;
        buffer.LoopBegin = 0;
        buffer.LoopLength = 0;
        buffer.LoopCount = numLoops - 1;
        buffer.pContext = this;

        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->SubmitSourceBuffer(&buffer)),
            "Failed to submit audio buffer."
            );
    }

    size_t SourceVoice::getNumQueued()
    {
        XAUDIO2_VOICE_STATE state;
        sourceVoice_->GetState(&state);
        return state.BuffersQueued;
    }

    void SourceVoice::start()
    {
        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->Start(0)),
            "Failed to start source voice."
            );
        isPlaying_ = true;
    }

    void SourceVoice::stop()
    {
        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->Stop()),
            "Failed to stop source voice."
            );
    }

    void SourceVoice::flush()
    {
        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->FlushSourceBuffers()),
            "Failed to flush source buffer."
            );
    }

    bool SourceVoice::isPlaying() const
    {
        return isPlaying_;
    }

    void SourceVoice::applyFrequencyRatio(float ratio)
    {
        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->SetFrequencyRatio(ratio)),
            "Failed to set the frequency ratio.");
    }

    void SourceVoice::applyOutputMatrix(size_t numSrcChannels, size_t numDestChannels, const float* levelMatrix)
    {
        enforce<XAudioException>(
            SUCCEEDED(sourceVoice_->SetOutputMatrix(nullptr, numSrcChannels, numDestChannels, levelMatrix)),
            "Failed to set the output matrix.");
    }
}