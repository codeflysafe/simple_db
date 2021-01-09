/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:24:52 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:16:23 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_DB_COMMON
#define SIMPLE_DB_COMMON

#include <cstdlib>
#include <memory>
#include <list>
#include <unordered_map>

#define DB_FILE_PATH "./data.dbf"
#define MAX_PAGE_NUM (50 * 1024)           //51200，一个文件存放的最大page数
#define FIRST_PAGE_SIZE (MAX_PAGE_NUM * 4) //200kb，为第一个page的大小，存放page数与索引
#define FRAME_SIZE 4096
#define DEF_BUF_SIZE 1024

struct Frame
{
    typedef std::shared_ptr<Frame> sptr;
    char field[FRAME_SIZE] = {};
};

/**
     * 随机生成frame内容
     */
Frame::sptr generate_random_frame();

#endif //ADB_PROJECT_COMMON_HPP
