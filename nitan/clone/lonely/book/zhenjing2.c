#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(WHT "「九陰真經」下冊" NOR, ({ "zhenjing xiace", "xiace", "zhenjing", "jing"}));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", WHT "\n這是一本用薄紙寫成的書，封皮上寫有「九陰真經」下\n"
                            "冊六字。書皮泛黃，看來已經保存很久了。真經中記載\n"
                            "有催心掌、九陰白骨爪和銀龍鞭法等絕技，你可以試著\n"
                            "讀讀(read)看。\n\n" NOR, );
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

        string skill, book;
        int lv;

        if (! arg)
        {
                write("研讀九陰真經指令格式：read <技能> from <九陰真經>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研讀九陰真經指令格式：read <技能> from <九陰真經>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙著呢。\n");
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
                write("你無法在這裡靜下心來研讀真經。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("這裡沒有這本書。\n");
                return 1;
        }

        if (skill != "jiuyin-baiguzhao" && skill != "九陰白骨爪"
           && skill != "cuixin-zhang" && skill != "催心掌"
           && skill != "yinlong-bian" && skill != "銀龍鞭法"
           && skill != "天誅龍蛟訣"
           && skill != "奪命催心"
           && skill != "九陰神爪"
           && skill != "奪命連環爪")
        {
                write("真經上並沒有記載你打算研究的內容。\n" NOR);
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("你的梵文水平太低，無法看懂真經裡所記載的內容。\n");        
                return 1;
        }

        if( count_lt(query("combat_exp", me),800000) )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if (skill == "天誅龍蛟訣")
        {

                if( query("can_perform/yinlong-bian/zhu", me) )
                {
                        write("你不是已經會了嗎？\n"); 
                        return 1;
                }
                if (me->query_skill("yinlong-bian", 1) < 100)
                {
                        write("你銀龍鞭法不夠熟練，無法領悟該招。\n");
                        return 1;
                }
                tell_object(me, HIG "你學會了「天誅龍蛟訣」。\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                set("can_perform/yinlong-bian/zhu", 1, me);

                   if (me->can_improve_skill("whip"))
                           me->improve_skill("whip", 1500000);
                   if (me->can_improve_skill("yinlong-bian"))
                           me->improve_skill("yinlong-bian", 1500000); 
                   if (me->can_improve_skill("martial-cognize"))
                           me->improve_skill("martial-cognize", 1500000);

                return 1;          
 
        }

        else

        if (skill == "奪命催心")
        {

                if( query("can_perform/cuixin-zhang/cui", me) )
                {
                        write("你不是已經會了嗎？\n"); 
                        return 1;
                }
                if (me->query_skill("cuixin-zhang", 1) < 120)
                {
                        write("你催心掌不夠熟練，無法領悟該招。\n");
                        return 1;
                }

                tell_object(me, HIG "你學會了「奪命催心」。\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                set("can_perform/cuixin-zhang/cui", 1, me);

                   if (me->can_improve_skill("strike"))
                           me->improve_skill("strike", 1500000);
                   if (me->can_improve_skill("cuixin-zhang"))
                           me->improve_skill("cuixin-zhang", 1500000); 
                   if (me->can_improve_skill("martial-cognize"))
                           me->improve_skill("martial-cognize", 1500000);

                return 1; 
        }

        else 

        if (skill == "九陰神爪")
        {
                if( query("can_perform/jinyin-baiguzhao/zhua", me) )
                {
                        write("你不是已經會了嗎？\n"); 
                        return 1;
                }
                if (me->query_skill("jinyin-baiguzhao", 1) < 120)
                {
                        write("你九陰白骨爪不夠熟練，無法領悟該招。\n");
                        return 1;
                }

                tell_object(me, HIG "你學會了「九陰神爪」。\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                set("can_perform/jinyin-baiguzhao/zhua", 1, me);

                   if (me->can_improve_skill("claw"))
                           me->improve_skill("claw", 1500000);
                   if (me->can_improve_skill("jinyin-baiguzhao"))
                           me->improve_skill("jinyin-baiguzhao", 1500000); 
                   if (me->can_improve_skill("martial-cognize"))
                           me->improve_skill("martial-cognize", 1500000);

                return 1; 
        }

        else

        if (skill == "奪命連環爪")
        {
                if( query("can_perform/jinyin-baiguzhao/duo", me) )
                {
                        write("你不是已經會了嗎？\n"); 
                        return 1;
                }
                if (me->query_skill("jinyin-baiguzhao", 1) < 140)
                {
                        write("你九陰白骨爪不夠熟練，無法領悟該招。\n");
                        return 1;
                }

                tell_object(me, HIG "你學會了「奪命連環爪」。\n" NOR);
                me->receive_damage("jing", 80);
                me->start_busy(2);
                set("can_perform/jinyin-baiguzhao/duo", 1, me);

                   if (me->can_improve_skill("claw"))
                           me->improve_skill("claw", 1500000);
                   if (me->can_improve_skill("jinyin-baiguzhao"))
                           me->improve_skill("jinyin-baiguzhao", 1500000); 
                   if (me->can_improve_skill("martial-cognize"))
                           me->improve_skill("martial-cognize", 1500000);

                return 1; 
        }

        else
        
        if (skill == "jiuyin-baiguzhao" || skill == "九陰白骨爪")
                skill = "jiuyin-baiguzhao";
        else

        if (skill == "cuixin-zhang" || skill == "催心掌")
                skill = "cuixin-zhang";
        else

        if (skill == "yinlong-bian" || skill == "銀龍鞭法")
                skill = "yinlong-bian";

        if (! SKILL_D(skill)->valid_learn(me))
                       return 0;

        if (! me->can_improve_skill(skill))
               {
                       write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                       return 1;
               }

        lv = me->query_skill(skill, 1);

        if (lv >= 180)
        {
                write("你研讀了一會兒，但是發現上面所說的對你而言都太淺了。\n");
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
        message("vision", me->name() + "正專心地研讀九陰真經。\n",
                          environment(me), me);
        write("你仔細研讀九陰真經，頗有心得。\n");
        return 1;
}