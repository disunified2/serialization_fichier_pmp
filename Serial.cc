#include "Serial.h"

#include <stdexcept>

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

    /**
     * @brief Constructor
     *
     * Opens the file for reading or throws a `std::runtime_error` in case of
     * error.
     */
    IBinaryFile::IBinaryFile(const std::string& filename) {
        file_ = std::fopen(filename.c_str(), "rb");

        if (file_ == nullptr)
            throw std::runtime_error(filename + " could not be opened");

        this->position = 0;
    }

    /**
    * @brief Destructor
    */
    IBinaryFile::~IBinaryFile() {
        auto res = std::fclose(file_);

        if (res != 0)
            throw std::runtime_error("File could not be closed");
    }

    /**
     * @brief Read `size` bytes from the file and store them in the buffer
     * pointed by `data`.
     *
     * Returns the number of bytes actually read.
     */
    std::size_t IBinaryFile::read(std::byte* data, std::size_t size) {
        auto res = fread(data,sizeof(std::byte),size,file_);

        return res;
    }

    IBinaryFile& operator>>(IBinaryFile& file, int8_t& x) {
        std::byte data;
        size_t res = file.read(&data,1);

        if (res == 0)
            throw std::runtime_error("End of file reached");

        x = reinterpret_cast<uint8_t&>(data);

        return file;
    }

    IBinaryFile& operator>>(IBinaryFile& file, uint8_t& x) {
        std::byte data;
        size_t res = file.read(&data,1);

        if (res == 0)
            throw std::runtime_error("End of file reached");

        x = reinterpret_cast<uint8_t&>(data);

        return file;
    }
}