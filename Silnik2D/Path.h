#pragma once
#include <vector>
#include <memory>
#include "ShapeObject.h"

void GenerateLilies(bool lily_grid[10][9], std::vector<std::unique_ptr<ShapeObject>>& objects);