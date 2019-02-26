// jinshe1.c 

inherit ITEM;
inherit F_UNIQUE;

#include <ansi.h>; 

void setup()
{}

void init()
{
        add_action("do_du", "read");
}

void create()
{
        set_name(YEL"「金蛇祕芨」" NOR "上冊", ({ "jinshe book1","book1", }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("long",
        "這是一本用薄紙寫成的書。上書：「金蛇祕芨」。\n"
        "書皮泛黃，看來已經保存很久了。\n", );
                set("skill", ([
                        "name"        : "jinshe-jian",
                        "exp_required":        800000,
                        "jing_cost"   :        55,
                        "difficulty"  :        98,
                        "max_skill"   : 119,
                ]));
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (! arg)
        {
                write("研讀金蛇祕芨指令格式：read <技能> from <金蛇祕芨>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研讀金蛇祕芨指令格式：read <技能> from <金蛇祕芨>\n");
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

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你無法在這裏靜下心來研讀金蛇祕芨。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("這裏沒有這本書。\n");
                return 1;
        }

        if (skill != "蛇困愁城" && skill != "蛇影萬道"
           && skill != "金蛇噬天")
        {
                write("金蛇祕芨上並沒有記載你打算研究的內容。\n" NOR);
                return 1;
        }

        if( count_lt(query("combat_exp", me),800000) )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if (skill == "蛇困愁城")
        {
           if( query("can_perform/jinshe-jian/kun", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("jinshe-jian", 1) < 140)
           {
                write("你金蛇劍法不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (5) != 1)
           {
                write("你研究了半天，仍然無法將「蛇困愁城」融會貫通！\n");
                me->start_busy(15); 
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看祕芨，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;

           msg += HIG "$N" HIG "長歎一聲，感慨萬千。\n" NOR; 
           message_vision(msg, me); 

           if (me->can_improve_skill("sword"))
                   me->improve_skill("sword", 1500000);
           if (me->can_improve_skill("jinshe-jian"))
                   me->improve_skill("jinshe-jian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "蛇困愁城" HIW "」。\n" NOR);
           set("can_perform/jinshe-jian/kun", 1, me);
           
           return 1;
        }
    
        else 
       
        if (skill == "蛇影萬道")
        {
           if( query("can_perform/jinshe-jian/wan", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("jinshe-jian", 1) < 180)
           {
                write("你金蛇劍法不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (8) != 1)
           {
                write("你研究了半天，仍然無法將「蛇影萬道」融會貫通！\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看祕芨，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIG "$N" HIG "長歎一聲，感慨萬千。\n" NOR; 

           message_vision(msg, me); 

           if (me->can_improve_skill("sword"))
                   me->improve_skill("sword", 1500000);
           if (me->can_improve_skill("jinshe-jian"))
                   me->improve_skill("jinshe-jian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "蛇影萬道" HIW "」。\n" NOR);
           set("can_perform/jinshe-jian/wan", 1, me);

           return 1;
        }
 
        else 

        if (skill == "金蛇噬天")
        {
           if( query("can_perform/jinshe-jian/shi", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("jinshe-jian", 1) < 200)
           {
                write("你金蛇劍法不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (10) != 1)
           {
                write("你研究了半天，仍然無法將「萬劍縱橫」融會貫通！\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIG "$N" HIG "長歎一聲，感慨萬千。\n" NOR; 
           message_sort(msg, me); 

           if (me->can_improve_skill("sword"))
                   me->improve_skill("sword", 1500000);
           if (me->can_improve_skill("jinshe-jian"))
                   me->improve_skill("jinshe-jian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "金蛇噬天" HIW "」。\n" NOR);
           set("can_perform/jinshe-jian/shi", 1, me);
           
           return 1;
        }
}
