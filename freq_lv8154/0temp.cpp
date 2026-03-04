
#if 0

void formatFreq(char *result, uint32_t freq)
{
    if (freq > MAXCOUNT)
    {
        *result = '\0';
        return;
    }

    char temp[NCHARS + 1];
    ltoa(freq, temp, 10);
    char *p = temp;
    uint8_t len = strlen(temp);
    
    for (uint8_t i = 0; i < len; ++i)
    {
        *result++ = *p++;
        
        if ((len - i - 1) % 3 == 0 && i < len-1)
            *result++ = ' ';
    }

    *result++ = 0;
}

#endif

