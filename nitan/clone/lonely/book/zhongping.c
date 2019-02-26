#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(CYN "「中平槍譜」" NOR, ({ "zhongping qiangpu", "zhongping", "qiangpu",
                                            "pu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", CYN "這是一本薄薄的書冊，封皮上用正楷寫有「中平"
                            "槍法」四個大字。\n" NOR);
                set("value", 1);
                set("no_sell", "…這…這是啥？");
                set("material", "paper");
                set("skill", ([
                        "name" : "zhongping-qiang",
                        "exp_required" : 100000,
                        "jing_cost"  : 100,
                        "difficulty" : 40,
                        "max_skill"  : 149,
                        "min_skill"  : 0
                ]));
        }
}

void init()
{
        add_action("do_yanjiu", "yanjiu");
        add_action("do_yanjiu", "research");
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        string pfm, book;
        int lv;

        if (! arg)
        {
                write("研究中平槍譜指令格式：research|yanjiu <絕招> from <中平槍譜>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", pfm, book) != 2)
        {
                write("研究中平槍譜指令格式：research|yanjiu <絕招> from <中平槍譜>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙着呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if( query("no_fight", where) && query("doing", me) != "scheme" )
        {
                write("你無法在這裏靜下心來研讀槍譜。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("你要研究什麼？\n");
                return 1;
        }

        if (pfm != "ding")
        {
                write("槍譜上並沒有記載你想研究的絕招。\n");
                return 1;
        }

        if( query("combat_exp", me)<100000 )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("jing", me)<100 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if( query("potential", me)<query("learned_points", me)+10 )
        {
                write("你的潛能不夠了，研究不出什麼。\n");
                return 1;
        }

        // 中平槍法絕招定嶽七方
        if (pfm == "ding")
        {
                if( query("can_perform/zhongping-qiang/ding", me) )
                {
                        write("你已經學會了這招，再研究也沒用。\n");
                        return 1;
                }

                if (! (int)me->query_skill("zhongping-qiang"))
                {
                        write("你研究了半天，發現槍譜所記載的絕招與你毫無關係。\n");
                        return 1;
                }

                if ((int)me->query_skill("zhongping-qiang", 1) < 120)
                {
                        write("你發現槍譜上記載的絕招過於深奧，一時難以明白。\n");
                        return 1;
                }

                if (random(20) < 18)
                {
                        message_vision(HIR "$N" HIR "仔細的研讀槍譜上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "你對中平槍法有了更深的理解，但尚需進一"
                                       "步的研究。\n" NOR);
                } else
                { 
                        message_vision(HIR "$N" HIR "仔細的研讀槍譜上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "過得良久，陡然間你雙目一亮，終於領悟了"
                                        "槍譜中所記載的中平槍法絕技「定嶽七方」的奧"
                                        "祕！\n" NOR + HIC "你學會了「定嶽七方」。\n" NOR);

                        if (me->can_improve_skill("club"))
                                me->improve_skill("club", 1500000);
                        if (me->can_improve_skill("zhongping-qiang"))
                                me->improve_skill("zhongping-qiang", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        set("can_perform/zhongping-qiang/ding", 1, me);
                }
                me->receive_damage("jing", 80);
                addn("learned_points", 10, me);
                me->start_busy(2);
                return 1;
        }
}