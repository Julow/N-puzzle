-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   mid_bot_buttons.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 16:41:33 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/17 17:50:40 by ngoguey          ###   ########.fr       --
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
  -- useFileGrid();
  puzzleFrame:reloadGrid();
end

fileButton:setCallback('onClick', fileButton.onClick);

-- ************************************************************************** --
local defaultButton = defaultPuzzleButton
assert(defaultButton ~= nil);

function defaultButton:onClick(_, _)
  PickState:useDefaultGrid();
  puzzleFrame:reloadGrid();
end

defaultButton:setCallback('onClick', defaultButton.onClick);

-- ************************************************************************** --
local solveButton = solveLaunchButton
assert(solveButton ~= nil);

function solveButton:onClick(_, _)
  _G['bookmark-holder']:addView(createView("Bookmark", "view_de_merde"));
  PickState:tagForSolving();

end

solveButton:setCallback('onClick', solveButton.onClick);

-- ************************************************************************** --
