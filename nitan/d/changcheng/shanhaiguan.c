// Room: /d/changcheng/shanhaiguan.c
// Last Modified by Winder on Aug. 25 2000
#include <ansi.h>

inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", "山海關城樓");
        set("long", WHT@LONG
你登上山海關城樓，北望巍峨的角山，長城在山脊上奔騰，漸漸消
失在黛色的群山之中。關下，沉沉一線穿南北；南面，煙波萬頃，橫無
際涯。大明元帥徐達以此處“枕山襟海，實遼薊嚥喉”，故築此關。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("exits", ([
                "northwest" :__DIR__"changcheng23",
                "down"      :"/d/guanwai/shanhaiguan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 5000);
        set("coor/y", 5000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}