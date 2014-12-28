#include <iostream>

int a = 0;

template <typename T, T /*unnamed*/>
struct nnb_ForceInit { };

template<
	class T
>
class Scriptable {
public:
    struct nnb_Proxy {
        nnb_Proxy() {
			std::cout << "Proxy was executed! ID: " << T::id << std::endl;
			a++;
		}
    };

    static nnb_Proxy __nnb_proxy__;
	typedef nnb_ForceInit<nnb_Proxy&, __nnb_proxy__> __nnb_typedef_dummy__;
} ;

template<
	class T
>
typename Scriptable<T>::nnb_Proxy Scriptable<T>::__nnb_proxy__;

class Object : public Scriptable<Object> {
public:
	constexpr static auto id = "[Object]";
};

class Image : public Scriptable<Image> {
public:
	constexpr static auto id = "[Image]";
};

class Error : public Scriptable<Error> {
public:
	constexpr static auto id = "[Error]";
} ;

int main() {
	std::cout << "Done " << a << std::endl;
}
