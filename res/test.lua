-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   test.lua                                           :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:02:54 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/02 19:54:04 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

--[[ test slider ]]

function lol_slider:onValueChange(val)
	print("Value change: " .. tostring(val)
		.. " (By step: " .. tostring(self:getStepValue()) .. ")")
end

-- lol_slider:setBounds(0, 5)
-- lol_slider:setSteps(5)

lol_slider_right:setCallback("onMouseDown", function (self, _, _)
	lol_slider:setStepValue(lol_slider:getStepValue() - 1)
	print("right")
end)
lol_slider_left:setCallback("onMouseDown", function (self, _, _)
	lol_slider:setStepValue(lol_slider:getStepValue() + 1)
	print("left")
end)

lol_slider:setCallback("onValueChange", lol_slider.onValueChange)

--[[ test parent_key ]]

function test(v, k)
	print("parent." .. k .. " = " .. v[k]:getText() .. " (id=#" .. v[k]:getId() .. ")")
end

test(test_parent_key, "a");
test(test_parent_key, "b");
test(_G["big_layout-test2"], "a");
test(_G["big_layout-test2"], "b");
