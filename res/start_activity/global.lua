-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   global.lua                                         :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:02:54 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/23 19:29:26 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

-- test begin

function lol_slider:onValueChange(val)
	print("Value change: " .. tostring(val)
		.. " (By step: " .. tostring(self:getStepValue()) .. ")")
end

lol_slider:setBounds(-5, 5)
lol_slider:setSteps(5)

lol_slider:setCallback("onValueChange", lol_slider.onValueChange)

-- test end
