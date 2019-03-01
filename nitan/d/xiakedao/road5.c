// road5.c 山路

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是俠客島的後山，你走在一條巖石嶙峋的山道上，這是通向
俠客島 "望雲台" 的唯一路徑，旁邊是萬丈懸崖，抬頭隱約可見籠
罩在雲霧中的山峰，一條山路環山而行。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road6",
                "north" : __DIR__"shidong8",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3110);
        set("coor/y", -22110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}