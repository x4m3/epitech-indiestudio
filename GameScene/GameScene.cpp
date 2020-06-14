/*
** EPITECH PROJECT, 2020
** epitech-indiestudio
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "Player.hpp"
#include "MapGenerator.hpp"
#include "AssetSelector.hpp"
#include <iostream>

GameScene::GameScene(const std::shared_ptr<IrrlichtController> &ctrl, const std::string name) : AScene(ctrl, name)
{

}

GameScene::~GameScene()
{

}

std::shared_ptr<IGameObject> GameScene::initPowerUp(irr::core::vector3df pos, const std::string name)
{
    std::shared_ptr<PowerUp> power_up = std::make_shared<PowerUp>(_ctrl, name);
    power_up->Init();
    power_up->SetPosition(pos);
    return power_up;
}

void GameScene::addPowerUp(unsigned int prob)
{
    std::random_device dev;
    std::mt19937 _prob(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1,100);
    std::vector<std::shared_ptr<IGameObject>>::iterator ptr;

    for (ptr = _obj_list.begin(); ptr < _obj_list.end(); ptr++)
        if (ptr->get()->GetType() == IGameObject::type_e::GROUND || ptr->get()->GetType() == IGameObject::type_e::DESTRUCTABLE_WALL)
            if (distribution(_prob) <= prob) {
                _obj_list.push_back(initPowerUp(ptr->get()->GetPosition(), "skate"));
            }
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

    _ctrl->_scene_mgr->addCameraSceneNode(0, vector3df(30, 57 , 24), vector3df(10, -300, 24));
    irr::scene::ICameraSceneNode *camera = _ctrl->_scene_mgr->getActiveCamera();
    camera->setPosition(irr::core::vector3df(30, 57, 24));
    std::shared_ptr<Player> p = std::make_shared<Player>(_ctrl, "p1", Player::WHITE, Player::LEFT);
    std::shared_ptr<Player> p2 = std::make_shared<Player>(_ctrl, "p2", Player::GREEN, Player::RIGHT);
    p->Init();
    p2->Init();
    p->SetPosition(irr::core::vector3df(0, 0, 0));
    p2->SetPosition(irr::core::vector3df(20, 0, 0));
    AddGameObject(p);
    AddGameObject(p2);
    this->_ctrl->_music->Play(AssetSelector(MUSIC_GAME).string());
    std::shared_ptr<mapGenerator> map = std::make_shared<mapGenerator>(vector3df(0,0,0), 6, 11, 11);
    map->generate(_ctrl, _obj_list, AssetSelector(FLOOR_ASSET).string(), 100);
    map->generateWall(_ctrl, _obj_list, AssetSelector(WALL1_ASSET).string());
    map->generateBorder(_ctrl, _obj_list, AssetSelector(WALL1_ASSET).string());
    map->generateBlock(_ctrl, _obj_list, AssetSelector(WALL2_ASSET).string(), 30);
    addPowerUp(3);
}
