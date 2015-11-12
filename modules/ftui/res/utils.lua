-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   utils.lua                                          :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/12 20:48:21 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/12 20:56:21 by ngoguey          ###   ########.fr       --
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

function ftui.push_view(metatab, ud, id)
   local t = {};

   setmetatable(t, metatab);
   t.__index = t;
   t[0] = ud;
   if id ~= nil then
	  _G[id] = t;
   end
   _G[ud] = t;
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
