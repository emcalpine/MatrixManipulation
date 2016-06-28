/********************************************
 * Eric McAlpine
 * Fraction.cpp
 *
 * Purpose: Be a fraction that auto-reduces for ease of use.
 */
 
 
using namespace std;

DEFAULT_NUM = 0;
DEFAULT_DEN = 1;


//**************************
//     Constructors
//**************************
Fraction::Fraction()
{
  numerator = DEFAULT_NUM;
  denominator = DEFAULT_DEN;
}

Fraction::Fraction(int n, int d)
{
  numerator = n;
  denominator = (d != 0) ? d : DEFAULT_DEN;
}

Fraction::Fraction(Fraction f)
{
  numerator = f.numerator;
  denominator = f.denominator;
}

Fraction::Fraction(string s)
{
  numerator = DEFAULT_NUM;
  denominator = DEFAULT_DEN;
  bool stillNum = true;
  char ary[10];
  int slashIndex = -1;
  
  for (int i = 0; i < s.length(); i++)
  {
    if (s.at(i) == '/')
    {
     stillNum=false;
     slashIndex = i;
     numerator = atoi(ary);
     for (int j = 0; j < 10; j++)
      ary[j] = '0';
    }
    else if (s.at(i) == ' ')
    {
     break;
    }
    else if (stillNum)
     ary[i] = s[i];
    else
     ary[i-slashIndex] = s[i];
  }
  denominator = atoi(ary);
}


//**************************
//    Operator Overloads
//**************************
bool Fraction::operator==(Fraction f)
{
  if ((this->numerator == f.numerator) &&
      (this->denominator == f.denominator))
    return true;
  else
    return false;
}

Fraction Fraction::operator=(Fraction f)
{
  this->numerator = f.numerator;
  this->denominator = f.denominator;
  return *this;
}

Fraction Fraction::operator+(Fraction f)
{
  this->numerator = (this->numerator * f.denominator) + (f.numerator * this->denominator);
  this->denominator *= f.denominator;
  this.reduce();
  return *this;
}

Fraction Fraction::operator-(Fraction f)
{
  this->numerator = (this->numerator * f.denominator) - (f.numerator * this->denominator);
  this->denominator *= f.denominator;
  this.reduce();
  return *this;
}

Fraction Fraction::operator*(Fraction f)
{
  this->numerator *= f.numerator;
  this->denominator *= f.denominator;
  this.reduce();
  return *this;
}

Fraction Fraction::operator/(Fraction f)
{
  this->numerator *= f.denominator;
  this->denominator *= f.numerator;
  this.reduce();
  return *this;
}


//**************************
//    Public Functions
//**************************
bool Fraction::setNumerator(int n)
{
  numerator = n;
  return true;
}

bool Fraction::setDenominator(int d)
{
  bool success;
  if (d > 0)
  {
    denominator = d;
    success = true;
  }
  else
    success = false;
    
  return success;
}

int Fraction::getNumerator() { return numerator; }

int Fraction::getDenominator() { return denominator; }

string Fraction::toString()
{
  string str;
  str = numerator + "/" + denominator;
  return str;
}

//*******************************
//      Private functions
//*******************************
void Fraction::reduce()
{
  // correct signs
  numerator = (denominator > 0) ? numerator : -numerator;
  denominator = (denominator > 0) ? denominator : -denominator;
  
  for(int gcf = denominator; gcf > 1; gcf --)
  {
    if((numerator % gcf == 0) && (denominator % gcf == 0))
    {
      numerator /= gcf;
      denominator /= gcf;
      
      gcf = denominator;  //reset gcf
    }
  }
}
