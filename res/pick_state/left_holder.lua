-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   left_holder.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/28 14:05:17 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/01 19:35:46 by jaguillo         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_frame = left_holder;
assert(f_frame ~= nil);

local f_algHolder = algo_holder;
assert(f_algHolder ~= nil);
local f_algFrames = {};

local f_heuHolder = heu_holder;
assert(f_heuHolder ~= nil);
local f_heuFrames = {};

local f_costText = cost_text;
assert(f_costText ~= nil);
local f_costFrame = cost_slider;
assert(f_costFrame ~= nil);

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
	self.onChange(i);
  end
end

local function makeGroup(parent, groupName, names, count, onChange)
  local group;

  group = {};
  for i = 0, count - 1 do
	line = createView('LinearLayout');
	check = createView('CheckBox');
	text = createView('TextView');

	parent:addView(line);
	line:addView(check);
	line:addView(text);

	line:setDirection(line.Direction.HORIZONTAL);

	check:setAlpha(0.75);
	check:setRequestedSize(20, 20);
	check:setNormalParams(0xFFFF0000, 0xFF00AA00, 3);
	check:setCheckedParams(0xB0FFFF00, 0x01000000, 6);
	check.i = i;
	check.group = group;
	check.onChange = onChange;

	check:setCallback("onClick", onCheckBoxClick);

	text:setText(names[i]);
	text:setTextSize(11);
	text:setTextColor(0x999eb8ff);

	group[i] = {check = check; text = text};
  end
  return group;
end

-- ALGORITHMS ------------------------------------------------------------------
local function f_algInit()
  local check, text;
  local names = Main:getAlgorithms();
  local count = #names + (names[0] == nil and 0 or 1);

  f_algFrames = makeGroup(f_algHolder, 'algo', names, count,
						  function (i)
							PickState:setAlgorithmId(i);
						  end
  );
  f_algFrames[Main:getAlgorithmId()].check:setChecked(1);
end

-- HEURISTICS ------------------------------------------------------------------
local function f_heuInit()
  local check, text;
  local names = Main:getHeuristics();
  local count = #names + (names[0] == nil and 0 or 1);

  f_heuFrames = makeGroup(f_heuHolder, 'heuristics', names, count,
						  function (i)
							PickState:setHeuristicId(i);
						  end
  );
  f_heuFrames[Main:getHeuristicId()].check:setChecked(1);

end

-- COST ------------------------------------------------------------------------
function f_costFrame:onValueChange(v)
  PickState:setCost(v);
  f_costText:setText(tostring(v));
end
f_costFrame:setCallback("onValueChange", f_costFrame.onValueChange);

-- function f_costText:onDraw(canvas)
--   canvas:drawText(18, 0
-- 				  , 0, 0xFF555555, 16);
-- end
-- f_costText:setCallback("onDraw", f_costText.onDraw);





-- EVENT HANDLING --------------------------------------------------------------
function f_frame:ON_GAME_LOADED(ev, ...)
  f_algInit();
  f_heuInit();
  f_frame:unregisterEvent("ON_GAME_LOADED");
end

f_frame:registerEvent('ON_GAME_LOADED');
