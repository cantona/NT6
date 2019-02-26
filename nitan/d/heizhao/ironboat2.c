// Room: /heizhao/ironboat2.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "鐵舟");
        set("long", @LONG
這是一艘黑黝黝的小船，舟中放着兩柄鐵槳，鐵舟很小至多隻
能乘坐二人。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("coor/x", -5020);
        set("coor/y", -1240);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}