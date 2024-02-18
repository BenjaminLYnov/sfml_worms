#ifndef COLLIDERCALLBACK_H
#define COLLIDERCALLBACK_H

#pragma once

#include <functional>
#include "GameObject/GameObject.h"

using ColliderCallback = std::function<void(GameObject*)>;

#endif