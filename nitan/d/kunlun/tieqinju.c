// Room: /d/kunlun/tieqinju.c 鐵琴居
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short","鐵琴居");
        set("long",@long
這兒便是“鐵琴先生”何太沖的居處。房間陳設頗為精巧，物品與
中土所見別是不同。幾個昆侖派弟子守在這裡，個個深有憂色。東邊通
往臥室。
long );
        set("objects",([
                CLASS_D("kunlun")+"/hetaichong" : 1,
                __DIR__"npc/kl-dizi2.c" :   1,
                __DIR__"npc/kl-dizi4.c" :   1,
        ]));
        set("exits", ([
                "south" : __DIR__"huapu",
                "east"  : __DIR__"sleeproom",
        ]));
        create_door("east", "小門", "west", DOOR_CLOSED);
        set("coor/x", -119980);
        set("coor/y", 40140);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;
        fam=query("family", me);

        if (dir == "east" &&
                objectp(present("he taichong", environment(me))) &&
                (!fam || fam["family_name"] != "昆侖派") &&
                !query_temp("kl_pass", me) )
                return notify_fail("何太沖攔住你，說道：裡側為內眷居住，還是請勿打擾為是。\n");

        return ::valid_leave(me, dir);
}
