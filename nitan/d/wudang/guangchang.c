#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武當廣場");
        set("long", @LONG
這是一個由大石板鋪成的廣場，是武當弟子學習武功和互相切磋
的地點。周圍種滿了梧桐樹，一到秋天就是滿地的落葉。有個年紀輕
輕的道童正在打掃。南邊是靈霄宮三清殿。
LONG );

        set("objects", ([
                CLASS_D("wudang") +"/first" : 1,
                CLASS_D("wudang") +"/daotong" : 2,
        ]));

        set("exits", ([
                "northdown"  : __DIR__"zixiaogate",
                "south"      : __DIR__"sanqingdian",
                "eastdown"   : __DIR__"tyroad1",
                "east"       : __DIR__"shanlu2",
        ]));

        set("outdoors", "wudang");
        set("coor/x", -370);
        set("coor/y", -290);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_float", "float");
        add_action("do_float", "piao");
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("tiyunzong", 1) < 120
           || me->query_skill("dodge", 1) < 120)
        {
                message_vision("$N跳了跳，原地蹦噠了一會兒。\n", me);
                return 1;
        }

        if( query("neili", me)<100 )
        {
                tell_object(me, "你的內力不夠，還是休息一下再説吧。\n");
                return 1;
        }

        addn("neili", -70, me);

        message_sort(HIC "\n$N" HIC"深吸一口氣，縱聲長笑，只"
                     "見人已飄然而起，態似神仙，晃晃悠悠的落"
                     "下山去了，笑音猶然未絕。\n\n" NOR, me);
        me->move("/d/wudang/wdroad5");
        tell_object(me, "片刻，你已經落到了山腳下。\n");
        message("vision", "忽然一陣笑聲傳來，只見" + me->name() +
                "飄然落下，有若神仙。\n", environment(me), ({ me }));
        return 1;
}
