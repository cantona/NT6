// Room: /d/songshan/songyueta.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "嵩岳寺塔");
        set("long", @LONG
嵩岳寺塔為密檐式磚塔，高達十余丈，外廓十二面，內室八方四門，
十五層密檐塔剎向上收緊，優美絕倫。
LONG );
        set("exits", ([
                "east" : __DIR__"songyuesi",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" :1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -30);
        set("coor/y", 790);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}