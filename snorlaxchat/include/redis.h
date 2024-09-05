#ifndef REDIS_H
#define REDIS_H

#include <sw/redis++/redis++.h>
#include <string>

class Redis {
public:
    explicit Redis(const std::string &url);
    Redis(Redis &&other) noexcept;

private:
    sw::redis::Redis redis_;
};

#endif // REDIS_H
