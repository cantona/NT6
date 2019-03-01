inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是連接內堂和後堂的長廊，雖不見花木，但也能聞到淡
淡的花香。
LONG);
        set("exits", ([
               "north"   : __DIR__"changlang3",
               "south"   : __DIR__"neitang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}