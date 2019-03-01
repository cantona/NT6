// Room: /d/huanghe/road5.c
// Last Modified by winder on Apr. 10 2000
inherit ROOM;
void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條黃土路上。這裡已經是陝西地面了，向南走是一條黃土
大道，兩邊望不盡的黃土高坡，沒有一絲吝嗇的綠色。東北隱隱傳來流
水的聲響。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "northeast" : __DIR__"weifen",
                "south"     : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1010);
        set("coor/y", 690);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
