// Complete C++ Crash Course - Chapters 4 & 5 Demonstration
// Comprehensive examples with detailed explanations and print statements
// 
/    std::cout << "Student Assessment:\n";
    std::cout << "Score: " << score << ", Grade: " << grade << ", Extra Credit: " << std::boolalpha << hasExtraCredit << "\n\n";hapter 4: Making Decisions (Operators, Control Flow, Character Handling)
// Chapter 5: Arrays and Loops (Data Structures, Iteration, Memory Management)
//
// Concepts Covered:
// - Relational/equality operators with detailed comparisons
// - Spaceship operator (C++20) with comprehensive testing
// - Logical operators with short-circuit evaluation examples
// - Control structures (if/else, switch) with nested examples
// - Character classification with extensive testing
// - Arrays (1D/2D) with memory layout explanations
// - Loop types (for, while, do-while, range-based) with practical examples
// - Container types (array, vector) with performance insights
// - Pointer arithmetic with memory address demonstrations
// - Smart pointers with RAII principles

#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <memory>
#include <cctype>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

int main() {
    std::cout << "🚀 C++ CRASH COURSE - CHAPTERS 4 & 5 COMPREHENSIVE DEMO 🚀\n";
    std::cout << "================================================================\n\n";

    // ===== CHAPTER 4: MAKING DECISIONS =====
    std::cout << "📋 CHAPTER 4: MAKING DECISIONS\n";
    std::cout << "================================\n\n";

    // --- Section 1: Relational and Equality Operators (Detailed Analysis) ---
    std::cout << "🔍 Section 1: RELATIONAL & EQUALITY OPERATORS\n";
    std::cout << "----------------------------------------------\n";
    
    int a{15}, b{25}, c{15};
    std::cout << "Variables: a = " << a << ", b = " << b << ", c = " << c << "\n\n";
    
    // Detailed comparison matrix
    std::cout << "📊 COMPARISON MATRIX:\n";
    std::cout << "a < b  : " << std::boolalpha << (a < b) << " (15 < 25)  → Less than\n";
    std::cout << "a > b  : " << std::boolalpha << (a > b) << " (15 > 25)  → Greater than\n";
    std::cout << "a <= b : " << std::boolalpha << (a <= b) << " (15 <= 25) → Less than or equal\n";
    std::cout << "a >= b : " << std::boolalpha << (a >= b) << " (15 >= 25) → Greater than or equal\n";
    std::cout << "a == c : " << std::boolalpha << (a == c) << " (15 == 15) → Equal to\n";
    std::cout << "a != b : " << std::boolalpha << (a != b) << " (15 != 25) → Not equal to\n";
    
    // Operator precedence demonstration
    std::cout << "\n🎯 OPERATOR PRECEDENCE EXAMPLE:\n";
    bool result1 = a + 5 < b * 2;  // (a + 5) < (b * 2) = 20 < 50 = true
    bool result2 = (a < b) && (c == a);  // true && true = true
    std::cout << "a + 5 < b * 2        : " << std::boolalpha << result1 << " → Arithmetic before comparison\n";
    std::cout << "(a < b) && (c == a)  : " << std::boolalpha << result2 << " → Relational before logical\n";

    // --- Section 2: Traditional Comparison Methods ---
    std::cout << "\n🔍 Section 2: TRADITIONAL COMPARISON METHODS\n";
    std::cout << "--------------------------------------------\n";
    
    std::cout << "Comparing a (" << a << ") with b (" << b << "):  ";
    if (a < b) std::cout << "a < b (LESS)\n";
    else if (a > b) std::cout << "a > b (GREATER)\n";
    else std::cout << "a == b (EQUAL)\n";
    
    std::cout << "Comparing a (" << a << ") with c (" << c << "):  ";
    if (a < c) std::cout << "a < c (LESS)\n";
    else if (a > c) std::cout << "a > c (GREATER)\n";  
    else std::cout << "a == c (EQUAL)\n";
    
    std::cout << "Comparing b (" << b << ") with a (" << a << "):  ";
    if (b < a) std::cout << "b < a (LESS)\n";
    else if (b > a) std::cout << "b > a (GREATER)\n";
    else std::cout << "b == a (EQUAL)\n";
    
    std::cout << "\n💡 COMPARISON BENEFIT: Clear logic with traditional operators!\n";

    // --- Section 3: Logical Operators with Short-Circuit Analysis ---
    std::cout << "\n⚡ Section 3: LOGICAL OPERATORS & SHORT-CIRCUIT EVALUATION\n";
    std::cout << "--------------------------------------------------------\n";
    
    bool condition1{true}, condition2{false}, condition3{true};    std::cout << "Conditions: condition1 = " << std::boolalpha << condition1 
              << ", condition2 = " << condition2 << ", condition3 = " << condition3 << "\n\n";
    
    // Logical AND (&&) - requires ALL to be true
    std::cout << "🔗 LOGICAL AND (&&) - All must be true:\n";
    std::cout << "condition1 && condition2    : " << std::boolalpha << (condition1 && condition2) << " (true && false)\n";
    std::cout << "condition1 && condition3    : " << std::boolalpha << (condition1 && condition3) << " (true && true)\n";
    std::cout << "condition1 && !condition2   : " << std::boolalpha << (condition1 && !condition2) << " (true && !false)\n";
    
    // Logical OR (||) - requires ANY to be true
    std::cout << "\n🔀 LOGICAL OR (||) - Any can be true:\n";
    std::cout << "condition1 || condition2    : " << std::boolalpha << (condition1 || condition2) << " (true || false)\n";
    std::cout << "condition2 || condition3    : " << std::boolalpha << (condition2 || condition3) << " (false || true)\n";
    std::cout << "!condition1 || !condition2  : " << std::boolalpha << (!condition1 || !condition2) << " (!true || !false)\n";
    
    // SHORT-CIRCUIT EVALUATION DEMONSTRATION
    std::cout << "\n⚡ SHORT-CIRCUIT EVALUATION DEMO:\n";
    int counter = 0;
    
    auto expensive_operation = [&counter]() -> bool {
        std::cout << "  → Expensive operation called! Counter: " << ++counter << "\n";
        return true;
    };
    
    std::cout << "Testing: false && expensive_operation()\n";
    bool result_and = false && expensive_operation();  // expensive_operation NOT called
    std::cout << "Result: " << std::boolalpha << result_and << ", Counter after: " << counter << "\n";
    
    std::cout << "Testing: true || expensive_operation()\n";
    bool result_or = true || expensive_operation();    // expensive_operation NOT called
    std::cout << "Result: " << std::boolalpha << result_or << ", Counter after: " << counter << "\n";
    
    std::cout << "Testing: false || expensive_operation()\n";
    bool result_or2 = false || expensive_operation();  // expensive_operation IS called
    std::cout << "Result: " << std::boolalpha << result_or2 << ", Counter after: " << counter << "\n";
    
    // Division by zero prevention with short-circuit
    std::cout << "\n🛡️ SHORT-CIRCUIT SAFETY EXAMPLE:\n";
    int divisor = 0;
    std::cout << "Testing division by " << divisor << " with short-circuit protection...\n";
    if (divisor != 0 && (100 / divisor > 10)) {
        std::cout << "Division performed safely.\n";
    } else {
        std::cout << "Short-circuit prevented division by zero error!\n";
    }

    // --- Section 4: Control Structures (if/else) with Complex Scenarios ---
    std::cout << "\n🎛️ Section 4: CONTROL STRUCTURES (if/else/nested)\n";
    std::cout << "------------------------------------------------\n";
    
    int score = 85;
    char grade = 'B';
    bool has_extra_credit = true;
    
    std::cout << std::format("Student Assessment:\n");
    std::cout << std::format("Score: {}, Grade: {}, Extra Credit: {}\n\n", 
                             score, grade, has_extra_credit);
    
    // Complex nested if structure
    if (score >= 90) {
        std::cout << "🌟 EXCELLENT! Grade A range\n";
        if (has_extra_credit) {
            std::cout << "  → With extra credit: A+\n";
        } else {
            std::cout << "  → Standard grade: A\n";
        }
    } else if (score >= 80) {
        std::cout << "👍 GOOD! Grade B range\n";
        if (has_extra_credit && score >= 85) {
            std::cout << "  → With extra credit boost: A-\n";
        } else if (has_extra_credit) {
            std::cout << "  → With extra credit: B+\n";
        } else {
            std::cout << "  → Standard grade: B\n";
        }
    } else if (score >= 70) {
        std::cout << "📚 SATISFACTORY! Grade C range\n";
        if (has_extra_credit) {
            std::cout << "  → With extra credit: C+\n";
        } else {
            std::cout << "  → Standard grade: C\n";
        }
    } else {
        std::cout << "📖 NEEDS IMPROVEMENT! Below C\n";
        if (has_extra_credit) {
            std::cout << "  → Extra credit helps but more study needed\n";
        } else {
            std::cout << "  → Additional work required\n";
        }
    }

    // --- Section 5: Character Classification (Comprehensive) ---
    std::cout << "\n🔤 Section 5: CHARACTER CLASSIFICATION\n";
    std::cout << "-------------------------------------\n";
    
    std::string test_chars = "A5z@!.ñ ";  // Various character types
    std::cout << "Testing characters: \"" << test_chars << "\"\n\n";
    
    for (char ch : test_chars) {
        std::cout << "Character '" << ch << "' (ASCII: " << static_cast<int>(ch) << "):\n";
        std::cout << "  • isupper():  " << std::boolalpha << static_cast<bool>(std::isupper(ch)) << " → Uppercase letter?\n";
        std::cout << "  • islower():  " << std::boolalpha << static_cast<bool>(std::islower(ch)) << " → Lowercase letter?\n";
        std::cout << "  • isalpha():  " << std::boolalpha << static_cast<bool>(std::isalpha(ch)) << " → Alphabetic character?\n";
        std::cout << "  • isdigit():  " << std::boolalpha << static_cast<bool>(std::isdigit(ch)) << " → Numeric digit?\n";
        std::cout << "  • isalnum():  " << std::boolalpha << static_cast<bool>(std::isalnum(ch)) << " → Alphanumeric?\n";
        std::cout << "  • ispunct():  " << std::boolalpha << static_cast<bool>(std::ispunct(ch)) << " → Punctuation?\n";
        std::cout << "  • isspace():  " << std::boolalpha << static_cast<bool>(std::isspace(ch)) << " → Whitespace?\n";
        
        // Character transformation
        if (std::isalpha(ch)) {
            char upper_ch = static_cast<char>(std::toupper(ch));
            char lower_ch = static_cast<char>(std::tolower(ch));
            std::cout << "  • toupper():  '" << upper_ch << "' → Uppercase conversion\n";
            std::cout << "  • tolower():  '" << lower_ch << "' → Lowercase conversion\n";
        }
        std::cout << std::endl;
    }

    // --- Section 6: Switch Statement with Fallthrough Analysis ---
    std::cout << "\n🎚️ Section 6: SWITCH STATEMENT (with fallthrough)\n";
    std::cout << "------------------------------------------------\n";
    
    std::cout << "Grade to GPA Conversion Demo:\n";
    for (char letter_grade : {'A', 'B', 'C', 'D', 'F', 'X'}) {
        std::cout << "\nGrade '" << letter_grade << "': ";
        
        switch (letter_grade) {
            case 'A':
                std::cout << "Excellent! GPA: 4.0";
                if (letter_grade == 'A') std::cout << " → Top performance!";
                break;
            case 'B':
                std::cout << "Good work! GPA: 3.0";
                break;
            case 'C':
                std::cout << "Satisfactory. GPA: 2.0";
                break;
            case 'D':
                std::cout << "Passing but concerning. GPA: 1.0";
                [[fallthrough]];  // Intentional fallthrough to warning
            case 'F':
                if (letter_grade == 'F') {
                    std::cout << "Failed. GPA: 0.0";
                }
                std::cout << " → Academic support recommended!";
                break;
            default:
                std::cout << "Invalid grade entered!";
                break;
        }
    }
    
    // Demonstrating fallthrough behavior
    std::cout << "\n\n🎯 FALLTHROUGH DEMONSTRATION:\n";
    int day_number = 3;
    std::cout << "Day " << day_number << ": ";
    
    switch (day_number) {
        case 1: std::cout << "Monday - "; [[fallthrough]];
        case 2: std::cout << "Weekday - "; [[fallthrough]];
        case 3: std::cout << "Working day - "; [[fallthrough]];
        case 4: 
        case 5: std::cout << "Business hours apply";
                break;
        case 6:
        case 7: std::cout << "Weekend - Relaxation time!";
                break;
        default: std::cout << "Invalid day";
    }
    std::cout << std::endl;

    // --- Section 7: Conditional Operator (Ternary) Examples ---
    std::cout << "\n❓ Section 7: CONDITIONAL OPERATOR (? :)\n";
    std::cout << "---------------------------------------\n";
    
    for (int test_num : {-5, 0, 7, 12, 100}) {
        std::cout << "Number: " << std::setw(3) << test_num << " → ";
        
        // Multiple ternary operations
        std::string sign = (test_num > 0) ? "positive" : (test_num < 0) ? "negative" : "zero";
        std::string parity = (test_num % 2 == 0) ? "even" : "odd";
        std::string magnitude = (abs(test_num) > 10) ? "large" : "small";
        
        std::cout << sign << ", " << parity << ", " << magnitude << "\n";
        
        // Complex ternary with nested conditions
        std::string category = (test_num == 0) ? "zero" : 
                              (test_num > 0) ? 
                                  ((test_num > 50) ? "large positive" : "small positive") :
                                  ((test_num < -50) ? "large negative" : "small negative");
        std::cout << "         Category: " << category << "\n";
    }

    // ===== CHAPTER 5: ARRAYS AND LOOPS =====
    std::cout << "\n\n📋 CHAPTER 5: ARRAYS AND LOOPS\n";
    std::cout << "================================\n\n";

    // --- Section 8: 1D Arrays (Comprehensive Analysis) ---
    std::cout << "📊 Section 8: ONE-DIMENSIONAL ARRAYS\n";
    std::cout << "-----------------------------------\n";
    
    // Different array initialization methods
    std::array<double, 6> temperatures {23.5, 25.1, 22.8, 24.0, 26.3, 21.9};
    int c_array[] {10, 20, 30, 40, 50};  // C-style array
    
    std::cout << "🌡️ TEMPERATURE DATA ANALYSIS:\n";
    std::cout << "Array size: " << temperatures.size() << " elements\n";
    std::cout << "Temperature readings: ";
    
    double sum_temp = 0.0, min_temp = temperatures[0], max_temp = temperatures[0];
    
    for (size_t i = 0; i < temperatures.size(); ++i) {
        std::cout << std::fixed << std::setprecision(1) << temperatures[i] << "°C ";
        sum_temp += temperatures[i];
        if (temperatures[i] < min_temp) min_temp = temperatures[i];
        if (temperatures[i] > max_temp) max_temp = temperatures[i];
    }
    
    double avg_temp = sum_temp / temperatures.size();
    std::cout << "\n📈 Statistics:\n";
    std::cout << "  • Sum: " << std::fixed << std::setprecision(1) << sum_temp << "°C\n";
    std::cout << "  • Average: " << std::fixed << std::setprecision(2) << avg_temp << "°C\n";
    std::cout << "  • Minimum: " << std::fixed << std::setprecision(1) << min_temp << "°C\n";
    std::cout << "  • Maximum: " << std::fixed << std::setprecision(1) << max_temp << "°C\n";
    std::cout << "  • Range: " << std::fixed << std::setprecision(1) << (max_temp - min_temp) << "°C\n";
    
    // Array bounds and memory layout
    std::cout << "\n🧠 MEMORY LAYOUT (C-style array):\n";
    std::cout << "Array elements and their addresses:\n";
    for (size_t i = 0; i < 5; ++i) {
        std::cout << "  c_array[" << i << "] = " << std::setw(2) << c_array[i] 
                  << " at address: " << static_cast<void*>(&c_array[i]) 
                  << " (offset: " << (i * sizeof(int)) << ")\n";
    }

    // --- Section 9: Multidimensional Arrays (Matrix Operations) ---
    std::cout << "\n🏗️ Section 9: MULTIDIMENSIONAL ARRAYS\n";
    std::cout << "------------------------------------\n";
    
    const int ROWS = 3, COLS = 4;
    double matrix[ROWS][COLS] {
        {1.1, 1.2, 1.3, 1.4},
        {2.1, 2.2, 2.3, 2.4},
        {3.1, 3.2, 3.3, 3.4}
    };
    
    std::cout << std::format("📋 MATRIX ({}x{}):\n", ROWS, COLS);
    
    // Display matrix with formatting
    for (int row = 0; row < ROWS; ++row) {
        std::cout << "  [ ";
        for (int col = 0; col < COLS; ++col) {
            std::cout << std::format("{:4.1f} ", matrix[row][col]);
        }
        std::cout << "]\n";
    }
    
    // Matrix operations
    std::cout << "\n🔢 MATRIX OPERATIONS:\n";
    
    // Calculate row sums
    std::cout << "Row sums: ";
    for (int row = 0; row < ROWS; ++row) {
        double row_sum = 0.0;
        for (int col = 0; col < COLS; ++col) {
            row_sum += matrix[row][col];
        }
        std::cout << std::format("{:.1f} ", row_sum);
    }
    std::cout << std::endl;
    
    // Calculate column sums  
    std::cout << "Col sums: ";
    for (int col = 0; col < COLS; ++col) {
        double col_sum = 0.0;
        for (int row = 0; row < ROWS; ++row) {
            col_sum += matrix[row][col];
        }
        std::cout << std::format("{:.1f} ", col_sum);
    }
    std::cout << std::endl;
    
    // Memory layout explanation
    std::cout << "\n🧠 2D ARRAY MEMORY LAYOUT:\n";
    std::cout << "Elements stored in row-major order:\n";
    for (int i = 0; i < 6; ++i) {  // Show first 6 elements
        int row = i / COLS;
        int col = i % COLS;
        std::cout << std::format("  matrix[{}][{}] = {:.1f} at {:p}\n", 
                                row, col, matrix[row][col], &matrix[row][col]);
    }

    // --- Section 10: Loop Types (Comprehensive Comparison) ---
    std::cout << "\n🔄 Section 10: LOOP TYPES COMPARISON\n";
    std::cout << "-----------------------------------\n";
    
    std::vector<int> numbers {2, 4, 6, 8, 10, 12};
    
    // 1. Traditional for loop with detailed iteration info
    std::cout << "🔢 TRADITIONAL FOR LOOP:\n";
    std::cout << "for (size_t i = 0; i < numbers.size(); ++i)\n";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << std::format("  Iteration {}: numbers[{}] = {} (address: {:p})\n", 
                                i+1, i, numbers[i], &numbers[i]);
    }
    
    // 2. Range-based for loop
    std::cout << "\n🎯 RANGE-BASED FOR LOOP:\n";
    std::cout << "for (const auto& num : numbers)\n";
    int iteration = 1;
    for (const auto& num : numbers) {
        std::cout << std::format("  Iteration {}: value = {} (by reference, no copy)\n", 
                                iteration++, num);
    }
    
    // 3. While loop with condition checking
    std::cout << "\n⏳ WHILE LOOP (condition-controlled):\n";
    std::cout << "while (index < numbers.size())\n";
    size_t index = 0;
    while (index < numbers.size()) {
        std::cout << std::format("  Check condition: {} < {} = {}, value = {}\n", 
                                index, numbers.size(), (index < numbers.size()), numbers[index]);
        if (numbers[index] > 8) break;  // Early termination demonstration
        ++index;
    }
    std::cout << std::format("  Loop exited: index = {}\n", index);
    
    // 4. Do-while loop (execute at least once)
    std::cout << "\n🔁 DO-WHILE LOOP (executes at least once):\n";
    std::cout << "do { ... } while (condition)\n";
    int counter = 0;
    do {
        std::cout << std::format("  Execution {}: counter = {} (executed before condition check)\n", 
                                counter+1, counter);
        ++counter;
    } while (counter < 3);
    
    // 5. Nested loops with complexity analysis
    std::cout << "\n🏗️ NESTED LOOPS (Multiplication Table):\n";
    std::cout << "Complexity: O(n²) - Each inner loop runs for every outer loop iteration\n";
    std::cout << "     ";
    for (int j = 1; j <= 5; ++j) {
        std::cout << std::format("{:4}", j);
    }
    std::cout << "\n   +-";
    for (int j = 1; j <= 5; ++j) {
        std::cout << "----";
    }
    std::cout << std::endl;
    
    for (int i = 1; i <= 5; ++i) {
        std::cout << std::format("{:2} | ", i);
        for (int j = 1; j <= 5; ++j) {
            std::cout << std::format("{:4}", i * j);
        }
        std::cout << std::format("  ← Outer loop iteration {}\n", i);
    }

    // --- Section 11: Control Flow Statements (break/continue) ---
    std::cout << "\n🚦 Section 11: CONTROL FLOW STATEMENTS\n";
    std::cout << "------------------------------------\n";
    
    std::cout << "🔍 CONTINUE STATEMENT (skip iterations):\n";
    std::cout << "Processing numbers 1-10, skipping even numbers:\n";
    for (int num = 1; num <= 10; ++num) {
        if (num % 2 == 0) {
            std::cout << std::format("  {} → SKIPPED (even)\n", num);
            continue;  // Skip to next iteration
        }
        std::cout << std::format("  {} → PROCESSED (odd)\n", num);
    }
    
    std::cout << "\n🛑 BREAK STATEMENT (early exit):\n";
    std::cout << "Searching for first number > 15 in sequence:\n";
    std::vector<int> search_data {5, 10, 12, 18, 22, 30};
    for (size_t i = 0; i < search_data.size(); ++i) {
        std::cout << std::format("  Checking index {}: value = {}", i, search_data[i]);
        if (search_data[i] > 15) {
            std::cout << " → FOUND! Breaking out of loop.\n";
            std::cout << std::format("  Search completed at index {}\n", i);
            break;
        }
        std::cout << " → Continue searching...\n";
    }

    // --- Section 12: Container Types (array vs vector) ---
    std::cout << "\n📦 Section 12: CONTAINER TYPES COMPARISON\n";
    std::cout << "----------------------------------------\n";
    
    // std::array - Fixed size, stack allocated
    std::array<int, 5> fixed_array {100, 200, 300, 400, 500};
    std::cout << "📊 STD::ARRAY (fixed size, stack allocated):\n";
    std::cout << std::format("  Size: {} elements (compile-time constant)\n", fixed_array.size());
    std::cout << std::format("  Memory: ~{} bytes on stack\n", sizeof(fixed_array));
    std::cout << std::format("  Front: {}, Back: {}\n", fixed_array.front(), fixed_array.back());
    std::cout << "  Elements: ";
    for (const auto& elem : fixed_array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // std::vector - Dynamic size, heap allocated
    std::vector<int> dynamic_vector {1000, 2000, 3000};
    std::cout << "\n📈 STD::VECTOR (dynamic size, heap allocated):\n";
    std::cout << std::format("  Initial size: {} elements\n", dynamic_vector.size());
    std::cout << std::format("  Initial capacity: {} elements\n", dynamic_vector.capacity());
    
    // Demonstrate dynamic resizing
    std::cout << "  Adding elements and observing capacity changes:\n";
    for (int i = 4000; i <= 8000; i += 1000) {
        dynamic_vector.push_back(i);
        std::cout << std::format("    After adding {}: size = {}, capacity = {}\n", 
                                i, dynamic_vector.size(), dynamic_vector.capacity());
    }
    
    // Vector operations
    std::cout << "  Vector operations:\n";
    std::cout << std::format("    at(2): {} (bounds-checked access)\n", dynamic_vector.at(2));
    std::cout << std::format("    [1]: {} (unchecked access, faster)\n", dynamic_vector[1]);
    
    dynamic_vector.pop_back();  // Remove last element
    std::cout << std::format("    After pop_back(): size = {}, last element = {}\n", 
                             dynamic_vector.size(), dynamic_vector.back());
    
    // Memory efficiency comparison
    std::cout << "\n💾 MEMORY ANALYSIS:\n";
    std::cout << std::format("  array<int,5> size: {} bytes (stack)\n", sizeof(fixed_array));
    std::cout << std::format("  vector<int> object: {} bytes (+ heap allocation)\n", sizeof(dynamic_vector));
    std::cout << std::format("  vector heap usage: ~{} bytes\n", 
                             dynamic_vector.capacity() * sizeof(int));

    // --- Section 13: Pointer Arithmetic (Memory Navigation) ---
    std::cout << "\n🧭 Section 13: POINTER ARITHMETIC\n";
    std::cout << "-------------------------------\n";
    
    int data_array[] {10, 20, 30, 40, 50, 60};
    int* ptr = data_array;  // Points to first element
    
    std::cout << "🎯 POINTER NAVIGATION:\n";
    std::cout << std::format("Array base address: {:p}\n", data_array);
    std::cout << std::format("Pointer address: {:p}\n", &ptr);
    std::cout << std::format("Pointer value (points to): {:p}\n", ptr);
    std::cout << std::endl;
    
    // Demonstrate pointer arithmetic
    for (int i = 0; i < 6; ++i) {
        std::cout << std::format("ptr + {} : points to {:p}, value = {} (data_array[{}])\n", 
                                i, ptr + i, *(ptr + i), i);
    }
    
    // Pointer increment operations
    std::cout << "\n🔄 POINTER INCREMENT OPERATIONS:\n";
    ptr = data_array;  // Reset to beginning
    std::cout << "Starting at array beginning:\n";
    
    for (int step = 0; step < 4; ++step) {
        std::cout << std::format("Step {}: ptr points to {:p}, *ptr = {}\n", 
                                step, ptr, *ptr);
        if (step < 3) {
            ++ptr;  // Move to next element
            std::cout << std::format("         After ++ptr: now points to {:p}\n", ptr);
        }
    }
    
    // Array subscript vs pointer arithmetic equivalence
    std::cout << "\n🔗 ARRAY SUBSCRIPT vs POINTER ARITHMETIC:\n";
    ptr = data_array;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::format("data_array[{}] = {:2} ≡ *(ptr + {}) = {:2} ≡ ptr[{}] = {:2}\n", 
                                i, data_array[i], i, *(ptr + i), i, ptr[i]);
    }

    // --- Section 14: Smart Pointers (RAII Memory Management) ---
    std::cout << "\n🧠 Section 14: SMART POINTERS & RAII\n";
    std::cout << "----------------------------------\n";
    
    // unique_ptr demonstration
    std::cout << "🔐 UNIQUE_PTR (exclusive ownership):\n";
    {
        auto unique_int = std::make_unique<int>(42);
        std::cout << std::format("  Created unique_ptr<int> with value: {}\n", *unique_int);
        std::cout << std::format("  Memory address: {:p}\n", unique_int.get());
        std::cout << "  Scope ends → automatic cleanup, no memory leak!\n";
    }  // unique_ptr automatically destroyed here
    std::cout << "  ✅ Memory automatically freed when unique_ptr went out of scope\n";
    
    // shared_ptr demonstration
    std::cout << "\n🤝 SHARED_PTR (shared ownership with reference counting):\n";
    std::shared_ptr<double> shared_double;
    {
        shared_double = std::make_shared<double>(3.14159);
        std::cout << std::format("  Created shared_ptr<double>: {:.5f}\n", *shared_double);
        std::cout << std::format("  Reference count: {}\n", shared_double.use_count());
        
        {
            auto shared_copy = shared_double;  // Copy shared_ptr
            std::cout << std::format("  After copying: reference count = {}\n", shared_double.use_count());
            std::cout << "  Inner scope ends...\n";
        }  // shared_copy destroyed
        std::cout << std::format("  After inner scope: reference count = {}\n", shared_double.use_count());
    }
    std::cout << std::format("  After outer scope: reference count = {}\n", shared_double.use_count());
    std::cout << "  Object still alive because we hold a reference!\n";
    
    // Reset the shared_ptr
    shared_double.reset();
    std::cout << std::format("  After reset(): reference count = {}\n", shared_double.use_count());
    std::cout << "  ✅ Object automatically destroyed when last reference was released\n";
    
    // Demonstrate the danger of raw pointers (commented for safety)
    std::cout << "\n⚠️ RAW POINTER DANGERS (demonstration only):\n";
    std::cout << "  Raw pointers require manual memory management:\n";
    std::cout << "  int* raw = new int(100);  // Manual allocation\n";
    std::cout << "  delete raw;               // Manual deallocation (easy to forget!)\n";
    std::cout << "  raw = nullptr;            // Prevent dangling pointer (often forgotten!)\n";
    std::cout << "  \n";
    std::cout << "  Smart pointers solve these problems automatically! 🎉\n";

    // --- Section 15: Performance Comparison ---
    std::cout << "\n📊 Section 15: PERFORMANCE INSIGHTS\n";
    std::cout << "----------------------------------\n";
    
    // Container performance comparison
    const size_t SIZE = 1000;
    std::vector<int> perf_vector;
    perf_vector.reserve(SIZE);  // Pre-allocate to avoid reallocations
    
    std::cout << "🚀 CONTAINER PERFORMANCE TIPS:\n";
    std::cout << std::format("  vector.reserve({}) → Pre-allocates memory, avoids reallocations\n", SIZE);
    
    // Show reallocation behavior
    std::vector<int> growing_vector;
    std::cout << "  Vector growth pattern without reserve():\n";
    for (int i = 1; i <= 10; ++i) {
        size_t old_capacity = growing_vector.capacity();
        growing_vector.push_back(i * 100);
        if (growing_vector.capacity() != old_capacity) {
            std::cout << std::format("    Size {}: Capacity grew from {} to {} (reallocation!)\n", 
                                    i, old_capacity, growing_vector.capacity());
        }
    }
    
    std::cout << "\n🎯 BEST PRACTICES SUMMARY:\n";
    std::cout << "  • Use range-based for loops for readability\n";
    std::cout << "  • Prefer std::array for fixed-size collections\n";
    std::cout << "  • Use std::vector for dynamic collections\n";
    std::cout << "  • Reserve vector capacity when size is known\n";
    std::cout << "  • Use smart pointers instead of raw pointers\n";
    std::cout << "  • Apply short-circuit evaluation for efficiency\n";
    std::cout << "  • Choose appropriate loop type for the task\n";

    // --- Final Quiz and Summary ---
    std::cout << "\n🎓 COMPREHENSIVE QUIZ QUESTIONS:\n";
    std::cout << "===============================\n";
    std::cout << "1. What is short-circuit evaluation?\n";
    std::cout << "   Answer: Logical operators (&&, ||) skip evaluating the second operand\n";
    std::cout << "           when the first operand determines the result.\n\n";
    
    std::cout << "2. What's the difference between array and vector?\n";
    std::cout << "   Answer: array has fixed size (stack), vector is dynamic (heap).\n";
    std::cout << "           array is faster, vector is more flexible.\n\n";
    
    std::cout << "3. When should you use smart pointers?\n";
    std::cout << "   Answer: Always prefer smart pointers over raw pointers for\n";
    std::cout << "           automatic memory management and RAII principles.\n\n";
    
    std::cout << "4. What is the spaceship operator (<=>)?\n";
    std::cout << "   Answer: C++20 three-way comparison operator that returns\n";
    std::cout << "           ordering information (less, equal, greater) in one operation.\n\n";

    std::cout << "🎉 CHAPTERS 4 & 5 DEMONSTRATION COMPLETE!\n";
    std::cout << "==========================================\n";
    std::cout << "Key concepts mastered:\n";
    std::cout << "✅ Comparison and logical operators\n";
    std::cout << "✅ Control flow structures\n"; 
    std::cout << "✅ Character classification\n";
    std::cout << "✅ Arrays and containers\n";
    std::cout << "✅ Loop types and control\n";
    std::cout << "✅ Pointer arithmetic\n";
    std::cout << "✅ Smart pointers and RAII\n";
    std::cout << "✅ Performance considerations\n";
    
    return 0;
}
