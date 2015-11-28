-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   left_holder.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/28 14:05:17 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/28 15:53:54 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_frame = left_holder;
assert(f_frame ~= nil);

local f_algHolder = algo_holder;
assert(f_algHolder ~= nil);

local f_algNames, f_algCount;
local f_algFrames = {};

-- ALGORITHMS ------------------------------------------------------------------
local function f_algInit()
  local check, text;

  f_algNames = Main:getAlgorithms();
  f_algCount = #f_algNames + (f_algNames[0] == nil and 0 or 1);

  for i = 0, f_algCount - 1 do
	line = createView('LinearLayout', 'algoLine' .. tostring(i));
	check = createView('CheckBox', 'algoCheckBox' .. tostring(i));
	text = createView('TextView', 'algoTextView' .. tostring(i));

	f_algHolder:addView(line);
	line:addView(check);
	line:addView(text);

	line:setDirection(line.Direction.HORIZONTAL);
	-- check:setCallback("onMeasure",
	-- 				  function (self)
	-- 					print('onMeasure');
	-- 					check:setRequestedSize(20, 20);
	-- 					print(check:getRequestedSize());

	-- 				  end
	-- );
	check:setRequestedSize(20, 20);
	check:setNormalParams(0xFFFF0000, 0xFF00AA00, 3);
	check:setCheckedParams(0xB0FFFF00, 0x01000000, 6);
	-- check:setCallback("onSizeChange",
	-- 				  function (self)
	-- 					print('onSizeChange');
	-- 					check:setRequestedSize(20, 20);
	-- 					print(check:getRequestedSize());
	-- 				  end
	-- );

	text:setText(f_algNames[i]);
	text:setTextSize(12);
	text:setTextColor(0xFF0000AA);

	f_algFrames[i] = {check = check; text = text};
	ft.pparents(check);
	ft.pparents(text);
  end
  ft.ptab(f_algFrames);
  ft.ptab(ft);
  ft.pchildren(UIParent);
end



-- EVENT HANDLING --------------------------------------------------------------
function f_frame:ON_GAME_LOADED(...)
  print('salut');
  f_algInit();
end

f_frame:registerEvent('ON_GAME_LOADED');
