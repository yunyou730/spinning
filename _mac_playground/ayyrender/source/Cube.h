#pragma once
#include "Geometric.h"

namespace ayy {
class Cube : public Geometric
{

private:
    virtual void InitVertices() override;
};
}
