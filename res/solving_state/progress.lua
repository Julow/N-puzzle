-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   progress.lua                                       :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/12/07 19:14:48 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/08 12:41:49 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_sframe = progress_slider;
local f_tframe1 = progress_text1;
local f_tframe2 = progress_text2;
local f_tframe3 = progress_text3;
local f_bframe = leave_button;

local f_val, f_failed;

assert(f_sframe ~= nil);
assert(f_tframe1 ~= nil);
assert(f_tframe2 ~= nil);
assert(f_bframe ~= nil);

function	f_sframe:PROGRESS(text, val)
  f_val = (val * 10.) // 0.1;
  f_failed = false;
  f_tframe1:setText(text);
  f_tframe2:setText(tostring(f_val) .. '%');
  f_tframe3:setText('Abort');
  f_sframe:setValue(f_val);
end

function	f_sframe:FAIL(text)
  f_failed = true;
  f_tframe1:setText(text);
  f_tframe2:setText('Failed: "' .. text .. '"');
  f_tframe3:setText('Back');
end

f_sframe:registerEvent("PROGRESS");
f_sframe:registerEvent("FAIL");

function	f_bframe:onClick()
  SolvingState:tagForLeave();
end

f_bframe:setCallback("onClick", f_bframe.onClick);
