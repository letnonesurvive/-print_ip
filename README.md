# Task:
## Implement a function to print a conditional IP address.

The conditional nature of this address is that the number of elements does not necessarily have to be 4 or 8, and each element does not have to be a number in the range of 0..255.

The only thing that remains from the concept of an IP address is the output of elements separated by . (dot symbol).
The function needs to be implemented for various input parameters using the SFINAE (Substitution Failure Is Not An Error) mechanism. You are required to implement 3 mandatory and 1 optional version of the function.

* The address may be represented as any arbitrary integer type. Print the bytes in an unsigned format, starting from the most significant byte, with the . (dot symbol) as a separator. Print all the bytes of the number.
* The address may be represented as a string. It should be printed as is, regardless of the content.
* The address may be represented as containers like std::list, std::vector.
* Print the full contents of the container, with each element separated by . (dot symbol). The elements are printed as is.
* Optionally, the address may be represented as a std::tuple, provided that all types are the same. Print the full contents of the tuple, with each element separated by . (dot symbol). The elements are printed as is. If the tuple contains different types, the code should produce a compilation error.

The application code should contain the following calls:
```
print_ip( int8_t{-1} ); // 255
print_ip( int16_t{0} ); // 0.0
print_ip( int32_t{2130706433} ); // 127.0.0.1
print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
print_ip( std::string{"Hello, World!"} ); // Hello, World!
print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
```

## Additional Requirements

* The print function should be a single template function, with different input options implemented through the SFINAE mechanism.
* The variant for integer representation should be a single function.
* The variant for containers std::list and std::vector should be a single function.
* There should be no "if nothing else matches, assume it's a container" implementation.
* Find the simplest way to print a std::string (but the function must still be a template).
* The optional implementation for std::tuple should result in a compilation error if the types are different.
* There should be no limitations on the size of integer types (in bytes), container size, or tuple size (number of elements).
* The binary file and package should be named print_ip.
