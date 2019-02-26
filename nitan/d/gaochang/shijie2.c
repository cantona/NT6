// Room: /d/gaochang/shijie2.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
眼前遽然出現一大片松林。松林長得極密，石階上鋪滿了厚厚的朽
黃的松針。踩在腳下，發出察察的響聲。一隻小松鼠吱地在眼前閃過，
消失在林海里。
LONG
        );

        set("outdoors", "gaochang");
        set("exits", ([
                "southdown" : __DIR__"shijie1",
                "northup" : __DIR__"shijie3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -36500);
        set("coor/y", 10010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}