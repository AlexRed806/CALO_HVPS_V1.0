#include <vector>
#include "MOS_callbackInterface.h"

class CALO_HVPS;

class Quasar_Callback :  public MOS_CallbackInterface
{
public:
    Quasar_Callback();
    Quasar_Callback(CALO_HVPS *hvTracker);

    void  dataChange(std::vector<std::string> listElements, std::vector<std::string> listValues);
    void abort();

    void infoDebug();
private:
    CALO_HVPS  *m_hvCalo;
};

