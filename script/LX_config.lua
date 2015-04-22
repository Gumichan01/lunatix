

--[[

	LunatiX_engine
	Copyright (C) 2014-2015 Luxon Jean-Pierre
	gumichan01.olympe.in

	LunatiX-engine is a SDL-based game engine.
	It can be used for open-source or commercial games thanks to the zlib/libpng license.

	Luxon Jean-Pierre (Gumichan01)
	luxon.jean.pierre@gmail.com

]]

local SDL_CONFIG_FILE = "config/lxsdl.cfg";
local WINDOW_CONFIG_FILE = "config/lxwindow.cfg";


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


function getFlags()

	-- Check the two files when opening them
	local sdlfile = assert(io.open(SDL_CONFIG_FILE, "r"));
	local winfile = assert(io.open(WINDOW_CONFIG_FILE, "r"));

	-- The result table
	local result = {video=0, ttf=0, audio=0, joystick=0, opengl=0,
						font=0, size=0, width=0, height=0, fullscreen=0};

	-- Keys
	local video_str = "video";
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


			-- True type font library
			if(string.find(line, ttf_str))
			then

				local _,_, key, value = string.find(line, "(%a+)%s*=%s*(%d+)");

				if( key and value )
				then
						result["ttf"] = value;
				end

			end


			-- audio
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

			-- font file
			if(string.find(line, font_str))
			then

				local _,_, key, value , pt, ext = string.find(line, "(%a+)%s*=%s*(%a+)(%p+)(%a+)");

				if( key and value )
				then
						result["font"] = value;
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

	sdlfile:close();

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

			-- fullscreen
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

--local res = getFlags();

--print("Resultat table : "..res["video"].." "..res["font"]);
--print("Resultat table : "..res["width"].." "..res["height"].." "..res["fullscreen"]);

