/**
 *
 */

#ifndef ENVFILE_H
#define ENVFILE_H

#include <FS.h>
#include <map>


/* DEBUG */
#define DEBUG

#ifdef DEBUG
#define ENVFILE_DEBUG_PRINTF(...) Serial.print("[ENVFile] "); Serial.printf(__VA_ARGS__);
#else
#define ENVFILE_DEBUG_PRINTF(...) ((void)0)
#endif

// Use LittleFS by default
#include <LittleFS.h>

class ENVFile {

public:

    /**
     * @brief Constructor
     * @param fs Default LittleFS
     * @param filePath Default ".env"
     */
    explicit ENVFile(FS& fs = LittleFS, String  filePath = ".env") : _fs(&fs), _filePath(std::move(filePath)) {}

    /**
     * @brief Constructor
     * @param filePath Default ".env"
     */
    explicit ENVFile(const String &filePath) {
        _fs = &LittleFS;
        _filePath = filePath;
    }

    ~ENVFile() {
        _env.clear();
        _fs = nullptr;
    }

    /**
     * @brief Begin loading the file
     */
    void begin();

    /**
     * @brief Get the value of a key as a string
     * @param key
     * @param defaultValue
     * @return
     */
    String getString(const String& key, String defaultValue = "");

    /**
     * @brief Get the value of a key as a boolean
     * @param key
     * @param defaultValue
     * @return
     */
    bool getBool(const String& key, bool defaultValue = false);

    /**
     * @brief Get the value of a key as an integer
     * @param key
     * @param defaultValue
     * @return
     */
    long getInt(const String& key, long defaultValue = 0);

    /**
     * @brief Get the value of a key as a float
     * @param key
     * @param defaultValue
     * @return
     */
    float getFloat(const String& key, float defaultValue = 0);

    /**
     * @brief Get the value of a key as a double
     * @param key
     * @param defaultValue
     * @return
     */
    double getDouble(const String& key, double defaultValue = 0);

    /**
     * @brief Set bool value for a key
     * @param key
     * @param value
     * @param saveNow save to file immediately
     */
    template<typename T, typename std::enable_if<std::is_same<T, bool>::value, int>::type = 0>
    void set(const String& key, T value, bool saveNow = true) {
        _env[key] = value ? "true" : "false";
        if (saveNow) save();
    }

    /**
     * @brief Set string value for a key
     * @param key
     * @param value
     * @param saveNow save to file immediately
     */
    void set(const String& key, String value, bool saveNow = true) {
        _env[key] = std::move(value);
        if (saveNow) save();
    }

    /**
     * @brief Set int value for a key
     * @param key
     * @param value
     * @param saveNow save to file immediately
     */
    template<typename T, typename std::enable_if<std::is_same<T, int>::value, int>::type = 0>
    void set(const String& key, T value, bool saveNow = true) {
        _env[key] = String(value);
        if (saveNow) save();
    }

    /**
     * @brief Set float value for a key
     * @param key
     * @param value
     * @param saveNow save to file immediately
     */
    template<typename T, typename std::enable_if<std::is_same<T, float>::value, int>::type = 0>
    void set(const String& key, T value, bool saveNow = true) {
        _env[key] = String(value);
        if (saveNow) save();
    }

    /**
     * @brief Set double value for a key
     * @param key
     * @param value
     * @param saveNow save to file immediately
     */
    template<typename T, typename std::enable_if<std::is_same<T, double>::value, int>::type = 0>
    void set(const String& key, T value, bool saveNow = true) {
        _env[key] = String(value);
        if (saveNow) save();
    }

    /**
     * @brief Save the environment variables to the file
     */
    void save();

protected:
    FS* _fs = nullptr;
    String _filePath;
    std::map<String, String> _env;
    bool _loaded = false;

    void _load();

    bool _has(const String& key);
};


#endif //ENVFILE_H
