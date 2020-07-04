#ifndef BENCH_BENCHMARK_H
#define BENCH_BENCHMARK_H

#include <chrono>

#include "alg/AdvSketch.h"
#include "alg/SS.h"
#include "alg/USS.h"
#include "alg/Count_Heap.h"

typedef std::chrono::high_resolution_clock::time_point TP;
typedef std::pair<count_type, data_type> Counter;

inline TP now(){
    return std::chrono::high_resolution_clock::now();
}

uint32_t Get_TopK(HashMap mp, uint32_t k){
    uint32_t size = mp.size();
    uint32_t *num = new uint32_t [size];

    uint32_t pos = 0;
    HashMap::iterator it;
    for(it = mp.begin();it != mp.end();++it){
        num[pos++] = it->second;
    }
    std::nth_element(num, num + size - k, num + size);
    uint32_t ret = num[size - k];

    delete [] num;
    return ret;
}


void BenchOther(const char* PATH){
    Abstract* sketches[] = {
            new USS(4000),
            new SS(4000),
            new Count_Heap<40000, 3>(2500),
            new AdvSketch<4>(4000)
    };

    FILE* file = fopen(PATH,"rb");
    data_type item;
    HashMap mp;

    while(fread(&item, sizeof(data_type), 1, file) > 0)
    {
        if(mp.find(item) == mp.end())
            mp[item] = 1;
        else
            mp[item] += 1;

        for(Abstract* sketch : sketches){
            sketch->Insert(item);
        }
    }

    fclose(file);

    uint32_t topK = Get_TopK(mp, 2000);
    for(Abstract* sketch : sketches){
        sketch->Check(mp, topK);
        delete sketch;
    }
}

void BenchThp(const char* PATH){
    Abstract* sketches[] = {
            new USS(4000),
            new SS(4000),
            new Count_Heap<40000, 3>(2500),
            new AdvSketch<4>(4000)
    };

    for(Abstract* sketch : sketches){
        TP start, finish;

        FILE* file = fopen(PATH,"rb");
        data_type item;
        uint32_t test_size = 0;

        start = now();
        while(fread(&item, sizeof(data_type), 1, file) > 0)
        {
            test_size += 1;
            sketch->Insert(item);
        }
        finish = now();

        fclose(file);

        printf("%s: %lf\n", sketch->name, (double) test_size / std::chrono::duration_cast<std::chrono::duration<double,std::ratio<1,1000000>>>(finish - start).count());
    }
}


#endif //BENCH_BENCHMARK_H
