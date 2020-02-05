#include "stdafx.h"
#include "MousePointer.h"







//			auto mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
//			Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
//			Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
//			
//			
//			Vector2 InputManager::GetMouseWorldPosition()
//			{
//			    return mousePosition * (DesignResolution / ApplicationManager::GetInstance()->GetResolution());
//			}

Vector2 MousePointer::GetMousePosition()
{

	pos = _ptMouse + CAMERA->GetPosition();

	Vector3 mouse(pos.x, pos.y, 1);
	
	Vector3 changePos = Matrix3x3::Mul(mouse, CAMERA->GetTransMatrix().GetInverseMatrix());



	return Vector2(changePos.GetX(), changePos.GetY());
}
