inherit ROOM;

void create()
{
        set("short", "兜率大士院");
        set("long", @LONG
這是一般參拜者所能到的最遠的地方，再往南就是天龍寺歷代高
僧靜修之處──牟尼堂。那是常人不可輕易打攪的地方，你最好不要
擅自闖入。除非你確信能給高僧們帶去好消息。
LONG );
        set("exits", ([
                "north" : __DIR__"qingxinge",
                "south" : __DIR__"banruotai",
                "northeast" : __DIR__"doumugong",
                "northwest" : __DIR__"sanwugong",
        ]));
        set("objects",([
                __DIR__"obj/xianglu" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}