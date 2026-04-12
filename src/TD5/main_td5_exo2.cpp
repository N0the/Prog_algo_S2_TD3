#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <fstream>

enum Direction
{
    Haut,
    Droite,
    Bas,
    Gauche
};

struct Position
{
    int x;
    int y;

    // friend (vu avec Jules) : de ce que j'ai compris, ça permet d'avoir une fonction comme si elle était déclaré à l'extérieur
    Position &operator+=(Position const &a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }
};

struct Input_Structure // La carte
{
    Direction directionGarde;
    // On veut ici obtenir les coordonnées minimales et maximales de la carte, pour vérifier avec le garde s'il sort du scope
    int x_max;
    int y_max;

    Position gardPos;
    std::vector<Position> obstacles;
};

bool operator==(Position const &a, Position const &b)
{
    return a.x == b.x && a.y == b.y;
}

std::ostream &operator<<(std::ostream &os, Position const &a)
{
    return os << '(' << a.x << ", " << a.y << ')';
}

Position &operator+=(Position &a, Direction const &b)
{
    switch (b)
    {
    case Haut:
        a.y -= 1;
        return a;
    case Droite:
        a.x += 1;
        return a;
    case Bas:
        a.y += 1;
        return a;
    case Gauche:
        a.x -= 1;
        return a;
    default:
        return a;
    }
}
Position operator+(Position a, Direction const &b)
{
    a += b;
    return a;
}
Direction turn_right(Direction const a)
{
    switch (a)
    {
    case Haut:
        return Droite;
    case Droite:
        return Bas;
    case Bas:
        return Gauche;
    case Gauche:
        return Haut;
    default:
        return a;
    }
}

/* Création de la carte */

Input_Structure read_input(std::istream &input_stream)
{
    int x{0}; // Position de la colonne (logiquement j'aurais du mettre y, mais bon ^^)
    int y{0}; // Position de la ligne
    Input_Structure carte;
    Position Obstaclepos;
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != "";)
    {
        for (size_t x = 0; x < line.size(); ++x)
        {
            if (line[x] == '#') // Détection d'un obstacle
            {
                Obstaclepos.x = x;
                Obstaclepos.y = y;
                carte.obstacles.push_back(Obstaclepos);
            }
            switch (line[x]) // Détection de la position du garde
            {
            case '^':
                carte.gardPos.x = x;
                carte.gardPos.y = y;
                carte.directionGarde = Haut;
                break;
            case '>':
                carte.gardPos.x = x;
                carte.gardPos.y = y;
                carte.directionGarde = Droite;
                break;
            case 'v':
                carte.gardPos.x = x;
                carte.gardPos.y = y;
                carte.directionGarde = Bas;
                break;
            case '<':
                carte.gardPos.x = x;
                carte.gardPos.y = y;
                carte.directionGarde = Gauche;
                break;
            default:
                break;
            }
        }
        carte.x_max = line.size() - 1; // On sait que la carte est rectangulaire, alors ici ça marche
        y += 1;                        // On change de ligne, on passe à la ligne du dessous
    }
    // On obtient les coordonnées min et max de la carte
    carte.y_max = y;
    return carte;
}

namespace std
{
    template <>
    struct hash<Position>
    {
        std::size_t operator()(const Position &pos) const
        {
            // Problème avec ce hash, c'est que la position 1,2 et 2,1 donnent le même hash, donc j'ai une position en plus
            return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
        }
    };
}

struct WalkResult // Historique des pas du garde
{
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
};

WalkResult walk_garde(Input_Structure const &carte)
{
    int x_min = 0;
    int y_min = 0;
    WalkResult result;
    Position current_position{carte.gardPos.x, carte.gardPos.y};
    Direction direction_garde = carte.directionGarde;
    std::unordered_set<Position> visited_positions;
    // On vérifie si le garde ne sort pas du scope de la carte
    while (current_position.x >= x_min && current_position.x <= carte.x_max &&
           current_position.y >= y_min && current_position.y <= carte.y_max)
    {
        visited_positions.insert(current_position);
        Position pos_suivante = current_position + direction_garde;
        if (std::find(carte.obstacles.begin(), carte.obstacles.end(), pos_suivante) != carte.obstacles.end())
        {
            direction_garde = turn_right(direction_garde);
        }
        else
        {
            current_position += direction_garde;
        }
        result.steps_taken++;
    }
    result.visited_positions = visited_positions;
    result.final_position = current_position;
    return result;
}

// Je fais pas la question 4 exo 2, sorry

int main()
{
    /* Exo 2 Question 3 partie 3*/
    std::ifstream file1("../guard_test.txt");
    Input_Structure map1 = read_input(file1);
    WalkResult results1 = walk_garde(map1);

    /* Exo 2 Question 3 partie 4*/
    std::ifstream file2("../input_guard_patrol.txt");
    Input_Structure map2 = read_input(file2);
    WalkResult results2 = walk_garde(map2);

    std::cout << "Map 1 :" << std::endl;
    std::cout << "Position finale : " << results1.final_position << std::endl;
    std::cout << "Nombre de position : " << results1.steps_taken << std::endl;
    std::cout << "Nombre de position differentes : " << results1.visited_positions.size() << std::endl;

    std::cout << "Map 2 :" << std::endl;
    std::cout << "Position finale : " << results2.final_position << std::endl;
    std::cout << "Nombre de position : " << results2.steps_taken << std::endl;
    std::cout << "Nombre de position differentes : " << results2.visited_positions.size() << std::endl;
};