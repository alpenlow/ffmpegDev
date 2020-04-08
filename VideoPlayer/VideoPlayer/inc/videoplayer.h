#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/pixfmt.h"
#include "libswresample/swresample.h"


#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_types.h>
#include <SDL_name.h>
#include <SDL_main.h>
#include <SDL_config.h>
}

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
}PacketQueue;

#define VIDEO_PICTURE_QUEUE_SIZE 1
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

#define MAX_AUDIO_SIZE (25 * 16 * 1024)
#define MAX_VIDEO_SIZE (25 * 256 * 1024)

class VideoPlayer;

typedef struct VideoState {
    AVFormatContext *ic;
    int videoStream, audioStream;
    AVFrame *audio_frame;
    PacketQueue audioq;
    AVStream *audio_st;
    unsigned int audio_buf_size;
    unsigned int audio_buf_index;
    AVPacket audio_pkt;
    uint8_t *audio_pkt_data;
    int audio_pkt_size;
    uint8_t *audio_buf;
    DECLARE_ALIGNED(16,uint8_t,audio_buf2) [AVCODEC_MAX_AUDIO_FRAME_SIZE*4];
    enum AVSampleFormat audio_src_fmt;
    enum AVSampleFormat audio_tgt_fmt;
    int audio_src_channels;
    int audio_tgt_channels;
    int64_t audio_src_channel_layout;
    int64_t audio_tgt_channel_layout;
    int audio_src_freq;
    int audio_tgt_freq;
    struct SwrContext *swr_ctx;
    int audio_hw_buf_size;

    double audio_clock;
    double video_clock;

    AVStream *video_st;
    PacketQueue videoq;

    int         seek_req;
    int64_t     seek_pos;
    int         seek_flag_audio;
    int         seek_flag_video;
    int         seek_time;

    bool isPause;
    bool quit;
    bool readFinished;
    bool readThreadFinished;
    bool videoThreadFinished;

    SDL_Thread *video_tid;
    SDL_AudioDeviceID audioID;

    VideoPlayer *player;
}VideoState;


class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    enum PlayerState {
        Playing, Pause, Stop
    };

    explicit VideoPlayer();
    ~VideoPlayer();

    bool setFileName(QString path);
    bool play();
    bool pause();
    bool stop(bool isWait = false);
    void seek(int64_t pos);
    int64_t getTotalTime();
    double getCurrentTime();
    void disPlayVideo(QImage img);

protected:
    void run();

private:
    QString mFileName;
    VideoState mVideoState;
    PlayerState mPlayerState;

signals:
    void sig_GetOneFrame(QImage);
    void sig_StateChanged(VideoPlayer::PlayerState state);
    void sig_TotalTimeChanged(qint64 uSec);

};

#endif // VIDEOPLAYER_H
