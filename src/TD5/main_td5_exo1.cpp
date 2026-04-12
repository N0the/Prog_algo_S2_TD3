#include <iostream>

size_t folding_string_hash(std::string const &s, size_t max)
{
    size_t hash{0};
    for (size_t i{0}; i < s.size(); i++)
    {
        hash += s[i];
    }
    hash %= max;
    return hash;
};

size_t folding_string_ordered_hash(std::string const &s, size_t max)
{
    size_t hash{0};
    for (size_t i{0}; i < s.size(); i++)
    {
        hash = (hash + (s[i] * (i + 1))) % max;
    }
    return hash;
}

size_t polynomial_rolling_hash(std::string const& s, size_t p, size_t m)
{
    size_t hash{0};
    size_t power{1};   // p^0 = 1 au départ
    for (size_t i{0}; i < s.size(); i++)
    {
        hash = (hash + (s[i] * power) % m) % m;
        power = (power * p) % m;
    }
    return hash;
}

int main()
{
    std::string str{};
    std::cout << "Entrez une string : " << std::endl;
    std::cin >> str;
    size_t max = 256;
    size_t p = 31;
    size_t m = 1e9 + 9;
    size_t hash1 = folding_string_hash(str, max);
    size_t hash2 = folding_string_ordered_hash(str, max);
    size_t hash3 = polynomial_rolling_hash(str,p,m);
    std::cout << "Premier hash : " << hash1 << std::endl;
    std::cout << "Deuxieme hash : " << hash2 << std::endl;
    std::cout << "Troisieme hash : " << hash3 << std::endl;
    
    return 0;

}
