#ifndef ABSTRACT_H
#define ABSTRACT_H

#include "hash.h"

#include <string>
#include <random>
#include <unordered_map>
#include <limits.h>
#include <algorithm>
#include <string.h>

#define MAX(a, b) (a > b? a:b)
#define MIN(a, b) (a < b? a:b)

typedef uint32_t data_type; //note: according to your dataset
typedef int32_t count_type; //note: according to your dataset
typedef std::unordered_map<data_type, count_type> HashMap;

inline uint32_t hash(data_type item, uint32_t seed = 0){
    return Hash::BOBHash64((uint8_t*)&item, sizeof(data_type), seed);
}

static std::random_device rd;
static const count_type COUNT[2] = {1, -1};


count_type Get_Median(count_type result[], uint32_t length){
    std::sort(result, result + length);
    return (length & 1) ? result[length >> 1] :
           (result[length >> 1] + result[(length >> 1) - 1]) / 2;
}

class Abstract{
public:
    char* name;

    Abstract(char* _name):name(_name){};
    virtual ~Abstract(){};

    virtual void Insert(const data_type item) = 0;
    virtual count_type Query(const data_type item) = 0;

    void Check(HashMap mp, count_type HIT){
        HashMap::iterator it;
        count_type value = 0, all = 0, hit = 0, size = 0;
        double aae = 0, are = 0, cr = 0, pr = 0, total = 0;
        for(it = mp.begin();it != mp.end();++it){
            value = Query(it->first);
            if(it->second > HIT){
                all++;
                if(value > HIT){
                    hit += 1;
                    aae += abs(it->second - value);
                    are += abs(it->second - value) / (double)it->second;
                }
            }
            if(value > HIT)
                size += 1;

            total += (value - it->second);
        }

        aae /= hit; are /= hit; cr = hit / (double)all;
        pr = hit / (double)size;
        printf("%s: %d\nAAE: %lf\nARE: %lf\nCR: %lf\nPR: %lf\n", name, all, aae, are, cr, pr);
    }
};

#endif // ABSTRACT_H
