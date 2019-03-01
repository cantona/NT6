// Room: /d/yueyang/longkou.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "龍口");
        set("long", @LONG
龍口位于君山南端，兩邊鉗形山嘴，巖壁拱護，為龍的上、下□，
張口向南，含住一彎洞庭湖水，形如長龍吞水，故名龍口。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"longxianjing",
                "eastup"    : __DIR__"shijie1",
                "southeast" : __DIR__"xiaolu1",
                "southwest" : __DIR__"xiaolu2",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/xu" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 4,
        ]));
        set("coor/x", -1720);
        set("coor/y", 2290);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}