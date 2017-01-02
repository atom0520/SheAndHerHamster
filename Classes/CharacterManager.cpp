#include "CharacterManager.h"
#include "GameManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
CharacterManager * CharacterManager::_instance = nullptr;

CharacterManager * CharacterManager::getInstance(){
	if (_instance == nullptr){
		_instance = new CharacterManager();
		_instance->init();
	}
	return _instance;
}

void CharacterManager::destroyInstance(){
	if (!_instance){
		return;
	}
    
    /*for (std::vector<Character *>::iterator it = _instance->_hamsters.begin();\
         it != _instance->_hamsters.end();){
        if ((*it) != nullptr){
            if((*it)->getReferenceCount()>0){
                (*it)->release();
            }
            (*it)=nullptr;
        }
        it = _instance->_hamsters.erase(it);
    }*/
    
    delete _instance;
	_instance = nullptr;
}

bool CharacterManager::init(){
	_player = nullptr;
    
    /*for (std::vector<Character *>::iterator it = _instance->_hamsters.begin();\
         it != _instance->_hamsters.end();){
        (*it)=nullptr;
        it++;
    }*/

	return true;
}

void CharacterManager::update(){
	/*if (CharacterManager::getInstance()->_player != nullptr){
		CharacterManager::getInstance()->_player->update();
	}

	for (std::vector<Character *>::iterator it = _opponentHamsters.begin(); it != _opponentHamsters.end();){
		if ((*it) != nullptr){
			(*it)->update();
		}
		it++;
	}*/
	
	for (std::vector<Character *>::iterator it = _hamsters.begin(); it != _hamsters.end();){
		if ((*it) != nullptr){
			(*it)->update();
		}
		it++;
	}



	switch (GameManager::getInstance()->_gameMode){
	case (int)GameManager::GameMode::GUIDE_MODE:
	case (int)GameManager::GameMode::RANKING_MODE:{
		for (std::vector<Character *>::iterator it1 = _hamsters.begin(); it1 != _hamsters.end();){
			if ((*it1) != nullptr){
				if (((Hamster*)*it1)->_finish != true\
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::WIN \
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::PAUSE){
					((Hamster*)(*it1))->_ranking = 1;
					for (std::vector<Character *>::iterator it2 = _hamsters.begin(); it2 != _hamsters.end();){
						if ((*it2) != nullptr){
							if ((*it1) != (*it2)){
								if (((Hamster*)*it2)->_state == (int)Hamster::State::WIN\
									|| ((Hamster*)*it2)->_state == (int)Hamster::State::PAUSE){
									((Hamster*)(*it1))->_ranking += 1;
								}else if ((*it2)->getPositionY()<(*it1)->getPositionY()){
									((Hamster*)(*it1))->_ranking += 1;
								}
							}
						}
						it2++;
					}
				}
			}
			it1++;
		}
	}break;
	case (int)GameManager::GameMode::ELIMINATION_MODE:{
		for (std::vector<Character *>::iterator it1 = _hamsters.begin(); it1 != _hamsters.end();){
			if ((*it1) != nullptr){
				if (((Hamster*)*it1)->_finish != true\
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::WIN \
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::LOSE \
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::PAUSE){
					
					((Hamster*)(*it1))->_ranking = 1;
					for (std::vector<Character *>::iterator it2 = _hamsters.begin(); it2 != _hamsters.end();){
						if ((*it2) != nullptr){
							if ((*it1) != (*it2)){
								if (((Hamster*)*it2)->_state == (int)Hamster::State::LOSE){

								}
								else if (((Hamster*)*it2)->_state == (int)Hamster::State::WIN\
									|| ((Hamster*)*it2)->_state == (int)Hamster::State::PAUSE){
									((Hamster*)(*it1))->_ranking += 1;
								}
								else if ((*it2)->getPositionY()<(*it1)->getPositionY()){
									((Hamster*)(*it1))->_ranking += 1;
								}

							}
						}
						it2++;
					}
				}
				else if (((Hamster*)*it1)->_state == (int)Hamster::State::LOSE){
					((Hamster*)(*it1))->_ranking = 1;
					for (std::vector<Character *>::iterator it2 = _hamsters.begin(); it2 != _hamsters.end();){
						if ((*it2) != nullptr){
							if ((*it1) != (*it2)){
								if (((Hamster*)*it2)->_state == (int)Hamster::State::LOSE){
									if ((*it2)->getPositionY() < (*it1)->getPositionY()){
										((Hamster*)(*it1))->_ranking += 1;
									}
								}
								else{
									((Hamster*)(*it1))->_ranking += 1;
								}
								

							}
						}
						it2++;
					}
				}
			}
			it1++;
		}
	}break;
	case (int)GameManager::GameMode::SURVIVAL_MODE:{
		for (std::vector<Character *>::iterator it1 = _hamsters.begin(); it1 != _hamsters.end();){
			if ((*it1) != nullptr){
				if (((Hamster*)*it1)->_finish != true\
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::WIN \
					&& ((Hamster*)*it1)->_state != (int)Hamster::State::PAUSE){
					((Hamster*)(*it1))->_ranking = 1;
					for (std::vector<Character *>::iterator it2 = _hamsters.begin(); it2 != _hamsters.end();){
						if ((*it2) != nullptr){
							if ((*it1) != (*it2)){
								if (((Hamster*)*it2)->_state == (int)Hamster::State::WIN\
									|| ((Hamster*)*it2)->_state == (int)Hamster::State::PAUSE){
									((Hamster*)(*it1))->_ranking += 1;
								}
								else if ((*it2)->getPositionY()<(*it1)->getPositionY()){
									((Hamster*)(*it1))->_ranking += 1;
								}
							}
						}
						it2++;
					}
				}
			}
			//MessageBox(Value(((Hamster*)(*it1))->_ranking).asString().c_str(), Value(((Hamster*)(*it1))->_id).asString().c_str());
			it1++;
		}
	}break;
	}
	

	/*if (CharacterManager::getInstance()->_player != nullptr \
		&& ((Hamster*)CharacterManager::getInstance()->_player)->_finish != true\
		&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::WIN \
		&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::LOSE\
		&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::PAUSE){
		((Hamster*)_player)->_ranking = 1;
		for (std::vector<Character *>::iterator it = _opponentHamsters.begin(); it != _opponentHamsters.end();){
			if ((*it) != nullptr){
				if ((*it)->getPositionY() < _player->getPositionY()){
					((Hamster*)_player)->_ranking += 1;
				}
				else if ((*it)->getPositionY() == _player->getPositionY()){

				}
			}
			it++;
		}
	}

	for (std::vector<Character *>::iterator it1 = _opponentHamsters.begin(); it1 != _opponentHamsters.end();){
		if ((*it1) != nullptr \
			&& ((Hamster*)CharacterManager::getInstance()->_player)->_finish != true\
			&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::WIN \
			&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::LOSE\
			&& CharacterManager::getInstance()->_player->_state != (int)Hamster::State::PAUSE){
			((Hamster*)(*it1))->_ranking = 1;
			if (CharacterManager::getInstance()->_player != nullptr){
				if (_player->getPositionY()<(*it1)->getPositionY()){
					((Hamster*)(*it1))->_ranking += 1;
				}
			}

			for (std::vector<Character *>::iterator it2 = _opponentHamsters.begin(); it2 != _opponentHamsters.end();){
				if ((*it2) != nullptr){
					if ((*it1) != (*it2)){
						if ((*it2)->getPositionY()<(*it1)->getPositionY()){
							((Hamster*)(*it1))->_ranking += 1;
						}
					}
				}
				it2++;
			}
			
		}
		it1++;
	}*/

	for (std::vector<Character *>::iterator it = _masters.begin(); it != _masters.end();){
		if ((*it) != nullptr){
			(*it)->update();
		}
		it++;
	}

	for (std::vector<Character *>::iterator it = _predators.begin(); it != _predators.end();){
		if ((*it) != nullptr){
			(*it)->update();
		}
		it++;
	}

}