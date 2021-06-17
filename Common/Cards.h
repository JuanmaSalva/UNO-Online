#pragma once
#include <iostream>

enum class Colors : short
{
	Red = 0,
	Yellow = 1,
	Green = 2,
	Blue = 3,
	Wild = 4
	//NULL
};

enum class Symbols : short
{
	Zero = 0,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Reverse,
	Skip,
	DrawTwo,
	Wild,
	WildDrawFour
	//NULL
};

class Card
{
protected:
	Colors _color;
	Symbols _symbol;

public:
	Card() : Card(Colors::Red, Symbols::DrawTwo) {}
	Card(Colors color, Symbols symbol) : _color(color), _symbol(symbol) {}

	Colors getColor() const { return _color; }
	Symbols getSymbol() const { return _symbol; }

	void setColor(Colors color) { _color = color; }

	bool compareColors(Card &other) const
	{
		return _color == other.getColor() || _color == Colors::Wild || other.getColor() == Colors::Wild;
	}

	void print()
	{
		//imprimimos el color
		switch (_color)
		{
		case Colors::Red:
			std::cout << "Red ";
			break;
		case Colors::Yellow:
			std::cout << "Yellow ";
			break;
		case Colors::Green:
			std::cout << "Green ";
			break;
		case Colors::Blue:
			std::cout << "Blue ";
			break;
		case Colors::Wild:
		default:
			break;
		}

		//imprimimos el simbolo
		switch (_symbol)
		{
		case Symbols::Reverse:
			std::cout << "Reverse ";
			break;
		case Symbols::Skip:
			std::cout << "Skip ";
			break;
		case Symbols::DrawTwo:
			std::cout << "DrawTwo ";
			break;
		case Symbols::Wild:
			std::cout << "Wild";
			break;
		case Symbols::WildDrawFour:
			std::cout << "Te mamaste (aka x4 multicolor)";
			break;
		default:
			std::cout << (int)_symbol << " ";
			break;
		}
	}
};