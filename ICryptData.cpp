#include "ICryptData.h"



std::string crypto::ICryptData::generateKey()
{
	std::string str;
	std::mt19937 gen(time(NULL));
	std::uniform_int_distribution <int> uid1(5, 10);
	int num = uid1(gen);
	int r;
	std::uniform_int_distribution <int> uid2('0', 'z');
	for (int i = 0; i < num; i++)
	{
		do { r = uid2(gen); } while ((r > '9' && r < 'A') || (r > 'Z' && r < 'a'));
		str += r;
	}
	return str;
}

#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <limits>
#include <windows.h> 

/////////////////////////////////////////////////////////////////////////////////////////
typedef std::string  T_str;
/////////////////////////////////////////////////////////////////////////////////////////
T_str  crypto::ICryptData::from_DOS(T_str  DOS_string)
{
	char buf[1000000];
	OemToCharA(DOS_string.c_str(), buf);
	return buf;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_str  crypto::ICryptData::xor_to_key(const T_str & s, unsigned key)
{
	struct  T_xor_to_key
	{
		unsigned  key_;
		//-------------------------------------------------------------------------------
		T_xor_to_key(unsigned  key) : key_(key)
		{}
		//-------------------------------------------------------------------------------
		char  operator() (char  symb)
		{
			return symb ^ key_;
		}
	};
	T_str  res_s;
	std::transform(s.begin(), s.end(), std::back_inserter(res_s), T_xor_to_key(key));
	return  res_s;
}
/////////////////////////////////////////////////////////////////////////////////////////
T_str  crypto::ICryptData::swap_odd_and_even_bits(const T_str & s)
{
	struct  T_swap_odd_and_even_bits
	{
		char  operator() (char  symb)
		{
			char  even_bits = symb & std::bitset<8>(T_str("10101010")).to_ulong();
			even_bits >>= 1;
			even_bits &= std::bitset<8>(T_str("01111111")).to_ulong();

			char  odd_bits = symb & std::bitset<8>(T_str("01010101")).to_ulong();
			odd_bits <<= 1;

			return  even_bits | odd_bits;
		}
	};
	T_str  res_s;
	std::transform(s.begin(), s.end(), std::back_inserter(res_s), T_swap_odd_and_even_bits());
	return  res_s;
}


T_str crypto::ICryptData::encrypt(const T_str & s, unsigned   key)
{
	return  swap_odd_and_even_bits(xor_to_key(s, key));
}

T_str crypto::ICryptData::decrypt(const T_str & s, unsigned key)
{
	return  xor_to_key(swap_odd_and_even_bits(s), key);
}
