//
//  Quad.hpp
//  ayyrender
//
//  Created by bytedance on 2021/2/9.
//

#pragma once
#include "Geometric.h"

namespace ayy {
class Quad : public Geometric
{
private:
    virtual void InitVertices() override;
};
}

