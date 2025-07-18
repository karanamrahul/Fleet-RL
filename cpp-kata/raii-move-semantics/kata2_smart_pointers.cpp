/*
 * RAII Kata #2: Smart Pointers and Move Semantics
 * 
 * Goal: Implement a simple unique_ptr-like class to understand:
 * - Automatic memory management
 * - Move-only semantics
 * - Transfer of ownership
 */

#include <iostream> // For console output and debugging
#include <memory> // For std::unique_ptr  and std::make_unique std::unique_ptr: a smart pointer that manages a dynamically allocated object
// For std::make_unique: a helper function to create unique_ptrs
#include <vector> // For std::vector: a dynamic array container

// Simple class for testing
class Resource { // Represents a resource that we will manage with our smart pointer
public: 
    Resource(int value) : value_(value) { // Constructor initializes the resource with a value
        // RAII: Resource acquisition in constructor
        // This is where we acquire the resource (e.g., allocate memory, open a file, etc.)
        // Here we just print a message for demonstration
        // This is a simple resource that just holds an integer value
        std::cout << "🔨 Resource(" << value_ << ") constructed at address " << this << "\n";
    }
    
    ~Resource() {
        // RAII: Resource cleanup in destructor
        // This is where we release the resource (e.g., deallocate memory, close a
        // file, etc.)
        // Here we just print a message for demonstration
        // This destructor will be called automatically when the object goes out of scope
        // or is deleted
        std::cout << "Resource(" << value_ << ") destroyed\n";
    }
    
    int getValue() const { return value_; } // Getter for the value
    void setValue(int value) { value_ = value; } // Setter for the value 
    
private:
    int value_; // The value of the resource
};

// TODO: Implement SimpleUniquePtr class
template<typename T> // A simple unique pointer implementation  
class SimpleUniquePtr { // A simple unique pointer that manages a dynamically allocated object of type T
private:
    T* ptr_; // Raw pointer to the managed object

public:
    // Constructor - takes ownership of raw pointer
    explicit SimpleUniquePtr(T* ptr = nullptr) : ptr_(ptr) {
        // RAII: We acquire the resource (take ownership of the pointer)
        // The 'explicit' keyword prevents implicit conversions
        if (ptr_) {
            std::cout << "🔨 SimpleUniquePtr::Constructor - Taking ownership of pointer " << ptr_ << " (Resource exists)\n";
        } else {
            std::cout << "🔨 SimpleUniquePtr::Constructor - Created with nullptr (No resource)\n";
        }
    }
    
    // Destructor - delete the managed object
    ~SimpleUniquePtr() {
        // RAII: We release the resource (delete the object)
        if (ptr_) {
            std::cout << "💀 SimpleUniquePtr::Destructor - Deleting pointer " << ptr_ << " (Resource will be destroyed)\n";
            delete ptr_;
        } else {
            std::cout << "💀 SimpleUniquePtr::Destructor - Nothing to delete (ptr is nullptr)\n";
        }
    }
    
    // TODO: Delete copy constructor and copy assignment (move-only type)
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    // Move constructor - transfer ownership
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr_(other.ptr_) {
        // Move semantics: Transfer ownership from 'other' to 'this'
        // 1. Take the pointer from 'other'
        // 2. Set 'other' to null (moved-from state)
        std::cout << "🚀 SimpleUniquePtr::Move Constructor - Transferring ownership of pointer " << ptr_ << " from source to destination\n";
        other.ptr_ = nullptr;  // Leave 'other' in a valid but empty state
        std::cout << "🚀 SimpleUniquePtr::Move Constructor - Source pointer set to nullptr (moved-from state)\n";
    }
    
    // Move assignment - transfer ownership
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        // Move assignment: Transfer ownership from 'other' to 'this'
        std::cout << "⚡ SimpleUniquePtr::Move Assignment - Starting move assignment\n";
        if (this != &other) {  // Self-assignment check
            std::cout << "⚡ SimpleUniquePtr::Move Assignment - Not self-assignment, proceeding\n";
            // 1. Clean up our current resource
            if (ptr_) {
                std::cout << "⚡ SimpleUniquePtr::Move Assignment - Deleting old pointer " << ptr_ << " (old resource will be destroyed)\n";
                delete ptr_;
            } else {
                std::cout << "⚡ SimpleUniquePtr::Move Assignment - No old resource to delete\n";
            }
            // 2. Take ownership from 'other'
            ptr_ = other.ptr_;
            std::cout << "⚡ SimpleUniquePtr::Move Assignment - Acquired pointer " << ptr_ << " from source\n";
            // 3. Leave 'other' in valid but empty state
            other.ptr_ = nullptr;
            std::cout << "⚡ SimpleUniquePtr::Move Assignment - Source pointer set to nullptr (moved-from state)\n";
        } else {
            std::cout << "⚡ SimpleUniquePtr::Move Assignment - Self-assignment detected, doing nothing\n";
        }
        return *this;
    }
    
    // TODO: Dereference operators
    T& operator*() const {
        // Your implementation here
        if (!ptr_) {
            throw std::runtime_error("Dereferencing a null pointer");
        }
        return *ptr_; // Dereference the pointer to access the object
    }
    
    T* operator->() const {
        // Your implementation here'
        if (!ptr_) {
            throw std::runtime_error("Dereferencing a null pointer");
        }
        return ptr_; // Return the raw pointer to access the object's members
    }
    
    // TODO: Get raw pointer
    T* get() const {
        // Your implementation here
        return ptr_; // Return the raw pointer to the managed object
    }
    
    // TODO: Release ownership
    T* release() {
        // Your implementation here
        T* temp = ptr_; // Store the current pointer
        ptr_ = nullptr; // Leave the pointer in a null state
        std::cout << "🔓 SimpleUniquePtr::Release - Released ownership of pointer " << temp << " (caller now owns it)\n";
        return temp; // Return the raw pointer, transferring ownership
    }
    
    // TODO: Reset with new pointer
    void reset(T* ptr = nullptr) {
        // Your implementation 
        if (ptr_) {
            std::cout << "🔄 SimpleUniquePtr::Reset - Deleting old pointer " << ptr_ << " (old resource will be destroyed)\n";
            delete ptr_; // Delete the current object
        } else {
            std::cout << "🔄 SimpleUniquePtr::Reset - No old resource to delete\n";
        }
        ptr_ = ptr; // Take ownership of the new pointer
        if (ptr_) {
            std::cout << "🔄 SimpleUniquePtr::Reset - Now managing new pointer " << ptr_ << " (new resource acquired)\n";
        } else {
            std::cout << "🔄 SimpleUniquePtr::Reset - Reset to nullptr (no resource)\n"; 
        }
    }
    
    // TODO: Check if pointer is valid
    explicit operator bool() const {
        // Your implementation here
        return ptr_ != nullptr; // Return true if the pointer is not null
    }
};

// TODO: Implement make_simple_unique helper function
template<typename T, typename... Args>
SimpleUniquePtr<T> make_simple_unique(Args&&... args) 

{
    // This function creates a SimpleUniquePtr by allocating a new object of type T
    // and forwarding the arguments to its constructor
    return SimpleUniquePtr<T>(new T(std::forward<Args>(args)...));
}

// Test functions
void test_move_semantics() {
    std::cout << "=== RAII Kata #2: Smart Pointers and Move Semantics ===\n";
    
    // Test 1: Basic usage
    {
        std::cout << "\n--- Test 1: Basic Usage ---\n";
        std::cout << "📝 Creating SimpleUniquePtr with Resource(42)...\n";
        SimpleUniquePtr<Resource> ptr(new Resource(42));
        std::cout << "📖 Accessing resource value through smart pointer...\n";
        std::cout << "Resource value: " << ptr->getValue() << std::endl;
        std::cout << "📝 Leaving scope - smart pointer should automatically clean up...\n";
    } // Resource should be automatically destroyed here
    std::cout << "✅ Test 1 completed - RAII automatically cleaned up resource!\n";
    
    // Test 2: Move constructor
    {
        std::cout << "\n--- Test 2: Move Constructor ---\n";
        std::cout << "📝 Creating first smart pointer...\n";
        SimpleUniquePtr<Resource> ptr1(new Resource(100));
        std::cout << "📝 Moving ptr1 to ptr2 using move constructor...\n";
        SimpleUniquePtr<Resource> ptr2 = std::move(ptr1);
        
        std::cout << "📊 After move constructor:\n";
        std::cout << "ptr1 is " << (ptr1 ? "valid" : "null") << " (should be null - ownership transferred)\n";
        std::cout << "ptr2 is " << (ptr2 ? "valid" : "null") << " (should be valid - now owns resource)\n";
        if (ptr2) {
            std::cout << "ptr2 value: " << ptr2->getValue() << std::endl;
        }
        std::cout << "📝 Leaving scope - only ptr2 should clean up (ptr1 has nothing to clean)...\n";
    }
    std::cout << "✅ Test 2 completed - Move constructor transferred ownership correctly!\n";
    
    // Test 3: Move assignment
    {
        std::cout << "\n--- Test 3: Move Assignment ---\n";
        std::cout << "📝 Creating two smart pointers with different resources...\n";
        SimpleUniquePtr<Resource> ptr1(new Resource(200));
        SimpleUniquePtr<Resource> ptr2(new Resource(300));
        
        std::cout << "📊 Before move assignment:\n";
        std::cout << "ptr1 value: " << ptr1->getValue() << " (will be moved)\n";
        std::cout << "ptr2 value: " << ptr2->getValue() << " (will be replaced and destroyed)\n";
        
        std::cout << "📝 Performing move assignment: ptr2 = std::move(ptr1)...\n";
        ptr2 = std::move(ptr1); // ptr2's old resource should be destroyed
        
        std::cout << "📊 After move assignment:\n";
        std::cout << "ptr1 is " << (ptr1 ? "valid" : "null") << " (should be null - ownership transferred)\n";
        if (ptr2) {
            std::cout << "ptr2 value: " << ptr2->getValue() << " (should be 200 - received from ptr1)\n";
        }
        std::cout << "📝 Leaving scope - only ptr2 should clean up...\n";
    }
    std::cout << "✅ Test 3 completed - Move assignment transferred ownership and cleaned up old resource!\n";
    
    // Test 4: make_simple_unique
    {
        std::cout << "\n--- Test 4: make_simple_unique ---\n";
        std::cout << "📝 Creating smart pointer using make_simple_unique helper...\n";
        auto ptr = make_simple_unique<Resource>(500);
        std::cout << "📖 Created resource with value: " << ptr->getValue() << std::endl;
        std::cout << "📝 Leaving scope - make_simple_unique result should clean up...\n";
    }
    std::cout << "✅ Test 4 completed - make_simple_unique worked correctly!\n";
    
    // Test 5: Container of move-only objects
    {
        std::cout << "\n--- Test 5: Container Usage ---\n";
        std::cout << "📝 Creating vector of move-only smart pointers...\n";
        std::vector<SimpleUniquePtr<Resource>> resources;
        
        for (int i = 0; i < 3; ++i) {
            std::cout << "📝 Adding resource " << i << " to container...\n";
            resources.push_back(make_simple_unique<Resource>(i * 10));
        }
        
        std::cout << "📊 Resources in container:\n";
        for (const auto& res : resources) {
            std::cout << "  Value: " << res->getValue() << std::endl;
        }
        std::cout << "📝 Leaving scope - all container resources should be destroyed...\n";
    } // All resources should be destroyed when vector is destroyed
    std::cout << "✅ Test 5 completed - Container correctly managed move-only objects!\n";
    
    std::cout << "\n🎉 All tests completed successfully!\n";
}

int main() {
    test_move_semantics();
    return 0;
}
