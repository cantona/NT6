inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
你的眼前是一條用漢白玉鋪成的台階，一直向下延伸，兩邊的牆
壁都是花崗巖，牆上隔十來步就有一盞油燈，使你能看清周圍。
LONG );
        set("exits", ([
                "southup" : __DIR__"midao2",
                "eastdown": __DIR__"midao4",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}