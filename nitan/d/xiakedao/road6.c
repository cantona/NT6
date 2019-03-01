// road6.c 山路

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條巖石嶙峋的山道上，這是通向俠客島望雲台的唯一
路徑，旁邊是萬丈懸崖，抬頭隱約可見籠罩在雲霧中的山峰，一條
山路環山而行。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road7",
                "northdown" : __DIR__"road5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3110);
        set("coor/y", -22120);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}