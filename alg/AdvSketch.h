#ifndef COUNT_BUCKET_H
#define COUNT_BUCKET_H

#include "common/abstract.h"

template<uint32_t slot_num>
class AdvSketch : public Abstract{
public:

    struct Bucket{
        data_type items[2][slot_num];
        count_type counters[2][slot_num];
        count_type incast;

        void Insert(const data_type item){
            uint32_t choice = hash(item, 17) & 1;
            count_type min_num = INT_MAX;
            uint32_t min_pos = -1;

            for(uint32_t i = 0;i < slot_num;++i){
                if(counters[choice][i] == 0){
                    items[choice][i] = item;
                    counters[choice][i] = 1;
                    return;
                }
                else if(items[choice][i] == item){
                    counters[choice][i] += 1;
                    return;
                }

                if(counters[choice][i] < min_num){
                    min_num = counters[choice][i];
                    min_pos = i;
                }
            }

            if(incast * COUNT[choice] == min_num){
                items[choice][min_pos] = item;
                counters[choice][min_pos] += 1;
            }
            else{
                incast += COUNT[choice];
            }
        }

        count_type Query(const data_type item){
            uint32_t choice = hash(item, 17) & 1;

            for(uint32_t i = 0;i < slot_num;++i){
                if(items[choice][i] == item){
                    return counters[choice][i];
                }
            }

            return 0;
        }
    };

    AdvSketch(uint32_t _BUCKET_NUM):Abstract("AdvSketch"), BUCKET_NUM(_BUCKET_NUM / 2){
        buckets = new Bucket[BUCKET_NUM];
        memset(buckets, 0, BUCKET_NUM * sizeof(Bucket));
    }
    ~AdvSketch(){
        delete [] buckets;
    }

    void Insert(const data_type item){
        uint32_t bucket_pos = hash(item) % BUCKET_NUM;
        buckets[bucket_pos].Insert(item);
    }

    count_type Query(const data_type item){
        uint32_t bucket_pos = hash(item) % BUCKET_NUM;
        return buckets[bucket_pos].Query(item);
    }

private:
    Bucket* buckets;
    const uint32_t BUCKET_NUM;
};

#endif //BUCKET_UNBIASED_H
