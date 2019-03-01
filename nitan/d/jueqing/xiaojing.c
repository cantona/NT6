inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
這是絕情谷大廳通往後花園的一條必經之路。道路兩旁花
草叢生，花香宜人。
LONG);
        set("exits", ([
               "east"   : __DIR__"huayuan",
               "west"   : __DIR__"dating",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}