/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lru.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:16:54 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:17:04 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lru.h"

LRU::LRU()
{
    lru_list = new std::list<int>();
    lru_map = new std::unordered_map<int, std::list<int>::iterator>();
}

LRU::~LRU()
{
    free(lru_list);
    free(lru_map);
}

int LRU::get_victim()
{
    int victim = lru_list->back();
    lru_list->pop_back();
    return victim;
}

void LRU::push(int id)
{
    lru_list->push_front(id);
    (*lru_map)[id] = lru_list->begin();
}

void LRU::update(int id)
{
    auto iter = (*lru_map)[id];
    lru_list->erase(iter);
    push(id);
}