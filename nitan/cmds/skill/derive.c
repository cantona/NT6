// derive.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int deriving(object me);
int halt_deriving(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where;
        int point;
        string skill;

        seteuid(getuid());
        where = environment(me);
        
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( me->is_busy() || query_temp("pending/deriving", me) )
                return notify_fail("你現在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中還是好好的凝神對敵吧。\n");

        if( query("combat_exp", me)<100000 )
                return notify_fail("你的實戰經驗太淺，還無法領會通過實戰獲得的心得。\n");

        if( query("experience", me)<query("learned_experience", me)+60 )
                return notify_fail("你現在積累的實戰體會還太少。\n");

        if( query("qi", me)<query("max_qi", me)*7/10 )
                return notify_fail("你現在沒有充足的體力用來吸收實戰的心得。\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("你現在精神不濟，難以抓住實戰體會中的祕要！\n");

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("你無法在這個地方安心吸收通過實戰得到的心得。\n");

        if (arg && sscanf(arg, "%d %s", point, skill) == 2 ||
            arg && sscanf(arg, "%d", point) == 1)
        {
                if( query("experience", me)-query("learned_experience", me)<point )
                        return notify_fail("你並沒有積累這麼多實戰體會。\n");

                if (point < 60)
                        return notify_fail("似乎沒有必要為吸收這點體會下功夫。\n");
        } else
        {
                point = -1;
                if (arg)
                        sscanf(arg, "%s", skill);
        }

        if (! stringp(skill)) skill = "martial-cognize";

        write("你默默的想了想先前一段時間和對手交手時的情形，開始吸收汲取其中的心得。\n");

        set_temp("pending/deriving", 1, me);
        set_temp("derived_point", point, me);
        set_temp("derived_skill", skill, me);
        me->set_short_desc("正在演練招式。");
        message_vision("$N慢慢放開姿勢，忽前忽後，手舞足蹈，似乎在思索什麼。\n", me);
        me->start_busy(bind((:call_other, __FILE__, "deriving" :), me),
                       bind((:call_other, __FILE__, "halt_deriving" :), me));
        return 1;
}

int deriving(object me)
{
        int improve;
        int cost;
        string skl_id, skl_name;
        object weapon;
        string skill;
        int r;
        int n;

        skill=query_temp("derived_skill", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" || 
            skill != "sword-cognize")
                skl_id = "martial-cognize";
        else skl_id = "sword-cognize";
 
        skl_name = to_chinese(skl_id);
                        
        if (! me->can_improve_skill(skl_id))
        {
                write("你感覺自己的實戰經驗還有欠缺，還無法"
                      "領會更高境界的" + skl_name + "。\n");
                message("vision", me->name() + "輕輕的歎了口氣，怔怔"
                        "的發了一會兒的呆。\n", environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                me->set_short_desc(0);
                return 0;
        }

        cost = me->query_skill(skl_id, 1) / 2 + 1;
        cost+=query_temp("apply/derive_times", me);
        if (present("derive emblem", me)) 
                cost += cost * 3;
                
        if( query("special_skill/musha", me) )
                cost += cost * 50 / 100;

        if( n = ACTION_D->query_action("jiqu_speed") )
                cost *= n;

        if( cost+query("learned_experience", me)>query("experience", me) )
                cost=query("experience", me)-query("learned_experience", me);

        // gain martial-cognize & combat_exp, potential
        improve = cost * (1 + random(5 + me->query_skill(skl_id, 1) / 10));
        if( intp(r=query_temp("apply/derive_effect", me)) )
                improve += improve * r / 100;

        if( intp(r=query("jingmai/derive_effect", me)) )
                improve += improve * r / 100;

        if( query("jingmai/finish", me) )
                improve += improve * ZHOUTIAN_D->query_jingmai_effect("derive_effect")/100;
                
        // 轉世技能羣邪辟易提升汲取效果
        if( query("special_skill/nopoison", me) )
                improve += improve * 50 / 100; 

        if( query("special_skill/musha", me) )
                improve += improve * 50 / 100; 
        
        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;
                
        // 幫派榮譽點
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "jiqu") )
                improve += improve * 20 / 100;

        if( me->query_family() && BUNCH_D->query_family_efficient(me->query_family(), "jiqu") )
                improve += improve * 20 / 100;
                
        if (me->can_improve_skill(skl_id))
                me->improve_skill(skl_id, improve);

        addn("combat_exp", 1+random(2), me);

        if (random(2))
                // not limit by potential limit
                addn("potential", 1, me);

        // cost experience
        if( me->add("learned_experience",cost) >= query("experience", me) )
        {
                write("你將實戰中獲得的體會心得充分的消化吸收了。\n");
                message("vision", me->name() + "微微一笑，看來內心頗為喜悦。\n",
                        environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                delete_temp("derived_point", me);
                delete_temp("derived_skill", me);
                me->set_short_desc(0);
                return 0;
        }

        if( query_temp("derived_point", me)>0 )
        {
                if( me->add_temp("derived_point",-cost)<1 )
                {
                        write("你消化吸收了一些實戰中獲得的體會心得。\n");
                        message("vision", me->name() + "微微一笑，看來內心頗為喜悦。\n",
                                environment(me), ({ me }));
                        delete_temp("pending/deriving", me);
                        delete_temp("derived_point", me);
                        delete_temp("derived_skill", me);
                        me->set_short_desc(0);
                        return 0;
                }
        }

        switch (skl_name)
        {
        case "武學修養":
                switch (random(20))
                {
                case 0:
                        write("你凝思良久，對內功方面又有了新的體會。\n");
                        break;
        
                case 1:
                        write("你默默思索，對拳腳功夫又想通了一些關節。\n");
                        break;
        
                case 2:
                        write("你靜心琢磨，對輕身功夫又添了一層理解。\n");
                        break;
        
                case 3:
                        write("你總結了見識過的種種兵器功夫，又想通了其中的一些奧祕。\n");
                        break;
                }
                break;

        case "劍道修養":
                switch (random(20))
                {
                case 0:
                        write("你輕揮長劍，細細揣摩劍道精微之處。\n");
                        break;
        
                case 1:
                        write("你手中長劍點抹切削，暗暗分析各種手法的不同。\n");
                        break;
        
                case 2:
                        write("你靜心琢磨，彷彿又明白了一點劍術上攻守進退的技巧。\n");
                        break;
        
                case 3:
                        write("你眼前浮現出不同門派的各式劍法，似有所悟。\n");
                        break;
                }
                break;
        }

        if( random(2) && query("total_hatred", me)>0 )
        {
                // addn("total_hatred", -random(1 + cost), me);
                addn("total_hatred", -(random(10) + 1), me);
                tell_object(me, CYN "你只覺一陣清氣透入肺腑，胸中殺意漸消。\n" NOR);
                if( query("total_hatred", me)<0 )
                        set("total_hatred", 0, me);
        }

        return 1;
}

int halt_deriving(object me)
{
        tell_object(me, "你心隨意轉，收回念頭，不再思索武學祕奧。\n");
        tell_room(environment(me), me->name() + "唯一皺眉，收住了姿勢。\n", me);
        delete_temp("pending/deriving", me);
        delete_temp("derived_point", me);
        delete_temp("derived_skill", me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : derive [<點數>] [ 技能 ]

    這個指令可以讓你吸收汲取實戰中的體會，當你充分的消化了其
中的祕奧以後，可以提升自己的武學修養。這是一門艱深的學問，是
所有武學的基礎，身為一代宗師，武學修養是必不可少的。如果你裝
備了劍這種武器，而且指定了技能名為 sword-cognize，則將獲得劍
道修養。

HELP );
        return 1;
}
