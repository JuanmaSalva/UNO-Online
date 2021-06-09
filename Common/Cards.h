#pragma once

enum class Colors : short
{
	Wild = 0,
	Red = 1,
	Yellow = 2,
	Green = 3,
	Blue = 4,
	NULL
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
	WildDrawFour,
	NULL
};

class Card
{
protected:
	Colors _color;
	Symbol _symbol;

public:
	Card() : Card(Colors::NULL,Symbol::NULL) {}
	Card(Colors color, Symbol symbol) : _color(color), _symbol(symbol) {}

	Colors getColor() const {return _color;}
	Symbol getSymbol() const {return _symbol;}
};