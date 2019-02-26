// Room: /d/mingjiao/huangtulu1.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "黃土小路");
        set("long", @LONG
這裏是茂密松林中的一條黃土小路。松林極密，四面都是藍幽幽
的感覺，映襯着天心雪峯，極盡悽美。
LONG );
        set("exits", ([
                "west" : __DIR__"huangtulu2",
                "east" : __DIR__"shanlu2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
