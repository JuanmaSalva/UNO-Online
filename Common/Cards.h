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

	bool isValidMatchup(Card &other) const
	{
		return compareColors(other) || (_symbol == other.getSymbol());
	}

	void print()
	{
		changeColor();

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
			std::cout << "Draw Two ";
			break;
		case Symbols::Wild:
			std::cout << "Wild";
			break;
		case Symbols::WildDrawFour:
			std::cout << "Wild Draw Four";
			break;
		default:
			std::cout << (int)_symbol << " ";
			break;
		}

		std::cout << "\033[0;97m"; //Vuelve a poner el color en blanco
	}

	void changeColor()
	{
		//cambia el color de la consola
		switch (_color)
		{
		case Colors::Red:
			std::cout << "\033[0;31m";
			break;
		case Colors::Yellow:
			std::cout << "\033[0;33m";
			break;
		case Colors::Green:
			std::cout << "\033[0;32m";
			break;
		case Colors::Blue:
			std::cout << "\033[0;34m";
			break;
		default:
			std::cout << "\033[0;95m";
			break;
		}
	}
};