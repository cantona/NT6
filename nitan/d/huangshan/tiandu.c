// Room: /d/huangshan/tiandu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "天都峰");
        set("long", @LONG
天都是三大主峰中最為險峻的一座，古稱“群仙所都”，意為天上
都會。現在路邊已有依山鑿就的石級和鐵索圍護的登山道，但是仍然令
人有“難于上青天”之感。途中有一石屏風，刻有“天上玉屏”四字，
由此處遠望，浮雲怪峰，山泉鬆海，盡收眼底。
LONG
        );
        set("exits", ([ 
                "westdown"  : __DIR__"jiyu",
                "northdown" : __DIR__"yixian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -565);
        set("coor/y", -1060);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}