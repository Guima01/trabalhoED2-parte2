#include <string>

using namespace std;

class RegistrosCoordenados
{

private:
    int stateCode;
    string cityCode;
    string cityName;
    double latitude;
    double longitude;
    bool capital;

public:
    RegistrosCoordenados();
    ~RegistrosCoordenados();
    int getStateCode();
    string getCityCode();
    string getCityName();
    double getLatitude();
    double getLongitude();
    bool getCapital();
    void setStateCode(int stateCode);
    void setCityCode(string cityCode);
    void setCityName(string cityName);
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setCapital(bool capital);
};