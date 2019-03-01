// Room: /d/mobei/guanmu1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "灌木叢");
        set("long", @LONG
腳下走動時掠過長長的茅草，身邊是高高矮矮的灌木叢。你叫不出
名目來，也看不清楚四邊的景色，只有一條小路在灌木叢中時隱時現地
伸向小土丘的山頂。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 2 */
                "eastdown" : __DIR__"caoyuan",
                "southwest" : __DIR__"guanmu",
        ]));
        set("outdoors","mobei");
        set("coor/x", -240);
        set("coor/y", 5170);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}