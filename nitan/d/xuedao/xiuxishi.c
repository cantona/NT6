inherit ROOM;

void create()
{
        set("short", "側洞");
        set("long", @LONG
這裡是一個小小的山洞，地上舖了很多茅草，非常的幹燥。光線
有些昏暗，只是西面透出一些亮光。你不禁覺得有些疲倦了，一時忍
不住想躺下睡睡。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([
                "west" : __DIR__"shandong3",
        ]));
        setup();
        replace_program(ROOM);
}