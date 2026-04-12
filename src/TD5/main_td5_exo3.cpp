#include <iostream>
#include <unordered_map>
#include <vector>

enum class CardKind
{
    Heart,
    Diamond,
    Club,
    Spade,
};

enum class CardValue
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

struct Card
{
    CardKind kind;
    CardValue value;

    int hash() const
    {
        /*Permet de retourner en fonction du type de la carte et de sa valeur, un nombre entre 0 et 51, si c'est un 3 de coeur par 
        exemple ça sera la valeur 1*/
        return static_cast<int>(this->kind) * 13 + static_cast<int>(this->value);
    }
};

namespace std {
    template<>
    struct hash<Card> {
        size_t operator()(Card const& card) const {
            return card.hash();
        }
    };
}

std::vector<Card> get_cards(size_t const size) {
    std::vector<Card> cards {};
    cards.reserve(size);
    for (size_t i {0}; i < size; ++i) {
        cards.push_back({static_cast<CardKind>(rand() % 4), static_cast<CardValue>(rand() % 13)});
    }
    return cards;
}

std::string card_name(Card const& card) {
    std::string name {};

    unsigned int card_value {(static_cast<unsigned int>(card.value)+2) % 14};

    if (card_value < 10) {
        name += '0' + std::to_string(card_value);
    }else if (card_value == 10) {
        name += "10";
    }else if (card_value == 11) {
        name += 'J';
    }else if (card_value == 12) {
        name += 'Q';
    }else if (card_value == 13) {
        name += 'K';
    }

    name += " of ";

    if (card.kind == CardKind::Heart) {
        name += "Heart";
    }else if (card.kind == CardKind::Diamond) {
        name += "Diamond";
    }else if (card.kind == CardKind::Club) {
        name += "Club";
    }else if (card.kind == CardKind::Spade) {
        name += "Spade";
    }
    return name;
}

bool operator==(Card const &a, Card const &b)
{
    return a.kind == b.kind && a.value == b.value;
}

int main()
{
    size_t size = 100;
    std::vector<Card>cartes = get_cards(size);
    std::unordered_map<Card,int> counts;
    for (Card const& card : cartes) {
        counts[card]++;
    }
    for (auto const& pair : counts) {
        // Affiche le nom de la carte et le nombre de fois qu'elle apparaît dans le vecteur
        std::cout << card_name(pair.first) << " : " << pair.second << std::endl;
    }
    return 0;
}