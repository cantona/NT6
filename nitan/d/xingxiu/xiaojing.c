// Room: /d/xingxiu/xiaojing.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
這裡是星宿海。因方圓幾百裡都是一望無際的湖泊和沼澤，當地牧
羊人稱之為“海”。也因陰暗潮濕，毒蟲繁殖甚富。星宿弟子常來此捕
捉毒蟲，以備練毒之用。這裡通向星宿海的深處。西面有一條小徑，兩
旁點綴了些花卉。雖是稀少，但在星宿海是一奇觀了。不由得讓人心花
怒放，哼起了小曲。
LONG
        );
        set("exits", ([
                "east" : __DIR__"xxh2",
                "west" : __DIR__"shidao",
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -50100);
        set("coor/y", 20200);
        set("coor/z", 0);
        set("yushi_count", 1);
        setup();
}

void init()
{
        object obj, me = this_player();
        mapping fam;
        fam=query("family", me);
  
        if(mapp(fam) && fam["family_name"] == "星宿派" &&
                query("xx_points", me)>10 && 
                (random(30) == query("kar", me)) && 
                query("yushi_count") >= 1 &&
                !query_temp("yushi_get", me) )
        {
                write("你看見土裡有個東西一"WHT"閃"NOR"，揀起來才發現原來是一小塊玉石！\n");
                set_temp("yushi_get", 1, me);
                obj = new(__DIR__"obj/yushi");
                obj->move(me);
                addn("yushi_count", -1);
        }
}
