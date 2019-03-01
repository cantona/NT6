inherit ROOM;

void create()
{
        set("short", "囚室大門");
        set("long", @LONG
這是縹緲峰靈鷲宮關押犯人的地方，這是囚室東邊，西面便是囚
室。
LONG );
        set("exits", ([
                "west" : __DIR__"qiushi",
                "east" : __DIR__"changl11",
        ]));
        setup();
        replace_program(ROOM);
}