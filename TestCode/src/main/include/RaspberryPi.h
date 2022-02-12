#include "Fermat.h"

class RaspberryPi{
    public:
        RaspberryPi(DalekDrive *drive);
        bool SwerveTurn(double degree, double distance);
    private:
        DalekDrive *m_drive;
};