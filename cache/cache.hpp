#pragma once

#include<list>
#include<unordered_map>
#include<iterator>

namespace cache
{
    const int default_capacity = 100;

    template <typename KEY, typename VALUE>
    class Lru
    {
    public:

        Lru(int capacity = default_capacity):mCapacity(capacity),mCacheContainer{},mIndexToNode{}{}

        // return true if get value associated with key,return false if the key does not exist in cache.
        bool object(const KEY &key_,VALUE& value_)
        {
            if (mIndexToNode.end() == mIndexToNode.find(key_))
            {
                return false;
            }

            std::pair<KEY, VALUE> node = *mIndexToNode[key_];
            mCacheContainer.erase(mIndexToNode[key_]);
            mCacheContainer.push_front(node);
            mIndexToNode[key_] = mCacheContainer.begin();
            value_ = node.second;
            return true;
        }

        // 
        bool insert(const KEY &key_,const VALUE &value_)
        {
            auto newNode = std::make_pair(key_, value_);

            if (mIndexToNode.count(key_))
            {
                mCacheContainer.erase(mIndexToNode[key_]);
            }
            else
            {
                if (mCapacity == mCacheContainer.size())
                {
                    mIndexToNode.erase(mCacheContainer.back().first);
                    mCacheContainer.pop_back();
                }
            }

            mCacheContainer.push_front(newNode);
            mIndexToNode[key_] = mCacheContainer.begin();

            return true;
        }

        bool contains(const KEY &key_)
        {
            if (mIndexToNode.end() == mIndexToNode.find(key_))
            {
                return false;
            }
            return true;
        }

    private:
        uint                                                                    mCapacity;
        std::list<std::pair<KEY, VALUE>>                                             mCacheContainer;
        std::unordered_map<KEY, typename std::list<std::pair<KEY, VALUE>>::iterator>     mIndexToNode;
    };
}