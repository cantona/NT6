// cunzhangjia.c 村長家
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "村長家");
        set("long", @LONG
這裡是村長的家，堂屋裡堆放著一些鋤頭、鐮刀之類的農耕用
具，有一些是村中村民家裡壞了，來央求村長給修的。屋檐前吊著
數十串鮮紅的辣椒，還有一些風幹的野味。
LONG
        );
        set("exits", ([
                "south" : __DIR__"guchang",
        ]));
        set("objects", ([
                __DIR__"npc/dibao" : 1,
        ]));
        set("coor/x", -12270);
	set("coor/y", 850);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}