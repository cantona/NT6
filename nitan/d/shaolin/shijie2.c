// Room: /d/shaolin/shijie2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
長長的石階往上依然看不到盡頭。身邊的山壁受着長年風雨的浸
潤，長出了薄弧的青苔。上面依稀有些刻鑿的痕跡。有一行字特別清
晰：『金剛伏邪魔，寶塔鎮羣妖』
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie1",
                "northup" : __DIR__"shijie3",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
