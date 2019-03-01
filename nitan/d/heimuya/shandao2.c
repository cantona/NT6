// shandao2.c

inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
這一路上山，地勢極險，腳下是萬丈深谷，而山道極之陡峭窄小，
倘若一不留神，必將命喪於此。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "eastdown" : __DIR__"shandao1",
            "westup"   : __DIR__"shijie1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}