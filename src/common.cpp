/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:24:42 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:17:47 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

Frame::sptr generate_random_frame()
{
    auto frame = std::make_shared<Frame>();
    for (unsigned int i = 0; i < FRAME_SIZE - 1; i++)
    {
        frame->field[i] = 'a' + arc4random_uniform(26);
    }
    frame->field[FRAME_SIZE - 1] = 0;
    return frame;
}