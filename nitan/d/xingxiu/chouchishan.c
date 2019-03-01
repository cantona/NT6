// Room: /d/xingxiu/chouchishan.c
// Last Modified by winder on Apr. 25 2001
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", GRN"仇池山"NOR);
        set("long", @LONG
這裡絕壁峭峙，孤險雲高，山峰拔地而起，直刺藍天。山頂平田千畝，風
景秀美，物產豐饒，氣候溫和，泉水多，勝跡遍山。仇池石色赭紅，吸水性能
強，適宜養育小樹花卉。遠遠可以看見東南邊有一座雄偉的關隘。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "southeast" : __DIR__"silk1",
                "north"     : __DIR__"silk2",
                "southwest" : __DIR__"shuiliandong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20000);
        set("coor/y", 500);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
