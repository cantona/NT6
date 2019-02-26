// practice.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string skillname;
        string base_skname;
        int skill, skill_basic, times, i;
        int c, r;
        int difficult, diff, improve;
        int neili_cost, qi_cost, qi;
        int t1, t2, t3, t4;
        int t = time();
        int n;

        if( !where ) return notify_fail("你目前的位置有問題，還是先找巫師解決吧！\n");

        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( t == query_temp("time/practice", me) )
                return notify_fail("你剛剛才練習過（如果你要連續練習，可以指明練習的次數）。\n");

        if( me->is_fighting() )
                return notify_fail("你已經在戰鬥中了，學一點實戰經驗吧。\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            query("doing", me) != "scheme" )
                return notify_fail("你無法在這個地方安心練習。\n");

        if( !arg ) return (__DIR__"enable")->main(me, arg);

        if( (sscanf(arg, "%s %d", base_skname, times) != 2) ) {
                times = 1;
                base_skname = arg;
        }

        c=200+query_temp("apply/practice_times", me);
        if( present("practice emblem", me))
                c += 300;

        if( query("special_skill/wisdom", me) )
                c += 500;

        if( n = ACTION_D->query_action("lianxi_times") )
                c *= n;
        if( times < 1 || times > c )
                return notify_fail("練習次數必須大於一次，但不能超過" + chinese_number(c) + "次。\n");

        if( !stringp(skillname = me->query_skill_mapped(base_skname)) )
                return notify_fail("你只能練習用 enable 指定的特殊技能。\n");

        skill_basic = me->query_skill(base_skname, 1);
        skill = me->query_skill(skillname, 1);
        if( skill < 1 )
                return notify_fail("你好像還沒有學過這項技能吧？最好先去請教別人。\n");

        if( skill_basic < 1 )
                return notify_fail("你對這方面的技能還是一竅不通，最好從先從基本學起。\n");

        if( skill_basic <= skill )
                return notify_fail("你的" + to_chinese(base_skname) +
                                   "火候不夠，難以繼續提升你" +
                                   to_chinese(skillname) + "的水平。\n");

        notify_fail("你現在不能練習這項技能。\n");

        if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

        if( !XUE_CMD->can_learn(me, skillname) )

        notify_fail("你試着練習" + to_chinese(skillname) + "，但是並沒有任何進步。\n");
        if( !me->can_improve_skill(skillname) )
                return notify_fail("也許是缺乏實戰經驗，你的練習總沒法進步。\n");

        set_temp("time/practice", t, me);

        if( skill >= 2000 )
                improve = skill_basic / 4;
        else
        if( skill >= 1000 )
                improve = skill_basic / 2;
        else
                improve = skill_basic;

        if( intp(r=query_temp("apply/practice_effect", me)) )
                improve += improve * r / 100;

        if( intp(r=query("jingmai/practice_effect", me)) )
                improve += improve * r / 100;

        if( query("jingmai/finish", me) )
                improve += ZHOUTIAN_D->query_jingmai_effect("practice_effect")/100;
                
        if( query("special_skill/wisdom", me) )
                improve += improve * 50 / 100;

        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;
        
        // 幫派榮譽點
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "lianxi") )
                improve += improve * 20 / 100;

        if( me->query_family() && BUNCH_D->query_family_efficient(me->query_family(), "lianxi") )
                improve += improve * 20 / 100;
                
        diff = SKILLS_D->query_skill_difficult(skillname);
        difficult = SKILL_D(skillname)->difficult_level();
        if( !diff) diff = difficult;
        if( !diff) diff = 100;
        improve = improve / (diff / 100 + 1);

        if( !SKILL_D(skillname)->practice_skill(me) )
                return 0;

        neili_cost = diff / 20 + 20;
        qi_cost = diff / 10 + 10;

        t1=query("neili", me)/neili_cost+1;
        t2=query("qi", me)/qi_cost+1;
        t3 = min(t1, t2);

        if( t3 > times ) t3 = times;
        t4 = t3 - 1;

        me->receive_damage("qi", qi_cost * t4);
        addn("neili", -neili_cost*t4, me);

        me->improve_skill(skillname, improve * (t3 + 1),
                          skill_basic > skill? 0: 1);

        if( t3 > 0 )
                write(HIC "你試着把" + to_chinese(skillname) +
                      "練了" + chinese_number(t3)+"趟。\n" NOR);

        if( t3 >= times )
                return 1;

        return 1;
}

int help(object me)
{
        write(@TEXT
指令格式：practice|lian <技能種類> <次數>

這個指令讓你練習某個種類的技能，這個技能必須是經過 enable 的專業技能。

如果你對這方面的基本技能夠高，可以經由練習直接升級，而且升級的上限只跟
你基本技能的等級有關，換句話説，勤加練習是使你的所學「青出於藍勝於藍」
的唯一途徑，當然，在這之前你必須從實際運用中獲得足夠的經驗以提升你的基
本技能。
TEXT );
        return 1;
}

