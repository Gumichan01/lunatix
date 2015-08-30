

--[[

	LunatiX_engine
	Copyright (C) 2015 Luxon Jean-Pierre
	gumichan01.olympe.in

	LunatiX-engine is a SDL-based game engine.
	It can be used for open-source or commercial games thanks to the zlib/libpng license.

	Luxon Jean-Pierre (Gumichan01)
	luxon.jean.pierre@gmail.com

]]

local SDL_CONFIG_FILE = "config/lxsdl.cfg";
local WINDOW_CONFIG_FILE = "config/lxwindow.cfg";


function getFlags()

	-- Check the if these files can be opened
	local sdlfile = assert(io.open(SDL_CONFIG_FILE, "r"));
	local winfile = assert(io.open(WINDOW_CONFIG_FILE, "r"));

	-- The result table
	local result = {video=0, vsync=0, ttf=0, audio=0, joystick=0, opengl=0,
						font=0, size=0, width=0, height=0, fullscreen=0};

	-- Keys
	local video_str = "video";
	local vsync_str = "vsync";
	local ttf_str = "ttf";
	local audio_str = "audio";
	local joystick_str = "joystick";
	local opengl_str = "opengl";
	local font_str = "font";
	local size_str = "size";
	local width_str = "width";
	local height_str = "height";
	local fullscreen_str = "fullscreen";


	for line in sdlfile:lines()
	do
		local comment = string.find(line, "#");

		if not comment
		then

			-- Video flag
			if(string.find(line, video_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

					if( key and value )
					then
							result["video"] = value;
					end
			end

			-- VSync flag
			if(string.find(line, vsync_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

					if( key and value )
					then
							result["vsync"] = value;
					end
			end

			-- True type font library
			if(string.find(line, ttf_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["ttf"] = value;
				end
			end

			-- Audio
			if(string.find(line, audio_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["audio"] = value;
				end
			end

			-- Joystick
			if(string.find(line, joystick_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["joystick"] = value;
				end
			end

			-- OpenGL
			if(string.find(line, opengl_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["opengl"] = value;
				end

			end

			-- Font file
			if(string.find(line, font_str))
			then

				local _,_, key, value , pt, ext = string.find(line, "(%a+)%s*=%s*(%a+)(%p+)(%a+)");

				if( key and value )
				then
						result["font"] = "font/"..value..pt..ext;
				end
			end

			-- Size of text
			if(string.find(line, size_str))
			then
				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["size"] = value;
				end
			end
		end
	end

	sdlfile:close(); -- End of file : Close it!

	-- Read the content of the window file
	for line in winfile:lines()
	do

		local comment = string.find(line,"#");

		if not comment
		then

			-- Width
			if(string.find(line, width_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["width"] = value;
				end

			end

			-- Height
			if(string.find(line, height_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["height"] = value;
				end
			end

			-- Fullscreen
			if(string.find(line, fullscreen_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["fullscreen"] = value;
				end
			end
		end
	end

	winfile:close();

	return result;
end


-- For debug
--[[
local res = getFlags();

print("Result : Video: "..res["video"].."\n VSync: "..res["vsync"].."\n font: "..res["font"].."\n Text size: "..res["size"]);
print(" Audio: "..res["audio"].."\n Joystick: "..res["joystick"].."\n OpenGL: "..res["opengl"]);
print(" Width: "..res["width"].."\n Height: "..res["height"].."\n Fullscreen:"..res["fullscreen"]);]]

