#include <iostream>

#include "crypt_id.h"

int64_t crypt_id(const int64_t id_telegram)
{
    return id_telegram ^ MASK;
}

int64_t decrypt_id(const int64_t crypted_telegram)
{
    return crypted_telegram ^ MASK;
}