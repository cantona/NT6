// Room: /d/huangshan/paiyun.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "排雲亭");
        set("long", @LONG
觀西海雲的最佳處。黃山雲海歷來五分，東西南北海加天海，其中
西海雲多為層狀，好似排濤疊浪，排雲亭是為觀雲而建，也因雲而名，
在這裏可以盡覽黃山四奇之雲海的妙處。
LONG
        );
        set("exits", ([ 
                "northup" : __DIR__"shizi",
                "south"   : __DIR__"feilai",
                "east"    : __DIR__"sanhua",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -605);
        set("coor/y", -1020);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}