

--[[

	LunatiX_engine
	Copyright (C) 2014 Luxon Jean-Pierre
	gumichan01.olympe.in

	The LunatiX-engine is a SDL-based game engine.
	It can be used for open-source or commercial games thanks to the zlib/libpng license.

	Luxon Jean-Pierre (Gumichan01)
	luxon.jean.pierre@gmail.com

]]

local SDL_CONFIG_FILE = "config/sdl_conf.cfg";
local WINDOW_CONFIG_FILE = "config/window.cfg";


--	@fn function getVideo()
--
--	Get the video flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getVideo()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local video_str = "video";
	local video_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, video_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						video_val = value;
				end

			end

		end

	end

	file:close();

	return video_val;

end



--	@fn function getTTF()
--
--	Get the true type font flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getTTF()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local ttf_str = "ttf";
	local ttf_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, ttf_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						ttf_val = value;
				end

			end

		end

	end

	file:close();

	return ttf_val;

end


--	@fn function getAudio()
--
--	Get the audio flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getAudio()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local audio_str = "audio";
	local audio_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, audio_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						audio_val = value;
				end

			end

		end

	end

	file:close();

	return audio_val;

end



--	@fn function getJoystick()
--
--	Get the joystick flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getJoystick()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local joystick_str = "joystick";
	local joystick_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, joystick_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						joystick_val = value;
				end

			end

		end

	end

	file:close();

	return joystick_val;

end



--	@fn function getOpenGL()
--
--	Get the opengl flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getOpenGL()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local opengl_str = "opengl";
	local opengl_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, opengl_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						opengl_val = value;
				end

			end

		end

	end

	file:close();

	return opengl_val;

end



--	@fn function getFont()
--
--	Get the font file
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getFont()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local font_str = "font";
	local rep = font_str .."/";
	local font_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  											-- check if the line is not a comment line
		then

			if( string.find(line, font_str))						-- if the line contains the pattern
			then

				local _,_, key, value , pt, ext = string.find(line, "(%a+)%s*=%s*(%a+)(%p+)(%a+)");		-- we are sure the line contains the pattern

				if( key and value and pt and ext)					--we check if key and value have a value
				then
						font_val = rep..value..pt..ext;
				end

			end

		end

	end

	file:close();

	return font_val;

end


--	@fn function getFontSize()
--
--	Get the font size
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getFontSize()

	local file = assert(io.open(SDL_CONFIG_FILE, "r"));

	local size_str = "size";
	local size_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  											-- check if the line is not a comment line
		then

			if( string.find(line, size_str))						-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value)					--we check if key and value have a value
				then
						size_val = value;
				end

			end

		end

	end

	file:close();

	return size_val;

end



--	@fn function getWidth()
--
--	Get the window width
--
--	@return the width if all re ok, -1 if the variable was not found in the file
--

function getWidth()

	local file = assert(io.open(WINDOW_CONFIG_FILE, "r"));

	local width_str = "width";
	local width_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, width_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						width_val = value;
				end

			end

		end

	end

	file:close();

	return width_val;

end




--	@fn function getHeight()
--
--	Get the window height
--
--	@return the height if all re ok, -1 if the variable was not found in the file
--

function getHeight()

	local file = assert(io.open(WINDOW_CONFIG_FILE, "r"));

	local height_str = "height";
	local height_val = -1;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, height_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													-- we check if key and value have a value
				then
						height_val = value;
				end

			end

		end

	end

	file:close();

	return height_val;

end




--	@fn function getFullscreen()
--
--	Get the fullscreen flag
--
--	@return 1 if the configuration variable is activated, 0 otherwise
--

function getFullscreen()

	local file = assert(io.open(WINDOW_CONFIG_FILE, "r"));

	local fullscreen_str = "fullscreen";
	local fullscreen_val = 0;

	for line in file:lines()
	do

		--print( "lentgh of line" .. #line);

		local comment = string.find(line, "#");

		if not comment  															-- check if the line is not a comment line
		then

			if( string.find(line, fullscreen_str))										-- if the line contains the pattern
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");		-- we are sure the line contains the pattern

				if( key and value )													--we check if key and value have a value
				then
						fullscreen_val = value;
				end

			end

		end

	end

	file:close();

	return fullscreen_val;

end





-- For debug

--print("video : "..getVideo())
--print("ttf : "..getTTF())
--print("audio : "..getAudio())
--print("joystick : "..getJoystick())
--print("opengl : "..getOpenGL())
--print("font : "..getFont())
--print("size : "..getFontSize())
--print("window width : "..getWidth())
--print("window height : "..getHeight())
--print("fullscreen : "..getFullscreen())

