-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   mid_bot_buttons.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 16:41:33 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/25 19:09:36 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame

-- ************************************************************************** --
local randomizeButton = randomPuzzleButton
assert(randomizeButton ~= nil);

function randomizeButton:onClick(_, _)
  PickState:useRandomGrid(4, 1);
  -- TODO: ACCEPT BOOLEAN IN ftlua::handle
  -- TODO: RETREIVE WIDTH AND SOLVABLE FROM SLIDER/CHECKBOXES
  puzzleFrame:reloadGrid();
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
