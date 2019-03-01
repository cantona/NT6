// Room: northroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
這裏就是北大街了，空氣中有着一種怪怪的氣味，不是太好聞。
路很寬，但人卻不多，尤其是在黃昏以後。西南是另一條大街，北大
街從此一直往東，西北有一家兵器鋪，進進出出的人都面無表情，死
氣沉沉。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"       : __DIR__"northroad2",
            "southwest"  : __DIR__"westroad3",
            "northwest"  : __DIR__"bingqidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15230);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}