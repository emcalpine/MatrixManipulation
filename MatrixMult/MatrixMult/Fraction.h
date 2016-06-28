/*
 *  Eric McAlpine
 *  Fraction.h
 *
 * 
 *  Purpose: Define a fraction 
 *
 *
 */
 
 #ifndef FRACTION_H
 #define FRACTION_H
 
class Fraction
{
public:
  Fraction();
  Fraction(int n, int d);
  Fraction(Fraction f);
  Fraction(string s);
  
  bool operator==(Fraction f);
  Fraction operator=(Fraction f);
  Fraction operator+(Fraction f);
  Fraction operator-(Fraction f);
  Fraction operator*(Fraction f);
  Fraction operator/(Fraction f);
  
  bool setNumerator(int n);
  bool setDenominator(int d);
  int getNumerator();
  int getDenominator();
  
  string toString();

private:
  int denominator;
  int numerator;
  void reduce();
  
  static const int DEFAULT_NUM;
  static const int DEFAULT_DEN;
};

#endif
