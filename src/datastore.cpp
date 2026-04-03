#include "datastore.h"

long long DataStore::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void DataStore::set(const std::string& key, const std::string& value, int ttl) {
    long long expiry = -1;

    if (ttl != -1) {
        expiry = getCurrentTime() + ttl;
    }

    store[key] = {value, expiry};
}

std::string DataStore::get(const std::string& key) {
    if (store.find(key) == store.end()) {
        return "(nil)";
    }

    auto [value, expiry] = store[key];

    if (expiry != -1 && getCurrentTime() > expiry) {
        store.erase(key);
        return "(nil)";
    }

    return value;
}