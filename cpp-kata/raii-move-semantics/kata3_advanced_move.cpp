/*
 * RAII Kata #3: Advanced Move Semantics and Perfect Forwarding
 * 
 * Goal: Implement a container class that demonstrates:
 * - Move semantics optimization
 * - Perfect forwarding
 * - Exception safety
 * - Efficient resource management
 */

#include <iostream> // For console output and debugging
#include <vector>   // For std::vector: a dynamic array container
#include <string>   // For std::string 
#include <utility>  // For std::move and std::forward
#include <algorithm> // For std::copy, std::move, etc.

// Example class with expensive copy operations
class ExpensiveObject {
private:
    std::string name_; // Name of the object
    std::vector<int> data_; // Data storage for the object
    
public:
    // Constructor
    ExpensiveObject(const std::string& name, size_t size = 1000) 
        : name_(name), data_(size, 42) {
        std::cout << "🔨 ExpensiveObject('" << name_ << "') constructed with " << size << " elements at address " << this << "\n";
    }
    
    // Copy constructor (expensive)
    ExpensiveObject(const ExpensiveObject& other) 
        : name_(other.name_ + "_copy"), data_(other.data_) {
        std::cout << "📄 ExpensiveObject('" << name_ << "') COPIED from '" << other.name_ << "' (expensive - " << data_.size() << " elements duplicated!)\n";
    }
    
    // Copy assignment (expensive)
    ExpensiveObject& operator=(const ExpensiveObject& other) {
        if (this != &other) {
            name_ = other.name_ + "_assigned";
            data_ = other.data_;
            std::cout << "📝 ExpensiveObject('" << name_ << "') COPY ASSIGNED from '" << other.name_ << "' (expensive - " << data_.size() << " elements duplicated!)\n";
        }
        return *this;
    }
    
    // TODO: Move constructor (efficient)
    ExpensiveObject(ExpensiveObject&& other) noexcept {
        // Your implementation here
        std::cout << "🚀 ExpensiveObject Move Constructor - Starting efficient transfer from '" << other.name_ << "'\n";
        name_ = std::move(other.name_); // Transfer ownership of the name
        data_ = std::move(other.data_); // Transfer ownership of the data
        std::cout << "🚀 ExpensiveObject('" << name_ << "') MOVED efficiently! (no copying, just pointer transfer)\n";
        // Leave 'other' in a valid but empty state
        other.name_.clear(); // Clear the name of the moved-from object
        other.data_.clear(); // Clear the data of the moved-from object 
        std::cout << "🚀 Source object left in empty but valid state\n";
    }
    
    // TODO: Move assignment (efficient)
    ExpensiveObject& operator=(ExpensiveObject&& other) noexcept {
        // Your implementation here
        if (this != &other) { // Self-assignment check
            std::cout << "⚡ ExpensiveObject Move Assignment - Replacing '" << name_ << "' with '" << other.name_ << "'\n";
            name_ = std::move(other.name_); // Transfer ownership of the name
            data_ = std::move(other.data_); // Transfer ownership of the data
            std::cout << "⚡ ExpensiveObject('" << name_ << "') MOVE ASSIGNED efficiently! (no copying, just pointer transfer)\n";
            // Leave 'other' in a valid but empty state
            other.name_.clear(); // Clear the name of the moved-from object
            other.data_.clear(); // Clear the data of the moved-from object 
            std::cout << "⚡ Source object left in empty but valid state\n";
        } else {
            std::cout << "⚡ ExpensiveObject Move Assignment - Self-assignment detected, doing nothing\n";
        }
        return *this;
    }
    
    ~ExpensiveObject() {
        std::cout << "💀 ExpensiveObject('" << name_ << "') destroyed (had " << data_.size() << " elements)\n";
    }
    
    const std::string& getName() const { return name_; }
    size_t getDataSize() const { return data_.size(); }
    
    void setName(const std::string& name) { name_ = name; }
};

// TODO: Implement OptimizedContainer class
template<typename T>
class OptimizedContainer {
private:
    std::vector<T> elements_;
    
public:
    // TODO: Default constructor
    OptimizedContainer() {
        // Your implementation here
        std::cout << "📦 OptimizedContainer created (empty container ready)\n";
    }
    
    // TODO: Copy constructor
    OptimizedContainer(const OptimizedContainer& other) {
        // Your implementation here
        std::cout << "📄 OptimizedContainer COPIED (expensive - copying " << other.elements_.size() << " elements!)\n";
        elements_ = other.elements_; // Copy elements from the other container      
    }
    
    // TODO: Copy assignment
    OptimizedContainer& operator=(const OptimizedContainer& other) {
        // Your implementation here
        if (this != &other) { // Self-assignment check
            std::cout << "📝 OptimizedContainer COPY ASSIGNED (expensive - copying " << other.elements_.size() << " elements!)\n";
            elements_ = other.elements_; // Copy elements from the other container
        }
        return *this;
    }
    
    // TODO: Move constructor
    OptimizedContainer(OptimizedContainer&& other) noexcept {
        // Your implementation here
        std::cout << "🚀 OptimizedContainer MOVED (efficient - transferring " << other.elements_.size() << " elements!)\n";
        elements_ = std::move(other.elements_); // Transfer ownership of the elements
        // Leave 'other' in a valid but empty state
        other.elements_.clear(); // Clear the elements of the moved-from object 
        std::cout << "🚀 Source container left empty, destination now has " << elements_.size() << " elements\n";
    }
    
    // TODO: Move assignment
    OptimizedContainer& operator=(OptimizedContainer&& other) noexcept {
        // Your implementation here
        if (this != &other) { // Self-assignment check
            std::cout << "⚡ OptimizedContainer MOVE ASSIGNED (efficient - transferring " << other.elements_.size() << " elements!)\n";
            elements_ = std::move(other.elements_); // Transfer ownership of the elements
            // Leave 'other' in a valid but empty state
            other.elements_.clear(); // Clear the elements of the moved-from object 
            std::cout << "⚡ Source container left empty, destination now has " << elements_.size() << " elements\n";
        }
        return *this;
    }
    
    // TODO: Add element with perfect forwarding
    template<typename U>
    void add(U&& element) {
        // Your implementation here
        // Hint: Use std::forward to preserve value category
        std::cout << "📥 OptimizedContainer::add() - Adding element using perfect forwarding\n";
        if constexpr (std::is_lvalue_reference_v<U>) {
            std::cout << "📄 Detected lvalue reference - will COPY element (expensive)\n";
        } else {
            std::cout << "🚀 Detected rvalue reference - will MOVE element (efficient)\n";
        }
        elements_.emplace_back(std::forward<U>(element)); // Use emplace_back to add the element
        std::cout << "✅ Element added successfully, current size: " << elements_.size() << std::endl;
    }
    
    // TODO: Emplace element with perfect forwarding of constructor arguments
    template<typename... Args>
    void emplace(Args&&... args) {
        // Your implementation here
        // Hint: Use std::forward and emplace_back
        std::cout << "🏗️ OptimizedContainer::emplace() - Constructing element directly in container\n";
        std::cout << "🏗️ Perfect forwarding " << sizeof...(args) << " constructor arguments\n";
        elements_.emplace_back(std::forward<Args>(args)...); // Use emplace_back to construct the element in place
        std::cout << "✅ Element emplaced directly (most efficient!), current size: " << elements_.size() << std::endl;
    }
    
    // TODO: Access elements
    const T& operator[](size_t index) const {
        // Your implementation here
        if (index >= elements_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return elements_[index]; // Return a const reference to the element at the given index
    }
    
    T& operator[](size_t index) {
        // Your implementation here
        if (index >= elements_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return elements_[index]; // Return a reference to the element at the given index
    }
    
    size_t size() const {
        // Your implementation here
        return elements_.size(); // Return the number of elements in the container
    }
    
    bool empty() const {
        // Your implementation here'
        return elements_.empty(); // Return true if the container is empty
    }
    
    // TODO: Iterator support
    auto begin() -> decltype(elements_.begin()) {
        // Your implementation here
        return elements_.begin(); // Return an iterator to the beginning of the elements
    }
    
    auto end() -> decltype(elements_.end()) {
        // Your implementation here
        return elements_.end(); // Return an iterator to the end of the elements
    }
    
    auto begin() const -> decltype(elements_.begin()) {
        // Your implementation here
        return elements_.begin(); // Return a const iterator to the beginning of the elements
    }
    
    auto end() const -> decltype(elements_.end()) {
        // Your implementation here
        return elements_.end(); // Return a const iterator to the end of the elements
    }
};

// Helper function to create ExpensiveObject
ExpensiveObject createExpensiveObject(const std::string& name) {
    std::cout << "🏭 Helper function creating temporary ExpensiveObject (will be moved efficiently)\n";
    return ExpensiveObject(name, 500);
}

void test_advanced_move_semantics() {
    std::cout << "=== 🚀 RAII Kata #3: Advanced Move Semantics and Perfect Forwarding ===\n";
    std::cout << "This kata demonstrates the performance difference between copying and moving!\n\n";
    
    // Test 1: Basic container operations
    {
        std::cout << "\n🎯 --- Test 1: Basic Operations (Emplace - Most Efficient) ---\n";
        std::cout << "📝 Creating empty container...\n";
        OptimizedContainer<ExpensiveObject> container;
        
        // Test emplace - construct in place
        std::cout << "\n🏗️ Testing emplace() - constructs object DIRECTLY in container:\n";
        container.emplace("direct_construct", 100);
        
        std::cout << "\n📊 Container size: " << container.size() << std::endl;
        std::cout << "✅ Test 1 Complete: Emplace is most efficient - no temporary objects!\n";
    }
    std::cout << "🧹 Test 1 scope ended - container and its contents destroyed\n";
    
    // Test 2: Move vs Copy semantics
    {
        std::cout << "\n--- Test 2: Move vs Copy Semantics ---\n";
        OptimizedContainer<ExpensiveObject> container;
        
        // Add by copy (expensive)
        ExpensiveObject obj1("copy_source", 200);
        std::cout << "\nAdding by copy:\n";
        container.add(obj1);
        
        // Add by move (efficient)
        std::cout << "\nAdding by move:\n";
        container.add(std::move(obj1));
        
        // Add temporary (should be moved)
        std::cout << "\nAdding temporary:\n";
        container.add(createExpensiveObject("temporary"));
        
        std::cout << "Final container size: " << container.size() << std::endl;
    }
    
    // Test 3: Container move semantics
    {
        std::cout << "\n--- Test 3: Container Move Semantics ---\n";
        OptimizedContainer<ExpensiveObject> container1;
        container1.emplace("container1_obj1");
        container1.emplace("container1_obj2");
        
        std::cout << "\nMoving entire container:\n";
        OptimizedContainer<ExpensiveObject> container2 = std::move(container1);
        
        std::cout << "Original container size: " << container1.size() << std::endl;
        std::cout << "New container size: " << container2.size() << std::endl;
    }
    
    // Test 4: Exception safety
    {
        std::cout << "\n--- Test 4: Range-based for loop ---\n";
        OptimizedContainer<ExpensiveObject> container;
        container.emplace("loop_obj1");
        container.emplace("loop_obj2");
        container.emplace("loop_obj3");
        
        for (const auto& obj : container) {
            std::cout << "Object: " << obj.getName() << " (size: " << obj.getDataSize() << ")\n";
        }
    }
    
    std::cout << "\nAll advanced tests completed!\n";
}

int main() {
    test_advanced_move_semantics();
    return 0;
}
