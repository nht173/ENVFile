#include "ENVFile.h"


void ENVFile::begin() {
    _load();
}


String ENVFile::getString(const String& key, String defaultValue) {
    if (!_has(key)) return defaultValue;
    return _env[key];
}


bool ENVFile::getBool(const String& key, bool defaultValue) {
    if (!_has(key)) return defaultValue;
    return _env[key] == "true";
}


long ENVFile::getInt(const String& key, long defaultValue) {
    if (!_has(key)) return defaultValue;
    return _env[key].toInt();
}


float ENVFile::getFloat(const String& key, float defaultValue) {
    if (!_has(key)) return defaultValue;
    return _env[key].toFloat();
}


double ENVFile::getDouble(const String& key, double defaultValue) {
    if (!_has(key)) return defaultValue;
    return _env[key].toDouble();
}


void ENVFile::save() {
    if (!_fs) {
        ENVFILE_DEBUG_PRINTF("[save] Filesystem pointer is null");
        return;
    }
    if (!_loaded) {
        std::map<String, String> temp_map = _env;
        _load();
        for (auto &e : temp_map) {
            _env[e.first] = e.second;
        }
    }
    File file = _fs->open(_filePath, "w");
    if (!file) return;
    for (auto &e : _env) {
        file.printf("%s=%s\n", e.first.c_str(), e.second.c_str());
    }
    file.close();
}


void ENVFile::_load() {
    if (!_fs) {
        ENVFILE_DEBUG_PRINTF("[load] Filesystem pointer is null\n");
        return;
    }

    // Begin file system
#if defined(_LITTLEFS_H_)
#ifdef ESP32
    LittleFS.begin(true);
#else // another
    LittleFS.begin();
#endif // ESP32
#elif defined(_SPIFFS_H_)
    #ifdef ESP32
        SPIFFS.begin(true);
#else // another
        SPIFFS.begin();
#endif // ESP32
#endif // _LITTLEFS_H_

    File file = _fs->open(_filePath, "r");
    if (!file) return;
    while (file.available()) {
        String d = file.readStringUntil('\n');
        if (d.length() == 0) continue;
        if (d[0] == '#') continue; // Skip comments
        int pos = d.indexOf('=');
        if (pos == -1) continue;
        String key = d.substring(0, pos);
        String value = d.substring(pos + 1);
        _env[key] = value;
    }
    file.close();
    _loaded = true;
}


bool ENVFile::_has(const String& key) {
    if (!_loaded) _load();
    return _env.count(key) > 0;
}