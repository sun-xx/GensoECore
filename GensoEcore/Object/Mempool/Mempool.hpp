#ifndef MEMPOOL_HPP_INCLUDED
#define MEMPOOL_HPP_INCLUDED

//inspired by LuaSTGPlus,FixedObjectPool
#include<bits/stdc++.h>
#pragma once
namespace Genso
{
    template<typename T,size_t MaxAllocCnt>//�ض������ͣ��ڴ�ش�С��block������
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

            ///@brief �������һ��memblock
            ///@return ����ɹ���block��index��ʧ��Ϊ-1
            size_t alloc();

            ///@brief ����һ��block
            void free(size_t id);

            ///@brief ��ȡ��������
            ///@return ʧ�ܷ���nullptr
            T* data(size_t id);

            ///@brief ����ڴ��
            void clear();

            ///@brief �ѷ����block����
            size_t blockused() noexcept;

            std::optional<T&> at(size_t index);

    };

}



#endif // MEMPOOL_HPP_INCLUDED
