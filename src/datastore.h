#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <unordered_map>
#include <chrono>

class DataStore {
private:
    std::unordered_map<std::string, std::pair<std::string, long long>> store;

    long long getCurrentTime();

public:
    void set(const std::string& key, const std::string& value, int ttl = -1);
    std::string get(const std::string& key);
};

#endif