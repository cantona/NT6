inherit ROOM;

void create()
{
        set("short", "慈悲院");
        set("long", @LONG
這是僧人們點化頑徒的地方。不少江湖豪客由於厭倦了打打殺殺
的日子，來到此處落髮為僧，叛依佛門。牆上一幅佛祖神像，兩邊各
有一條幅，上書：放下屠刀，立地成佛。
LONG );
        set("exits", ([
                "east" : __DIR__"wuwujing",
                "south" : __DIR__"sanwugong",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}