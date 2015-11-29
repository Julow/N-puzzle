-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   mid_bot_buttons.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 16:41:33 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/29 12:03:38 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
local bookmark_holder = _G['bookmark-holder'];


local gensize_slider = _G['gensize_slider'];
local gensize_slider_text = _G['gensize_slider_text'];

local genloops_slider = _G['genloops_slider'];
local genloops_slider_text = _G['genloops_slider_text'];

local gencheckbox_no = gencheckbox_no;
local gencheckbox_yes = gencheckbox_yes;

local f_genloops, f_gensize, f_gensolvable;

-- ************************************************************************** --
local randomizeButton = randomPuzzleButton
assert(randomizeButton ~= nil);

local function refresh_genloops()
  f_genloops = math.tointeger((math.exp(genloops_slider:getValue()) - 1.) // 1.);
end

function randomizeButton:onClick(_, _)

  print('size, , genloops', f_gensize, f_gensolvable, f_genloops);
  PickState:pushRandomGrid(f_gensize, f_gensolvable, f_genloops);
  -- TODO: RETREIVE WIDTH AND SOLVABLE FROM SLIDER/CHECKBOXES
end

randomizeButton:setCallback('onClick', randomizeButton.onClick);

genloops_slider:setCallback(
  'onValueChange',
  function (self, v)
	refresh_genloops();
	genloops_slider_text:setText(f_genloops);
  end
);
refresh_genloops();




local function refresh_gensize()
  f_gensize = math.tointeger(gensize_slider:getValue() // 1);
end

gensize_slider:setCallback(
  'onValueChange',
  function (self, v)
	refresh_gensize();
	gensize_slider_text:setText(f_gensize);
  end
);
refresh_gensize();




gencheckbox_yes:setCallback(
  'onClick',
	function (self)
	  if self:isChecked() == false then
		self:setChecked(1);
	  else
		gencheckbox_no:setChecked(0);
		f_gensolvable = 1;
	  end
	end
);

gencheckbox_no:setCallback(
  'onClick',
	function (self)
	  if self:isChecked() == false then
		self:setChecked(1);
	  else
		gencheckbox_yes:setChecked(0);
		f_gensolvable = 0;
	  end
	end
);
f_gensolvable = 1;

-- ************************************************************************** --
-- local fileButton = filePuzzleButton
-- assert(fileButton ~= nil);

-- function fileButton:onClick(_, _)
--   ft.pchildren(UIParent);
--   ft.pparents(self);
-- end

-- fileButton:setCallback('onClick', fileButton.onClick);

-- ************************************************************************** --
-- local defaultButton = defaultPuzzleButton
-- assert(defaultButton ~= nil);

-- function defaultButton:Bordel(...)
--   print('defaultButton:Bordel', ...);
-- end

-- function defaultButton:onClick(_, _)
--   PickState:useDefaultGrid();
--   puzzleFrame:reloadGrid();
--   self:registerEvent("Bordel");
-- end

-- defaultButton:setCallback('onClick', defaultButton.onClick);

-- ************************************************************************** --
local solveButton = solveLaunchButton
assert(solveButton ~= nil);

function solveButton:onClick(_, _)
  PickState:tagForSolving();
end

solveButton:setCallback('onClick', solveButton.onClick);

-- ************************************************************************** --
