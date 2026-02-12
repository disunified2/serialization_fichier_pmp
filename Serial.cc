#include "Serial.h"
#include <stdexcept>
#include <utility>

namespace serial {

    OBinaryFile::OBinaryFile(const std::string& filename, Mode mode) : file_(nullptr) {
        const char* open_mode = (mode == Truncate) ? "wb" : "rb";
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
    std::size_t write(const std::byte* data, std::size_t size) {
        return 0;
    }

    //Constructor
    IBinaryFile::IBinaryFile(const std::string& filename) {
        file_ = std::fopen(filename.c_str(), "rb");

        if (file_ == nullptr)
            throw std::runtime_error(filename + " could not be opened");

        this->position = 0;
    }

    //Destructor
    IBinaryFile::~IBinaryFile() {
        if (file_) {
            auto res = std::fclose(file_);
            if (res != 0)
                throw std::runtime_error("File could not be closed");
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

        position += res;

        return res;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        std::byte data;
        size_t res = file.read(&data,1);

        if (res == 0)
            throw std::runtime_error("End of file reached");

        x = static_cast<int8_t>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        std::byte data;
        size_t res = file.read(&data,1);

        if (res == 0)
            throw std::runtime_error("End of file reached");

        x = static_cast<uint8_t>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int16_t& x){
        std::byte data;
        x = 0;

        for (int i = 1; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<int8_t>(data);
            x |= static_cast<int16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint16_t& x){
        std::byte data;
        x = 0;

        for (int i = 1; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<uint8_t>(data);
            x |= static_cast<uint16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int32_t& x){
        std::byte data;
        x = 0;

        for (int i = 2; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<int8_t>(data);
            x |= static_cast<int16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint32_t& x){
        std::byte data;
        x = 0;

        for (int i = 2; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<uint8_t>(data);
            x |= static_cast<uint16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int64_t& x){
        std::byte data;
        x = 0;

        for (int i = 3; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<int8_t>(data);
            x |= static_cast<int16_t>(tmp) << (8 * i);
        }

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint64_t& x){
        std::byte data;
        x = 0;

        for (int i = 3; i >= 0; i--) {
            size_t res = file.read(&data,1);
            if (res == 0)
                throw std::runtime_error("End of file reached");

            auto tmp = static_cast<uint8_t>(data);
            x |= static_cast<uint16_t>(tmp) << (8 * i);
        }

        return file;
    }
}
