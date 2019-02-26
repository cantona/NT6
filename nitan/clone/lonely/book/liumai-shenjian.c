#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIW "「六脈神劍譜」" NOR, ({ "liumai jianpu", "liumai", "jianpu"}));
        set_weight(500);
        if (clonep())
               destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n這是一本用薄紙寫成的書，封皮上寫有「六脈神"
                            "劍譜」四\n字。你可以試着讀讀(read)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
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
                write("研讀六脈神劍譜指令格式：read <技能> from <六脈神劍譜>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研讀六脈神劍譜指令格式：read <技能> from <六脈神劍譜>\n");
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
                write("你無法在這裏靜下心來研讀六脈神劍譜。\n");
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

        if (skill != "shaochong-sword" && skill != "少衝劍"
           && skill != "guanchong-sword" && skill != "關衝劍"
           && skill != "shaoze-sword" && skill != "少澤劍"
           && skill != "zhongchong-sword" && skill != "中衝劍"
           && skill != "shangyang-sword" && skill != "商陽劍"
           && skill != "shaoshang-sword" && skill != "少商劍"
           && skill != "無形劍氣" && skill != "六脈劍氣"
           && skill != "萬劍縱橫")
        {
                write("六脈神劍譜上並沒有記載你打算研究的內容。\n" NOR);
                return 1;
        }

        if( count_lt(query("combat_exp", me),1000000) )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if (skill == "無形劍氣")
        {
           if( query("can_perform/liumai-shenjian/qi", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("liumai-shenjian", 1) < 185)
           {
                write("你六脈神劍不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (10) != 1)
           {
                write("你研究了半天，仍然無法將「無形劍氣」融會貫通！\n");
                me->start_busy(15); 
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIG "$N" HIG "中指一按，一股凌厲無倫的無形劍氣直奔天際。\n" NOR;
           msg += HIG "$N" HIG "長歎一聲，感慨萬千，將內力收回丹田。\n" NOR; 
           message_vision(msg, me); 

           if (me->can_improve_skill("finger"))
                   me->improve_skill("finger", 1500000);
           if (me->can_improve_skill("liumai-shenjian"))
                   me->improve_skill("liumai-shenjian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "無形劍氣" HIW "」。\n" NOR);
           set("can_perform/liumai-shenjian/qi", 1, me);
           destruct(this_object());
           return 1;
        }
    
        else 
       
        if (skill == "六脈劍氣")
        {
           if( query("can_perform/liumai-shenjian/six", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("liumai-shenjian", 1) < 220)
           {
                write("你六脈神劍不夠熟練，無法研讀此絕招！\n");
                return 1;
           }

           if (random (18) != 1)
           {
                write("你研究了半天，仍然無法將「六脈劍氣」融會貫通！\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIW "$N" HIW "攤開雙手，手指連彈，霎時間空氣炙熱，幾"
                  "欲沸騰，六道劍氣分自六穴，一起衝向天際" HIW "！\n" NOR;
           msg += HIG "$N" HIG "長歎一聲，感慨萬千，將內力收回丹田。\n" NOR; 
           message_vision(msg, me); 

           if (me->can_improve_skill("finger"))
                   me->improve_skill("finger", 1500000);
           if (me->can_improve_skill("liumai-shenjian"))
                   me->improve_skill("liumai-shenjian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "六脈劍氣" HIW "」。\n" NOR);
           set("can_perform/liumai-shenjian/six", 1, me);
           destruct(this_object());
           return 1;
        }
 
        else 

        if (skill == "萬劍縱橫")
        {
           if( query("can_perform/liumai-shenjian/zong", me) )
           {
                write("你不是已經會了嗎？\n");
                return 1;
           }
           if (me->query_skill("liumai-shenjian", 1) < 240)
           {
                write("你六脈神劍不夠熟練，無法研讀此絕招！\n");
                return 1;
           }
           if (me->query_skill("force", 1) < 340)
           {
                write("你內功火候不夠，無法研讀此絕招！\n");
                return 1;
           }

           if (random (50) != 1)
           {
                write("你研究了半天，仍然無法將「萬劍縱橫」融會貫通！\n");
                me->start_busy(15);
                set("jing", 1, me);
                return 1;
           }
           msg = HIG "$N" HIG "翻看劍譜，仔細研究上面所記載的武學，霎那間忽有所悟"
                     "……\n" NOR;
           msg += HIM "$N" HIM "一聲清嘯，十指紛彈，頓覺六脈劍譜已湧上心頭，此起"
                  "彼伏、連綿不絕。霎時劍氣如奔，連綿無盡的萬道劍氣豁然貫向虛空" HIM 
                  "！\n" NOR;
           msg += HIG "$N" HIG "長歎一聲，感慨萬千，將內力收回丹田。\n" NOR; 
           message_sort(msg, me); 

           if (me->can_improve_skill("finger"))
                   me->improve_skill("finger", 1500000);
           if (me->can_improve_skill("liumai-shenjian"))
                   me->improve_skill("liumai-shenjian", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "你學會了「" HIG "萬劍縱橫" HIW "」。\n" NOR);
           set("can_perform/liumai-shenjian/zong", 1, me);
           destruct(this_object());
           return 1;
        }

        else 
       
        if (me->query_skill("liumai-shenjian", 1))
        {
             write("你不是已經會六脈神劍了嗎？還學這幹什麼？\n");
             return 1;
        }

        else 
 
        if (skill == "shaochong-sword" || skill == "少衝劍")
                skill = "shaochong-sword";
        else

        if (skill == "shaoze-sword" || skill == "少澤劍")
                skill = "shaoze-sword";
        else

        if (skill == "shaoshang-sword" || skill == "少商劍")
                skill = "shaoshang-sword";
        else

        if (skill == "zhongchong-sword" || skill == "中衝劍")
                skill = "zhongchong-sword";
        else

        if (skill == "guanchong-sword" || skill == "關衝劍")
                skill = "guanchong-sword";
        else

        if (skill == "shangyang" || skill == "商陽劍")
                skill = "shangyang-sword";

        if (! SKILL_D(skill)->valid_learn(me))
                       return 0;

        if (! me->can_improve_skill(skill))
               {
                       write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                       return 1;
               }

        lv = me->query_skill(skill, 1);

        if (lv >= 1)
        {
                write("你研讀了一會兒，但是發現上面所説的實在有限。\n");
                return 1;
        }

        // 天賦聰穎增加研讀速度
        if( query("special_skill/clever", me) )
                me->improve_skill(skill,query("int", me)+5);
        else
                me->improve_skill(skill,query("int", me)+1);

        me->receive_damage("qi", random(50) + 30);
        me->receive_damage("jing", random(50) + 30);
        addn("neili", -lv, me);
        message("vision", me->name() + "正專心地研讀六脈神劍譜。\n",
                          environment(me), me);
        write("你仔細研讀六脈神劍譜，頗有心得。\n");
        destruct(this_object());
        return 1;
}