#include <ansi.h>
inherit F_SSERVER;

string name() { return "練毒"; }

int perform(object me,object target)
{
        int sp, dp, temp;
        int my_skill, my_force, tg_age, skill_count, duli;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡太嘈雜，你不能靜下心來修煉。\n");

        if( !objectp(target)
         || query("host_id", target) != query("id", me) )
                return notify_fail("你要吸取什麼毒蟲的毒素？\n");

        if( query("age", target)<99 )
                return notify_fail("你看清楚點，那東西像是毒蟲嗎？\n");

        my_skill = (int)me->query_skill("qianzhu-wandushou", 1);
        my_force = (int)me->query_skill("xiuluo-yinshagong", 1);
        tg_age=query("age", target);

        if( my_skill < 100 )
                return notify_fail("你的千蛛萬毒手火候太淺，不能用來吸取毒素！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能修煉千蛛萬毒手！\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中無法修煉千蛛萬毒手！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢！\n");

        if( target->is_fighting() || target->is_busy() )
                return notify_fail("毒蟲正忙著呢，不能和你配合！\n");

        if( query_temp("wudu_suck", me) )
                return notify_fail("你正在修煉中！\n");

        if (! me->can_improve_skill("qianzhu-wandushou"))
                return notify_fail("你的實戰經驗不夠，無法繼續修煉千蛛萬毒手！\n");

        if( my_skill < 130 && tg_age > 99 )
                return notify_fail(query("name", target)+"的毒力對你來說太強了，小心把小命送了！\n");

        if( my_skill < 160 && tg_age > 999 )
                return notify_fail(query("name", target)+"的毒力對你來說太強了，小心把小命送了！\n");

        if( my_skill > 140 && my_skill < 170 && tg_age < 999 )
                return notify_fail(query("name", target)+"的毒力對你來說已經太輕微了！\n");

        if( my_skill > 200 && tg_age < 9999 )
                return notify_fail(query("name", target)+"的毒力對你來說已經太輕微了！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，不足以對抗毒氣，別把小命送掉。\n");

        if( query("qi", target)<50 )
                return notify_fail(query("name", target)+"已經奄奄一息了，你"
                                    "無法從他體內吸取任何毒素！\n");

        if( query("qi", me)<200 )
                return notify_fail( "你快不行了，再練會送命的！\n");

        tell_object(me,RED"你小心翼翼的將手伸到"+query("name", target)+
                        RED "的面前，它張嘴就咬住了你的中指。你深吸一口\n氣，"
                        "面上頓時罩著一股黑氣，豆大的汗珠從額頭滾了下來。你只"
                        "覺得"+query("name", target)+RED"的\n毒素自傷處"
                        "源源不絕地流了進來，隨真氣遍布全身。\n\n" NOR );

        target->receive_wound("qi", 5);

        if( tg_age < 999 )
        {
                duli = 3;
        }

        if( tg_age > 999 && tg_age < 9999)
        {
                duli = 5;
        }

        if( tg_age > 9999 )
        {
                duli = 7;
        }

        skill_count = duli * (10 + random((int)me->query_int()));
        me->improve_skill("qianzhu-wandushou", skill_count);
        me->improve_skill("poison", skill_count * 2 / 3);
        tell_object(me, HIC "你的「千蛛萬毒手」和「基本毒技」進步了！\n" NOR);

        set_temp("wudu_suck", 1, me);
        call_out("del_wudusuck", 3, me, target);
/*
        switch( random(duli) )
        {
        case 0:
                temp=query("combat_exp", me);
                addn("combat_exp", temp/1000, target);

                if( query("combat_exp", target)>(temp*12/10) )
                            set("combat_exp", temp*12/10, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的經驗提高到"+
                        chinese_number(query("combat_exp", target))+"點。\n"NOR);
                break;

        case 1:
                addn_temp("apply/attack", 1, target);

                if( query_temp("apply/attack", target)>300 )
                            set_temp("apply/attack", 300, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的攻擊力提高到"+
                        chinese_number(query_temp("apply/attack", target))+"點。\n"NOR);
                break;

        case 2:
                addn_temp("apply/defense", 1, target);

                if( query_temp("apply/defense", target)>300 )
                            set_temp("apply/defense", 300, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的防御力提高到"+
                        chinese_number(query_temp("apply/defense", target))+"點。\n"NOR);
               break;

        case 3:
                addn_temp("apply/armor", 1, target);

                if( query_temp("apply/armor", target)>1500 )
                            set_temp("apply/armor", 1500, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的抗打擊能力提高到"+
                        chinese_number(query_temp("apply/armor", target))+"點。\n"NOR);
                break;

        case 4:
                addn("max_qi", 10, target);

                if( query("max_qi", target)>20000 )
                            set("max_qi", 20000, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的生命力提高到"+
                        chinese_number(query("max_qi", target))+"點。\n"NOR);
                break;

        case 5:
                addn("max_jing", 10, target);

                if( query("max_jing", target)>20000 )
                            set("max_jing", 20000, target);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的精提高到"+
                        chinese_number(query("max_jing", target))+"點。\n"NOR);
                break;

        case 6:
                temp = (int)target->query_skill("dodge", 1);

                target->set_skill("dodge",temp+1);
                if((int)target->query_skill("dodge",1)>300)
                            target->set_skill("dodge",300);
                else
                    tell_object(me,HIC+query("name", target)+NOR+HIC"的躲閃技能提高到"+
                        chinese_number((int)target->query_skill("dodge", 1)) +"級。\n"NOR );
        }
*/
        return 1;
}

void del_wudusuck(object me,object target)
{
        if( query_temp("wudu_suck", me) )
        {
                delete_temp("wudu_suck", me);
                tell_object(me, RED "\n只見它的肚子越漲越大，“吧嗒”一聲，鬆"
                                "開口掉在了地上。"+query("name", target)+RED
                                "吸飽了鮮\n血，身上透出一層寶光，身子頓時漲大"
                                "了許多！\n\n\n" NOR,);
                me->receive_damage("qi", 20);
        }

        set_temp("nopoison", 0, target);
}