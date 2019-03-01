#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "南巖峰");
        set("long", @LONG
這裡是武當三十六巖之最，鬆樹翳天，木石爭奇，峭壁萬仞。在
懸崖之半築有一宮宇，下臨深淵，工程浩大。宮前有一石柱，自峭壁
上橫出。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/mo": 1,
        ]));

        set("exits", ([
                "eastdown" : __DIR__"langmeiyuan",
                "southdown": __DIR__"shizhu",
                "west"     : __DIR__"sheshenya",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -360);
        set("coor/y", -320);
        set("coor/z", 110);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "武當派")
           && dir == "southdown"
           && objectp(present("mo shenggu", environment(me))))
                return notify_fail(CYN "莫聲谷攔住你說：此處乃本派禁"
                                   "地，請止步。\n" NOR);

        return ::valid_leave(me, dir);
}