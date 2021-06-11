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

	void print(){
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
				std::cout << "Wild";
				break;
			case Symbol::WildDrawFour:
				std::cout << "Te mamaste (aka x4 multicolor)";
				break;
			default:
				std::cout << (int)_symbol << " ";
				break;
		}
	}
};