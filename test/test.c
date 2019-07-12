/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "Tokenizer.h"
#include "ArrayMap.h"
#include "LinkedList.h"

CLASS(Point,
    // To declare a instance variable
    // you must add "," comma at the end
    long double x;
    long double y;
    String toString,

    // Use "this" to access the instance in constructor 
    // don't forget "," comma at the end
    CONSTRUCTOR(Point, (long double x, long double y),
        this->x = x;
        this->y = y;
        this->toString = $("");
    ),//end constructor

    void point_free(Point* this){
        // Point* this = obj;
        if(this == NULL) return;
        delete(this->toString, this);
    }//end func

    String point_toString(Point* this){
        free(this->toString);
        this->toString = $("position: ", _(this->x), ", ", _(this->y));
        return this->toString;
    }//end func

    int point_getX(Point* this){
        return this->x;
    }//end func

    int point_getY(Point* this){
        return this->y;
    }//end func

    void point_multiplier(Point* this, int multiplier){
        this->x = this->x * multiplier;
        this->y = this->y * multiplier;
    }//end func

);//end class

void* func_total(Number total, Number element){
    void* toBeReturned =  new_Number( (*total) * (*element) );
    free(total);
    return toBeReturned;
}

void* func_filterOdd(Number element){
    if(*element > 2){
        Number result = new_Number( *element );
        return result;
    }else{
        return NULL;
    }
}

void* func_multiply(Number element){
    Number result = new_Number(*element*2);
    return result;
}//end end for

int main(){

    String testSlice = $("0123456789.");
    string_slice(testSlice, 8, 2);
    print(testSlice);
    delete(testSlice);
    
    Map* testingSameKey = new_Map(string_free);
    map_add(testingSameKey, "bobs", $("send boby"));
    print("first: ", map_get(testingSameKey, "bobs"));
    map_add(testingSameKey, "bobs", $("it works!"));
    print("second: ", map_get(testingSameKey, "bobs"));
    map_free(testingSameKey);

    // To declare point object
    Point* position = new_Point(10, 15);
    print(point_toString(position));
    // Setter function to multiply the point value
    point_multiplier(position, 2);
    print(
        "the new x value is ", 
        _(point_getX(position)),
        "\nand the new y value is ", 
        _(point_getY(position)) 
    );

    point_free(position);

    Array* numbers = new_Array(free);
    array_addMultiple(numbers, 
        new_Number(1),
        new_Number(2),
        new_Number(3),
        new_Number(4)
    );

    Array* numbers2 = array_mapper(numbers, func_multiply, free);
    Array* numbers3 = array_filter(numbers, func_filterOdd, free);
    Number numberResult = array_reducer(numbers, func_total, new_Number(1) );
    print("the number result: ", _(*numberResult) );

    for_in(x, numbers){
        Number temp = array_get(numbers, x);
        print("number: ", _(*temp));
    }
    for_in(x, numbers2){
        Number temp2 = array_get(numbers2, x);
        print("number2: ", _(*temp2));
    }
    for_in(x, numbers3){
        Number temp = array_get(numbers3, x);
        print("number3: ", _(*temp));
    }

    delete(numberResult);
    array_free(numbers);
    array_free(numbers2);
    array_free(numbers3);

    // Add multipler points to the array
    Array* points = new_Array(point_free);
    array_addMultiple(points, 
        new_Point(10, 10),
        new_Point(20, 20),
        new_Point(30, 30),
        new_Point(40, 40)
    );

    // Loop the array and print the point object
    for_in(x, points){
        print(point_toString(array_get(points, x)));
    }//end for

    array_free(points);
    
    Map* cars = new_Map(string_free);
    String ferrariKey = $("Ferrari");
    String hondaKey = $("Honda");
    
    // Adding to the map
    map_add(cars, ferrariKey, $("Price of ", ferrariKey,": $300,000"));
    map_add(cars, hondaKey, $("Price of ", hondaKey, ": $20,000"));
    
    // Get the data by passing the key
    print(map_get(cars, "Ferrari"));
    print(map_get(cars, "Honda"));

    map_free(cars);
    delete(ferrariKey, hondaKey);

    Map* randomString = new_Map(string_free);
    int counter = 0;
    loop(x, 10){
        counter++;
        String countStr = _(counter);
        map_add(randomString, countStr, $("string = ", _(counter)));
        free(countStr);
    }

    map_remove(randomString, "4");
    map_remove(randomString, "8");
    map_remove(randomString, "8");
    map_remove(randomString, "8");
    map_remove(randomString, "2");

    counter = 0;
    loop(x, randomString->length){
        counter++;
        String tempKey = _(counter);
        print("result: ", map_get(randomString, tempKey));
        print("ArrayMapData: ", map_iterator(randomString, x));
        free(tempKey); 
    }
    map_free(randomString);

    // garbage collector
    MEM_START;
        String hello = $("hello"); 
        String myName = $("my name is vic");
        String testingMem = $("testing some mem");
        String testMem2 = $("testing this thing"); 
        MEM_ADD(hello, myName, testMem2, testingMem);
        print(hello, " ", myName, " ",testingMem, " ", testMem2);
    MEM_END;

    int num = 0;
    loop(x, 5){
        num++;
        String tempStr = $("index is ", _(num));
        String tempStr2 = $("the ", tempStr);
        print(tempStr);
        // free
        delete(tempStr, tempStr2);
    }//end loop

    //c
    Array* listOfCars = new_Array(string_free);
    array_add(listOfCars, $("Lambo"));
    array_add(listOfCars, $("Honda"));

    // java
    // Array listOfCars = new Array();
    // listOfCars.add("Lambo");
    // listOfCars.add("Honda");

    print("car is ", array_get(listOfCars, 1));
    array_free(listOfCars);
    //******************************************* testing string tag

    String test = $("Hello world!");
    print("print1: ", test);

    String name = $("Vic");
    String sayHello = NULL;

    sayHello = $("Hello my name is ", name, ", how is it going?");
    print("print2: ", sayHello);

    const int age = 8;
    String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
    print("print", _(3) , ": ", sayYourCodeYears); 

    int num1 = 2;
    int num2 = 2;
    String addition = $(_(num1), " plus ", _(num2), " is ", _(num1+num2));
    print("print4: ", addition, " minus 1 that's 3 quick math.");

    const double pi = 3.14159;
    String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
    print("print", _dec(5, 0), ": ", sayPiInDecimal);

    String salute = $("hello");
    print("the salute value is ", salute);
    $$(salute) = $("cya");
    print("the salute value is ", salute);
    $$(salute) = $("okay");
    $$(salute) = $("dude");
    print("the salute value is ", salute);
    free(salute);

    // free
    free(test);
    free(name);
    free(addition);
    free(sayHello);
    free(sayYourCodeYears);
    free(sayPiInDecimal);

    //**************************************************token test

    String toBeSplit = $("This string is going to be split into array of string");
    Token* token = new_Token(toBeSplit, " ");
    for(int x=0; x<token->length; x++){
        print("token[", _(x), "]: ", token_getTokenAt(token, x));
    }//end for

    print("outputing 3 and 6 = (", token_combine(token, 3, 6), ")");

    int indexSearch = token_search(token, "going", true);
    print("the index token is ", _(indexSearch));

    indexSearch = token_search(token, "string", false);
    print("found ", _(indexSearch), " with the name string");


    //***********************************************************array test

    // declareing a new object
    Array* listOfString = new_Array(string_free);

    // to add object to an array
    array_add(listOfString, $("first string") );

    // to add multiple object to an array
    array_addMultiple(listOfString,
        $("second string"),
        $("third string"),
        $("fourth string"),
        $("fith string"),
        $("last string"),
        $("last string"),
        $("last string")
    );

    array_remove(listOfString, 0);
    array_remove(listOfString, 0);

    loop(x, listOfString->length+1){
        String current = array_get(listOfString, x);
        print(current);
    }//end if

    // free
    array_free(listOfString);

    //**********************************************************map test

    Map* map = new_Map(string_free);

    map_add(map, "one", $("hunny"));
    map_add(map, "two", $("boo boo"));
    map_add(map, "three", $("yee"));
    map_add(map, "four", $("okay"));
    map_add(map, "five", $("dude"));
    map_add(map, "six", $("sup"));
    map_add(map, "seven", $("keep"));
    map_add(map, "eight", $("goin"));
    map_add(map, "nine", $("please"));
    map_add(map, "ten", $("stop")); 
    map_add(map, "eleven", $("wow"));
    map_add(map, "twelve", $("nah"));
    map_add(map, "thirteen", $("im"));
    map_add(map, "fourteen", $("done"));
    
    print("one = ", map_get(map, "one"));
    print("two = ", map_get(map, "two"));
    print("three = ", map_get(map, "three"));
    print("four = ", map_get(map, "four"));
    print("five = ", map_get(map, "five"));
    print("six = ", map_get(map, "six"));
    print("seven = ", map_get(map, "seven"));
    print("eight = ", map_get(map, "eight"));
    print("nine = ", map_get(map, "nine"));
    print("ten = ", map_get(map, "ten"));
    print("nine = ", map_get(map, "eleven"));
    print("ten = ", map_get(map, "twelve"));
    print("thirteen = ", map_get(map, "thirteen"));
    print("fourteen = ", map_get(map, "fourteen"));

    map_free(map);
    free(toBeSplit);
    token_free(token);
    //testing class

    //*************************** testing char at
    String charTest = $("hello world");
    String theChar = string_charAt(charTest, 6);
    print("this should be 'w': ", theChar);
    $$(theChar) = string_charAt(charTest, 11);
    print("this should be 'd': ", theChar);
    $$(theChar) = string_charAt(charTest,-1);
    print("this should be 'h': ", theChar);
    delete(charTest, theChar);

    // testing double free
    String google = $("hire me please and thank you");
    print("yo google ", google);
    free(google);
    free(google);
    free(google);

}//end main