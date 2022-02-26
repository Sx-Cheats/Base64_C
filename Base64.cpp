#include <iostream>
#include <bitset>
#include<cstring>
#include<string>

using namespace std;

constexpr const char* b64_char = (char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+\\";

template<typename T>
void for_each(string v, T callback)
{
    for (string::iterator _v = v.begin(); _v != v.end(); ++_v)
    {
        callback(*_v);
    }
}
string  text_to_bits(string text, string bits = "")
{
    for_each(text, [&bits](char b) {bits += bitset<8>(b).to_string();});
    return bits;
}
string base64encode(string text, string pack = "")
{
    string b64;
    int r = 1;
    for_each(text_to_bits(text), [&](char c)
        {
            pack += c;
            if (!(r % 6))
            {
                b64 += b64_char[stoi(pack, nullptr, 2)];
                pack.clear();
            }
            r++;
        });

    b64 += b64_char[stoi(pack + string(6 - strlen(pack.c_str()), '0'), nullptr, 2)];
    return b64;
};
int get_index(string c, char v)
{
    int i_same = 0;
    for_each(c, [&i_same, &v](char c)
        {
            if (c == v)
                v = 0;
            if (v != 0)
                i_same++;
        });
    return i_same;
}
string base64decode(string text)
{
    string bin_base_64, decode, _8;
    int r = 1;
    for_each(text, [&bin_base_64](char c)
        {
            bin_base_64 += bitset<6>(get_index(b64_char, c)).to_string();
        });
    for_each(bin_base_64, [&](char c)
        {
            _8 += c;
            if (!(r % 8))
            {
                decode += (char)bitset<8>(_8).to_ulong();
                _8.clear();
            }
            r++;
        });
    return decode;
}

int main()
{
    string b64 = base64encode("Hello World");
    string d_b64 = base64decode(b64);
    cout << " Encoded = " << b64 << endl << " Decoded = " << d_b64 << endl;
    system("pause");
}
