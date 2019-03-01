// Room: /d/wuyi/path10.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天遊小路");
        set("long", @LONG
這是天遊峰後山的一條小路。路面是丹崖石板舖就的，兩邊都是密
密層層的鬆柏。東上就是天遊峰了，西下直指桃源洞。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "southup"  : __DIR__"tianyoufeng",
                "westdown" : __DIR__"taoyuandong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1380);
        set("coor/y", -4970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
