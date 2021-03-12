#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "RegistrosCoordenados.h"

using namespace std;

RegistrosCoordenados::RegistrosCoordenados()
{
    this->stateCode;
    this->capital;
    this->cityCode;
    this->cityName;
    this->latitude;
    this->longitude;
}

RegistrosCoordenados::~RegistrosCoordenados(){}

int RegistrosCoordenados::getStateCode()
{
    return this->stateCode;
}
string RegistrosCoordenados::getCityCode()
{
    return this->cityCode;
}
string RegistrosCoordenados::getCityName()
{
    return this->cityName;
}
double RegistrosCoordenados::getLatitude()
{
    return this->latitude;
}
double RegistrosCoordenados::getLongitude()
{
    return this->longitude;
}
bool RegistrosCoordenados::getCapital()
{
    return this->capital;
}

void RegistrosCoordenados::setStateCode(int stateCode)
{
    this->stateCode = stateCode;
}
void RegistrosCoordenados::setCityCode(string cityCode)
{
    this->cityCode = cityCode;
}
void RegistrosCoordenados::setCityName(string cityName)
{
    this->cityName = cityName;
}
void RegistrosCoordenados::setLatitude(double latitude)
{
    this->latitude = latitude;
}
void RegistrosCoordenados::setLongitude(double longitude)
{
    this->longitude = longitude;
}
void RegistrosCoordenados::setCapital(bool capital)
{
    this->capital = capital;
}