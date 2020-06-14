/*
** EPITECH PROJECT, 2020
** epitech-indiestudio
** File description:
** [enter description here]
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(const std::shared_ptr<IrrlichtController> &ctrl, const std::string name) : GameObject(ctrl, irr::core::vector3df(5, 5, 5), name)
{
    _position = irr::core::vector3df(0, 0, 0);
    _rotation = irr::core::vector3df(0, 0, 0);
    _node = NULL;
}

void PowerUp::Init(void)
{
    std::random_device dev;
    std::mt19937 _prob(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, 2);

    if (distribution(_prob) == 1)
        _node = _ctrl->_scene_mgr->addAnimatedMeshSceneNode(_ctrl->_scene_mgr->getMesh(SKATE));
    else
        _node = _ctrl->_scene_mgr->addAnimatedMeshSceneNode(_ctrl->_scene_mgr->getMesh(SKATE));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node->setMD2Animation(scene::EMAT_STAND);
}

void PowerUp::SetPosition(irr::core::vector3df position)
{
    _position = position;
    if (_node)
        _node->setPosition(position);
    _collider->SetPosition(position);
}

PowerUp::~PowerUp()
{

}

void PowerUp::Update(std::vector<std::shared_ptr<IGameObject>> &obj)
{

}

void PowerUp::Delete(void)
{
    _status = DELETED;
}

const IGameObject::type_e PowerUp::GetType(void)
{
    if (_id.compare("skate") == 0)
        return IGameObject::type_e::PWU_SKATE;
    if (_id.compare("wall_pass") == 0)
        return IGameObject::type_e::PWU_WALL_PASS;
    return IGameObject::type_e::BONUS;
}
