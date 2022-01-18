/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:48:36 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 16:54:23 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
- Each element (except the map) first's information is the type identifier 
(composed by one or two character(s)), followed by all specific informations for each object in a strict order 
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any
order in the file.
- Except for the map, each type of information from an element can be separated by one or more space(s).
*/

// int	check_elements(t_param *param, char *filename)
// {
// 	return (0);
// }
