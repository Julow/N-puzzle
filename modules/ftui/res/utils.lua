-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   utils.lua                                          :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/12 20:48:21 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/01 18:29:53 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

ftui = {}

local ftui = ftui

function ftui.finalize_template(t, p)
   t.__index = t;
   if p ~= nil then
	  setmetatable(t, p);
	  if t.__ipairs == nil then
		 t.__ipairs = p.__ipairs
	  end
   end
end

ftui.ALayoutdef = {
   __ipairs = function(t)
	  local i, n = -1, t:size();

	  return function()
		 i = i + 1;
		 if i < n then
			return i, t:at(i);
		 end
	  end
   end
}

LinearLayout = {
	Align = {
		LEFT = 0,
		TOP = 0,
		RIGHT = 1,
		BOTTOM = 1,
		CENTER = 2
	},
	Direction = {
		VERTICAL = 0,
		HORIZONTAL = 1
	}
};
