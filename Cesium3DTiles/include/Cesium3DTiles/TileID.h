#pragma once

#include "CesiumGeometry/QuadtreeTileID.h"
#include "CesiumGeometry/OctreeTileID.h"
#include <variant>
#include <string>

namespace Cesium3DTiles {

    typedef std::variant<std::string, CesiumGeometry::QuadtreeTileID, CesiumGeometry::OctreeTileID, CesiumGeometry::QuadtreeChild> TileID;

}