// Room: /d/kunlun/shankou.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "崑崙山埡口");
        set("long",@long
這是位於兩山之間的一個小山口。只見崑崙山脈綿延千里，羣山復
疊，山上樹木並不多，不時露出光禿禿的山面和石頭，山腰以上均為冰
雪覆蓋，冰峯雄峙，高插雲霄。
long);
        set("exits",([
                "west"      : __DIR__"klshanlu",
                "southeast" : __DIR__"kekexili",
                "enter" : "/d/llszhuang/road",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -110000);
        set("coor/y", 30000);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
