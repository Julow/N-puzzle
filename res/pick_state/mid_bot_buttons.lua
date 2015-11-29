-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   mid_bot_buttons.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 16:41:33 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/29 10:22:10 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
local bookmark_holder = _G['bookmark-holder'];
local gen_slider = _G['gen_slider'];
local nloops_slider = _G['nloops_slider'];

-- ************************************************************************** --
local randomizeButton = randomPuzzleButton
assert(randomizeButton ~= nil);

local function int_to_float_expscale(v)
  return math.tointeger((math.exp(v) - 1.) // 1.)
end

function randomizeButton:onClick(_, _)
  local size = math.tointeger(gen_slider:getValue() // 1);
  local nloops = int_to_float_expscale(nloops_slider:getValue());

  print('size, 1, nloops', size, 1, nloops);
  PickState:pushRandomGrid(size, 1, nloops);
  -- TODO: RETREIVE WIDTH AND SOLVABLE FROM SLIDER/CHECKBOXES
end

randomizeButton:setCallback('onClick', randomizeButton.onClick);

-- ************************************************************************** --
local fileButton = filePuzzleButton
assert(fileButton ~= nil);

function fileButton:onClick(_, _)
  ft.pchildren(UIParent);
  ft.pparents(self);
end

fileButton:setCallback('onClick', fileButton.onClick);

-- ************************************************************************** --
local defaultButton = defaultPuzzleButton
assert(defaultButton ~= nil);

function defaultButton:Bordel(...)
  print('defaultButton:Bordel', ...);
end

function defaultButton:onClick(_, _)
  PickState:useDefaultGrid();
  puzzleFrame:reloadGrid();
  self:registerEvent("Bordel");
end

defaultButton:setCallback('onClick', defaultButton.onClick);

-- ************************************************************************** --
local solveButton = solveLaunchButton
assert(solveButton ~= nil);

function solveButton:onClick(_, _)
  PickState:tagForSolving();
end

solveButton:setCallback('onClick', solveButton.onClick);

-- ************************************************************************** --
