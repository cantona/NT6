#include <ansi.h>
inherit ROOM;

string* books = ({
        "laozi1",
        "daodejing-i",
        "laozi2",
        "daodejing-i",
        "laozi8",
        "daodejing-i",
        "laozi13",
        "laozi1",
        "laozi16",
        "daodejing-i",
        "laozi18"
});

void create()
{
        set("short", "藏經閣");
        set("long", @LONG
這裡是藏經閣，靠牆是一排書架，擺滿了道教的典籍。中央有一
個長方形的大桌子，上面也堆滿了書。一個道童正在整理書籍。幾個
老道盤膝而做，正在此地靜修(jingxiu)。
LONG );
        set("exits", ([
                "southdown" : __DIR__"xilang",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/daotong" : 1,
                "/clone/book/" + books[random(sizeof(books))] : 1,
                "/clone/book/" + books[random(sizeof(books))] : 1
        ]));
        set("coor/x", -380);
        set("coor/y", -290);
        set("coor/z", 100);
        setup();
}

void init()
{
        add_action("do_jingxiu", "jingxiu");
}

int do_jingxiu(string arg)
{
        object me;
        int cost;

        me = this_player();
        if (me->is_busy())
                return notify_fail("等你忙完了手頭的事情再說！\n");

        if (me->is_fighting())
                return notify_fail("你邊打架一邊靜修？真有你的。\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("你現在的靜不夠，無法靜修。\n");

        if (me->query_skill("taoism", 1) < 250)
                return notify_fail("你對道學心法理解太淺，靜修獲得不了什麼進境。\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("你要花多少潛能進行靜修？\n");

        if( cost >= query("potential", me)-query("learned_points", me) )
                return notify_fail("你現在沒有這麼多的潛能！\n");

        if (cost < 100)
                return notify_fail("你至少要花一百點潛能才能有所進步。\n");

        message_vision(HIC "\n$N" HIC "找了一個地方坐了下來，閉目冥神，開"
                       "始專心研究道學心法。\n\n" NOR, me);

        set_temp("pending/jingxiu", 1, me);
        set_temp("potential_cost", cost, me);
        me->set_short_desc("正坐在地下冥神靜修。");
        me->start_busy((:call_other, __FILE__, "jingxiu" :),
                       (:call_other, __FILE__, "halt_jingxiu" :));
        return 1;
}

int jingxiu(object me)
{
        int cost;

        cost=query_temp("potential_cost", me);
        if (cost > 0)
        {
                cost = random(cost) + 1;
                if (cost > 3) cost = 3;
        } else
                cost = 0;

        me->improve_skill("taoism", me->query_int() / 5 +
                          random(me->query_skill("taoism", 1) * cost));
        addn("learned_points", cost, me);
        if( me->addn_temp("potential_cost",-cost)>0 )
                return 1;

        set_temp("pending/jingxiu", 0, me);
        me->set_short_desc(0);
        message_vision(HIG "$N" HIG "靜修完畢，面露微笑，站了起來。\n" NOR, me);
        return 0;
}

int halt_jingxiu(object me)
{
        tell_object(me, HIY "你睜開眼睛，站了起來。\n" NOR);
        tell_room(environment(me), HIY + me->name() + HIY "慢慢的睜開了"
                                   "雙眼，站了起來。\n" NOR, me);
        set_temp("pending/jingxiu", 0, me);
        delete_temp("potential_cost", me);
        me->set_short_desc(0);
        return 1;
}