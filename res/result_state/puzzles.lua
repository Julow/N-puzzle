-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzles.lua                                        :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/12/08 14:49:26 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/08 15:27:25 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_sframe = main_slider;
local f_tframe2 = progress_text2;
local f_puzframe = puzzleFrame;
local f_bframe = leave_button;

local f_cur, f_max, f_grids, f_w;

assert(f_sframe ~= nil);
assert(f_tframe2 ~= nil);
assert(f_puzframe ~= nil);
assert(f_bframe ~= nil);

local function set(i)
  f_sframe:setValue(i);
  f_cur = i;
  f_tframe2:setText(tostring(i) .. '/' .. tostring(f_max));
  f_puzframe.setGrid(f_grids[i], f_w); --todo
end

function f_sframe:RESULT_DATA(
	time, g, init_h, avg_h, nodes, max_open, max_closed, max_botho, max_bothc, grids)
  f_sframe:setBounds(0, g);
  f_sframe:setSteps(g);
  f_max = g;
  f_grids = grids; --todo
  f_w = math.tointeger(math.sqrt(#grids[0] + 1)); --todo
  print(f_w);
  set(0);
end

function f_sframe:onVChange(v)
  set(math.tointeger(v));
end

f_sframe:registerEvent("RESULT_DATA");
f_sframe:setCallback("onValueChange", f_sframe.onVChange);


f_bframe:setCallback("onClick", function () ResultState:tagForLeave() end);
