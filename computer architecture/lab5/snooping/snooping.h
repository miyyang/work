#ifndef SNOOPING_H
#define SNOOPING_H

#include"myType.h"
#include<vector>

using namespace std;

class Cache
{
public:
    Cache();
    void reset();
    enum MSI _status[CACHE_SIZE];
    int _memAddr[CACHE_SIZE];
};


class Snooping
{
public:
    Snooping();

    void read(int cpuIndex,int memAddr);
    void write(int cpuIndex,int memAddr);
    void reset();
    enum snooping_status *get_status();
    int get_local_wb_addr();
    int get_remote_wb_addr();
    void clear_status();


private:
    void read_miss(int cpuIndex,int memAddr);
    void write_miss(int cpuIndex,int memAddr);
    void invalid(int cpuIndex,int memAddr);

    vector<Cache> _cache;
    enum snooping_status _status[5*CACHE_NUM];

    int _local_wb_addr;
    int _remote_wb_addr;


};

#endif // SNOOPING_H
