#include <iostream>

#include "crypt_id.h"

ll crypt_id(const ll id_telegram) {
    return id_telegram ^ MASK;
}

ll decrypt_id(const ll crypted_telegram) {
    return crypted_telegram ^ MASK;
}