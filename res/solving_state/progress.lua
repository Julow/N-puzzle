-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   progress.lua                                       :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/12/07 19:14:48 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/07 19:51:36 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_sframe = progress_slider;
local f_tframe1 = progress_text1;
local f_tframe2 = progress_text2;

local f_val;

assert(f_sframe ~= nil);
assert(f_tframe1 ~= nil);
assert(f_tframe2 ~= nil);

function	f_sframe:PROGRESS(text, val)
  f_val = (val * 10.) // 0.1;
  f_tframe1:setText(text);
  f_tframe2:setText(tostring(f_val) .. '%');
  f_sframe:setValue(f_val);
end

f_sframe:registerEvent("PROGRESS");
