// Room: /d/shaolin/shijie9.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
眼前遽然出現一大片松林。松林長得極密，石階上鋪滿了厚厚的
朽黃的松針。踩在腳下，發出察察的響聲。一隻小松鼠吱地在眼前閃
過，消失在林海里。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie8",
                "northup" : __DIR__"shijie10",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
