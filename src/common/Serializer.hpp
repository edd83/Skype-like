#pragma once

#include <sstream>
#include <utility>
#include <string>
#include <list>


// Declaration: Serializer Class
class Serializer
{
public:
	~Serializer();

	template <typename T> static std::string serialize(T const&);
	template <typename T> static T deserialize(std::istringstream&);

private:
	Serializer();

};
// End of Declaration: Serializer Class



// Declaration and Definition: ActualSerializer Class - Generic
namespace Generic
{
	template <typename T>
	struct ActualSerializer
	{
		static std::string Serialize(T const& data)
		{
			const char* buff = reinterpret_cast<const char*>(&data);
			std::string r;
			r.append(buff, sizeof(T));
			return r;
		}

		static T Deserialize(std::istringstream& iss)
		{
			char* buff = new char[sizeof(T)];
			iss.read(buff, sizeof(T));
			T tmp = *(reinterpret_cast<T*>(buff));
			T data(tmp);
			delete[] buff;
			return data;
		}
	};
}
// End of Declaration and Definition: ActualSerializer Class - Generic



// Declaration and Definition: ActualSerializer Class - String Explicit Specialization
namespace Generic
{
	template <>
	struct ActualSerializer <std::string>
	{
		static std::string Serialize(std::string const& data)
		{
			return ((char)(data.length())) + data;
		}

		static std::string Deserialize(std::istringstream& iss)
		{
			int length = iss.get();
			if (length == std::char_traits<char>::eof())
				return std::string("");
			char* buff = new char[length];
			iss.read(buff, length);
			std::string r("");
			r.append(buff, length);
			delete[] buff;
			return r;
		}
	};
}
// End of Declaration and Definition: ActualSerializer Class - String Explicit Specialization



// Declaration and Definition: ActualSerializer Class - List Partial Specialization
namespace Generic
{
	template <typename T>
	struct ActualSerializer < std::list<T> >
	{
		static std::string Serialize(std::list<T> const& data)
		{
			std::string r = Serializer::serialize<int>(data.size());
			for (typename std::list<T>::const_iterator it = data.begin(); it != data.end(); ++it)
			{
				std::string tmp = Serializer::serialize<T>(*it);
				r.append(tmp);
			}
			return r;
		}

		static std::list<T> Deserialize(std::istringstream& iss)
		{
			std::list<T> r;
			int length = Serializer::deserialize<int>(iss);
			for (int i = 0; i < length; ++i)
			{
				T elem = Serializer::deserialize<T>(iss);
				r.push_back(elem);
			}
			return r;
		}
	};
}
// End of Declaration and Definition: ActualSerializer Class - List Partial Specialization



// Declaration and Definition: ActualSerializer Class - Pair Partial Specialization
namespace Generic
{
	template <typename U, typename V>
	struct ActualSerializer< std::pair<U, V> >
	{
		static std::string Serialize(std::pair<U, V> const& data)
		{
			std::string r = Serializer::serialize<U>(data.first);
			r += Serializer::serialize<V>(data.second);
			return r;
		}

		static std::pair<U, V> Deserialize(std::istringstream& iss)
		{
			U first = Serializer::deserialize<U>(iss);
			V second = Serializer::deserialize<V>(iss);
			std::pair<U, V> r(first, second);
			return r;
		}
	};
}
// End of Declaration and Definition: ActualSerializer Class - Pair Partial Specialization



// Definition: Serializer Class
template <typename T>
std::string				Serializer::serialize(T const& data)
{
	return Generic::ActualSerializer<T>::Serialize(data);
}

template <typename T>
T						Serializer::deserialize(std::istringstream& iss)
{
	return Generic::ActualSerializer<T>::Deserialize(iss);
}
// End of Definition: Serializer Class

