# Dynamic String API for C

A dynamic string API to make string coding much easier in C similar to other modern languages.

## Installation of API

### 1. Download

```Bash
git clone https://github.com/vicmoh/DynamicStringAPI
```

### 2. Run

To compile and run the program type `make` or `make valgrind` on terminal program directory.
Place any of your `.c` files in `src` folder and `.h` in `include`.
No need to change the `makefile`.
Any files you placed in `scr`, `include`, `lib` will automatically compile and run the program when `make` is invoked.

```bash
make
```

### Directory Structure

Any C file should be placed under the `src` folder.
There is already `main.c` where you can start your project.

```Bash
src/main.c
```

Any shared or static libraries goes under the `lib` folder.

```Bash
lib/DynamicString.a
```

Your header .h files must be inside the `include` folder.

```Bash
include/DynamicString.h
include/Tokenizer.h
include/ArrayMap.h
include/LinkedList.h
```

The bin folder is where the executable files goes to.
By default, `runProgram` will be your executable when `make` is invoked on the terminal.

```Bash
bin/runProgram
```

If you already have a project, you can add the API to your `makefile`.
Copy and paste the `DynamicString.a` and the header file you want to use to your project.

## How to Use the Dynamic String API

### String Usage

Simply, any tag inside `$( )` is a string.
Higher level languages uses `+` symbol to assign multiple strings together.
In comparison, you can assign similar way using `,` to represent different strings inside the string tag.
Similar to other languages, the function `print( )` is also available using the string tag format which will output to the console.

To declare a string:

```javascript
String test = $("Hello world!");
print("print1: ", test);

/************ output ************
print1: Hello world!
*********************************/
```

You can also assign string with other string. As long as it is in the string tag it will return a dynamically allocated combined string:

```javascript
String name = $("Vic");
String sayHello = NULL;
String toBeAssigned = NULL;

sayHello = $("Hello my name is ", name, ", how is it going?");
toBeAssigned = $(sayHello);
print("print2: ", toBeAssigned);

/************ output ************
print2: Hello my name is Vic, how is it going?
*********************************/
```
### Number in String

Number variables such as int or double in string tag `$( )` must use `_( )` or it will not compile.
You can also use constant numbers inside instead of variables such as `_(3)`:

```javascript
const int age = 8;
String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
print("print", _(3) , ": ", sayYourCodeYears); 

/************ output ************
print3: I have been coding for 8 years.
*********************************/
```

Another example:

```javascript
int num1 = 2;
int num2 = 2;
String addition = $(_(num1), " plus by ", _(num2), " is ", _(num1+num2));
print("print4: ", addition, " minus 1 that's 3 quick math.");

/************ output ************
print4: 2 plus 2 is 4 minus 1 that's 3 quick math.
*********************************/
```

Here's another example to print with decimal places on numbers.
The first argument in `_dec( )` is the value, and the second is the number of decimal places to show:

```javascript
const double pi = 3.14159;
String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
print("print", _dec(5, 0), ": ", sayPiInDecimal);

/************ output ************
print5: What is the Pi number? 3.14 is the number, duh!
*********************************/
```

### Memory Management

Previously this is how we use to code string in C. We had to use an array of chars.

The code below is how we manipulate char array in C, problem with this is that the size is constant and it could not hold string longer than `30`. So what if it happens to be a longer string? 

Another way to fix the problem is to create a dynamic char array by mallocing and then reallocing to a bigger size when we need to hold more char. So, we have to keep track of the size and it can be difficult to manage.

```javascript
// Dynamically char size previously how we use to code
char* sayYourName = malloc(sizeof(char*)*30);
char* name = malloc(sizeof(char*)*30);
strcpy(name, "Jeff");
strcpy(sayYourName, "My name is ");
strcat(sayYourName, name);
strcat(sayYourName, ".");

printf("%s\n", sayYourName);

// And when we need more memory we can just realloc the size
char* sayYouName = realloc(sayYourName, sizeof(char*)*50)

/************ output ************
My name is Jeff.
*********************************/
```

The string tag `$( )` is a simpler form of dynamic chars in C which will adjust accordingly based on the string size. As a result, there is no need to keep track of the memory size of the char array, it will adjust dynamically based on the string size for you. Hence, making dynamic string simpler to code in C similar to other modern languages!

```javascript
// The new way of manipulating string in C
String name = $("Jeff");
String sayYourName = $("My name is ", name, ".");

print(sayYourName);

// In comparison to modern language like JavaScript
var name = "Jeff";
var sayYourName = "My name is " + name + ".";

console.log(sayYourName);

/************ output ************
My name is Jeff.
*********************************/
```

However, since string tag returns a dynamic allocated string,
every new string that has been created needs to be freed. 
So don't forget to free your string!

```javascript
// If DynamicString.h is used it will assign null after free when using free()
free(test);
free(name);
free(multiply);
free(sayHello);
free(toBeAssigned);
free(sayYourCodeYears);
free(sayPiInDecimal);

// You can also free multiple variables using delete() functions
delete(test, name, addition, sayHello, sayYourCodeYears, sayPiInDecimal);
```

## Tokenizer

You can also split string through the token object
which split the token into an array of tokens similar to Java:

```javascript
// You can use 'split()' or 'new_Token()' to create token object
String toBeSplit = $("This string is going to be split into array of string");
Token* token = new_Token(toBeSplit, " ");
for(int x=0; x<token->length; x++){
    print("token[", _(x), "]: ", token->list[x]);
}//end for

/************ output ************
token[0]: This
token[1]: string
token[2]: is
token[3]: going
token[4]: to
token[5]: be
token[6]: split
token[7]: into
token[8]: array
token[9]: of
token[10]: string
*********************************/

free(toBeSplit);
Token_free(token);
```

## Data Structure

The library also contains other data structure such as array, map or linked list.
It follows a standard to declare and access an object.
To initialize an object simply declare by: `[objectType]* varName = new_[objectType]()`

Every new object starts with `new_` tag 
and you can access the object method by: `[objectTypeInLowerCase]_[functionName]()`

### Array

```javascript
// Declaring a new object. The parameter takes a function of what to free.
// You can pass in NULL if you don't wont the array data to be freed.
Array* cars = new_Array(string_free);

// To add object to an array
array_add(listOfString, $("first string") );

// To add multiple object to an array
array_addMultiple(listOfString,
    $("second string"),
    $("third string"),
    $("fourth string"),
    $("fith string")
);

// You can also use 'for in' loop.
// But the object struct must have length variable
// such as map, linked list, and array from the library.
for_in(x, listOfString){
    String current = array_getIndexOf(listOfString, x);
    print(current);
}//end if

/************ output ************
first string
second string
third string
fourth string
fith string
*********************************/

array_free(listOfString);
```

### Map

```javascript
// Declaring a new object. The first param set the size of table,
// if table is maxed out it will automatically resize the table.
// The second param takes a function of what to free.
// You can pass in NULL if you don't wont the data to be freed.
Map* cars = new_Map(11, string_free);
String ferrariKey = $("Ferrari");
String hondaKey = $("Honda");

// Adding to the map
map_add(cars, ferrariKey, $("Price of a ", ferrariKey,": $300,000"));
map_add(cars, hondaKey, $("Price of a ", hondaKey, ": $20,000"));

// Get the data by passing the key and print to console
print(map_get(cars, "Ferrari"));
print(map_get(cars, "Honda"));

/************ output ************
Price of a Ferrari: $300,000
Price of a Honda: $20,000
*********************************/

map_free(cars);
delete(ferrariKey, hondaKey);
```

## Other Advance Usage

The DynamicString.h also contain preprocessors of another way to make objects:

```javascript

// Declaring Point object and
// using the parameter for creating a new object
CLASS(Point, (long double x, long double y),

    // To declare an instance variable
    // you must add "," comma at the end.
    long double x;
    long double y;
    String toString,

    // Use "this" to access the instance
    // variable members in Point construtor.
    // Don't forget "," comma at the end.
    CONSTRUCTOR(
        this->x = x;
        this->y = y;
        this->toString = $("cordinate: ", _(this->x), ", ", _(this->y));
    ),//end constructor

    // function to free object
    void point_free(void* obj){
        Point* this = obj;
        if(this == NULL){
            return;
        }//end if
        delete(this->toString, this);
    }//end func

    // toString function
    void point_toString(Point* this){
        free(this->toString);
        this->toString = $("cordinate: ", _(this->x), ", ", _(this->y));
    }//end func

    // cloning function
    Point* point_clone(Point* toBeClone){
        Point* new = new_Point(toBeClone->x, toBeClone->y);
        return new;
    }//end func

    // function to multiply the cordinate
    void point_multiply(Point* this, int numToMultiply){
        this->x = this->x * numToMultiply;
        this->y = this->y * numToMultiply;
        point_toString(this);
    }//end func
);//end class

```

Usage example 1:

```javascript
// Declare a new point
Point* cordinate = new_Point(10, 25);
print(cordinate->toString);

// Multiply the cordinate by 5
point_multiply(cordinate, 5);
print("the new ", cordinate->toString);

/************ output ************
cordinate: 10, 25
the new cordinate: 50, 125
*********************************/

point_free(cordinate);
```

Usage example 2:

```javascript
// Declare and put points in the array
Array* points = new_Array(point_free);
array_addMultiple(points,
    new_Point(10, 10),
    new_Point(20, 20),
    new_Point(30, 30),
    new_Point(40, 40)
);

// Loop and print the points
for_in(x, points){
    Point* currentPoint = array_getIndexOf(points, x);
    print(currentPoint->toString);
}//end for

/************ output ************
cordinate: 10, 10
cordinate: 20, 20
cordinate: 30, 30
cordinate: 40, 40
*********************************/

array_free(points);
```




