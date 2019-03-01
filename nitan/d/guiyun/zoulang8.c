// Room: /d/guiyun/zoulang8.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是連接花廳與花園的走廊。長長的走廊曲曲折折，雕欄畫柱，彩
繪鏤空，滿目綠意，兩旁種滿了花樹。
LONG );
        set("exits",([
                "east"  : __DIR__"huating",
                "north" : __DIR__"zoulang9",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 260);
        set("coor/y", -810);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}