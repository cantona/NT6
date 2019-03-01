// Room: /d/guiyun/zoulang5.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是從中廳通向練武場的走廊。長長的走廊曲曲折折，雕欄畫柱，
彩繪鏤空，滿目綠意，兩旁種滿了花樹。
LONG );
        set("exits",([
                "east"  : __DIR__"zoulang4",
                "south" : __DIR__"zoulang6",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 250);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}