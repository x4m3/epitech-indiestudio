/*
** EPITECH PROJECT, 2020
** epitech-indiestudio
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene(const std::shared_ptr<IrrlichtController> &ctrl, const std::string name) : _id(name), _ctrl(ctrl)
{

}

GameScene::~GameScene()
{

}

void GameScene::Init(void)
{
    irr::SKeyMap keyMap[5];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
    keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;

    _ctrl->_scene_mgr->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 5);
    irr::scene::ICameraSceneNode *camera = _ctrl->_scene_mgr->getActiveCamera();
    camera->setPosition(irr::core::vector3df(0, 45, 0));
    camera->setRotation(irr::core::vector3df(90, 180, 0));
}

void GameScene::AddGameObject(const std::shared_ptr<GameObject> &obj)
{
    _obj_list.push_back(obj);
}

#include <iostream>

void GameScene::Update(void)
{
    int idx = 0;
    for (auto i = _obj_list.begin(); i != _obj_list.end(); i++) {
        i->get()->Update();
        irr::core::vector3df v = i->get()->GetPosition();
        std::string name = i->get()->GetId();
        //printf("%s %0.2f %0.2f %0.2f\n", name.c_str(), v.X, v.Y, v.Z);
    }
}

void GameScene::Render(void)
{
    for (auto i = _obj_list.begin(); i != _obj_list.end(); i++)
        i->get()->Render();
    _ctrl->_scene_mgr->drawAll();

}

void GameScene::Delete(void)
{

}

const std::string &GameScene::GetId(void)
{
    return _id;
}