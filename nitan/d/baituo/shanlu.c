inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是白駝山莊廣場西邊的一條小路，尋常百姓平時都是經過這
條小路上山。
LONG );
        set("exits", ([
                "north" : __DIR__"shanlu1",
                "east"  : __DIR__"guangchang",
        ]));
        set("outdoors", "baituo");
        set("no_clean_up", 0);
        set("coor/x", -49990);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}