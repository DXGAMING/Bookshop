#pragma once
#include <iostream>
#include <ctime>
#include <random>
namespace crypto
{
	typedef std::string  T_str;
	class ICryptData
	{
		static T_str from_DOS(T_str DOS_string);
		static T_str xor_to_key(const T_str& s, unsigned key);
		static T_str swap_odd_and_even_bits(const T_str& s);
	public:
		static std::string generateKey();

		static T_str encrypt(const T_str& s, unsigned key);
		static T_str decrypt(const T_str& s, unsigned key);

	};
}