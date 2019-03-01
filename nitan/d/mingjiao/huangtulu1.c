// Room: /d/mingjiao/huangtulu1.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "黃土小路");
        set("long", @LONG
這裡是茂密鬆林中的一條黃土小路。鬆林極密，四面都是藍幽幽
的感覺，映襯著天心雪峰，極盡凄美。
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
