// 75-Minute 4-Loop Delay

void Delay75min(void)
{
    volatile unsigned char L1, L2, L3, L4;

    for (L4 = 255; L4 > 0; L4--)
    {
        for (L3 = 255; L3 > 0; L3--)
        {
            for (L2 = 255; L2 > 0; L2--)
            {
                for (L1 = 255; L1 > 0; L1--)
                {
                    // Empty loop to waste time
                    // Volatile prevents the compiler from optimizing this away
                }
            }
        }
    }
}
