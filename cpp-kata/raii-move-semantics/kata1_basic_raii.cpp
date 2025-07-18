/*
 * RAII Kata #1: Basic Resource Management
 * 
 * Goal: Implement a FileHandle class that demonstrates RAII principles
 * - Resource acquisition in constructor
 * - Automatic resource cleanup in destructor
 * - Exception safety
 */

#include <iostream> // For console output
#include <fstream> // For file operations
#include <string> // For string operations
#include <stdexcept> // For exception handling

// TODO: Implement the FileHandle class
class FileHandle {
private:
    std::fstream file_; // File stream for managing file operations
    std::string filename_; // Store the filename for reference
    bool is_open_; // Track if the file is open

public:
    // TODO: Constructor should open the file and handle errors
    explicit FileHandle(const std::string& filename, std::ios::openmode mode = std::ios::in | std::ios::out) { // explicit is used to prevent implicit conversions
        // Your implementation here
        filename_ = filename; // Store the filename for reference 
        file_.open(filename,mode); // Check if the file opened successfully
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        is_open_ = true; // Set the file as open
    }

    
    // TODO: Destructor should automatically close the file
    ~FileHandle() {
        if (!is_open_) {
            return; // If the file is not open, nothing to close
        }
        file_.close(); // Close the file
        is_open_ = false; // Mark the file as closed
        std::cout << "File '" << filename_ << "' closed automatically.\n";
        
        // Your implementation here
    }
    
    // TODO: Disable copy constructor and copy assignment (Rule of 5)
    FileHandle(const FileHandle&) = delete; // Disable copy constructor
    FileHandle& operator=(const FileHandle&) = delete; // Disable copy assignment
    
    // TODO: Implement move constructor and move assignment
    FileHandle(FileHandle&& other) noexcept {
        file_ = std::move(other.file_); // Transfer ownership of the file stream
        filename_ = std::move(other.filename_); // Transfer ownership of the filename
        is_open_ = other.is_open_; // Transfer the open state
        other.is_open_ = false; // Leave 'other' in a valid but empty state
        std::cout << "FileHandle moved from '" << other.filename_ << "' to '" << filename_ << "'\n";
        other.filename_.clear(); // Clear the filename of the moved-from object
    }
    
    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) { // Self-assignment check? whats this? this is a this pointer that points to the current object
            // If the current file is open, close it first
            if (is_open_) {
                file_.close(); // Close the current file if open
            }
            file_ = std::move(other.file_); // Transfer ownership of the file stream
            filename_ = std::move(other.filename_); // Transfer ownership of the filename
            is_open_ = other.is_open_; // Transfer the open state
            other.is_open_ = false; // Leave 'other' in a valid but empty state
            std::cout << "FileHandle moved from '" << other.filename_ << "' to '" << filename_ << "'\n";
            other.filename_.clear(); // Clear the filename of the moved-from object
        }
        return *this;
    }
    
    // TODO: Add utility methods
    bool is_open() const {
        return is_open_; // Return the open state of the file
    }
    
    void write(const std::string& data) {
        if (!is_open_) {
            throw std::runtime_error("File is not open for writing: " + filename_);
        }
        file_ << data; // Write data to the file
        if (!file_) {
            throw std::runtime_error("Failed to write to file: " + filename_);
        }
    }
    
    std::string read() {
        if (!is_open_) {
            throw std::runtime_error("File is not open for reading: " + filename_);
        }
        std::string content;
        std::getline(file_, content, '\0'); // Read the entire file content
        if (!file_) {
            throw std::runtime_error("Failed to read from file: " + filename_);
        }
        return content;
    }
};

// Test function
void test_basic_raii() {
    std::cout << "=== RAII Kata #1: Basic Resource Management ===\n";
    
    try {
        // Test 1: Basic RAII functionality
        {
            FileHandle fh("test1.txt", std::ios::out);
            fh.write("Hello RAII!");
            // File should be automatically closed when fh goes out of scope
        }
        
        // Test 2: Read the file
        {
            FileHandle fh("test1.txt", std::ios::in);
            std::cout << "File content: " << fh.read() << std::endl;
        }
        
        // Test 3: Move semantics
        {
            FileHandle fh1("test2.txt", std::ios::out);
            fh1.write("Move test");
            
            FileHandle fh2 = std::move(fh1); // Move constructor
            std::cout << "Move constructor test passed\n";
        }

        // Test 4: Move assignment
        {
            FileHandle fh3("test3.txt", std::ios::out);
            fh3.write("Move assignment test");
            
            FileHandle fh4("test4.txt", std::ios::out); // Create another file handle (output mode)
            fh4 = std::move(fh3); // Move assignment
            std::cout << "Move assignment test passed\n";
        }
        
        std::cout << "All tests passed!\n";
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    test_basic_raii();
    return 0;
}
