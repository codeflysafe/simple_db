/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lru.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 09:42:12 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/20 15:04:50 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_DB_LRU
#define SIMPLE_DB_LRU
#include <list>
#include <unordered_map>

class LRU
{
public:
    LRU();

    ~LRU();

    /**
         * 选择一个victim，将其从链表中移出
         */
    int get_victim();

    /**
         * 将frame放入头部
         */
    void push(int id);

    /**
         * 将frame标记为最新使用，从list中移动至头部
         */
    void update(int id);

private:
    std::list<int> *lru_list;
    std::unordered_map<int, std::list<int>::iterator> *lru_map;
};

#endif