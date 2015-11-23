-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   global.lua                                         :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:02:54 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/23 18:21:30 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

-- test begin

function lol_slider:onValueChange(val)
	print("Value change: " .. tostring(self:getValue()) .. " to " .. tostring(val))
end

lol_slider:setBounds(-1, -2)

lol_slider:setCallback("onValueChange", lol_slider.onValueChange)

-- test end
