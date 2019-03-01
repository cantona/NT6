// Room: /d/guiyun/zoulang7.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是連接中廳與花廳的走廊。長長的走廊曲曲折折，雕欄畫柱，彩
繪鏤空，滿目綠意，兩旁種滿了花樹。
LONG );
        set("exits",([
                "north" : __DIR__"huating",
                "west"  : __DIR__"zoulang1",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 270);
        set("coor/y", -820);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}