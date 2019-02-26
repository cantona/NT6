// Room: /d/xingxiu/shimen.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "石門");
        set("long", @LONG
這裏兩峯對峙，形如門，故名。又因常有虎豹出沒，俗稱卧虎台。
山壁高立千仞，蒼翠欲滴。四周峭壁無徑，中間一條小路。真是一座天
險。
LONG);
        set("outdoors", "silu");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"silk3",
                "northwest" : __DIR__"silk4",
                "northup"   : __DIR__"yanzhishan",
                "southup"   : __DIR__"xinglongshan",
        ]));
        set("coor/x", -22000);
        set("coor/y", 600);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
