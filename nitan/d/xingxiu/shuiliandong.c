// Room: /d/xingxiu/shuiliandong.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "水簾洞");
        set("long", @LONG
這裏羣峯高聳，沿曲徑入幽林，峯迴路轉，石壁中露出有拱形洞窟，洞內
水鏽青苔，紅綠班駁，亂石穿孔。雨季山頂飛流直下如水簾，因有此名。
LONG);
        set("outdoors", "silu");
        set("exits", ([
                "southeast" : __DIR__"xianrenya",
                "northeast" : __DIR__"chouchishan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -21000);
        set("coor/y", 400);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
