//
//
#include "redis.h"

Redis::Redis(const std::string &url) : redis_(url) {}

Redis::Redis(Redis &&other) noexcept : redis_(std::move(other.redis_)) {}
