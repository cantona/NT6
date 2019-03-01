inherit ROOM;

void create()
{
        set("short", "墳墓內部");
        set("long", @LONG
你用力往墓碑一推，忽然眼前一黑，掉進了一個大坑，這裡黑乎
乎的，似乎看不見任何東西。
LONG );
        set("exits", ([
                "south" : __DIR__"sec1",
                "out" : __DIR__"luan2",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}