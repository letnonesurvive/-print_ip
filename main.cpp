#include <iostream>
//#include <Windows.h>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <array>
#include <tuple>

using namespace std;

namespace tuple_namespace {

template <size_t Index = 0, typename... Args>
typename enable_if_t <Index == sizeof...(Args)>
printTupleElements (const tuple<Args...>&) {
}

template <size_t Index = 0, typename... Args>
typename enable_if_t <Index < sizeof...(Args)>
printTupleElements (const std::tuple <Args...>& theTuple) {
    cout << std::get <Index>(theTuple);
    if (Index < sizeof...(Args) - 1) {
        cout << '.';
    }
    printTupleElements <Index + 1> (theTuple);
}

template <typename... Args>
void printTuple (const tuple<Args...>& theTuple) {
    printTupleElements (theTuple);
    cout << endl;
}

template <class T>
constexpr bool is_same_type_pack() {
    return true;
}

template <class T, class U, class... Rest>
constexpr bool is_same_type_pack() {
    return std::is_same<T, U>::value && is_same_type_pack<T, Rest...>();
}

}

namespace impl {

template <class T, class = enable_if_t <is_integral_v <T>>>
void print_ip (const T& theValue, int)
{
    static_assert (is_integral_v <T>, "integral type required.");

    unsigned int aSize = sizeof (theValue);
    uint8_t aBytes [sizeof (theValue)];
    unsigned int aBitsNum = aSize * 8;

    bool isFirst = true;
    for (unsigned int i = 0; i < aSize; ++i) {
        if (!isFirst) {
            std::cout << ".";
        }
        aBitsNum = aBitsNum - 8;
        aBytes[i] = (theValue >> aBitsNum) & 0xFF;
        cout << static_cast <unsigned int> (aBytes[i]);
        isFirst = false;
    }
    cout << endl;
}

template <class T, class = enable_if_t <is_same_v <T, string>>>
void print_ip (const T& theString, long)
{
    static_assert (is_same_v <T, string>, "string type required.");
    cout << theString << endl;
}

template < 
    template <typename, typename> class Container,
    class T,
    typename Allocator = std::allocator<T>,
    class = enable_if_t <is_same_v <Container <T, Allocator>, vector <T, Allocator>> || is_same_v <Container<T, Allocator>, list <T, Allocator>>>>
void print_ip (const Container<T, Allocator>& theContainer, long long)
{
    static_assert (is_same_v <Container <T, Allocator>, vector <T, Allocator>> ||
                   is_same_v <Container <T, Allocator>, list <T, Allocator>>, "vector or list type required");
    bool isFirst = true;
    for (const auto& aValue : theContainer) {
        if (!isFirst) {
            std::cout << ".";
        }
        cout << aValue;
        isFirst = false;
    }
    cout << endl;
}

template<
    template <class ...> class Tuple,
    class... Args,
    class = enable_if_t <is_same_v <Tuple <Args...>, std::tuple <Args...>>>> 
void print_ip (const Tuple <Args...>& theTuple, short)
{
    static_assert (tuple_namespace::is_same_type_pack <Args...>(), "the same type of tuple required");
    tuple_namespace::printTuple (theTuple);
}

}

template <class T>
void print_ip (const T& theValue)
{
    impl::print_ip (theValue, 42); 
}

int main()
{
    //setlocale(LC_ALL, "Russian");

    print_ip(int8_t{ -1 }); // 255
    print_ip(int16_t{ 0 }); // 0.0
    print_ip(int32_t{ 2130706433 }); // 127.0.0.1
    print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41
    print_ip(std::string{ "Hello, World!"}); // Hello, World!
    print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0

}

