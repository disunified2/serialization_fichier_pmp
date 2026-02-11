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
    std::size_t OBinaryFile::write(const std::byte* data, std::size_t size) const {
        if (!file_) {
            throw std::runtime_error("No file opened");
        }

        const std::size_t written_bytes = std::fwrite(data, 1, size, file_);
        if (written_bytes != size) {
            throw std::runtime_error("Failed to write all bytes to file");
        }
        return written_bytes;
    }

}
