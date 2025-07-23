Precedence and associativity of operators

- most of them are left just conditional oeprators are having right associativity 



ex. 
before the precedence 

x*y/z - b + c - d

after as * , / has is higher and + / - are left associative so hence the below expression:

((((x*y)/z) - b) + c) - d



bitwise operators

>> operator shifts bits to the right

<< operator shift bits to the left

number >>=2;  is similar to number = static_cast<unsigned short>(number >> 2);


 so shifting right two bits effectively divides the value by 4. As long as bits aren’t
lost, shifting n bits to the left is equivalent to multiplying by 2, n times. In other words, it’s equivalent to
multiplying by 2n. Similarly, shifting right n bits is equivalent to dividing by 2n. But beware: as you saw with
the left shift of number, if significant bits are lost, the result is nothing like what you would expect. However,
this is not different from the “real” multiply operation. If you multiplied the 2-byte number by 4, you would
get the same result, so shifting left and multiplying are still equivalent. The incorrect result arises because
the result of the multiplication is outside the range of a 2-byte integer

need to understnad this better

std::cout << number<<2 << std::endl;
163872

std::cout << (number<<2) << std::endl;
65548

std::cout << static_cast<unsigned short>(number<<2) << std::endl; 
12

explakn  the reason okay

shifted signed integers are little confusing


Chapter 3 ■ Working With Fundamental data types
77
■ Tip do not use signed integer types (or char) if your goal is to manipulate the bits of binary data.
this avoids the high-order bit from being propagated. also, for this and similar reasons, you should use the
std::byte type over unsigned char to manipulate binary data (std::byte is defined by the <cstddef>
module as of C++17).


~ is bitwise complement operator
& AND ( 1 1 = 1)
^ XOR  ( 1 1 = 0)
| OR

~ > & > ^ > | ( order of precedence or priority)


Using the Bitwise AND
You’ll typically use the bitwise AND operator to select particular bits or groups of bits in an integer value.
Suppose you are using a 16-bit integer to store the point size, the style of a font, and whether it is bold and/
or italic, as we illustrated in Figure 3-1. Suppose further that you want to define and initialize a variable to
specify a 12-point, italic, style 6 font (in fact, the very same one illustrated in Figure 3-1). In binary, the style
will be 00000110 (binary 6), the italic bit will be 1, the bold bit will be 0, and the size will be 01100 (binary
12). Remembering that there’s an unused bit as well, you need to initialize the value of the font variable to
the binary number 0000 0110 0100 1100. Because groups of four bits correspond to a hexadecimal digit, the
most compact way to do this is to specify the initial value in hexadecimal notation:
unsigned short font {0x064C}; // Style 6, italic, 12 point
Of course, ever since C++14 you also have the option to simply use a binary literal instead:
unsigned short font {0b00000110'0'10'01100}; // Style 6, italic, 12 point
Note the creative use of the digit grouping character here to signal the borders of the style, italic/bold,
and point size components.
To work with the size afterward, you need to extract it from the font variable; the bitwise AND operator
will enable you to do this. Because bitwise AND produces one bit only when both bits are 1, you can define a
value that will “select” the bits defining the size when you AND it with font. You need to define a value that
contains 1s in the bit positions that you’re interested in and 0s in all the others. This kind of value is called a
mask, and you can define such a mask with one of these statements (both are equivalent):
unsigned short size_mask {0x1F}; // unsigned short size_mask {0b11111};
The five low-order bits of font represent its size, so you set these bits to 1. The remaining bits are 0, so
they will be discarded. (Binary 0000 0000 0001 1111 is hexadecimal 1F.)
You can now extract the point size from font with the following statement:
auto size {static_cast<unsigned short>( font & size_mask )};
Where both corresponding bits are 1 in an & operation, the resultant bit is 1. Any other combination of
bits results in 0. The values therefore combine l

i didn't understand any of the bitwise AND theory and also what is 0x063X or 0x1F what are all these

help me out!!!
There’s an import declaration for the <format> module because the code uses std::format() to
conveniently display all values as hexadecimal values. To make it easier to compare output values, we also
arrange for them to have the same number of digits and leading zeros using the {:08X} replacement fields
throughout the program. Their 0 prefixes set the fill character to '0', the 8s toggle the field width, and the
X suffixes result in integers being formatted using hexadecimal notation with uppercase letters. If you use x
instead of X, the integers will be formatted using lowercase hexadecimal digits.
To see the effect of the 0 and X components of the {:08X} replacement fields, you can for instance
replace the replacement field in the "Initial value" output statement as follows:
std::cout << std::format("Initial value: red = {:8x}\n", red); // {:08X} --> {:8x}

e local automatic variable of that name. To access the
global value1, you must qualify it with the scope resolution operator, ::. Here’s how you could output the
values of the local and global variables that have the name value1:
std::cout << "Global value1 = " << ::value1 << std::endl;
std::cout << "Local value1 = " << value1 << std::endl;


this was cool

compile-time constants, that is, constant expressions that the compiler can evaluate. Such expressions
include literals, enumerators that have been defined previously, and variables that you’ve specified as const.
You can’t use non-const variables, even if you’ve initialized them using a literal.
The enumerators can be an integer type that you choose, rather than the default type int. You can also
assign explicit values to all the enumerators. For example, you could define this enumeration:
enum class Punctuation : char {Comma = ',', Exclamation = '!', Question='?'};
The type specification for the enumerators goes after the enumeration type name 

i dont understand const and non const literal




precedence is like order or priority 
associativit is like if they have same precedence then it decides left -> right or right -> left

*/ > +-
+,- is left and ?: is right


Can you take 5 minuties quiz back and forth asking all the questions for a exam about these topics be creative and make sure you keep it difficult so that you can check that i have understood the toipic quite well enough okay

???

What's the difference between signed and unsigned? Example: Why use unsigned short for bits?

I think signed 
has ( 1 as negative coz of order precedence )
unsigned are ususally used because of doing bit manipulation
also where do we use these bit operations in real life

for signed we need to use std::byte from cstddef lib

: Arithmetic can overflow; unsigned wraps around, signed is undefined behavior.

so why do we overflow why can't we enough memoery or change its datatype 
WHAT IS UNSIgned wraps aeround mean signed is undefined behavior in what sense

x * y / z - b + c - d → Groups as ((((x * y) / z) - b) + c) - d

* > = and -

how should i remember the order preceddence and associavtibvy its so easy to forget the order

also real life examples

<< - 2^m  >> - 1/2^n
shifts on signed can propogate singed bit so bits lost 

so how to print exact output of a singed short << 2 ??

got a understanding of how hex to binary is done but sometimes

if the left bits are empty then i shouldkeep it 0000 

also 4 bits are one byte and how much is int short unsigneed cnayou gie me that table and also explain this bit byte memory terms better make me clear about these topcis

Tip: Use std::byte over unsigned char for binary (avoids sign issues, C++17 <cstddef>).

i thought the reverse as unsigned can work normally but singed we need to use the std byte right?????


Explain 0x064C in binary and how & mask works. Why avoid signed for bits?

0X064C -> 0 x 0 , 0x6 , 0x4 , 0x C into binary

16 bit

0000 0110 0100 1100

mask is and operation where you want to focus on particukar bits like you have a list of font sizes or names using 5 bits so we try to extract those bits or information using AND operation to verify if the string is of this font name 


one small doubt why can't we just count the value and understand the font size from that or name from that

??

also singed bits are messed up coz they consider negative as 1 which is oopposite for the bit conversion with bit manipulations and  i odnt know how can we do for the signed variabes the??



Logical: &&, ||, !. Short-circuit evaluation.

whats this ?? short-circuit evaluation ??

i understand enum are like custom classes where we define out own data type with some number of acceptable variables

explain me with real life examples not the day or something normal

struct vs enum vs class help  me out

scope is pretty good

global is where we initialize at the beginning or gloabl ususally ahs zero value withotu init i guess and local is its until the } and aslo to acess global we do ::value1 if local shadows

const will optimize the compiler but can we make const temporatry like cache and remove it uf the progeam completely shuts down

so enum needs const variables okay makes sense

std::format{"{0.8X}",red} formats the text with the binary and red right??

Difference const vs. non-const? Example: Enum with char type.

const - static variables 

we need to delete it if you want ig

non-const are temporty which doesnt need init ig but these are like local scope just temporary


Enum with char type  what do you mean???


Struct vs. class difference?

struct is mainly public and class is private

but why cant we creare a class and make all variables public 

whyats the idea behind that 

help e out wigth thsi clas strcut enum stuff  i want to undeerstand proppelry

constuctors - default parameterised

class MyClass{ public: MyClass(int val) : member(val) {} ; private: int member;

~MyClass() destruvtors

rule of three/five means constryctor , destuctor , mvoe constuct , move assignment right ??}
What’s a member init list?

i have no clue what is this

Methods: Inline or out-of-line. Const methods: Can't modify object.


no clue 

Access: public, private, protected. Friends: Allow access (e.g., friend class).

what friend class??
Tie-in to Ch. 3: Class for font with private unsigned short bits, public getters using & masks (annotated TOC like class structure).

no idea

I think i need a crash course for ch4 and ch5 in depth

whats lvalueand ralues






-------------

Jot down: When would you use struct over class? Example: Public data grouping.

I think when you have private , protected varuaobles use class to have functionlity but struct is just used for noraml tasks wherre you dont care about the safety of these variables

like Friedns in FB and username and password is private by class 


member init list

it creates a memory or initialises the variable before even the constuctor is called 

thats crazy good 

as it saves memory and time but how much time are we talking like it till take the same time right

Explain member init list in your words. Why rule of five?

MEMBER INIT LIST 

i think it is like helpgin gthe consturctor to initiliaze before even calling saving time and memory ig uesss

member func are like getter and settersinlines

Marked const (e.g., int get() const { return member; })—promise not to modify the object. Usable on const objects (e.g., const MyClass obj; obj.get(); works, but non-const method wouldn't)
. No clue? Think: "Read-only" view—inspects but doesn't change.

so yiu are sayung const is used to make it 
 What's a friend? Example: Const method use.



 firend is like giving access to them see my public and private variabels

 const methis is like uoy cant change the objet that implies you cant change varaibaes or methfs itrght????


 references are aliases 

 int& ref = x;

 it means ref is another name for x and if you change ref it changes x too

 it must be initialized

 lvalue is the named addressable thing

 rvalues is temporary / unnamed liek the literal or expression itself x+1 or 

 lvalue ref & bins to lvalues
 rvalue && to temporaries for efficiency ( move semantics steal resources instead of copy)

 Real-life: Lvalue like a house (has address); rvalue like a temporary tent.

 lvalue is like  int & lref = x alias 
 int&& rref = 5  binds to temp 5

 5 is rvalue
 lref is the lvaluw right

 aw pointers: Hold addresses (e.g., int* ptr = &x;—ptr points to x's address). Dereference: *ptr = 20; changes x. Null: nullptr for "points nowhere"
.
Const pointers: const int* (can't change pointed value); int* const (can't change pointer itself)
.
Arrays: int arr[3]; int* p = arr; (p points to first element; arrays decay to pointers).


Lvalue vs. rvalue example? Why unique_ptr over raw?


L value is like main value
R value example lke literal 

not sure

unique_ptr - auto deletes the memory


ed in combination with the other bitwise operators to achieve the kind of operations we
described in the previous section. The >> operator shifts bits to the right, and the << operator shifts bits to the
left. Bits that fall off either end of the variable are lost.
All the bitwise operations work with integers of any type, but we’ll use type short, which is usually two
bytes, to keep the figures simple. Suppose you define and initialize a variable, number, with this statement:
unsigned short number {16387};
You can shift the contents of this variable with this statement:
auto result{ static_cast<unsigned short>(number << 2) }; // Shift left two bit positions
■ Caution if you want result to have the same type as number, namely unsigned short, you have to add
an explicit type conversion using static_cast<>. the reason is that the expression number << 2 evaluates to a
value of type int, despite the fact that number starts out as type short. there are technically no bitwise or even
mathematical operators for integer types smaller than int (that is: the same would happened for, say, number + 1).
if their operands are either char or short, they are always implicitly converted to int first. signedness is not
preserved during this conversion either.
The left operand of the left shift operator, <<, is the value to be shifted, and the right operand specifies
the number of bit positions by which the value is to be shifted. Figure 3-2 shows the effect.
Chapter 3 ■ Working With Fundamental data types
75
As you can see from Figure 3-2, shifting 16,387 two positions to the left produces the value 12. The
rather drastic change in the value is the result of losing the high order bit. This statement shifts the value
right two bit positions:
result = static_cast<unsigned short>(number >> 2); // Shift right two bit positions
The result is 4,096, so shifting right two bits effectively divides the value by 4. As long as bits aren’t
lost, shifting n bits to the left is equivalent to multiplying by 2, n times. In other words, it’s equivalent to
multiplying by 2n. Similarly, shifting right n bits is equivalent to dividing by 2n. But beware: as you saw with
the left shift of number, if significant bits are lost, the result is nothing like what you would expect. However,
this is not different from the “real” multiply operation. If you multiplied the 2-byte number by 4, you would
get the same result, so shifting left and multiplying are still equivalent. The incorrect result arises because
the result of the multiplication is outside the range of a 2-byte integer.
When you want to modify the original value of a variable using a shift operation, you can do so using the
>>= or <<= operator. Here’s an example:
number >>= 2; // Shift right two bit positions
This is equivalent to the following:
number = static_cast<unsigned short>(number >> 2); // Shift right two bit positions
These two bits are
shifted out and lost.
These two bits are
shifted out and lost.
Zeros are shifted in
from the left.
Zeros are shifted in
from the right.
Decimal 16,387 in binary is:
Shift left 2:
Shift right 2:
0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1
0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1
0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1
Figure 3-2. Shift operations
Chapter 3 ■ Working With Fundamental data types
76
There’s no confusion between these shift operators and the insertion and extraction operators for
input and output. In this case, as far as the compiler is concerned, the meaning is clear from the context.
But sometimes you do need to be careful. For example, suppose you want to verify that, for number equal to
16,387, the expression number << 2 does indeed result in 12 as seen in Figure 3-2. Then you could write the
following, very reasonable-looking statement:
std::cout << number<<2 << std::endl; // Prints 163872 ("16387" followed by "2")
Unfortunately, the compiler interprets this shift operator as a stream insertion operator, so you do not
get the intended result. To fix this you need to add extra parentheses:
std::cout << (number<<2) << std::endl; // Prints 65548
Better, but this still does not produce the predicted outcome 12. Instead, it prints 65,548, which
happens to be 16,387 times 4. The reason is that prior to shifting its bits to the left, number, being of type
unsigned short, is again implicitly promoted to a value of type (signed) int. And int, unlike unsigned
short, is more than large enough to represent the exact result, 65,548. To obtain 12 as in Figure 3-2, you can
use static_cast<> to explicitly cast the int result back to an unsigned short:
std::cout << static_cast<unsigned short>(number<<2) << std::endl; // Prints 12
Shifting Signed Integers
You can apply the bitwise shift operators to both signed and unsigned integers. As you know from previous
chapters, C++20 always encodes signed integers using the two’s complement notation. In this section you’ll
learn how bit shifting works with numbers using this encoding.
For negative numbers, right shift operators introduce 1 bits at the left to fill vacated bit positions; for
positive numbers, 0 bits. This is known as sign extension, as in both cases the added bits are equal to the sign
bit. The sign bit is propagated to maintain consistency between a right shift and a divide operation. We can
illustrate this with these two variables of type signed char.
signed char positive {+104}; // 01101000
signed char negative {-104}; // 10011000
(Remember, to obtain the two’s complement binary encoding, you have to first flip all bits of the positive
binary value and then add one.)
You can shift both values two bits to the right with these operations:
positive >>= 2; // Result is 00011010, or +26, which is +104 / 4
negative >>= 2; // Result is 11100110, or -26, which is -104 / 4
The results are shown in the comments. In both cases, two 0s are shifted out at the right end, and the
value of the sign bit is inserted twice at the left. The decimal value of the resulting values is ±26, which is the
same as if you had divided by 4, as you would expect.
With bitwise shift operations on unsigned integer types, the sign bit is of course not propagated, and 0s
are always inserted on the left.
Chapter 3 ■ Working With Fundamental data types
77
■ Tip do not use signed integer types (or char) if your goal is to manipulate the bits of binary data.
this avoids the high-order bit from being propagated. also, for this and similar reasons, you should use the
std::byte type over unsigned char to manipulate binary data (std::byte is defined by the <cstddef>
module as of C++17).
Left-shift operations are more straightforward: they shift the bits of a two’s complement number in
exactly the same way as they would for the unsigned number represented with the same bit-sequence. This
has one interesting consequence though. Suppose we use the same two variables as before, again equal to
±104, but this time we shift their bits two positions to the left instead of to the right:
positive <<= 2; // Result is 10100000, or -96 (+104 * 4 = +416, or 01'10100000)
negative <<= 2; // Result is 01100000, or 96 (-104 * 4 = -416, or 10'01100000)
The results are shown in the comments. As with unsigned integers, shifting to the left drops bits on the
left, and adds zeroes to the right. This example shows that once significant bits start dropping off at the left, a
left shift operation may change the sign of an integer. This occurs if the corresponding multiplication with a
power of two—shown in parentheses in the comments—results in an integer that falls outside of the range of
the signed integer type.
Logical Operations on Bit Patterns
Table 3-2 shows the four bitwise operators that modify bits in an integer value.
The operators appear in Table 3-2 in order of precedence, so the bitwise complement operator has the
highest precedence, and the bitwise OR operator has the lowest. The shift operators << and >> are of equal
precedence, and they’re below the ~ operator but above the & operator.
Table 3-2. Bitwise Operators
Operator Description
~ The bitwise complement operator is a unary operator that inverts the bits in its operand, so 1
becomes 0, and 0 becomes 1.
& The bitwise AND operator ANDs corresponding bits in its operands. If the corresponding
bits are both 1, then the resulting bit is 1; otherwise, it’s 0.
^ The bitwise exclusive OR operator or XOR operator exclusive-ORs corresponding bits in its
operands. If the corresponding bits are different, then the result is 1. If the corresponding
bits are the same, the result is 0.
| The bitwise OR operator ORs corresponding bits in its operands. If either bit is 1, then the
result is 1. If both bits are 0, then the result is 0.
Chapter 3 ■ Working With Fundamental data types
78
Using the Bitwise AND
You’ll typically use the bitwise AND operator to select particular bits or groups of bits in an integer value.
Suppose you are using a 16-bit integer to store the point size, the style of a font, and whether it is bold and/
or italic, as we illustrated in Figure 3-1. Suppose further that you want to define and initialize a variable to
specify a 12-point, italic, style 6 font (in fact, the very same one illustrated in Figure 3-1). In binary, the style
will be 00000110 (binary 6), the italic bit will be 1, the bold bit will be 0, and the size will be 01100 (binary
12). Remembering that there’s an unused bit as well, you need to initialize the value of the font variable to
the binary number 0000 0110 0100 1100. Because groups of four bits correspond to a hexadecimal digit, the
most compact way to do this is to specify the initial value in hexadecimal notation:
unsigned short font {0x064C}; // Style 6, italic, 12 point
Of course, ever since C++14 you also have the option to simply use a binary literal instead:
unsigned short font {0b00000110'0'10'01100}; // Style 6, italic, 12 point
Note the creative use of the digit grouping character here to signal the borders of the style, italic/bold,
and point size components.
To work with the size afterward, you need to extract it from the font variable; the bitwise AND operator
will enable you to do this. Because bitwise AND produces one bit only when both bits are 1, you can define a
value that will “select” the bits defining the size when you AND it with font. You need to define a value that
contains 1s in the bit positions that you’re interested in and 0s in all the others. This kind of value is called a
mask, and you can define such a mask with one of these statements (both are equivalent):
unsigned short size_mask {0x1F}; // unsigned short size_mask {0b11111};
The five low-order bits of font represent its size, so you set these bits to 1. The remaining bits are 0, so
they will be discarded. (Binary 0000 0000 0001 1111 is hexadecimal 1F.)
You can now extract the point size from font with the following statement:
auto size {static_cast<unsigned short>( font & size_mask )};
Where both corresponding bits are 1 in an & operation, the resultant bit is 1. Any other combination of
bits results in 0. The values therefore combine like this:
font 0000 0110 0100 1100
size_mask 0000 0000 0001 1111
font & size_mask 0000 0000 0000 1100
We have shown the binary values in groups of four bits just to make it easy to identify the hexadecimal
equivalent; it also makes it easier to see how many bits there are in total. The effect of the mask is to separate
out the five rightmost bits, which represent the point size.
You can use the same mechanism to select the font style, but you’ll also need to use a shift operator to
move the style value to the right. You can define a mask to select the left eight bits as follows:
unsigned short style_mask {0xFF00}; // Mask for style is 1111 1111 0000 0000
Chapter 3 ■ Working With Fundamental data types
79
You can obtain the style value with this statement:
auto style {static_cast<unsigned short>( (font & style_mask) >> 8 )};
The effect of this statement is as follows:
font 0000 0110 0100 1100
style_mask 1111 1111 0000 0000
font & style_mask 0000 0110 0000 0000
(font & style_mask) >> 8 0000 0000 0000 0110
You should be able to see that you could just as easily isolate the bits indicating italic and bold by
defining a mask for each. Of course, you still need a way to test whether the resulting bit is 1 or 0, and you’ll
see how to do that in the next chapter.
Another use for the bitwise AND operator is to turn bits off. You saw previously that a 0 bit in a mask will
produce 0 in the result of the AND operator. To just turn the italic bit off in font, for example, you bitwise-
AND font with a mask that has the italic bit as 0 and all other bits as 1. We’ll show you the code to do this
after we’ve shown you how to use the bitwise OR operator, which is next.
Using the Bitwise OR
You can use the bitwise OR operator for setting one or more bits to 1. Continuing with your manipulations
of the font variable, it’s conceivable that you would want to set the italic and bold bits on. You can define
masks to select these bits with these statements:
unsigned short italic {0x40}; // Seventh bit from the right
unsigned short bold {0x20}; // Sixth bit from the right
Naturally, you could again use binary literals to specify these masks. In this case, however, using the left-
shift operator is probably easiest:
auto italic {static_cast<unsigned short>( 1u << 6 )}; // Seventh bit from the right
auto bold {static_cast<unsigned short>( 1u << 5 )}; // Sixth bit from the right
■ Caution do remember, though, that, to turn on the nth bit, you have to shift the value 1 to the left by n-1
bits! to see this, it’s always easiest to think about what happens if you shift with smaller values: shifting by zero
gives you the first bit, shifting by one the second, and so on.
This statement then sets the bold bit to 1:
font |= bold; // Set bold
Chapter 3 ■ Working With Fundamental data types
80
The bits combine like this:
font 0000 0110 0100 1100
bold 0000 0000 0010 0000
font | bold 0000 0110 0110 1100
Now font specifies that the font is bold as well as italic. Note that this operation will set the bit on
regardless of its previous state. If it was on, it remains on.
You can also OR masks together to set multiple bits. The following statement sets both the bold and
italics bits:
font |= bold | italic; // Set bold and italic
■ Caution it’s easy to fall into the trap of allowing language to make you select the wrong operator. Because
you say “set italic and bold,” there’s the temptation to use the & operator, but this would be wrong. anding the
two masks would result in a value with all bits 0, so you wouldn’t change anything.
Using the Bitwise Complement Operator
As we said, you can use the & operator to turn bits off—you just need a mask that contains 0 at the bit
position you want to turn off and 1 everywhere else. However, this raises the question of how best to specify
such a mask. To specify it explicitly, you need to know how many bytes there are in the variable you want to
change (not exactly convenient if you want the program to be in any way portable). However, you can obtain
the mask that you want using the bitwise complement operator on the mask that you would use to turn the
bit on. You can obtain the mask to turn bold off from the bold mask that turns it on:
bold 0000 0000 0010 0000
~bold 1111 1111 1101 1111
The effect of the complement operator is to flip each bit, 0 to 1 or 1 to 0. This will produce the result
you’re looking for, regardless of whether bold occupies two, four, or eight bytes.
■ Note the bitwise complement operator is sometimes called the bitwise NOT operator because for every bit
it operates on, what you get is not what you started with.
Thus, all you need to do to turn bold off is to bitwise-AND the complement of the bold mask with font.
The following statement will do it:
font &= ~bold; // Turn bold off
Chapter 3 ■ Working With Fundamental data types
81
You can set multiple bits to 0 by combining several inverted masks using the & operator and bitwise-
ANDing the result with the variable you want to modify:
font &= ~bold & ~italic; // Turn bold and italic off
This sets both the italic and bold bits to 0 in font. No parentheses are necessary here because ~ has a
higher precedence than &. However, if you’re ever uncertain about operator precedence, put parentheses in
to express what you want. It certainly does no harm, and it really does good when they’re necessary. Note
that you can accomplish the same effect using the following statement:
font &= ~(bold | italic); // Turn bold and italic off
Here the parentheses are required. We recommend you take a second to convince yourself that both
statements are equivalent. If this doesn’t come natural yet, rest assured: you’ll get more practice working
with similar logic when learning about so-called Boolean expressions in the next chapter.
Using the Bitwise Exclusive OR
The outcome of the bitwise exclusive OR operator—or XOR operator for short—contains a 1 if and only if
precisely one of the corresponding input bits is equal to 1, while the other equals 0. Whenever both input
bits are equal, even if both are 1, the resulting bit is 0. The latter is where the XOR operator differs from the
regular OR operator. Table 3-3 summarizes the effect of all three binary bitwise operators.
One interesting property of the XOR operator is that it may be used to toggle or flip the state of
individual bits. With the font variable and the bold mask defined as before, the following toggles the bold
bit—that is, if the bit was 0 before, it will now become 1, and vice versa:
font ^= bold; // Toggles bold
This implements the notion of clicking the Bold button in a typical word processor. If the selected text
is not bold yet, it then simply becomes bold. If the selection is already bold, however, its font reverts to the
regular, nonbold style. Let’s take a closer look at how this works:
font 0000 0110 0100 1100
bold 0000 0000 0010 0000
font ^ bold 0000 0110 0010 1100
Table 3-3. Truth Table of Binary Bitwise Operators
x y x & y x | y x ^ y
0 0 0 0 0
1 0 0 1 1
0 1 0 1 1
1 1 1 1 0
Chapter 3 ■ Working With Fundamental data types
82
If the input is a font that is not bold, the result thus contains 0 ^ 1, or 1. Conversely, if the input already
would be bold, the outcome would contain 1 ^ 1, or 0.
The XOR operator is used less frequently than the & and | operators. Important applications arise,
however, in cryptography, random number generation, and computer graphics, for instance. XOR is also
used for the backup of hard disk data by certain RAID technologies. Suppose you have three similar hard
drives, two with data and one to serve as backup. The basic idea is to ensure that the third drive at all times
contains the XOR’ed bits of all contents of the two other drives, like so:
Drive one ... 1010 0111 0110 0011 ...
Drive two ... 0110 1100 0010 1000 ...
XOR drive (backup) ... 1100 1011 0100 1011 ...
If any of these three drives is then lost, its contents can be recovered by XOR’ing the other two drives.
Suppose, for instance, that you lose your second drive because of some critical hardware failure. Then its
contents are easily recovered as follows:
Drive one ... 1010 0111 0110 0011 ...
XOR drive (backup) ... 1100 1011 0100 1011 ...
Recovered data (XOR) ... 0110 1100 0010 1000 ...
Notice that even with such a relatively simple trick, you already need only one extra drive to back up two
others. The naïve approach would be to simply copy the contents of each drive onto another, meaning you’d
need not three but four drives. The XOR technique is thus already a tremendous cost saver!
Using the Bitwise Operators: An Example
It’s time we looked at some of this stuff in action. This example exercises bitwise operators:
// Ex3_01.cpp
// Using the bitwise operators
import <iostream>;
import <format>;
int main()
{
const unsigned int red{ 0xFF0000u }; // Color red
const unsigned int white{ 0xFFFFFFu }; // Color white - RGB all maximum
std::cout << "Try out bitwise complement, AND and OR operators:\n";
std::cout << std::format("Initial value: red = {:08X}\n", red);
std::cout << std::format("Complement: ~red = {:08X}\n", ~red);
std::cout << std::format("Initial value: white = {:08X}\n", white);
std::cout << std::format("Complement: ~white = {:08X}\n", ~white);
std::cout << std::format("Bitwise AND: red & white = {:08X}\n", red & white);
std::cout << std::format("Bitwise OR: red | white = {:08X}\n", red | white);
