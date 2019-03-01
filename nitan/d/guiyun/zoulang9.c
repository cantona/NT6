// Room: /d/guiyun/zoulang9.c
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
                "west"  : __DIR__"huayuan",
                "south" : __DIR__"zoulang8",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 260);
        set("coor/y", -800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}