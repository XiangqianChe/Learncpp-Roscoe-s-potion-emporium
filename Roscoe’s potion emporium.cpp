#include <array>
#include <iostream>
#include "Random.h"

namespace Potion
{
	enum Type
	{
		healing,
		mana,
		speed,
		invisisbility,
		max_potions,
	};

	constexpr std::array<Type, max_potions> types{ healing, mana, speed, invisisbility };
	using namespace std::string_view_literals;
	constexpr std::array<std::string_view, max_potions> names{ "healing"sv, "mana"sv, "speed"sv, "invisibility"sv };
	constexpr std::array<int, max_potions> costs{ 20, 30, 12, 50 };

	static_assert(std::size(types) == max_potions);
	static_assert(std::size(names) == max_potions);
	static_assert(std::size(costs) == max_potions);
};

void shop()
{
	std::cout << "Here is our selection for today:\n";
	for (auto potion : Potion::types)
		std::cout << potion << ") " << Potion::names[potion] << " costs " << Potion::costs[potion] << '\n';
}

class Player
{
private:
	std::string m_name{};
	std::array<int, Potion::max_potions> m_inventory{};
	int m_gold{};
public:
	explicit Player(std::string_view name)
		:m_name{ name }, m_gold{ Random::get(80, 120) }
	{}
	std::string_view getName() const { return m_name; }
	int getInventory(Potion::Type p) const { return m_inventory[p]; }
	int getGold() const { return m_gold; }
};

int main()
{
	std::cout << "Welcome to Roscoe's potion emporium!\nEnter your name : ";
	std::string name{};
	std::getline(std::cin >> std::ws, name);
	Player p{ name };
	std::cout << "Hello, " << p.getName() << ", you have " << p.getGold() << " gold.\n\n";
		shop();
		std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
	return 0;
}