#ifndef MEMPOOL_HPP_INCLUDED
#define MEMPOOL_HPP_INCLUDED

//inspired by LuaSTGPlus,FixedObjectPool
#include<bits/stdc++.h>
#pragma once
namespace Genso
{
    template<typename T,size_t MaxAllocCnt>//池对象类型，内存池大小（block数量）
    class BaseMemPool
    {
        private:
            std::vector<size_t> freeindex;
            std::array<bool,MaxAllocCnt> memused;
            std::array<T,MaxAllocCnt> memblocks;
        private:
            BaseMemPool(const BaseMemPool& mp)=delete;
            BaseMemPool& operator=(const BaseMemPool& mp)=delete;
        public:
            BaseMemPool()
            {
                clear();
            };

            ///@brief 申请分配一个memblock
            ///@return 申请成功的block的index，失败为-1
            size_t alloc();

            ///@brief 回收一个block
            void free(size_t id);

            ///@brief 获取对象数据
            ///@return 失败返回nullptr
            T* data(size_t id);

            ///@brief 清空内存池
            void clear();

            ///@brief 已分配的block数量
            size_t blockused() noexcept;

            std::optional<T&> at(size_t index);

    };

}



#endif // MEMPOOL_HPP_INCLUDED
