long taskOfPairing(int freq_count, long* freq) {
    long total[freq_count];
    long count_total = 0;
    for (int i = 0; i<freq_count; i++)
    {
        total[i] =freq[i];
        count_total += freq[i];
        if(freq[i] == 0)
        {
            if(count_total %2 == 1)
            {
                if(total[i-1] == 0)
                {
                    for(int j = i-2; j>0;j--)
                    {
                        if(total[j] != 0)
                        {
                            total[j] -= 1;
                            count_total -= 1;
                        }
                    }
                }
                else
                {
                    total[i-1]-=1;
                    count_total -= 1;
                }
            }
        }
    }
    long ans = 0;
    for (int i = 0; i<freq_count; i++)
    {
        ans += total[i];
    }
    return ans/2;
}