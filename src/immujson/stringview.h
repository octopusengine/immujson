#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>



namespace json {

	///stores a refernece to string and size
	/** Because std::string is very slow and heavy */
	template<typename T>
	class StringView {
	public:
		StringView() :data(0), length(0) {}
		StringView(const T *str) : data(str), length(calcLength(str)) {}
		StringView(const T *str, std::size_t length): data(str),length(length) {}
		StringView(const std::basic_string<T> &string) : data(string.data()), length(string.length()) {}
		StringView(const std::vector<T> &string) : data(string.data()), length(string.length()) {}
		StringView(const std::initializer_list<T> &list) :data(list.begin()), length(list.size()) {}

		operator std::basic_string<T>() const { return std::basic_string<T>(data, length); }

		StringView substr(std::size_t index) {
			std::size_t indexadj = std::min(index, length);
			return StringView(data + indexadj, length - indexadj);
		}
		StringView substr(std::size_t index, std::size_t len) {
			std::size_t indexadj = std::min(index, length);
			return StringView(data + indexadj, std::min(length-indexadj, len));
		}

		int compare(const StringView &other) const {
			std::size_t cnt = std::min(length, other.length);
			for (std::size_t i = 0; i < cnt; ++i) {
				if (data[i] < other.data[i]) return -1;
				if (data[i] > other.data[i]) return 1;
			}
			if (length < other.length) return -1;
			if (length > other.length) return 1;
			return 0;
		}

		bool operator==(const StringView &other) const { return compare(other) == 0; }
		bool operator!=(const StringView &other) const { return compare(other) != 0; }
		bool operator>=(const StringView &other) const { return compare(other) >= 0; }
		bool operator<=(const StringView &other) const { return compare(other) <= 0; }
		bool operator>(const StringView &other) const { return compare(other) > 0; }
		bool operator<(const StringView &other) const { return compare(other) < 0; }

		const T * const data;
		const std::size_t length;

		char operator[](std::size_t pos) const { return data[pos]; }
		
		const char *begin() const { return data; }
		const char *end() const { return data + length; }

		static std::size_t calcLength(const T *str) {
			const T *p = str;
			if (p) {
				while (*p) ++p;
				return p - str;
			} else {
				return 0;
			}

		}
		bool empty() const {return length == 0;}
	};

	template<typename T>
	std::ostream &operator<<(std::ostream &out, const StringView<T> &ref) {
		out.write(ref.data, ref.length);
		return out;
	}


}
