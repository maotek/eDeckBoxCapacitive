#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t get_value_with_key(const char *ns, const char *key, uint8_t def_val);

    bool set_value_with_key(const char *ns, const char *key, uint8_t val);

    void get_string_with_key(const char *ns, const char *key, char *buf, uint8_t bufsize, const char *def_val);

    bool set_string_with_key(const char *ns, const char *key, const char *val);

    void init_preferences(void);
#ifdef __cplusplus
}
#endif