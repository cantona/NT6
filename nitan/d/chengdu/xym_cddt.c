#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "俠義盟成都分舵");
        set("long", @LONG
這裡是俠義盟的的成都分舵，俠義盟這幾年名聲雀起，一方面成
大當家嚴厲幫規，另一方面也與各個分舵主的費心操勞是分不開的，
此間的舵主正是成總瓢把子的結拜義弟，人稱蜀都大俠的洪義。側面
的牆上掛著任務牌（paizi）。
LONG );

        set("objects", ([
               __DIR__"npc/boss-hong"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "west" : __DIR__"xym_cdfb",
        ]));

        set("coor/x", -15180);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>