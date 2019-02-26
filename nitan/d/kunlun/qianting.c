// Room: /d/kunlun/qianting.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "前廳");
        set("long",@long
這裏是座大廳，高檐大瓦，十分的簡樸而壯闊，廳內擺幾張高背方
椅，一張八仙桌，看來是接待客人的地方，西面和東面也是客廳，供客
人歇息，北面一條長廊通向後面。
long);
        set("exits",([
                "south" : __DIR__"pingfeng",
                "north" : __DIR__"shilu1",
                "west"  : __DIR__"wlang01",
                "east"  : __DIR__"elang01",
        ]));
        set("objects",([
                CLASS_D("kunlun")+"/xihuazi" : 1,
                CLASS_D("kunlun") + "/first" : 1,
        ]));
        set("valid_startroom", 1);
        set("coor/x", -119990);
        set("coor/y", 40060);
        set("coor/z", 90);
        setup();
        "/clone/board/kunlun_b"->foo();
}

int valid_leave(object me, string dir)
{
        mapping fam;
        fam=query("family", me);

        if ((!fam || fam["family_name"] != "崑崙派") && dir == "north" &&
                objectp(present("xi huazi", environment(me))))
                return notify_fail("西華子攔住你，説道：這裏是崑崙派的地盤，不要隨意亂闖！\n");

        return ::valid_leave(me, dir);
}
