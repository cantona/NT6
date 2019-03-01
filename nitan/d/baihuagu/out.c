// Room: /d/baihuagu/out.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
void create()
{
        set("short", "樹林外");
        set("long", @LONG
眼前一片光明，比起樹林裡的黑暗，簡直有點刺眼。南邊是一
片陰森森的大樹林，相信你是不敢再進去了。
LONG);
        set("outdoors", "baihuagu");
        set("exits", ([ 
                "south" : __DIR__"tree",
                "north" : __DIR__"bhgent",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}