#ifndef AVGBUFF_H
#define AVGBUFF_H

typedef struct _avgbuff
{
    uint16_t buff[BUFFSIZE];
    int index;
    uint16_t sum;

} avgbuff;

void avgFill(avgbuff *avg, uint16_t value)
{
    for (int i = 0; i < BUFFSIZE; ++i)
    {
        avg->buff[i] = value;
        avg->index = 0;
        avg->sum = value * BUFFSIZE;
    }
}

void avgAdd(avgbuff *avg, uint16_t value)
{
    avg->sum = avg->sum - avg->buff[avg->index];
    avg->buff[avg->index] = value;
    avg->sum = avg->sum + avg->buff[avg->index];
    avg->index = (avg->index+1) % BUFFSIZE;
}

uint16_t avgGet(avgbuff *avg)
{
    return (uint16_t) avg->sum / BUFFSIZE;
}

#endif AVGBUFF_H

