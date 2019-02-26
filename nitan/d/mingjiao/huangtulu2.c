// Room: /d/mingjiao/huangtulu2.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "黃土小路");
        set("long", @LONG
這裏是茂密松林中的一條黃土小路。松林極密，四面都是藍幽幽
的感覺，白白的冰雪反光耀眼。你來到一個山腰的危崖之邊，前邊有
一個小洞。
LONG );
        set("exits", ([
                "east"  : __DIR__"huangtulu1",
                "enter" : __DIR__"shandong",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
