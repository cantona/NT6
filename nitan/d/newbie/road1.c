inherit ROOM;

void create()
{
        set("short", "田埂小道");
        set("long", @LONG
這是一條向東的田間小道，兩旁是一片片綠油油的水田和悠閒的
牧童。
LONG);
        set("exits", ([
                "west" : __DIR__"cunkou",
                "east" : __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}