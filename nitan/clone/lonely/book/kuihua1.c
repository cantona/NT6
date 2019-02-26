#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIR "袈裟" NOR, ({ "jia sha", "jia", "sha", "cloth"}));
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", HIR "一件大紅色的粗布袈裟，上面密密麻麻寫滿了小字。\n" NOR);
                set("value", 1000);
                set("no_sell", 1);
                set("no_pawn", 1);
                set("no_store", 1);
                set("material", "cloth");
                set("armor_prop/armor", 25);
                set("wear_msg", HIR "$N" HIR "展開一件大紅色的袈裟披在身上。\n" NOR);
                set("remove_msg", HIR "$N" HIR "將袈裟從身上脱了下來，摺疊成小小的一團。\n" NOR);
        }
        setup();
}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
        add_action("do_yanjiu", "yanjiu");
        add_action("do_yanjiu", "research");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        mapping skill;
        int plvl, con, improve;
        int neili_lost;

        if (! arg || ! id(arg))
                return 0;

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
                write("你無法在這裏靜下心來研讀寶典。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if( !query("family/family_name", me) || query("family/family_name", me) != "日月神教" )
        {
                write("辟邪劍法只有日月神教的人方能領會。\n"); 
                return 1;
        }

        if( query("character", me) == "光明磊落" || 
            query("character", me) == "狡黠多變" )
        {
                write("你心中暗道：這辟邪劍法損人損己，修煉來何用。\n");
                return 1;
        }

        if( !query("special_skill/ghost", me)){
        if( query("gender", me) == "女性" )
        {
                write("自古以來沒聽説過女人可以修習葵花寶典。\n");
                return 1;
        }

        if( query("gender", me) == "男性" )
        {
                me->receive_wound("qi", 50);
                write(HIR "\n你試着修煉辟邪劍法，霎時只覺內息忽然大亂，幾"
                      "欲焚身。\n" NOR);
                return 1;
        }
        }

        if( query("int", me)<34 )
        {
                write("你的天資不足，無法理解辟邪劍法的深意。\n");
                return 1;
        }

        if( query("dex", me)<32 )
        {
                write("你先天身法孱弱，難以修煉辟邪劍法。\n");
                return 1;
        }

        if (me->query_skill("sword", 1) < 100)
        {
                write("你的基本劍法造詣太淺，無法理解辟邪劍法。\n");
                return 1;
        }

        if (me->query_skill("dodge", 1) < 100)
        {
                write("你的基本輕功造詣太淺，無法理解辟邪劍法。\n");
                return 1;
        }

        if (me->query_skill("parry", 1) < 100)
        {
                write("你的基本架造造詣太淺，無法理解辟邪劍法。\n");
                return 1;
        }

        if (me->query_skill("pixie-jian", 1) >= 180)
        {
                write("袈裟上面記載的東西對你來説已經太過淺顯了。\n");
                return 1;
        }

        if( query("combat_exp", me)<300000 )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("max_neili", me)<500 )
        {
                write("你的內力太差，無法修煉此等神功。\n");
                return 1;
        }

        switch (random(3))
        {
        case 0:
                message("vision", CYN "只見" + me->name() + CYN "偷偷"
                        "摸摸地正在研讀一件袈裟。\n" NOR,
                        environment(me), me);
                break;
        case 1:
                message("vision", CYN + me->name() + CYN "照着一件袈裟"
                        "騷首弄姿，好像在模仿女人。\n" NOR,
                        environment(me), me);
                break;
        case 2:
                message("vision", CYN + me->name() + CYN "邊讀袈裟邊把"
                        "腰身扭來扭去，甚為詭異。\n" NOR,
                        environment(me), me);
                break;
        }

        if( query("jing", me)<60 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        plvl = me->query_skill("pixie-jian", 1);
        if (plvl > 170) neili_lost = 120; else
        if (plvl > 150) neili_lost = 100; else
        if (plvl > 130) neili_lost = 90; else
        if (plvl > 110) neili_lost = 80; else
        if (plvl > 100) neili_lost = 70; else
        if (plvl > 90)  neili_lost = 60; else
        if (plvl > 80)  neili_lost = 50; else
        if (plvl > 70)  neili_lost = 40; else
        if (plvl > 60)  neili_lost = 30; else
        if (plvl > 50)  neili_lost = 20; else
                        neili_lost = 10;

        con = me->query_con();

        if( query("neili", me)<neili_lost )
        {
                write("你內力不夠，無法鑽研這麼高深的武功。\n");
                return 1;
        }

        if (! me->can_improve_skill("pixie-jian", 1))
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if ((plvl > 10) && (con / 2 + random(con) < 50) && random(100) == 1)
        {
                tell_object(me, HIR "你依照着寶典所示運轉內息，突然只覺內息逆流而"
                                "上，四肢冰涼，心火如\n焚，慘嚎一聲，暈了過去。\n" NOR);

                message("vision", HIR + me->name() + "突然慘嚎一聲，暈了過去。\n"
                                  NOR, environment(me), ({ me }));

                if( query("max_neili", me)>10 )
                {
                        addn("max_neili", -10-random(10), me);
                }
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", random(30) + 30);
        addn("neili", -neili_lost, me);

        // 天賦聰穎增加研讀速度
        if( query("special_skill/clever", me) )
                me->improve_skill("pixie-jian", me->query_int() * 2 + 20);
        else
                me->improve_skill("pixie-jian", me->query_int() * 2 + 1);

        me->start_busy(random(1) + 1);
        write(HIR "你仔細研讀袈裟上記載的神功，頗有心得。\n" NOR);
        return 1;
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        string pfm, jiasha;
        int lv;

        if (! arg)
        {
                write("研究葵花寶典指令格式：research|yanjiu <絕招> from <葵花寶典>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", pfm, jiasha) != 2)
        {
                write("研究葵花寶典指令格式：research|yanjiu <絕招> from <葵花寶典>\n");
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
                write("你無法在這裏靜下心來研讀寶典。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(jiasha))
        {
                write("你要研究什麼？\n");
                return 1;
        }

        if (pfm != "gui" && pfm != "duo" && pfm != "pi" && pfm != "po")
        {
                write("袈裟上並沒有記載你想研究的絕招。\n");
                return 1;
        }

        if( query("combat_exp", me)<300000 )
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

        // 辟邪劍法絕招奪目神劍
        if (pfm == "duo")
        {
                if( query("can_perform/pixie-jian/duo", me) )
                {
                        write("你已經學會了這招，再研究也沒用。\n");
                        return 1;
                }

                if (! (int)me->query_skill("pixie-jian"))
                {
                        write("你研究了半天，發現袈裟所記載的絕招與你毫無關係。\n");
                        return 1;
                }

                if ((int)me->query_skill("pixie-jian", 1) < 80)
                {
                        write("你發現袈裟上記載的絕招過於深奧，一時難以明白。\n");
                        return 1;
                }

                if (random(20) < 18)
                {
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "你對辟邪劍法有了更深的理解，但尚需進一"
                                       "步的研究。\n" NOR);
                } else
                { 
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "過得良久，陡然間你雙目一亮，終於領悟了"
                                        "袈裟中所記載的辟邪劍法絕技「奪目神劍」的奧"
                                        "祕！\n" NOR + HIC "你學會了「奪目神劍」。\n" NOR);

                        if (me->can_improve_skill("sword"))
                                me->improve_skill("sword", 1500000);
                        if (me->can_improve_skill("dodge"))
                                me->improve_skill("dodge", 1500000);
                        if (me->can_improve_skill("parry"))
                                me->improve_skill("parry", 1500000);
                        if (me->can_improve_skill("pixie-jian"))
                                me->improve_skill("pixie-jian", 1500000);
                              me->improve_skill("martial-cognize", 1500000);
                        set("can_perform/pixie-jian/duo", 1, me);
                }
                       me->receive_damage("jing", 80);
                       addn("learned_points", 10, me);
                       me->start_busy(2);
                return 1;
        }

        // 辟邪劍法絕招鬼魅身法
        if (pfm == "gui")
        {
                if( query("can_perform/pixie-jian/gui", me) )
                {
                        write("你已經學會了這招，再研究也沒用。\n");
                        return 1;
                }

                if (! (int)me->query_skill("pixie-jian"))
                {
                        write("你研究了半天，發現袈裟所記載的絕招與你毫無關係。\n");
                        return 1;
                }

                if ((int)me->query_skill("pixie-jian", 1) < 100)
                {
                        write("你發現袈裟上記載的絕招過於深奧，一時難以明白。\n");
                        return 1;
                }

                if (random(30) < 28)
                {
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "你對辟邪劍法有了更深的理解，但尚需進一"
                                       "步的研究。\n" NOR);
                } else
                { 
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "過得良久，陡然間你雙目一亮，終於領悟了"
                                        "袈裟中所記載的辟邪劍法絕技「鬼魅身法」的奧"
                                        "祕！\n" NOR + HIC "你學會了「鬼魅身法」。\n" NOR);

                        if (me->can_improve_skill("sword"))
                                me->improve_skill("sword", 1500000);
                        if (me->can_improve_skill("dodge"))
                                me->improve_skill("dodge", 1500000);
                        if (me->can_improve_skill("parry"))
                                me->improve_skill("parry", 1500000);
                        if (me->can_improve_skill("pixie-jian"))
                                me->improve_skill("pixie-jian", 1500000);
                              me->improve_skill("martial-cognize", 1500000);
                        set("can_perform/pixie-jian/gui", 1, me);
                }
                       me->receive_damage("jing", 80);
                       addn("learned_points", 10, me);
                       me->start_busy(2);
                return 1;
        }

        // 辟邪劍法絕招羣邪辟易
        if (pfm == "pi")
        {
                if( query("can_perform/pixie-jian/pi", me) )
                {
                        write("你已經學會了這招，再研究也沒用。\n");
                        return 1;
                }

                if (! (int)me->query_skill("pixie-jian"))
                {
                        write("你研究了半天，發現袈裟所記載的絕招與你毫無關係。\n");
                        return 1;
                }

                if ((int)me->query_skill("pixie-jian", 1) < 120)
                {
                        write("你發現袈裟上記載的絕招過於深奧，一時難以明白。\n");
                        return 1;
                }

                if (random(40) < 38)
                {
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "你對辟邪劍法有了更深的理解，但尚需進一"
                                       "步的研究。\n" NOR);
                } else
                { 
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "過得良久，陡然間你雙目一亮，終於領悟了"
                                        "袈裟中所記載的辟邪劍法絕技「羣邪辟易」的奧"
                                        "祕！\n" NOR + HIC "你學會了「羣邪辟易」。\n" NOR);

                        if (me->can_improve_skill("sword"))
                                me->improve_skill("sword", 1500000);
                        if (me->can_improve_skill("dodge"))
                                me->improve_skill("dodge", 1500000);
                        if (me->can_improve_skill("parry"))
                                me->improve_skill("parry", 1500000);
                        if (me->can_improve_skill("pixie-jian"))
                                me->improve_skill("pixie-jian", 1500000);
                              me->improve_skill("martial-cognize", 1500000);
                        set("can_perform/pixie-jian/pi", 1, me);
                }
                       me->receive_damage("jing", 80);
                       addn("learned_points", 10, me);
                       me->start_busy(2);
                return 1;
        }

        // 辟邪劍法絕招破元神劍
        if (pfm == "po")
        {
                if( query("can_perform/pixie-jian/po", me) )
                {
                        write("你已經學會了這招，再研究也沒用。\n");
                        return 1;
                }

                if (! (int)me->query_skill("pixie-jian"))
                {
                        write("你研究了半天，發現袈裟所記載的絕招與你毫無關係。\n");
                        return 1;
                }

                if ((int)me->query_skill("pixie-jian", 1) < 180)
                {
                        write("你發現袈裟上記載的絕招過於深奧，一時難以明白。\n");
                        return 1;
                }

                if (random(50) < 48)
                {
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "你對辟邪劍法有了更深的理解，但尚需進一"
                                       "步的研究。\n" NOR);
                } else
                { 
                        message_vision(HIR "$N" HIR "仔細的研讀袈裟上記載的絕招，似"
                                       "有所悟。\n" NOR, me);
                        tell_object(me, HIY "過得良久，陡然間你雙目一亮，終於領悟了"
                                        "袈裟中所記載的辟邪劍法絕技「破元神劍」的奧"
                                        "祕！\n" NOR + HIC "你學會了「破元神劍」。\n" NOR);

                        if (me->can_improve_skill("sword"))
                                me->improve_skill("sword", 1500000);
                        if (me->can_improve_skill("dodge"))
                                me->improve_skill("dodge", 1500000);
                        if (me->can_improve_skill("parry"))
                                me->improve_skill("parry", 1500000);
                        if (me->can_improve_skill("pixie-jian"))
                                me->improve_skill("pixie-jian", 1500000);
                              me->improve_skill("martial-cognize", 1500000);
                        set("can_perform/pixie-jian/po", 1, me);
                }
                       me->receive_damage("jing", 80);
                       addn("learned_points", 10, me);
                       me->start_busy(2);
                return 1;
        }
}