// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "LRU.h"
#include "utils/Log.h"

#include <atomic>
#include <mutex>
#include <set>
#include <string>

namespace milvus {
namespace cache {

template <typename ItemObj>
class Cache {
 public:
    // mem_capacity, units:GB
    Cache(int64_t capacity_gb, uint64_t cache_max_count);
    ~Cache() = default;

    int64_t
    usage() const {
        return usage_;
    }

    int64_t
    capacity() const {
        return capacity_;
    }  // unit: BYTE
    void
    set_capacity(int64_t capacity);  // unit: BYTE

    double
    freemem_percent() const {
        return freemem_percent_;
    }

    void
    set_freemem_percent(double percent) {
        freemem_percent_ = percent;
    }

    size_t
    size() const;
    bool
    exists(const std::string& key);
    ItemObj
    get(const std::string& key);
    void
    insert(const std::string& key, const ItemObj& item);
    void
    erase(const std::string& key);
    void
    print();
    void
    clear();

 private:
    void
    free_memory();

 private:
    int64_t usage_;
    int64_t capacity_;
    double freemem_percent_;

    LRU<std::string, ItemObj> lru_;
    mutable std::mutex mutex_;
};

}  // namespace cache
}  // namespace milvus

#include "cache/Cache.inl"
