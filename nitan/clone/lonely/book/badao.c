#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIG "「霸刀」" NOR, ({ "badao book", "badao", "book"}));
        set_weight(500);
        if (clonep())
               destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIG "\n這是一本用薄紙寫成的書，封皮上寫有「霸刀」二字。\n"
                            "你可以試着讀讀(read)看。\n\n" NOR, );
        }
        
        remove_call_out("check_environment");
        call_out("check_environment", 3);
}

// 檢查這本書
// 1、書必須在玩家身上
// 2、玩家必須在碧水寒潭內，一旦離開碧水寒潭則消失
void check_environment()
{
        object pob, eob;

        remove_call_out("check_environment");
        call_out("check_environment", 3);
                
        pob = environment(this_object());
        
        if (! objectp(pob))
        {
                destruct(this_object());
                return;
        }
        /*
        if (! userp(pob))
        {
                destruct(this_object());
                return;
        }
        */
        
        // 掉在碧水寒潭不消失
        if (pob->query("is_hantan"))return;

        eob = environment(pob);
        
        if (! objectp(eob))
        {
                destruct(this_object());
                return;
        }
        
        if (! eob->query("is_hantan"))
        {
                tell_object(pob, HIG "你離開了碧水寒潭，《霸刀》叮~~地一聲掉在地上，消失了！\n" NOR);
                destruct(this_object());
                return;
        }
        return;
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        string msg;
        
        if (! arg)
        {
                write("你要讀什麼？\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if (where->query("no_fight")
           && me->query("doing") != "scheme")
        {
                write("你無法在這裏靜下心來研讀霸刀。\n");
                return 1;
        }

    /* if (! me->query("scborn/ok"))
        {
                write("你還沒有經歷輪迴轉世呢，無法修煉霸刀。\n");
                return 1;
        } */
        
        if (me->query("str") < 38)
        {
                write("你先天臂力不足，無法修煉霸刀。\n");
                return 1;
        }

        if (me->query("con") < 38)
        {
                write("你先天臂力不足，無法修煉霸刀。\n");
                return 1;
        }

        if ((int)me->query_skill("sword", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }

        if ((int)me->query_skill("club", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }
                
        if ((int)me->query_skill("staff", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }
                
        if ((int)me->query_skill("whip", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }
                
        if ((int)me->query_skill("dagger", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }
                
        if ((int)me->query_skill("hammer", 1) && ! me->query("thborn/ok"))
        {
                write("你所學的雜學太多了，無法專心研習霸刀。\n");
                return 1;
        }
                                                          
        if ((int)me->query("max_neili") < 20000)
        {
                write("你的內力修為不足。\n");
                return 1;
        }

        if ((int)me->query_skill("force", 1) < 500)
        {
                write("你的內功火候太淺。\n");
                return 1;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 500)
        {
                write("你的武學修養不足。\n");
                return 1;
        }
                
        if ((int)me->query_skill("blade", 1) < 700)
        {
                write("你的基本刀法火候不夠，無法學習霸刀。\n");
                return 1;
        }
                
        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("你的梵文水平太低，無法看懂書裏所記載的內容。\n");        
                return 1;
        }
        
        if (! id(arg))
        {
                write("這裏沒有這本書。\n");
                return 1;
        }

        if (me->query_skill("yinyang-shiertian", 1) && ! me->query("thborn/ok"))
        {
                write("你體內的陰陽真氣無法與霸刀相兼容。\n");
                return 1;
        }
        
        if (me->query_skill("lunhui-sword", 1) && ! me->query("thborn/ok"))
        {
                write("你體內的六道輪迴真氣無法與霸刀相兼容。\n");
                return 1;
        }
                
        if ((int)me->query("combat_exp") < 30000000)
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if ((int)me->query("jing") < 100
           || (int)me->query("qi") < 100
           || (int)me->query("neili") < 200)
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        
        msg = HIG "$N" HIG "翻看《霸刀》，仔細研究上面所記載的武學，霎那間若有所悟……\n" NOR;
        msg += HIG "$N" HIG "以手做刀，左劈右砍，忽而眉頭金鎖，忽而閉目沉思。\n" NOR;
        msg += HIG "$N" HIG "長歎一聲，感慨萬千，似乎明白了什麼 ……\n" NOR; 
        message_vision(msg, me); 

        if (me->query_skill("badao", 1) < 180)
        {                        
                write(HIW "你對「" HIG "霸刀" HIW "」有了新的領悟。\n" NOR);
                // 第一次學習
                if (! me->query_skill("badao", 1))
                {
                        // 輪迴點
                        if (me->query("scborn/cur_lunhui_point") < 7 && ! me->query("thborn/ok"))
                        {
                                write("你輪迴點不足，無法領悟霸刀。\n");
                                return 1;
                        }    
                        if (! me->query("thborn/ok"))
                        {
                                me->add("scborn/cur_lunhui_point", -7);
                                write(HIG "\n恭喜你學會了霸刀，消耗輪迴點 7 點，請勿將霸刀放棄為0級後再重新學習，否則需要重新消耗輪迴點。\n" NOR);
                        }
                        me->set_skill("badao", 40 + random(21));
                        me->save();
                }
                else                                        
                        me->set_skill("badao", me->query_skill("badao", 1) + 40 + random(21));

                destruct(this_object());
        }
        else
        {
                write(HIR "你霸刀級別已經無法再通過研讀祕籍來提升了。\n" NOR);
                return 1;
        }

        return 1;
}
