/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 09:25:13 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/19 10:53:15 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_DB_INSTRUCTION
#define SIMPLE_DB_INSTRUCTION

#include "bmgr.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>

class Instruction
{
public:
    typedef std::shared_ptr<std::vector<Instruction>> vector;

    /**
    * 将指令字符串转换为指令
    * ","前为操作，0为读，1为写
    * ","后为所操作的`page_id`
    */
    explicit Instruction(const std::string &str)
    {
        int sp = str.find(',');
        std::string left = str.substr(0, sp);
        std::string right = str.substr(sp + 1, str.length());
        is_write = left == std::string("1");
        page_id = std::stoi(right);
    }

    /**
    * 直接构造指令
    * @param is_write 是否为写
    */
    Instruction(bool is_write, int page_id) : is_write(is_write), page_id(page_id){};

    /**
    * 执行指令
    * @param bm BMgr的shared_ptr
    */
    void execute(const BMgr::sptr &bm)
    {
        if (is_write)
        {
            auto new_frame = generate_frame();
            bm->write_page(page_id, new_frame);
        }
        else
        {
            bm->read_page(page_id);
        }
    };

    /**
    * 从指令文件中读取指令，生成vector
    * @param filename 指令文件名
    */
    static Instruction::vector read_instructions(const std::string &filename)
    {
        std::ifstream test_file(filename);
        assert(test_file.is_open());
        std::string line;
        auto ins_vector = std::make_shared<std::vector<Instruction>>();
        while (getline(test_file, line))
        {
            ins_vector->emplace_back(line);
        }
        return ins_vector;
    }

private:
    bool is_write;
    int page_id;
};
#endif //SIMPLE_DB_INSTRUCTION
