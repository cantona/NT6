// Room: /city/kedian2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
你正走在客店二樓的走廊上，可以聽到從客房裡不時地呼呼的打酣聲一
陣高過一陣。不時有睡意朦朧的旅客進進出出。
LONG
        );

        set("exits", ([
                "down" : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));

        setup();
        replace_program(ROOM);
}