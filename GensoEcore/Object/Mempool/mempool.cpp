#include"mempool.hpp"
template<typename T,size_t MaxAllocCnt>
std::optional<size_t> Genso::BaseMemPool<T,MaxAllocCnt>::alloc()
{
    if(freeindex.size()>0)
    {
        size_t id=freeindex.back();
        freeindex.pop_back();
        memused.at(id)=true;
        return id;
    }
    else
    {
        return std::nullopt;
    }
}
template<typename T,size_t MaxAllocCnt>
void Genso::BaseMemPool<T,MaxAllocCnt>::free(size_t id)
{
    if(id<MaxAllocCnt&&memused.at(id))
    {
        memused.at(id)=false;
        freeindex.push_back(id);
    }
}
template<typename T,size_t MaxAllocCnt>
T* Genso::BaseMemPool<T,MaxAllocCnt>::data(size_t id)
{
    if(id<MaxAllocCnt&&memused.at(id))
    {
        return &memblocks[id];
    }
    else return nullptr;
}
template<typename T,size_t MaxAllocCnt>
void Genso::BaseMemPool<T,MaxAllocCnt>::clear()
{
    freeindex.resize(memblocks.size());
    for(size_t i=0; i<memblocks.size(); i++)
    {
        freeindex[i]=memblocks.size()-1-i;
        memused[i]=false;
    }
}
template<typename T,size_t MaxAllocCnt>
size_t Genso::BaseMemPool<T,MaxAllocCnt>::blockused() noexcept
{
    return memblocks.size()-freeindex.size();
}
template<typename T,size_t MaxAllocCnt>
std::optional<T&> Genso::BaseMemPool<T,MaxAllocCnt>::at(size_t index)
{
    if(memused.at(index)==true)
    {
        return {memblocks[index]};
    }else
    {
        return std::nullopt;
    }
}
