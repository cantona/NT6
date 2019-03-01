inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是一間寬大的房間，房間兩旁放著兩排竹床，四處打掃得
一塵不染，這裡就是弟子們休息的地方。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "south" : __DIR__"ssl2",
]));

        set("sleep_room", 1);

        setup();
        replace_program(ROOM);
}
