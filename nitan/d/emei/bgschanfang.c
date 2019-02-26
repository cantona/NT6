inherit ROOM;

void create()
{
        set("short", "禪房");
        set("long", @LONG
這兒是保國寺內的一間禪房，佈局簡單，供寺內和尚誦經修行之
用。
LONG );
        set("exits", ([
                "east"    : __DIR__"dxdian",
        ]));
        set("sleep_room", 1);
        set("no_clean_up", 0);
        set("no_fight", 1);
        setup();
        replace_program(ROOM);
}