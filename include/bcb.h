/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhuang <hsjfans@mail.ustc.edu.cn>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:39:08 by sjhuang           #+#    #+#             */
/*   Updated: 2021/01/09 10:16:14 by sjhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_DB_BCB
#define SIMPLE_DB_BCB

class BCB
{
public:
    BCB(int page_id, int frame_id) : page_id(page_id), frame_id(frame_id), dirty(false){};

    int get_page_id() const;

    int get_frame_id() const;

    bool is_dirty() const;

    void set_dirty();

    void unset_dirty();

private:
    int page_id;
    int frame_id;
    bool dirty;
};

#endif