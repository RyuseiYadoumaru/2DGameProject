#pragma once

#include "../../Systems/Contents/Objects/Scene/Scene.h"

#include "../../Systems/Contents/Objects/GameObject/Character.h"
#include "../../Systems/Contents/Objects/GameObject/Item.h"
#include "../../Systems/Contents/Objects/GameObject/Widget.h"

#include "../../Systems/Contents/Objects/Component/Transform.h"
#include "../../Systems/Contents/Objects/Component/BoxCollider.h"

#include "../../Systems/Contents/Objects/Component/Script.h"

#include "../../Systems/Contents/Objects/Component/Camera.h"
#include "../../Systems/Contents/Objects/Component/RectRenderer.h"
#include "../../Systems/Contents/Objects/Component/WidgetRenderer.h"
#include "../../Systems/Contents/Objects/Component/SpriteRenderer.h"
#include"../../Systems/Contents/Objects/Component/TextRenderer.h"
#include"../../Systems/Contents/Objects/Component/TextMeshRenderer.h"


using Order = unsigned int;
using ID	= unsigned int;

using namespace myGame::Object;