#include <login.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "南巖宮地下室");
        set("long", @LONG
這是一個乾燥潔淨的地下室，四壁用光滑的大理石砌就而成，十
數支松明照得這裏通明透亮。
LONG );
        set("objects", ([
                   CLASS_D("wudang") +"/xiaosong": 1,
        ]));

        set("exits", ([
                "up"     : __DIR__"nanyangong",
                "east"   : __DIR__"nanyan1",
                "west"   : __DIR__"nanyan2",
                "south"  : __DIR__"nanyan3",
                "north"  : __DIR__"nanyan4",
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
            if (dir == "up")
            {
                       if (me->query_skill("taiji-shengong", 1) < 80)
                              return notify_fail(HIY "你試着推了推頂上的磚蓋，觸"
                                           "手冰涼，紋絲不動。\n" NOR);

                  message_sort(HIY "\n$N" HIY "全身運足太極神功，拔身錯步，嘿地"
                             "一聲，舉起雙掌向上猛擊。只見一股白氣自$N" HIY
                             "掌心而出，迅猛無比地擊中頂上的磚蓋。克剌剌一"
                             "聲巨響，磚蓋被震成無數小碎片四散飄飛。露出一"
                             "個向上的洞口來。\n\n" NOR, me );
             }
             return ::valid_leave(me, dir);
}