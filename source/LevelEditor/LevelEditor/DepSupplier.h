#ifndef DEP_SUPPLIER_H
#define DEP_SUPPLIER_H

#include <string>
#include <any>
#include <unordered_map>
#include <iostream>
#include <typeindex>

template<typename T>
struct DependencyKey
{
	std::string key;

	DependencyKey(const std::string key) :
		key(key)
	{}
};

struct DepSupplier
{
	template<typename T>
	void put(const DependencyKey<T>& key, T& value);
	
	template<typename T>
	void put(T& value);

	template<typename T>
	T& get(const DependencyKey<T>& key);

	template<typename T>
	T& get();

private:
	std::unordered_map<std::string, std::any> values;
	std::unordered_map<std::type_index, std::any> singletoneValues;
	int counter;
};

/*
* values with keys
*/

template<typename T>
void DepSupplier::put(const DependencyKey<T>& key, T& value)
{
	values[key.key] = &value;
}

template<typename T>
T& DepSupplier::get(const DependencyKey<T>& key)
{
	if (values.find(key.key) == values.end())
	{
		std::cout << "key " << key.key << " is not present in DepSupplier" << std::endl;
	}

	T* ptr;
	try
	{
		ptr = std::any_cast<T*>(values[key.key]);
	}
	catch (const std::bad_any_cast& e)
	{
		std::cout << "key " << key.key << " is present, but has a different type" << std::endl << e.what() << std::endl;
	}
	return *ptr;
}

/*
* singletone values
*/

template<typename T>
void DepSupplier::put(T& value)
{
	singletoneValues[typeid(T)] = (T*) &value;
}

template<typename T>
T& DepSupplier::get()
{
	T* ptr = std::any_cast<T*>(singletoneValues[typeid(T)]);
	return *ptr;
}

#endif