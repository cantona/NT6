#include <ansi.h>

inherit ROOM;

#define PLACE "hz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "無極幫杭州分舵");
        set("long", @LONG
這裏是無極幫設在杭州的分舵，這裏裝飾的極為氣派體面，一進
門正對着你的是一幅巨大的山水屏風畫，畫的正是那杭州西湖畔的美
景。大紅的地毯兩邊，整齊的排列着兩行座椅，看來這裏經常討論些
無極幫的大事。一個氣質不凡的中年人，端坐在太師椅上。想必就是
無極幫杭州分舵主萬劍愁萬大俠了。側面的牆上掛着任務牌（paizi）。

LONG );

        set("objects", ([
                __DIR__"npc/boss-wan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "east" : "/d/hangzhou/wjb_hzfb",
        ]));

	set("coor/x", 810);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>