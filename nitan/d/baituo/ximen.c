#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
這是個山莊的西門。拱月形的竹門分外雅致，門上掛著塊竹牌，
上面寫著「西門外面有毒蛇出沒，慎行」幾個醒目的大字。西門外面
則是雜草叢生，很是荒涼。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "west" : __DIR__"cao1",
                "east" : __DIR__"changlang",
        ]));
        set("objects", ([
                __DIR__"npc/menwei" : 1,
        ]));
        set("coor/x", -49990);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("men wei", this_object())))
                return 1;

        if (dir == "east")
                return guarder->permit_pass(me, dir);

        if (dir == "west"
            && query("combat_exp", me)<600
           && guarder)
                return notify_fail(CYN "門衛攔住你道：你經驗太低，會被"
                                   "毒蛇咬死，還是不要亂闖的好。\n" NOR);

        return 1;
}