inherit ROOM;

void create ()
{
        set ("short","西門");
        set ("long", @LONG
這裡是武漢的西門了。有很多商旅和武林人士進進出出。有幾個官
兵在這裡檢查來往的行人。旁邊站著一名軍官，看起來神氣十足，不停
地指手畫腳。
LONG);

        set("exits", ([
                "east":__DIR__"hzjie4",
                "west":"/d/jingzhou/guandao1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
                "/d/city/npc/wujiang" :1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5110);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}