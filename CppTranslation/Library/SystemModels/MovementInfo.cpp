#include "MovementInfo.h"

namespace Library::SystemModels
{

void MovementInfo::OnCreated()
{
    DBObject::OnCreated();
    RequiredClass = RequiredClass::All;
}

} // namespace Library::SystemModels
