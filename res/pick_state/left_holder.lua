-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   left_holder.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/28 14:05:17 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/28 16:44:10 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_frame = left_holder;
assert(f_frame ~= nil);

local f_algHolder = algo_holder;
assert(f_algHolder ~= nil);

local f_algFrames = {};

-- SHARED BEHAVIOURS -----------------------------------------------------------
local function onCheckBoxClick(self)
  local i;
  if self:isChecked() == false then
	self:setChecked(1);
  else
	i = self.i;
	for k , v in pairs(self.group) do
	  if k ~= self.i then
		self.group[k].check:setChecked(0);
	  end
	end
  end
end

local function makeGroup(parent, groupName, names, count)
  local group;

  group = {};
  for i = 0, count - 1 do
	line = createView('LinearLayout', groupName .. 'Line' .. tostring(i));
	check = createView('CheckBox', groupName .. 'CheckBox' .. tostring(i));
	text = createView('TextView', groupName .. 'TextView' .. tostring(i));

	parent:addView(line);
	line:addView(check);
	line:addView(text);

	line:setDirection(line.Direction.HORIZONTAL);

	check:setRequestedSize(20, 20);
	check:setNormalParams(0xFFFF0000, 0xFF00AA00, 3);
	check:setCheckedParams(0xB0FFFF00, 0x01000000, 6);
	check.i = i;
	check.group = group;

	check:setCallback("onClick", onCheckBoxClick);

	text:setText(names[i]);
	text:setTextSize(12);
	text:setTextColor(0xFF0000AA);

	group[i] = {check = check; text = text};
  end
  return group;
end

-- ALGORITHMS ------------------------------------------------------------------
local function f_algInit()
  local check, text;
  local names = Main:getAlgorithms();
  local count = #names + (names[0] == nil and 0 or 1);

  f_algFrames = makeGroup(f_algHolder, 'algo', names, count);
end

-- EVENT HANDLING --------------------------------------------------------------
function f_frame:ON_GAME_LOADED(...)
  print('salut');
  f_algInit();
end

f_frame:registerEvent('ON_GAME_LOADED');
