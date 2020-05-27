#ifndef COMMON_H
#define COMMON_H
#include <cstddef>
#include <cstdint>

enum ObjectType {
    EMPTY = 0 ,
    AMPHIPRION_FEMALE,
    AMPHIPRION_MALE,
    SHARK_FEMALE,
    SHARK_MALE,
    ROCK
};

struct ObjectInf
{
    ObjectInf() = default;
    ObjectInf(size_t id,size_t index, ObjectType type):
        m_id(id),m_index(index),m_type(type){}
    ObjectInf( ObjectInf const&) = default;
    ObjectInf( ObjectInf&&) = default;
    ObjectInf& operator= (const ObjectInf &) = default;

    size_t m_id = UINT64_MAX;
    size_t m_index = UINT64_MAX;
    ObjectType m_type = ObjectType::EMPTY;
};

#endif // COMMON_H
