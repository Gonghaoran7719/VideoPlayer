#include "packetqueue.h"

//初始化队列
void packet_queue_init(PacketQueue *queue)
{
     queue->first_pkt    = NULL;
     queue->last_pkt     = NULL;
     queue->nb_packets = 0;
     queue->size = 0;
     queue->mutex        = SDL_CreateMutex();
     queue->cond         = SDL_CreateCond();
}

//入队 -- 尾添加
int packet_queue_put(PacketQueue *queue, AVPacket *packet)
{
     AVPacketList   *pkt_list;

     // 包校验
     if (av_dup_packet(packet) < 0)
     {
         return -1;
     }

     pkt_list = (AVPacketList *)av_malloc(sizeof(AVPacketList));
     if (pkt_list == NULL)
     {
          return -1;
     }

     pkt_list->pkt   = *packet;
     pkt_list->next  = NULL;

     //上锁
     SDL_LockMutex(queue->mutex);

     if (queue->last_pkt == NULL)    //空队
     {
          queue->first_pkt = pkt_list;
     }
     else
     {
         queue->last_pkt->next = pkt_list;
     }

     queue->last_pkt = pkt_list;
     queue->nb_packets++;
     queue->size += packet->size;
     SDL_CondSignal(queue->cond);   //添加完发送条件变量的信号--没有信号要阻塞(生产者消费者)

     SDL_UnlockMutex(queue->mutex);

     return 0;
}

/// 出队--头删除
/// queue传入队列指针 pkt 输出类型的参数, 返回结果.
/// block 表示是否阻塞 为1时 队列为空阻塞等待
int packet_queue_get(PacketQueue *queue, AVPacket *pkt, int block)
{
     AVPacketList   *pkt_list = NULL;
     int            ret = 0;

     SDL_LockMutex(queue->mutex);

     while(1)
     {
          pkt_list = queue->first_pkt;
          if (pkt_list != NULL)         //队不空，还有数据
          {
              queue->first_pkt = queue->first_pkt->next;    //pkt_list->next
              if (queue->first_pkt == NULL)
              {
                   queue->last_pkt = NULL;
              }

              queue->nb_packets--;
              queue->size -= pkt_list->pkt.size;
              *pkt = pkt_list->pkt;          // 复制给packet。
              av_free(pkt_list);
              ret = 1;
              break;
          }
          else if (block == 0)
          {
               ret = 0;
               break;
          }
          else
          {
              SDL_CondWait(queue->cond, queue->mutex);
          }
     }

     SDL_UnlockMutex(queue->mutex);
     return ret;
}
void packet_queue_flush(PacketQueue *q)
{
    AVPacketList *pkt, *pkt1;

    SDL_LockMutex(q->mutex);
    for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1)
    {
        pkt1 = pkt->next;
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);
    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
}
