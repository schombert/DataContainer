#pragma once

#include <string>
#include <vector>
#include <functional>
#include <utility>

class raw_lines {
public:
	std::vector<char const*> lines;

	raw_lines& operator+(char const* l) {
		lines.push_back(l);
		return *this;
	}
};

class substitute {
public:
	std::string sub_key;
	std::string sub_text;

	substitute(char const* key, std::string text) : sub_key(key), sub_text(text) {

	}
};

class append {
public:
	std::string app_text;
};

template<typename T>
class block_lambda {
public:
	T func;
	block_lambda(T&& f) : func(f) {}
};

template<typename T>
class class_block_lambda {
public:
	T func;
	class_block_lambda(T&& f) : func(f) {}
};

template<typename T>
class inline_block_lambda {
public:
	T func;
	inline_block_lambda(T&& f) : func(f) {}
};

class basic_builder {
public:
	std::vector<substitute> substitutes;
	std::vector<std::string> lines;
	int32_t extra_tabs = 0;
	//basic_builder

	basic_builder& operator+(substitute const& sub) & {
		for(auto& s : substitutes) {
			if(s.sub_key == sub.sub_key) {
				s.sub_text = sub.sub_text;
				return *this;
			}
		}
		substitutes.push_back(sub);
		return *this;
	}
	basic_builder&& operator+(substitute const& sub) && {
		for(auto& s : substitutes) {
			if(s.sub_key == sub.sub_key) {
				s.sub_text = sub.sub_text;
				return std::move(*this);
			}
		}
		substitutes.push_back(sub);
		return std::move(*this);
	}
	basic_builder& operator+(char const* line) & {
		add_line(line);
		return *this;
	}
	basic_builder&& operator+(char const* line) && {
		add_line(line);
		return std::move(*this);
	}
	basic_builder& operator+(append const& a) & {
		if(lines.size() > 0)
			lines.back() += a.app_text;
		return *this;
	}
	basic_builder&& operator+(append const& a) && {
		if(lines.size() > 0)
			lines.back() += a.app_text;
		return std::move(*this);
	}
	basic_builder& operator+(std::string const& line) & {
		add_line(line);
		return *this;
	}
	basic_builder&& operator+(std::string const& line) && {
		add_line(line);
		return std::move(*this);
	}
	template<typename T>
	basic_builder& operator+(class_block_lambda<T> const& func) & {
		if(lines.size() > 0)
			lines.back() += " {";
		
		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("};");

		return *this;
	}
	template<typename T>
	basic_builder&& operator+(class_block_lambda<T> const& func) && {
		if(lines.size() > 0)
			lines.back() += " {";
		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("};");

		return std::move(*this);
	}
	template<typename T>
	basic_builder& operator+(block_lambda<T> const& func) & {
		if(lines.size() > 0)
			lines.back() += " {";

		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("}");

		return *this;
	}
	template<typename T>
	basic_builder&& operator+(block_lambda<T> const& func) && {
		if(lines.size() > 0)
			lines.back() += " {";

		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("}");

		return std::move(*this);
	}
	template<typename T>
	basic_builder& operator+(inline_block_lambda<T> const& func) & {
		add_line("{");
		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("}");

		return *this;
	}
	template<typename T>
	basic_builder&& operator+(inline_block_lambda<T> const& func) && {
		add_line("{");
		++extra_tabs;
		func.func(*this);
		--extra_tabs;
		add_line("}");

		return std::move(*this);
	}
	void add_line(std::string const& line) {
		std::string built_string;
		bool in_sub_name = false;
		for(size_t pos = 0; pos < line.length(); ) {
			size_t end_pos = line.find('@', pos);
			if(end_pos > line.length()) {
				end_pos = line.length();
			}

			std::string segment = line.substr(pos, end_pos - pos);

			if(in_sub_name) {
				bool found = false;
				for(auto s : substitutes) {
					if(s.sub_key == segment) {
						built_string += s.sub_text;
						found = true;
					}
				}
				if(!found) {
					built_string += (std::string("$") + segment + "$");
				}
			} else {
				built_string += segment;
			}
			in_sub_name = !in_sub_name;
			pos = end_pos + 1;
		}

		lines.push_back(std::string(extra_tabs, '\t') + built_string);
	}
	std::string to_string(int tab_level) {
		std::string output;
		std::string tabs = std::string(tab_level, '\t');

		for(auto& l : lines) {
			output += (tabs + l + "\n");
		}

		return output;
	}
};

#define block(...) block_lambda{ [&](basic_builder& o) { __VA_ARGS__ } }
#define class_block(...) class_block_lambda{ [&](basic_builder& o) { __VA_ARGS__ } }
#define inline_block(...) inline_block_lambda{ [&](basic_builder& o) { __VA_ARGS__ } }


