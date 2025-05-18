# ENVFile

**ENVFile** is a simple Arduino library for managing `.env` configuration files on ESP32 and other Arduino-compatible boards.

*[Tiếng Việt bên dưới](#envfile-tiếng-việt)*

## 🚀 Features

- Read and write key-value configuration from a file
- Supports multiple file systems: `LittleFS`, `SPIFFS`, `SD`
- Lightweight and easy to use

## 📦 Installation

Add this line to your `platformio.ini`:

```ini
lib_deps =
    nhthai173/ENVFile@^1.0.0
```

## 📄 Usage

[See full examples](./examples)

Basic usage:

```cpp
#include <ENVFile.h>
#include <LittleFS.h>  // or use SPIFFS.h, SD.h

ENVFile env;

void setup() {
    Serial.begin(115200);

    // Initialize your file system before using ENVFile
    LittleFS.begin();
    // Or SPIFFS.begin() if using SPIFFS

    env.begin();

    // Read a value
    String token = env.getString("my_token", "default_token");

    // Set and save immediately
    env.set("DEVICE_ID", "esp32-001");

    // Or set multiple values and save later
    env.set("TEMP", 36.5, false);
    env.set("HUMI", 78.8, false);
    env.save();
}

void loop() {
    // Do something
}
```

## 🧪 .env Format

The `.env` file is a plain text file with each line in the format:

```
KEY=value
DEVICE_NAME=esp32_test
TEMP=25.6
```

## ✅ Notes

- You **should `begin()` on the file system (e.g., `LittleFS.begin()`)** before using `ENVFile`.

---

# ENVFile (Tiếng Việt)

**ENVFile** là một thư viện đơn giản giúp bạn quản lý tập tin cấu hình `.env` trên các thiết bị sử dụng Arduino framework.

## 🚀 Tính năng

- Đọc và ghi các biến cấu hình từ file hệ thống.
- Hỗ trợ nhiều hệ thống file: `LittleFS`, `SPIFFS`, `SD`

## 📦 Cài đặt

Cấu hình cho dự án PlatformIO của bạn trong `platformio.ini`:

```ini
lib_deps =
    nhthai173/ENVFile@^1.0.0
```

## 📄 Cách sử dụng

[Xem ví dụ đầy đủ](./examples)

Sử dụng đơn giản:

```cpp
#include <ENVFile.h>
#include <LittleFS.h>  // hoặc SPIFFS.h, SD.h

ENVFile env;

void setup() {
    Serial.begin(115200);

    // Người dùng nên gọi begin() trước khi sử dụng
    LittleFS.begin();
    // Hoặc SPIFFS.begin() nếu dùng SPIFFS

    env.begin();

    // Đọc giá trị
    String token = env.getString("my_token", "default_token");

    // Ghi giá trị mới và lưu ngay
    env.set("DEVICE_ID", "esp32-001");

    // Hoặc chỉ set hàng loạt và lưu sau
    env.set("TEMP", 36.5, false);
    env.set("HUMI", 78.8, false);
    env.save();
}

void loop() {
    // Do something
}
```

## 🧪 Định dạng file `.env`

File `.env` là tập tin văn bản đơn giản, mỗi dòng có dạng:

```
KEY=value
DEVICE_NAME=esp32_test
TEMP=25.6
```

## ✅ Ghi chú

- Người dùng **nên gọi `begin()` cho hệ thống file trước** khi sử dụng `ENVFile`.