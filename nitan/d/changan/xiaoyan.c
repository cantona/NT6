// /d/changan/xiaoyan.c

inherit  ROOM;

void  create  ()
{
        set  ("short",  "小雁塔");
        set  ("long",  @LONG
小雁塔建於景龍年間，因比大雁塔小，故稱小雁塔。塔高十五級，
雙塔連理為一塔，形體秀麗美觀。
LONG);
        set("exits",  ([  //sizeof()  ==  4
                "northeast"  :  __DIR__"road5",
        ]));
        set("outdoors",  "changan");
        set("coor/x", -10730);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}