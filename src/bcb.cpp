/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcb.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:16:35 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:16:36 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bcb.h"

int BCB::get_page_id() const
{
    return page_id;
}

int BCB::get_frame_id() const
{
    return frame_id;
}

bool BCB::is_dirty() const
{
    return dirty;
}

void BCB::set_dirty()
{
    dirty = true;
}

void BCB::unset_dirty()
{
    dirty = false;
}