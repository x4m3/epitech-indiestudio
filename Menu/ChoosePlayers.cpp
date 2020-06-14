//
// Created by Pierre on 09/06/2020.
//

#include "ChoosePlayers.hpp"

ChoosePlayers::ChoosePlayers(const std::shared_ptr<IrrlichtController> &ctrl, const std::string name) : AScene(ctrl, name)
{
}

void ChoosePlayers::Init(void)
{
    this->_buttonOnePlayer = std::make_unique<Button>(this->_ctrl->_device, vector2d<int>(640, HEIGHT - 100), vector2d<int>(0, 100), GUI_ID_ONE_PLAYER_BUTTON, ONE_PLAYER_GREY_C, ONE_PLAYER_C);
    this->_buttonTwoPlayers = std::make_unique<Button>(this->_ctrl->_device, vector2d<int>(640, HEIGHT - 100), vector2d<int>(640, 100), GUI_ID_TWO_PLAYERS_BUTTON, TWO_PLAYERS_GREY_C, TWO_PLAYERS_C);
    this->_buttonBack = std::make_unique<Button>(this->_ctrl->_device, vector2d<int>(1280, 100), vector2d<int>(0, 0), GUI_ID_BACK_BUTTON, BUTTON_BACK_GREY_C, BUTTON_BACK_C);
    this->_buttonSound = std::make_unique<Sound>(this->_ctrl->_context, BUTTON_SOUND_C);
}

void ChoosePlayers::Update(void)
{
    if (this->_buttonOnePlayer->updateButton(this->_ctrl->_context))
        this->_buttonSound->Play();
    if (this->_buttonTwoPlayers->updateButton(this->_ctrl->_context))
        this->_buttonSound->Play();
    if (this->_buttonBack->updateButton(this->_ctrl->_context))
        this->_buttonSound->Play();
}

void ChoosePlayers::Render(void)
{
    this->_ctrl->_env->drawAll();
}

void ChoosePlayers::Clear(void)
{
    this->_ctrl->_env->clear();
}