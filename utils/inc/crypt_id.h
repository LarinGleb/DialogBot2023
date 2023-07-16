#ifndef __CRYPT_ID_H__
#define __CRYPT_ID_H__

#define MASK 7110110812197

int64_t crypt_id(const int64_t id_telegram);
int64_t decrypt_id(const int64_t crypted_telegram);

#endif