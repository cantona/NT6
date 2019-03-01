inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，一直通向後院，南邊是西練武場。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "north" : __DIR__"guofu_shilu-4",
               "south" : __DIR__"guofu_wuchang3",
        ]));
        setup();
        replace_program(ROOM);
}