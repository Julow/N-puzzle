-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   global.lua                                         :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:02:54 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/23 17:45:50 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

-- test begin

lol_slider:setCallback("onValueChange", function (val)
	print("Value change: " .. tostring(val))
end)

-- test end
