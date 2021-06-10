#pragma once
#include <iostream>

enum class Colors : short
{
	Wild = 0,
	Red = 1,
	Yellow = 2,
	Green = 3,
	Blue = 4
	//NULL
};

enum class Symbol : short
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
	Symbol _symbol;

public:
	Card() : Card(Colors::Red,Symbol::DrawTwo) {}
	Card(Colors color, Symbol symbol) : _color(color), _symbol(symbol) {}

	Colors getColor() const {return _color;}
	Symbol getSymbol() const {return _symbol;}

	void Print(){
		//imprimimos el simbolo
		switch (_symbol)
		{
			case Symbol::Reverse:
				std::cout << "Reverse ";
				break;
			case Symbol::Skip:
				std::cout << "Skip ";
				break;
			case Symbol::DrawTwo:
				std::cout << "DrawTwo ";
				break;
			case Symbol::Wild:
				std::cout << "Wild\n";
				break;
			case Symbol::WildDrawFour:
				std::cout << "Te mamaste ";
				break;
			default:
				std::cout << (int)_symbol << "\n";
				break;
		}

		//imprimimos el color
		switch (_color)
		{
			case Colors::Red:
				std::cout << "Red\n";
				break;
			case Colors::Yellow:
				std::cout << "Yellow\n";
				break;
			case Colors::Green:
				std::cout << "Green\n";
				break;
			case Colors::Blue:
				std::cout << "Blue\n";
				break;
			default:
				break;
		}
	}
};