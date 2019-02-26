// minju2.c 民居
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一家用茅草搭的房屋，家徒四壁，屋角的米缸是空的，廚房內
的水缸也是空的。幾個缺胳膊少腿的桌椅靠牆立着。看來主人已經把所
有能值錢的東西全都變賣了。
LONG
        );
        set("exits", ([
                "south" : __DIR__"xijie",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12260);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}