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

class Player
{
public:
	explicit Player(std::string_view name)
		:m_name{ name }, m_gold{ Random::get(80, 120) }
	{}
	std::string_view getName() const { return m_name; }
	int getInventory(Potion::Type type) const { return m_inventory[type]; }
	int getGold() const { return m_gold; }
	bool buy(Potion::Type type)
	{
		if (m_gold < Potion::costs[type])
			return false;
		++m_inventory[type];
		m_gold -= Potion::costs[type];
		return true;
	}
private:
	std::string m_name{};
	std::array<int, Potion::max_potions> m_inventory{};
	int m_gold{};
};

int charNumToInt(char c) { return c - '0'; }

void ignoreLine() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

Potion::Type whichPotion()
{
	std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
	char c{};
	while (true)
	{
		std::cin >> c;
		if (!std::cin)
		{
			std::cin.clear();
			ignoreLine();
			continue;
		}
		if (c == 'q')
			return Potion::max_potions;
		int i{ charNumToInt(c) };
		if (i >= 0 && i < Potion::max_potions)
			return static_cast<Potion::Type>(i);
		std::cout << "That is an invalid input.  Try again: ";
		ignoreLine();
	}
}

void shop(Player& player)
{
	while (true)
	{
		std::cout << "Here is our selection for today:\n";
		for (auto potion : Potion::types)
			std::cout << potion << ") " << Potion::names[potion] << " costs " << Potion::costs[potion] << '\n';
		Potion::Type potion{ whichPotion() };
		if (potion == Potion::max_potions) return;
		if (player.buy(potion))
			std::cout << "You purchased a potion of " << Potion::names[potion]
			<< ".  You have " << player.getGold() << " gold left.\n\n";
		else
			std::cout << "You can not afford that.\n\n";
	}
}

void printInventory(Player& player)
{
	std::cout << "Your inventory contains: \n";
	for (auto type : Potion::types)
		if (player.getInventory(type) > 0)
			std::cout << player.getInventory(type) << "x potion of " << Potion::names[type] << '\n';
	std::cout << "You escaped with " << player.getGold() << " gold remaining.\n";
}

int main()
{
	std::cout << "Welcome to Roscoe's potion emporium!\nEnter your name : ";
	std::string name{};
	std::getline(std::cin >> std::ws, name);
	Player player{ name };
	std::cout << "Hello, " << player.getName() << ", you have " << player.getGold() << " gold.\n\n";
	shop(player);
	std::cout << '\n';
	printInventory(player);
	std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
	return 0;
}