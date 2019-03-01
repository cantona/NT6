// /d/shenlong/fengding 峰頂
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "峰頂");
        set("long", @LONG
這是神龍島的最高峰，但是卻很是寬敞。站在峰頂，極目遠眺，但
見四周均是蔚藍的天空、茫茫的大海。你突然覺得自己是多麼的渺小，
猶如滄海之一粟。旁邊一群神龍教眾在巡邏著，偶爾不懷好意地朝你瞧
幾眼。西面是長廊，南面是下山的山道，往北有一條通向後山的小路，
路很小，似乎走的人不多。
LONG
        );
        set("exits", ([
                "east"      : __DIR__"changlang",
                "northdown" : __DIR__"lin1",
                "southdown" : __DIR__"shandao",
        ]));
        set("outdoors", "shenlong");
        set("objects", ([
                CLASS_D("shenlong")+"/hesheng" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
