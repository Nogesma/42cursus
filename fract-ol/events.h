/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:01:47 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/04 19:01:49 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

int	mouse_event(int button, int x, int y, t_all *a);

int	kbd_event(int button, t_all *a);

#endif //EVENTS_H
