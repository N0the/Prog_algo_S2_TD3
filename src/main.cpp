#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstdlib>
#include "ScopedTimer.hpp"

// Tri par sélection
bool is_sorted(std::vector<int> const &vec) { return std::is_sorted(vec.begin(), vec.end()); }

// Tri fusion
void merge_sort_merge(std::vector<int> &vec, size_t const left, size_t const middle, size_t const right);
void merge_sort(std::vector<int> &vec, size_t const left, size_t const right);
void merge_sort(std::vector<int> &vec)
{
    if (vec.size() <= 1)
    {
        return;
    }
    merge_sort(vec, 0, vec.size() - 1);
}
void selection_sort(std::vector<int> &vec);

std::vector<int> generate_random_vector(size_t const size, int const max = 100)
{
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]()
                  { return std::rand() % max; });
    return vec;
}

int search(std::vector<int> &vec, int checker)
{
    int left{0};
    int right{vec.size() - 1};
    int middle = (left + right) / 2;
    while (checker != vec[middle] && right != middle)
    {
        if (checker < vec[middle])
        {
            right = middle;
            middle = (left + right) / 2;
        }
        else
        {
            left = middle + 1;
            middle = (left + right) / 2;
        }
    }

    if (vec[middle] == checker)
    {
        return middle;
    }
    else
    {
        return -1;
    }
}

int main()
{
    std::vector<int> vectorMain{10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    merge_sort(vectorMain);
    std::cout << vectorMain[0] << std::endl;
    std::cout << vectorMain[vectorMain.size() - 1] << std::endl;
    if (is_sorted(vectorMain))
    {
        std::cout << "Le tableau est trie" << std::endl;
    }
    else
    {
        std::cout << "Le tableau n'est pas trie" << std::endl;
    }
    // Exo 3
    std::vector<int> test = generate_random_vector(100, 100);
    {
        ScopedTimer timer("Algo Bibliotheque standard");
        std::sort(test.begin(), test.end());
    }
    test = generate_random_vector(100, 100);
    {
        ScopedTimer timer("Tri par selection");
        selection_sort(test);
    }
    test = generate_random_vector(100, 100);
    {
        ScopedTimer timer("Tri fusion");
        merge_sort(test);
    }
    // Exo 4
    std::vector<int> dichotomie = {2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::cout << search(dichotomie, 22) << std::endl;
}
/*

Il semblerait que l'algorithme de selection soit le plus rapide dans les cas où l'on a un petit tableau, puis c'est l'algo de la bibliothèque standard et enfin le tri fusion.
Tandis que si l'on a un gros tableau, c'est l'algo de la bibliothèque standard le plus rapide, puis le tri par sélection et enfin le tri fusion.

*/

void selection_sort(std::vector<int> &vec)
{
    for (size_t i{0}; i < vec.size() - 1; i++)
    {
        int value{vec[i]};
        int switchPosition{i};
        for (size_t j{i + 1}; j < vec.size(); j++)
        {
            if (value > vec[j])
            {
                switchPosition = j;
                value = vec[j];
            }
        }
        if (value != vec[i])
        {
            std::swap(vec[i], vec[switchPosition]);
        }
    }
}

void merge_sort_merge(std::vector<int> &vec, size_t const left, size_t const middle, size_t const right)
{
    std::vector<int> vec1(vec.begin(), vec.begin() + middle);
    std::vector<int> vec2(vec.begin() + middle, vec.end());
    std::vector<int> vecFinal(vec.size());
    size_t i{0};
    size_t j{0};
    size_t k{0};

    merge_sort(vec1);
    merge_sort(vec2);
    while (i < vec1.size() && j < vec2.size())
    {
        if (vec1[i] < vec2[j])
        {
            vecFinal[k] = vec1[i];
            i++;
        }
        else
        {
            vecFinal[k] = vec2[j];
            j++;
        }
        k++;
    }
    while (vecFinal.size() != k)
    {
        if (vec1.size() == i)
        {
            vecFinal[k] = vec2[j];
            j++;
        }
        else
        {
            vecFinal[k] = vec1[i];
            i++;
        }
        k++;
    }
    vec = vecFinal;
}

void merge_sort(std::vector<int> &vec, size_t const left, size_t const right)
{
    size_t middle = (right - left + 1) / 2;

    merge_sort_merge(vec, left, middle, right);
}
