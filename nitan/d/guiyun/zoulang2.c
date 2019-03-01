// Room: /d/guiyun/zoulang2.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是連接中廳與後廳的走廊。長長的走廊曲曲折折，雕欄畫柱，彩
繪鏤空，滿目綠意，兩旁種滿了花樹。北邊有一間客房。
LONG );
        set("exits",([
                "east"  : __DIR__"zoulang1",
                "west"  : __DIR__"zoulang3",
                "north" : __DIR__"kefang",
        ]) );
        set("outdoors", "guiyun");
        set("objects",([
                __DIR__"npc/zhuangding2" : 1,
        ]));  
        set("coor/x", 250);
        set("coor/y", -820);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}