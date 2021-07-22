#ifndef _hashmap_hpp_
#define _hashmap_hpp_

#include <functional>
#include <type_traits>
#include <list>
/*
只支持class对象，必须自己实现hash方法
*/
template <class K, class Enable = void> struct hash_to {
    int
    operator()(const K& obj) const {
        if (std::is_class_v<K>) {
            return obj.hash();
        } else {
            return 0;
        }
    }
};

/*
只支持默认基础类型
*/
template <class K> struct hash_to<K, typename std::enable_if<std::is_integral_v<K>>::type> {
    int
    operator()(const K& obj) const {
        return (int)obj;
    }
};

/*
 * 一个简单的hashmap，只支持值类型,
 * todo: 还是要实现迭代器来释放元素。
 */
template <class K, class V, class Hash = hash_to<K>, class Equal = std::equal_to<K>> class HashMap {
private:
    struct Entry {
        K _k;
        V _v;
        Entry* _next;
    };

    struct Bucket {
        Entry* _list;
    };

private:
    Bucket* _buckets;

    Hash _hash;
    Equal _equal;
    const int NUM = 8;
    int count;

public:
    HashMap() {
        count    = 0;
        _buckets = new Bucket[NUM];
        for (int i{}; i < NUM; i++) {
            (_buckets + i)->_list = nullptr;
        }
    }

    ~HashMap() {
        for (int i{}; i < NUM; i++) {
            Bucket* bucket = _buckets + i;
            Entry* head    = bucket->_list;
            while (head != nullptr) {
                Entry* tmp = head->_next;
                delete head;
                head = tmp;
            }
        }
        delete[] _buckets;
    }

    void
    Put(K k, V v) {
        int hash       = _hash(k);
        int index      = hash % NUM;
        Bucket* bucket = _buckets + index;
        Entry* entry   = new Entry{ k, v, bucket->_list };
        bucket->_list  = entry;
        count++;
    }

    bool
    Get(K k, V* v) {
        int hash       = _hash(k);
        int index      = hash % NUM;
        Bucket* bucket = _buckets + index;
        Entry* head    = bucket->_list;

        while (head != nullptr) {
            if (_equal(head->_k, k)) {
                *v = head->_v;
                return true;
            } else {
                head = head->_next;
            }
        }
        return false;
    }

    void
    Remove(K k) {
        int hash       = _hash(k);
        int index      = hash % NUM;
        Bucket* bucket = _buckets + index;
        Entry** head   = &bucket->_list;

        for (Entry* entry{}; *head != nullptr;) {
            entry = *head;
            if (_equal(entry->_k, k)) {
                *head = entry->_next;
                delete entry;
                count--;
            } else {
                head = &entry->_next;
            }
        }
    }

    bool
    Exist(K k) {
        int hash       = _hash(k);
        int index      = hash % NUM;
        Bucket* bucket = _buckets + index;
        Entry* head    = bucket->_list;

        while (head != nullptr) {
            if (_equal(head->_k, k)) {
                return true;
            } else {
                head = head->_next;
            }
        }
        return false;
    }

    std::list<K>
    Keys() {
        std::list<K> keys;
        for (int i{}; i < NUM; i++) {
            Bucket* bucket = _buckets + i;
            Entry* head    = bucket->_list;

            while (head != nullptr) {
                keys.push_back(head->_k);
                head = head->_next;
            }
        }
        return keys;
    }

    std::list<V>
    Values() {
        std::list<V> values;
        for (int i{}; i < NUM; i++) {
            Bucket* bucket = _buckets + i;
            Entry* head    = bucket->_list;

            while (head != nullptr) {
                values.push_back(head->_v);
                head = head->_next;
            }
        }
        return values;
    }
};

#endif
