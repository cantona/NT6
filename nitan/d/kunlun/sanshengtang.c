// Room: /d/kunlun/sanshengtang.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "三聖堂");
        set("long", @long
崑崙三聖堂乃“崑崙三聖”何足道所建，原為了修身養性，讀書練
功。隨着崑崙派日益壯大，名聲遠播，這裏便成了崑崙派聚眾議事，接
待各路江湖英雄的地方。“崑崙三聖”也只好另覓安靜所在了。
long);
        set("exits",([
                "west"      : __DIR__"jiuqulang7",
                "east"      : __DIR__"jiuqulang3",
                "north"     : __DIR__"jiuqulang5",
                "south"     : __DIR__"jiuqulang1",
        ]));
        set("objects",([
                CLASS_D("kunlun")+"/banshuxian" :   1,
                __DIR__"npc/kl-dizi1.c" :   1,
                __DIR__"npc/kl-dizi4.c" :   1,
        ]));
        set("coor/x", -119990);
        set("coor/y", 40100);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;
        fam=query("family", me);
        if (dir == "north" &&
                objectp(present("ban shuxian", environment(me)) &&
                (!fam || fam["family_name"] != "崑崙派")) &&
                !query_temp("kl_pass", me) )
        {
                return notify_fail("班淑嫻攔住你，説道：除非你能過得了我這一關，否則還是請另覓佳處。\n");
        }
        if( dir == "south" && query("kl_pass", me) )
                delete_temp("kl_pass", me);
        return ::valid_leave(me, dir);
}