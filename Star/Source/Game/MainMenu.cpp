#include "MainMenu.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../../Source/Game/GameObjects/TextButton.h"
#include "../../Source/Engine/IText.h"
MainMenu::MainMenu(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = MainMenuLevel;
}

MainMenu::~MainMenu()
{
}

bool MainMenu::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY= Graphics->GetWindowHeight();
	ITexture* BackgroundTexture = Graphics->CreateTexture(L"Resource/Textures/R.png", "Background");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");


	IShader* BackgroundShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	IShader* ButtonShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	IRenderable* StartRender = Graphics->CreateFade(ButtonShader, ButtonTexture, Color);
	IRenderable* QuitRender = Graphics->CreateFade(ButtonShader, ButtonTexture, Color);
	IRenderable* BackgroundRender = Graphics->CreateBillboard(BackgroundShader, BackgroundTexture);
	
	IText* StartText = Graphics->CreateText("Start Game", 0, 0, 1,1,0,1,0,0,1);
	IText* QuitText = Graphics->CreateText("Quit Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	StartButton = new TextButton(StartRender, StartText, ButtonShader, screenX, screenY);
	StartButton->SetPosition( ( - screenX / 2) + 200, -200);
	StartButton->SetTextRelativePosition(-100,50);
	StartButton->SetScale(2, 2);
	StartButton->AddButtonPosition(170, 0);
	StartButton->SetButtonScale(5, 2);
	QuitButton = new TextButton(QuitRender, QuitText , ButtonShader, screenX, screenY);
	QuitButton->SetPosition((-screenX / 2) + 200, -400);
	QuitButton->SetTextRelativePosition(-100, 50);
	QuitButton->SetScale(2, 2);
	QuitButton->AddButtonPosition(170, 0);
	QuitButton->SetButtonScale(5, 2);

	QuitButton->Register(Graphics);
	StartButton->Register(Graphics);

	DebugText = Graphics->CreateText("Hello");
	Graphics->AddText(DebugText);
	return true;
}

void MainMenu::Update(float DeltaTime)
{
	float val = Input->GetValue(InputAction::LeftStickYAxis);
	DebugString = "Axis: " + std::to_string(ButtonSelection);
	DebugText->SetText(DebugString.data());
	if (val < 0)
	{
		ButtonSelection = ButtonSelection >= HighestButtonSelection ? HighestButtonSelection : ButtonSelection + 1;
	} 
	else if (val > 0)
	{
		ButtonSelection = ButtonSelection <= 0 ? 0 : ButtonSelection - 1;
	}
	if (Input->IsPressed(InputAction::ButtonBottom))
	{
		switch (ButtonSelection)
		{
		case 0:
			LevelSwitchKey = GameLevel;
			break;
		case 1:
			LevelSwitchKey = QuitProgram;
			break;
		default:
			LevelSwitchKey = QuitProgram;
			break;
		}
	}

}

void MainMenu::Cleanup()
{
	Graphics->Cleanup();
	delete StartButton;
	delete QuitButton;
}
