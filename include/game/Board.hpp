#pragma once

#include "Constants.hpp"

class Board
{
  public:
    auto initialize() -> bool;
    auto render() -> void;
    auto shutdown() -> void;
  private:
};
