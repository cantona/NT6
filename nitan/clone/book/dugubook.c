// jiuyang.c
#include <ansi.h>
inherit BOOK;
inherit F_UNIQUE;

void create()
{
        set_name("「獨孤九劍殘本」", ({ "dugu canben", "canben", "dugu" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "這是一本薄薄的佈滿灰塵的獨孤九劍殘本，只因長期藏\n"
                        "在空室之中，書頁已有些破損殘缺。\n",
                        );
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
        }
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        object me = this_player();

        if (! arg || ! id(arg))
                return notify_fail("你要讀什麼？\n");

        if( query("lonely-sword/nothing", me) )
                return notify_fail("這本殘本對你來説沒有任何用處了。\n");

        if (me->query_skill("lonely-sword", 1) < 300)
                return notify_fail("你的獨孤九劍修為太淺，無法領悟書中奧祕。\n");

        tell_object(me, "你仔細地研讀殘本上面的講解......\n"
                        "你開始如痴如狂，沉迷其中........\n"
                        "時間很快的過去..................\n"
                        "突然一日，你毛塞頓開，哈哈大笑起來。\n"
                        "你發現你原先所有對劍法的認識是那麼可笑，荒唐。\n"
                        "你通悟了獨孤九劍的精髓「" HIR "無招" NOR "」的奧祕。\n");
        tell_object(me, "突然獨孤九劍殘本變成了一片片碎片，消失了。\n");
        set("lonely-sword/nothing", 1, me);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        destruct(this_object());
        return 1;
}


