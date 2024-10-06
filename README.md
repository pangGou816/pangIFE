Interactive Fiction Engine
==========================
**An interactive fiction engine made in C**

The library used in the project
-------------------------------
### The library you should download into your system
 - [SDL 2.0]( https://wiki.libsdl.org/SDL2/FrontPage "Introduction to SDL 2.0" )
 - [SDL_image 2.0]( https://wiki.libsdl.org/SDL2_image/FrontPage "Introduction to SDL_image 2.0" )
 - [SDL_mixer 2.0]( https://wiki.libsdl.org/SDL2_mixer/FrontPage "Introduction to SDL_mixer 2.0" )
 - [SDL_ttf 2.0]( https://wiki.libsdl.org/SDL2_ttf/FrontPage "Introduction to SDL_ttf 2.0" )
 
### The library you don't need to download
 - [toml-c-master]( https://github.com/arp242/toml-c "The GitHub page of this library" )

What you should prepare
-----------------------
 - Folders that contain a `script.toml` and all your assets
 - An `Ubuntu 22.04.4` or newer system

How to write your `script.toml` for this IFE
------------------------------------------
To write your own `script.toml`.  
You should first know some basic principle of [TOML]( https://toml.io/en/ "Introduction to TOML" ) format.  
There is also a video, [Learn TOML in 10 Minutes]( https://www.youtube.com/watch?v=D_Jb52jw2HY ), explaining what TOML format is.

1. You need to prepare your asset.請注意：圖片檔僅支援jpg、jpeg、png，音樂僅支援mp3

2. 首先，建立scene屬性，用於標示你會用到的場景。  
 	格式：
 	```
	[scene.場景簡稱]
	name = "顯示在畫面上的名稱"
	path = "圖片路徑"
	```
  
	範例：
	```
	[scene.classroom]
	name = "The Classroom"
	path = "assets/scene/classroom.jpg"
	```

3. 接著，建立character屬性，用於標示你會用到的人物。  
	格式：
	```
	[character.人物簡稱]
	name = "顯示在畫面上的名字"
	avatar = "人物頭像圖片的路徑"
	tachie = "人物立繪圖片的路徑"
	```
 
	範例：
	```
	[character.hero]
	name = "Shark Egg"
	avatar = "assets/character/Shark_Egg_avatar.png"
	tachie = "assets/character/Shark_Egg_tachie.png"
	```

4. 建立item屬性，用於標示你會用到的物品。  
	格式：
	```
	[item.物品簡稱]
	name = "顯示在畫面上的名字"
	icon = "圖片路徑"
	```
    
 	範例：
 	```
	[item.ring]
	name = "Ring"
	icon = "assets/item/ring.png"
	```

5. 建立music屬性，用於標示你會用到的物品。  
	格式：
	```
	[music.音樂簡稱]
	name = "音樂名字"
	path = "音樂路徑"
	```
 
	範例：
	```
	[music.wedding]
	name = "wedding"
	path = "assets/music/wedding.mp3"
	```

6. 接下來，就可以開始撰寫你的劇本了~先來介紹一些簡單的撰寫格式：  
	指派場景：  
	&emsp;[event.名稱]，該event中須包含場景以及欲跳轉的dialogue/event，想要加音樂也可以加(非必要)

	範例：
	```
	[event.three]
	scene = "classroom"
	dialogue = "final0"
	music = "lone"
	```
  
	指派對話：  
	&emsp;[dialogue.名稱]，該dialogue中須包含人物、文字、欲跳轉的dialogue/event

	範例：
	```
	[dialogue.final0]
	character = "classmate"
	text = "我們專題要不要一組！"
	next = "final1"
	```
 
	>注意：  
	&emsp;如果要跳轉至dialogue(下一句話)，請用next = " "  
	&emsp;如果要跳轉至event(切換場景)，請用event = " "

	指派選項：  
	&emsp;[[dialogue.名稱.options]]，該dialogue中須包含文字、欲跳轉的dialogue/event

	範例：
	```
	[[dialogue.time3.options]]
	text = "最多兩天吧，畢竟我還有25學分"
	event = "two"
	```
 
	>注意：  
	&emsp;同一對話中的選項指派請勿超過4個。

	選項分數值：  
	&emsp;如果你想要設計每個選項可以獲得不同分數值，並且根據分數導引到不同場景/結局的話，可以使用這個功能

	【選項加分】 在選項中加入score = "正負整數，要加正負號"  
	範例：
	```
	[[dialogue.time3.options]]
	score = "+1"
	text = "除了寫其他作業的時間，我打算全部all in程設二！"
	event = "two"
	```
 
	【根據分數跳轉】新增[event.judge]，內容包含判斷分數(正負整數)、跳轉場景  
	範例：
	```
	[event.judge]
	total = "3"
	scene = "flunk"
	event = "four"
	```
	分數小於3，執行event.judge，else跳到指定的下一個event

	#最後請注意，所有event、dialogue、scene、charactor、item的名稱請勿重複  
	#必須以[event.one]作為劇本開頭

How to start
------------
1. Clone this repository to your computer
2. Open the `IFE` folder in the terminal
3. Type `make` in the terminal, and you will get a executable file called `main`
4. Type `./main` to play the demo game, or `./main [path]` to play your game
5. Congratulations!!! You can now enjoy your game

Game controll
-------------
 - Press `enter` to continue
 - Press `1` or `2` or `3` ... to choose an option
