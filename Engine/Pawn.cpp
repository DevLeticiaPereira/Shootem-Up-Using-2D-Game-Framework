#include "Pawn.h"
#include "InputManager.h"

Pawn::Pawn()
{
	GameEngine::GetInstance()->GetInputManager()->AddPawn(this);
}

