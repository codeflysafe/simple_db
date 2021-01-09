/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsmgr.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:22:36 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:42:07 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dsmgr.h"
#include <iostream>

// 首部存放信息的page不计入page_id，page_id从0开始
DSMgr::DSMgr()
{
    db_file = nullptr;
    open_file();
    read_first_page();
    io_count = 0;
}

DSMgr::~DSMgr()
{
    write_first_page();
    close_file();
}

bool DSMgr::is_page_exist(int page_id)
{
    return page_id > 0 && page_id <= first_page[0] && get_use(page_id);
}

int DSMgr::read_page(int page_id, Frame *frm)
{
    if (!is_page_exist(page_id))
    {
        return -1;
    }
    unsigned int page_pointer = get_page_pointer(page_id);
    seek(page_pointer);
    fread(frm->field, sizeof(char), FRAME_SIZE, db_file);
    inc_io_count();
    return 0;
}

int DSMgr::write_page(int page_id, Frame *frm)
{
    if (!is_page_exist(page_id))
    {
        return -1;
    }
    unsigned int page_pointer = get_page_pointer(page_id);
    seek(page_pointer);
    fwrite(frm->field, sizeof(char), FRAME_SIZE, db_file);
    inc_io_count();
    return 0;
}

int DSMgr::create_new_page(Frame *frm)
{
    int page_id = get_pages_num() + 1;
    int page_pointer = (page_id - 1) * (int)sizeof(frm->field) + FIRST_PAGE_SIZE;
    set_page_pointer(page_id, page_pointer);
    seek(page_pointer);
    fwrite(frm->field, sizeof(char), FRAME_SIZE, db_file);
    inc_pages_num();
    inc_io_count();
    return page_id;
}

void DSMgr::open_file()
{
    db_file = fopen(DB_FILE_PATH, "rb+");
    if (db_file == nullptr)
    {
        db_file = fopen(DB_FILE_PATH, "wb+");
        char temp[FIRST_PAGE_SIZE] = {0};
        fwrite(&temp, FIRST_PAGE_SIZE * sizeof(char), 1, db_file);
        close_file();
        db_file = fopen(DB_FILE_PATH, "rb+");
        assert(db_file != nullptr);
    }
}

int DSMgr::close_file()
{
    if (fclose(db_file) == -1)
    {
        return -1;
    }
    else
    {
        db_file = nullptr;
        return 0;
    }
}

int DSMgr::seek(unsigned int offset)
{
    return fseek(db_file, offset, SEEK_SET);
}

void DSMgr::read_first_page()
{
    seek(0);
    fread(first_page, sizeof(int), MAX_PAGE_NUM, db_file);
}

void DSMgr::write_first_page()
{
    seek(0);
    fwrite(first_page, sizeof(int), MAX_PAGE_NUM, db_file);
}

unsigned int DSMgr::get_page_pointer(int page_id)
{
    return first_page[page_id] & 0x7fffffff;
}

void DSMgr::set_page_pointer(int page_id, int pointer)
{
    first_page[page_id] = pointer;
}

void DSMgr::set_use(int page_id, bool is_use)
{
    if (is_use)
    {
        first_page[page_id] = first_page[page_id] & 0x7fffffff;
    }
    else
    {
        first_page[page_id] = first_page[page_id] | 0x80000000;
    }
}

bool DSMgr::get_use(int page_id)
{
    return !(first_page[page_id] & 0x80000000);
}

void DSMgr::inc_pages_num()
{
    first_page[0]++;
}

int DSMgr::get_pages_num()
{
    return first_page[0];
}

void DSMgr::inc_io_count()
{
    io_count++;
}

int DSMgr::get_io_count()
{
    return io_count;
}