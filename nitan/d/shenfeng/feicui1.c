#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "翡翠池");
        set("long", @LONG
這裡四周群山圍繞，就如一只大盆一般，盆子中心碧水瑩
然，綠若翡翠，是個圓形的大水池(pool)，隔了這千百年，竟
然並不曾幹枯，想來池底另有活水源頭。你走近池邊，伸下手
去只覺清涼入骨，雙手捧起水來但見池水澄凈清澈，更無纖毫
苔泥，原來圓池四周都是翡翠，池水才映成綠色。只見潔白的
玉峰映在碧綠的池中，明艷潔凈，幽絕清絕。
LONG);
        set("resource/water", 1);
        set("objects", ([ 
                __DIR__"obj/skeleton3" : 1,
        ]));

        set("item_desc", ([
                "pool" : HIC "\n池水澄凈清澈，更無纖毫苔泥，圓池四周都是翡翠。\n" NOR,
        ]));

        set("exits", ([ 
                "up" : __DIR__"yongdao5",
        ]));
        setup();
}

void init()
{
        add_action("do_jump", "jump");
        add_action("do_jump", "tiao");
}

int do_jump(string arg)
{
        object me = this_player();
        object cloth=query_temp("armor/cloth", me);

        if (! arg || arg == "")
                return 0;

        if (arg == "pool")
        {
                message_vision(HIC "\n$N" HIC "望著翡翠池，再也禁不住誘惑，撲通一聲"
                               "跳進了水中。\n\n" NOR, me);

                me->move(__DIR__"feicui2");

                message_vision(HIC "\n$N" HIC "撲通一聲跳進了翡翠池中。\n\n" NOR, me);

                if (cloth && cloth->washed(120 + random(120)))
                        tell_object(me, "你身上的" + cloth->name() + "全濕透了。\n");

                return 1;
        }
}
