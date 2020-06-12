//
// Created by Pierre on 10/06/2020.
//

#include "Introduction.hpp"

#include <iostream>

Introduction::Introduction(const std::shared_ptr<IrrlichtController> &ctrl, const std::string name) : GameScene(ctrl, name)
{

}

void Introduction::Init(void)
{
    this->_select = 0;
    this->_image_welcome = this->_ctrl->_driver->getTexture("../assets/menu/back_intro_welcome.jpg");
    this->_image_space = this->_ctrl->_driver->getTexture("../assets/menu/back_intro_space.jpg");
    this->_logo = 0;
//    this->_logo = this->_ctrl->_driver->getTexture("../assets/logo.jpg");
    this->_first_part = this->_ctrl->_driver->getTexture("../assets/menu/first_part.jpg");
    this->_second_part = this->_ctrl->_driver->getTexture("../assets/menu/second_part.jpg");
    this->_third_part = this->_ctrl->_driver->getTexture("../assets/menu/third_part.jpg");
    this->_fourth_part = this->_ctrl->_driver->getTexture("../assets/menu/fourth_part.jpg");
    this->start = std::chrono::steady_clock::now();
}

void Introduction::Update(void)
{
    this->end = std::chrono::steady_clock::now();
    this->elapsed_seconds = end-start;

    if (this->_select == 0) {
        if (this->elapsed_seconds.count() > 0.8)
            this->_logo = 1;
        if (this->elapsed_seconds.count() > 1.6)
            this->_logo = 2;
        if (this->elapsed_seconds.count() > 2.4)
            this->_logo = 3;
        if (this->elapsed_seconds.count() > 5) {
            this->_select = 1;
            this->_ctrl->_music->Play("../assets/audio/music_intro.ogg");
        }
    }
    if (this->elapsed_seconds.count() > 1.5 && (this->_select == 1 || this->_select == 2)) {
        if (this->_select == 1)
            this->_select = 2;
        else
            this->_select = 1;
        this->start = std::chrono::steady_clock::now();
    }
    if (this->_ctrl->_receiver->IsKeyDown(KEY_SPACE))
        this->_ctrl->_context.sceneName = "menuScene";
}

void Introduction::Render(void)
{
    if (this->_select == 0) {
        if (this->_logo == 0)
            this->_ctrl->_driver->draw2DImage(this->_first_part, core::position2d<s32>(0,0));
        if (this->_logo == 1)
            this->_ctrl->_driver->draw2DImage(this->_second_part, core::position2d<s32>(0,0));
        if (this->_logo == 2)
            this->_ctrl->_driver->draw2DImage(this->_third_part, core::position2d<s32>(0,0));
        if (this->_logo == 3)
            this->_ctrl->_driver->draw2DImage(this->_fourth_part, core::position2d<s32>(0,0));
    } else if (this->_select == 1)
        this->_ctrl->_driver->draw2DImage(this->_image_space, core::position2d<s32>(0,0));
    else
        this->_ctrl->_driver->draw2DImage(this->_image_welcome, core::position2d<s32>(0,0));
}

void Introduction::Clear(void)
{
    this->_ctrl->_env->clear();
}