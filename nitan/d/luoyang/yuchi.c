#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "洪德浴池");
        set("long", @LONG
門上掛了一塊大匾，匾上四個朱漆大字“洪德浴池”，這裏是洛陽城
最有特色的地方，分男女兩間，可算開中國古代浴池之先河，一些有錢的
老爺少爺小姐太太經常光顧這裏，生意相當不錯。大門口坐着個老頭，看
樣子是收錢的。樓上是女間，樓下是男間，可千萬別走錯喲。
LONG);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"rest1",
                  "up" : __DIR__"rest2",
                  "west" : __DIR__"sroad3",
        ]));
        set("objects", ([
                __DIR__"npc/zaotang" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( query("gender", me) == "女性" && dir == "east" )
                return notify_fail(CYN "澡堂夥計一把攔住你，説道：姑娘，男女有"
                                   "別，請到上面去。\n" NOR);

        if( query("gender", me) != "女性" && dir == "up" )
                return notify_fail(CYN "澡堂夥計一把攔住你，説道：喂！你一個大"
                                   "老爺們兒怎麼往女浴池鑽啊？\n" NOR);

        return ::valid_leave(me, dir);
}