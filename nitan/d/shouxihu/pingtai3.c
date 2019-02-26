// Room: /yangzhou/pingtai3.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "亂石平台");
        set("long", @LONG
水雲勝概前亂石平台，圍以石欄。面南兩端，設石級通湖岸。平台
低於大廳三級，高於湖岸一十六級，平台不僅用以襯托“水雲勝概”大
廳，也可作為戲班的露台。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "northup" : __DIR__"shuiyun",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 100);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}