#include <ansi.h> 
inherit ROOM;

int do_lianzhi(string arg);

void create()
{
        set("short", "練毒室");
        set("long", @LONG
這裡是五毒教弟子專門的練毒室，可以在這裡練制各種毒
藥，案上擺著各式各樣的器具。屋內正中放著一個一人多高的
丹爐，爐火正旺，有個黑瘦的道人正手持桃木劍繞爐疾走，嘴
裡吶吶自語不知在念些什麼。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"nanyuan",
        ]));
        set("objects", ([
                __DIR__"npc/daoren": 1,
        ]));
        setup();
}

void init()
{
        add_action("do_lianzhi", "lianzhi");
}

int do_lianzhi (string arg)
{
        object ob, me = this_player();
        int time = 15 + random(15);

        if( query("family/family_name", me) != "五毒教" )
                return notify_fail("你不知道該如何下手。\n");

        if( query_temp("liandu/wudu", me) )
                return notify_fail("你現在正煉著呢，切勿分心。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if (me->query_skill("wudu-qishu", 1) < 60 )
                return notify_fail("你的五毒奇術不夠嫻熟，無法煉毒。\n");

        if( query("jing", me)<80 || query("qi", me)<80 )
                return notify_fail("你現在的精神狀況不佳，無法煉毒。\n");

        if (arg != "heding hong" && arg != "furou gao" &&
            arg != "kongque dan" && arg != "chixie fen" &&
            arg != "wusheng san" && arg != "duanchang san")
                return notify_fail("你要煉制什麼毒藥？\n");

        if (arg == "heding hong")
        {
                if (! present("du nang", me)
                   || ! present("shexin zi", me)
                   || ! present("qianri zui", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("shexin zi", me));
                destruct(present("qianri zui", me));
                set_temp("liandu/wudu", "hedinghong", me);
        } else

        if (arg == "furou gao")
        {
                if (! present("du nang", me)
                   || ! present("fugu cao", me)
                   || ! present("chuanxin lian", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("fugu cao", me));
                destruct(present("chuanxin lian", me));
                set_temp("liandu/wudu", "furougao", me);
        } else

        if (arg == "kongque dan")
        {
                if (! present("du nang", me)
                   || ! present("fugu cao", me)
                   || ! present("qianri zui", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("fugu cao", me));
                destruct(present("qianri zui", me));
                set_temp("liandu/wudu", "kongquedan", me);
        } else

        if (arg == "chixie fen")
        {
                if (! present("du nang", me)
                   || ! present("shexin zi", me)
                   || ! present("duanchang cao", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("shexin zi", me));
                destruct(present("duanchang cao", me));
                set_temp("liandu/wudu", "chixiefen", me);
        } else

        if (arg == "duanchang san")
        {
                if (! present("du nang", me)
                   || ! present("duanchang cao", me)
                   || ! present("chuanxin lian", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("duanchang cao", me));
                destruct(present("chuanxin lian", me));
                set_temp("liandu/wudu", "duanchangsan", me);
        } else

        if (arg == "wusheng san")
        {
                if (! present("du nang", me)
                   || ! present("heding hong", me)
                   || ! present("duanchang san", me)
                   || ! present("furou gao", me)
                   || ! present("chixie fen", me)
                   || ! present("kongque dan", me)
                   || ! present("jinshe duye", me))
                        return notify_fail("你身上的原料不齊，無法煉毒。\n");

                destruct(present("du nang", me));
                destruct(present("heding hong", me));
                destruct(present("duanchang san", me));
                destruct(present("furou gao", me));
                destruct(present("chixie fen", me));
                destruct(present("kongque dan", me));
                destruct(present("jinshe duye", me));
                set_temp("liandu/wudu", "wushengsan", me);
        }

        message_vision (HIR "\n$N" HIR "將身上的藥品投入丹爐，按照秘法小心"
                        "煉制起來。\n\n" NOR, me);
        me->start_call_out((: call_other, __FILE__, "liandu", me :), time);
        me->start_busy(time / 2 + 1);
        return 1;
}

void liandu(object me)
{
        object ob;
        int skill, lvl;
        int exp, pot, sco;

        exp = 300 + random(300);
        pot = 100 + random(200);
        sco = 100 + random(100);

        skill = (int)me->query_skill("wudu-qishu", 1);

        lvl = (int)me->query_skill("poison", 1) / 2 +
              (int)me->query_skill("wudu-qishu", 1) + 10;

        if (environment(me) != this_object())
                return;

        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));

        if (random(skill) < 50 && random(3) == 1) 
        {
                delete_temp("liandu/wudu", me);
                message_vision(HIR "\n突然間一股腥惡的焦臭至$N" HIR "身旁傳"
                               "來，看來是煉毒失敗了。\n"NOR,me);
        } else
        {
                message_vision(HIW "\n爐頂白霧漸漸轉淡，傳出陣刺鼻的腥味，$N"
                               HIW "連忙小心翼翼地將藥粉取出。\n" NOR, me);

                if( query_temp("liandu/wudu", me) == "hedinghong" )
                {
                        ob = new("/clone/poison/hedinghong");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "鶴頂紅劇毒",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "你煉成了「" + NOR + ob->name()
                                        + NOR + HIY "」。\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "furougao" )
                {
                        ob = new("/clone/poison/furougao");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "腐肉膏劇毒",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "你煉成了「" + NOR + ob->name()
                                        + NOR + HIY "」。\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "kongquedan" )
                {
                        ob = new("/clone/poison/kongquedan");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "孔雀膽劇毒",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "你煉成了「" + NOR + ob->name()
                                        + NOR + HIY "」。\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "chixiefen" )
                {
                        ob = new("/clone/poison/chixiefen");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "赤蠍粉劇毒",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "你煉成了「" + NOR + ob->name()
                                        + NOR + HIY "」。\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "duanchangsan" )
                {
                        ob = new("/clone/poison/duanchangsan");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "斷腸散劇毒",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "你煉成了「" + NOR + ob->name()
                                        + NOR + HIY "」。\n" NOR);
                } else
                if( query_temp("liandu/wudu", me) == "wushengsan" )
                {
                        ob = new("/clone/poison/wushengsan");
                        ob->set("poison",([
                                "level" : lvl + 20,
                                "id":query("id", me),
                                "name"  : "五聖散劇毒",
                                "duration" : 25,
                        ]));
                        tell_object(me, HIY "你煉成了五毒教獨門秘藥「" + NOR
                                        + ob->name() + NOR + HIY "」。\n" NOR);

                        if( query("potential", me)>
                           me->query_potential_limit()) 
                                pot = 1;

                        addn("combat_exp", exp, me);
                        addn("score", sco, me);
                        me->improve_potential(pot);

                        tell_object(me, HIC "你獲得了" + chinese_number(exp)
                                        + "點經驗、" + chinese_number(pot) +
                                        "點潛能以及" + chinese_number(sco) +
                                        "點江湖閱歷。\n" NOR); 
                }

                ob->move(me);
                delete_temp("liandu/wudu", me);

                me->improve_skill("poison",50+query("int", me));
                if (me->can_improve_skill("wudu-qishu"))
                        me->improve_skill("wudu-qishu",50+query("int", me));

                tell_object(me, HIC "煉毒過程中你的「基本毒技」和「五毒奇術」"
                                "提高了！\n\n" NOR);
        }
}