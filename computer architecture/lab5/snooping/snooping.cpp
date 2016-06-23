#include"snooping.h"
#include<QDebug>

//***************************Cache***********************************

Cache::Cache()
{
    reset();
}

void Cache::reset()
{
    int i;
    for(i=0;i<CACHE_SIZE;i++)
    {
        _status[i]=I;//Invalid
        _memAddr[i]=-1;
    }
}


//***************************Snooping***********************************

Snooping::Snooping()
{
    _cache.resize(CACHE_NUM);
    clear_status();
}

int Snooping::get_local_wb_addr()
{
    return _local_wb_addr;
}

int Snooping::get_remote_wb_addr()
{
    return _remote_wb_addr;
}

void Snooping::reset()
{
    unsigned long i;
    for(i=0;i < _cache.size();i++)
        _cache.at(i).reset();
    clear_status();

}

enum snooping_status *Snooping::get_status()
{
    return _status;
}

void Snooping::read_miss(int cpuIndex,int memAddr)
{
    _status[cpuIndex+2*CACHE_NUM] = READ_MISS;
    int index = memAddr%CACHE_SIZE;
    for (int i=0; i<CACHE_NUM; i++)
        if (_cache[i]._memAddr[index] == memAddr)
            if (_cache[i]._status[index] == M)
            {
                _status[i+3*CACHE_NUM] = SHARED;
                _remote_wb_addr = memAddr;
                _cache[i]._status[index] = S;
                _status[i+4*CACHE_NUM] = SHARED;
            }
    _cache[cpuIndex]._memAddr[index] = memAddr;
}

void Snooping::write_miss(int cpuIndex,int memAddr)
{
    _status[cpuIndex+2*CACHE_NUM] = WRITE_MISS;
    int index = memAddr%CACHE_SIZE;
    for (int i=0; i<CACHE_NUM; i++)
        if (_cache[i]._memAddr[index] == memAddr)
        {
            if (_cache[i]._status[index] == S)
            {
                _cache[i]._status[index] = I;
                _status[i+4*CACHE_NUM] = INVALID;
            }
            else if (_cache[i]._status[index] == M)
            {
                _status[i+3*CACHE_NUM] = INVALID;
                _remote_wb_addr = memAddr;
                _cache[i]._status[index] = I;
                _status[i+4*CACHE_NUM] = INVALID;
            }
        }
    _cache[cpuIndex]._memAddr[index] = memAddr;
}

void Snooping::invalid(int cpuIndex,int memAddr)
{
    _status[cpuIndex+2*CACHE_NUM] = INVALID;
    int index = memAddr%CACHE_SIZE;
    for (int i=0; i<CACHE_NUM; i++)
        if (_cache[i]._memAddr[index] == memAddr)
            if (_cache[i]._status[index] == S)
            {
                _cache[i]._status[index] = I;
                _status[i+4*CACHE_NUM] = INVALID;
            }
}

void Snooping::clear_status()
{
    int i;
    for(i=0;i<5*CACHE_NUM;i++)
        _status[i]=NO_ACTION;
}

void Snooping::read(int cpuIndex,int memAddr)
{
    int index = memAddr%CACHE_SIZE;
    if (_cache[cpuIndex]._memAddr[index] == memAddr)
        _status[cpuIndex] = READ_HIT;
    else
    {
        _status[cpuIndex] = READ_MISS;
        if (_cache[cpuIndex]._status[index] == I)
        {
            read_miss(cpuIndex, memAddr);
            _cache[cpuIndex]._status[index] = S;
            _status[cpuIndex+4*CACHE_NUM] = SHARED;
        }
        else if ( _cache[cpuIndex]._status[index] == S)
            read_miss(cpuIndex, memAddr);
        else if (_cache[cpuIndex]._status[index] == M)
        {
            _status[cpuIndex+CACHE_NUM*1] = READ_MISS;
            _local_wb_addr = memAddr;
            read_miss(cpuIndex, memAddr);
            _cache[cpuIndex]._status[index] = S;
            _status[cpuIndex+4*CACHE_NUM] = SHARED;
        }
    }
}

void Snooping::write(int cpuIndex,int memAddr)
{
    int index = memAddr%CACHE_SIZE;
    if (_cache[cpuIndex]._memAddr[index] == memAddr)
    {
        _status[cpuIndex] = WRITE_HIT;
        if (_cache[cpuIndex]._status[index] == S)
        {
            invalid(cpuIndex, memAddr);
            _cache[cpuIndex]._status[index] = M;
            _status[cpuIndex+4*CACHE_NUM] = MODIFIED;
        }
    }
    else
    {
        _status[cpuIndex] = WRITE_MISS;
        if (_cache[cpuIndex]._status[index] == I)
        {
            write_miss(cpuIndex, memAddr);
            _cache[cpuIndex]._status[index] = M;
            _status[cpuIndex+4*CACHE_NUM] = MODIFIED;
        }
        else if (_cache[cpuIndex]._status[index] == S)
        {
            write_miss(cpuIndex, memAddr);
            _cache[cpuIndex]._status[index] = M;
            _status[cpuIndex+4*CACHE_NUM] = MODIFIED;
        }
        else if (_cache[cpuIndex]._status[index] == M)
        {
            _status[cpuIndex+1*CACHE_NUM] = WRITE_MISS;
            _local_wb_addr = memAddr;
            write_miss(cpuIndex, memAddr);
        }
    }
}
