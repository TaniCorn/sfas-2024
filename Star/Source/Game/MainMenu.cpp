#include "MainMenu.h"
#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"

#include "../../Source/Game/GameObjects/TextButton.h"
#include "../../Source/Engine/IText.h"
#include "../Engine/Implementation/InputSelection.h"
MainMenu::MainMenu(IGraphics* Graphics, IInput* InputIn) : ILevel(Graphics, InputIn)
{
	LevelSwitchKey = MainMenuLevel;
}

MainMenu::~MainMenu()
{
	delete GamepadSelection;
	delete Buttons[0];
	delete Buttons[1];
}

bool MainMenu::Load()
{
	float screenX = Graphics->GetWindowWidth();
	float screenY= Graphics->GetWindowHeight();
	ITexture* BackgroundTexture = Graphics->CreateTexture(L"Resource/Textures/R.png", "Background");
	ITexture* ButtonTexture = Graphics->CreateTexture(L"Resource/Textures/ButtonNormal.png", "Button");


	IShader* BackgroundShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");
	IShader* ButtonShader = Graphics->CreateShader(L"Resource/Shaders/DynamicColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0");

	IRenderable* StartRender = Graphics->CreateFade(ButtonShader, ButtonTexture, nullptr);
	IRenderable* QuitRender = Graphics->CreateFade(ButtonShader, ButtonTexture, nullptr);
	IRenderable* BackgroundRender = Graphics->CreateBillboard(BackgroundShader, BackgroundTexture);
	
	IText* StartText = Graphics->CreateText("Start Game", 0, 0, 1,1,0,1,0,0,1);
	IText* QuitText = Graphics->CreateText("Quit Game", 0, 0, 1, 1, 0, 1, 0, 0, 1);
	Buttons[0] = new TextButton(StartRender, StartText, ButtonShader, screenX, screenY);
	Buttons[0]->SetPosition( ( - screenX / 2) + 200, -200);
	Buttons[0]->SetTextRelativePosition(-100,50);
	Buttons[0]->SetScale(2, 2);
	Buttons[0]->AddButtonPosition(170, 0);
	Buttons[0]->SetButtonScale(5, 2);
	Buttons[1] = new TextButton(QuitRender, QuitText , ButtonShader, screenX, screenY);
	Buttons[1]->SetPosition((-screenX / 2) + 200, -400);
	Buttons[1]->SetTextRelativePosition(-100, 50);
	Buttons[1]->SetScale(2, 2);
	Buttons[1]->AddButtonPosition(170, 0);
	Buttons[1]->SetButtonScale(5, 2);

	for (int i = 0; i < 2; i++)
	{
		Buttons[i]->Register(Graphics);
	}
	Buttons[0]->BoundFunction = std::bind(&MainMenu::StartGame, this);
	Buttons[1]->BoundFunction = std::bind(&MainMenu::QuitGame, this);

	StartRender->BindParam(Buttons[0]->GetColorBind());
	QuitRender->BindParam(Buttons[1]->GetColorBind());

	GamepadSelection = new InputSelection(Buttons[0]);
	GamepadSelection->AddButtonLink(Buttons[0], Buttons[1], Down);
	GamepadSelection->AddButtonLink(Buttons[1], Buttons[0], Up);
	return true;
}


void MainMenu::Update(float DeltaTime)
{
	GamepadSelection->Update(Input);

}

void MainMenu::Cleanup()
{
	Graphics->Cleanup();
}


void MainMenu::QuitGame()
{
	LevelSwitchKey = QuitProgram;
}

void MainMenu::StartGame()
{
	LevelSwitchKey = GameLevel;
}
