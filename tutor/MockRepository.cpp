#include "MockRepository.h"

MockRepository& MockRepository::Get()
{
    static MockRepository instance;
    return instance;
}

MockRepository::MockRepository()
{

}

