#include "Serial.h"

#include <charconv>
#include <stdexcept>
#include <utility>
#include <cstring>

#include <stdexcept>

#include "gtest/gtest-printers.h"

namespace serial {

    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode) : file_(nullptr) {
        const char* open_mode = (mode == Truncate) ? "wb" : "ab";
        file_ = ::fopen(filename.c_str(), open_mode);
        if (!file_) {
            throw std::runtime_error("Cannot open file " + filename);
        }
    }

    OBinaryFile::~OBinaryFile() {
        if (file_) {
            fclose(file_);
            file_ = nullptr;
        }
    }

    OBinaryFile::OBinaryFile(OBinaryFile&& other) noexcept :
    file_(std::exchange(other.file_, nullptr)) { }

    OBinaryFile& OBinaryFile::operator=(OBinaryFile&& other) noexcept {
        if (this != &other) {
            if (file_) {
                fclose(file_);
            }
            file_ = std::exchange(other.file_, nullptr);
        }
        return *this;
    }

    // Write implementation
    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) {
        if (!file_) {
            throw std::runtime_error("No file opened");
        }

        const std::size_t written_bytes = std::fwrite(data, 1, size, file_);
        if (written_bytes != size) {
            throw std::runtime_error("Failed to write all bytes to file");
        }
        return written_bytes;
    }

    OBinaryFile& operator<<(OBinaryFile &file, uint8_t &x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, int8_t x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, uint16_t x) {
        std::byte data[2];
        data[0] = static_cast<std::byte>(x >> 8 & 0xFF);
        data[1] = static_cast<std::byte>(x & 0xFF);
        file.write(data, 2);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, int16_t x) {
        std::byte data[2];
        data[0] = static_cast<std::byte>(x >> 8 & 0xFF);
        data[1] = static_cast<std::byte>(x & 0xFF);
        file.write(data, 2);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, uint32_t x) {
        std::byte data[4];
        for (int i = 3; i >= 0; --i) {
            data[3-i] = static_cast<std::byte>(x >> (8 * i) & 0xFF);
        }
        file.write(data, 4);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, int32_t x) {
        std::byte data[4];
        for (int i = 3; i >= 0; --i) {
            data[3-i] = static_cast<std::byte>(x >> (8 * i) & 0xFF);
        }
        file.write(data, 4);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, uint64_t x) {
        std::byte data[8];
        for (int i = 7; i >= 0; --i) {
            data[7-i] = static_cast<std::byte>(x >> (8 * i) & 0xFF);
        }
        file.write(data, 8);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, int64_t x) {
        std::byte data[8];
        for (int i = 7; i >= 0; --i) {
            data[7-i] = static_cast<std::byte>(x >> (8 * i) & 0xFF);
        }
        file.write(data, 8);
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, char x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, float x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, double x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, bool x) {
        file.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
        return file;
    }

    OBinaryFile& operator<<(OBinaryFile &file, const std::string& x) {
        const std::uint64_t len = x.length();
        file << len;
        for (std::uint64_t i = 0; i < len; i++) {
            file << x[i];
        }
        return file;
    }

    /**
     * @brief Constructor
     *
     * Opens the file for reading or throws a `std::runtime_error` in case of
     * error.
     */
    //Constructor
    IBinaryFile::IBinaryFile(const std::string& filename) {
        file_ = std::fopen(filename.c_str(), "rb");

        if (file_ == nullptr)
            throw std::runtime_error(filename + " could not be opened");
    }

    //Destructor
    IBinaryFile::~IBinaryFile() {
        if (file_) {
            std::fclose(file_);

            file_ = nullptr;
        }
    }

    //Move constructor
    IBinaryFile::IBinaryFile(IBinaryFile&& other) noexcept :
        file_(std::exchange(other.file_, nullptr)){ }

    //Move assignment
    IBinaryFile& IBinaryFile::operator=(IBinaryFile&& other) noexcept {
        if (this != &other) {
            if (file_) {
                fclose(file_);
            }
            file_ = std::exchange(other.file_, nullptr);
        }
        return *this;
    }

    /**
     * @brief Read `size` bytes from the file and store them in the buffer
     * pointed by `data`.
     *
     * Returns the number of bytes actually read.
     */
    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        auto res = fread(data,sizeof(std::byte),size,file_);

        if (res != size) {
            throw std::runtime_error("Failed to write all bytes to file");
        }

        return res;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        std::byte data;
        x = 0;
        file.read(&data,1);

        x = std::to_integer<int8_t>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        std::byte data;
        x = 0;

        file.read(&data,1);

        x = static_cast<uint8_t>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x){
        std::byte data;
        uint16_t y = 0;

        for (int i = 1; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            y |= static_cast<uint16_t>(tmp) << (8 * i);
        }

        x = static_cast<int16_t>(y);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x){
        std::byte data;
        x = 0;

        for (int i = 1; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            x |= static_cast<uint16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x){
        std::byte data;
        uint32_t y = 0;

        for (int i = 3; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            y |= static_cast<uint32_t>(tmp) << (8 * i);
        }
        x = static_cast<int32_t>(y);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x){
        std::byte data;
        x = 0;

        for (int i = 3; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            x |= static_cast<uint32_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x){
        std::byte data;
        uint64_t y = 0;

        for (int i = 7; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            y |= static_cast<uint64_t>(tmp) << (8 * i);
        }
        x = static_cast<int64_t>(y);
        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x){
        std::byte data;
        x = 0;

        for (int i = 7; i >= 0; i--) {
            file.read(&data,1);

            auto tmp = std::to_integer<uint8_t>(data);
            x |= static_cast<uint64_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, char& x) {
        std::byte data;

        file.read(&data,1);

        auto tmp = static_cast<unsigned char>(data);
        x = static_cast<char>(tmp);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, float& x) {
        std::byte data[4];

        for (int i = 0; i < 4; i++) {
            file.read(&data[i],1);
        }

        std::memcpy(&x,&data,sizeof(float));

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, double& x) {
        std::byte data[8];

        for (int i = 0; i < 8; i++) {
            file.read(&data[i],1);
        }

        std::memcpy(&x,&data,sizeof(double));

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, bool& x) {
        std::byte data;

        file.read(&data,1);

        x = static_cast<bool>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, std::string& x) {
        char c;
        uint64_t size;
        file >> size;

        for (auto i = 0; i < size; i++) {
            file >> c;
            x.push_back(c);
        }

        return file;
    }
}
