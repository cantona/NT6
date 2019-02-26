// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <localtime.h>

int check_count(object me, int count)
{
        int age, tmp1, tmp2, tmp, lvl, qmwx, bonus;
        mixed *local;

        age=query("age", me);
        local=localtime((query("birthday", me)-14*365*24*60)*60);
        tmp1 = (local[LT_YEAR] % 10 + local[LT_YEAR] % 12 + local[LT_MON] + local[LT_MDAY]) % 8;
        tmp2 = (((local[LT_HOUR] + 1) % 24) / 2) % 8;
        tmp = tmp1 * 8 + tmp2;
        qmwx = me->query_skill("qimen-wuxing", 1);
        lvl = 1 + random(qmwx) / 20;

        if (tmp == count)
        {
                if( query_temp("taohua/count", me) == 2080 )
                {
                        tell_object(me,HIW"\n\n
四周景物突然變得模糊起來，你覺得頭腦一陣暈眩......
你定了定神，發現自己成功了！
\n\n"NOR);
                        /*
                        tell_object(me,
                                HIR "四周景物突然變得模糊起來，你覺得頭腦一陣暈眩......你在一陣煙霧中消失了。\n\n" NOR);
                        */
                        if( !query("taohua_maze", me) )
                        {
                                if ( qmwx < 1000) bonus = 10000;
                                else bonus = qmwx*10;
                                addn("combat_exp", bonus, me);
                                addn("potential", bonus/2, me);
                                addn("int", 1, me);
                                set("taohua_maze", age, me);
                                delete_temp("taohua/count", me);
                                tell_object(me,sprintf(HIY"你獲得了%d點經驗、%d點潛能，1點先天悟性！\n"NOR,
                                                bonus,
                                                bonus*2));
                                // me->move("/d/taohua/xiangzhong");
                                me->move("/d/taohua/mudi");
                        }
                } else
                {
                        tell_object(me,
                                HIW "你腳下一虛，不由自主的向下飛墜......你的意識漸漸模糊起來......\n\n" NOR);
                        if (userp(me))
                        me->unconcious();
                        delete_temp("taohua/count", me);
                        me->move("/d/taohua/enter_m");
                }
        } else
        if( query_temp("/taohua/count", me)>2100 )
        {
                tell_object(me,
                        HIW "忽見得一陣狂風掛來，天空中烏雲密佈，一陣陰冷的濃霧瞬間把你裹住......\n\n" NOR);
                if (userp(me))
                me->unconcious();
                delete_temp("taohua/count", me);
                me->move("/d/taohua/enter_m");
        }

        return 1;
}

void remove_effect(object me, int level)
{
        addn_temp("apply/int", -level, me);
        tell_object(me, HIB "你心中一動，腦海中空空蕩蕩，似乎有什麼東西正離你而去。\n" NOR);
}
