//
//  BloomFilter.cpp
//  Bloom_Filter
//
//  Created by Pranjali Ingole on 30/10/18.
//  Copyright © 2018 Pranjali Ingole. All rights reserved.
//

#include <stdio.h>
#include <bitset>
#include <string>
#include <cmath>
#include <ctype.h>

/*  Add code to calculte it from acceptable false positive probability (P) and fixed length of short_url (LEN). Value of M and K is hardcoded temporarily for P = 1% and LEN = 3 */
#define M 1559100
#define K 4

using namespace std;

bitset<M> BloomFilter;

void Initialize()
{
    BloomFilter.reset();
}

/* murmurHash3 can be used instead of this function, Library available in Python and not available in C or C++. Already implemented hash function is available though.*/
uint64_t Str_Hash(string short_url, int url_length)
{
    uint64_t HashVal = 0;
    int Prime_No = 31;
    for(int i=0; i<url_length; i++)
    {
        int ascii_val = 0;
        if(isupper(short_url[i]))
        {
            ascii_val = short_url[i] - 'A';
        }
        else if(islower(short_url[i]))
        {
            ascii_val = short_url[i] - 'a';
        }
        else
        {
            ascii_val = short_url[i] - '0';
        }
        HashVal += ascii_val*(pow(Prime_No,i));
    }
    HashVal %= M;
    
    return HashVal;
}

uint64_t K_hash(int i, uint64_t HashVal)
{
    uint64_t Hash1, Hash2;
    Hash2 = HashVal * 0xFFFF;
    Hash1 = (HashVal >> 32) * 0xFFFF;
    
    return (Hash1 + (i * Hash2));
}

void Add(string short_url, int url_length)
{
    for(int i=0; i<K; i++)
    {
        uint64_t HashVal = Str_Hash(short_url, url_length);
        uint64_t index = K_hash(i, HashVal);
        BloomFilter.set(index);
    }
}

bool test(string short_url, int url_length)
{
    bool flag = true;
    
    for(int i=0; i<K; i++)
    {
        uint64_t HashVal = Str_Hash(short_url, url_length);
        uint64_t index = K_hash(i, HashVal);
        if(!BloomFilter.test(index))
        {
            flag = false;
            break;
        }
    }
    return flag;
}