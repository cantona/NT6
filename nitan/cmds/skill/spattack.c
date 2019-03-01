// spattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping weapon_name = ([
        "sword" : "劍",
        "blade" : "刀",
        "staff" : "杖",
        "whip"  : "鞭",
        "club"  : "棍",
]);

void do_remote_fight(object me, object couple, object target, int n);
void do_here_fight(object me, object couple, object target, int n);

int main(object me, string arg)
{
        int same_place;
        string couple_id;
        string couple_name;
        object couple;
        object target;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡不能戰鬥。\n");

        if (! arg)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        } else
                target = present(arg, environment(me));

        if (! target || ! me->is_fighting(target))
                return notify_fail("會心一擊只能對戰鬥中的對手使用。\n");

        if( !stringp(couple_id=query("couple/couple_id", me)) )
                return notify_fail("你還沒有伴侶，使什麼會心一擊？\n");

        couple_name=query("couple/couple_name", me);

        if (! objectp(couple = find_player(couple_id)))
                return notify_fail(couple_name + "不在這個世界上，無法給與你力量。\n");

        if (couple->is_ghost())
                return notify_fail(couple_name + "現在是鬼魂一個，無"
                                   "法穿越靈界給與你力量。\n");

        if (! living(couple))
                return notify_fail("你的心靈現在無法和" + couple_name + "溝通。\n");

        if (target == couple)
                return notify_fail("你有病啊！\n");

        same_place = (environment(couple) == environment(me));

        if (! same_place)
                do_remote_fight(me,couple,target,query("sex/"+couple->name(1, me)));
        else
                do_here_fight(me,couple,target,query("sex/"+couple->name(1, me)));
        return 1;
}

void do_remote_fight(object me, object couple, object target, int n)
{
        object weapon;
        string chinese_type;
        int need, cost;
        int enhance, count;
        string msg;

        if (n > 500) n = 500;
        need = 300 - n / 2;
        cost = 300 - n / 3;

        if( query("jingli", me)<need )
        {
                write("你試圖和你的伴侶進行心靈上的溝通，但是"
                      "一時覺得精力不濟，難以聯系。\n");
                return;
        }

        if( query("jingli", couple)<need )
        {
                write("你隱隱約約的感覺到你伴侶"
                      "的靈力，但是非常微弱，很難捕捉到。\n");
                return;
        }

        if (me->is_busy())
        {
                write("( 你上一個動作還沒有完成，不能施展會心一擊。)\n");
                return;
        }

        if (random(2))
                tell_object(me, HIM "你心中默默的念著" + couple->name(1) +
                            HIM "的名字，隱隱感到那若即若離的"
                            "靈覺，穿透了無盡的虛空，和你心心相連。\n\n" NOR);
        else
                tell_object(me, HIM "穿過了縹緲的虛空，你仿佛看到" + couple->name(1) +
                            HIM "，給予你無上的鼓舞和無盡的力量。\n\n" NOR);

        if (random(2))
                tell_object(couple, HIM "你似乎感覺到" + me->name(1) +
                            HIM "在你心靈深處呼喚你的名字，兩人之"
                            "間有如心有靈犀，你默默的為" +
                            gender_pronoun(query("gender", me))+
                            "祝福：去吧，我的愛人！\n" NOR);
        else
                tell_object(couple, HIM "冥冥你感到了" + me->name(1) +
                            HIM "對你的呼喚，這一剎那，你們在心靈上"
                            "全然相通，讓你把無形的力量注入給對方，鼓舞著" +
                            gender_pronoun(query("gender", me))+"。\n"NOR);

        addn("jingli", -cost, me);
        addn("jingli", -cost, couple);
        weapon=query_temp("weapon", me);
        if (weapon && (chinese_type = weapon_name[query("skill_type", weapon)]))
        {
                if( query("gender", me) == "女性" )
                        msg = HIG "$N" HIG "彈" + chinese_type +
                              "輕吟，宛若黃鶯出谷，飄身而進，手中的" +
                              weapon->name() + HIG "化作流星夜雨，披向$n"
                              HIG "。\n" NOR;
                else
                        msg = HIC "$N持" + chinese_type + "而進，竟然視$n" HIC "有若無物，手中" +
                              weapon->name() + HIC "揮洒自如，盪起層層" +
                              chinese_type + "影，將$p" HIC "困在當中。\n" NOR;
        } else
        {
                if( query("gender", me) == "女性" )
                        msg = HIG "$N" HIG "輕聲淺笑，飄然而進，身法驚艷"
                              "絕倫，有若九天玄女踏足紅塵，舉手投足之間沒有任何破綻。\n" NOR;
                else
                        msg = HIC "$N" HIC "縱聲長嘯，一股殺氣凜然而起，天"
                              "地登時色變，$N" HIC "挾風雷萬鈞之勢，壓向$n"
                              HIC "。\n" NOR;
        }

        message_combatd(msg, me, target);
        enhance = ((int)couple->query_skill("force") + n / 10) / 5;
        count = 1 + random(3 + n / 100);
        if (count > 3)
                count = 3;
        addn_temp("apply/attack", enhance, me);
        while (count--)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        }
        addn_temp("apply/attack", -enhance, me);
        me->start_busy(3);
        return;
}

void do_here_fight(object me, object couple, object target, int n)
{
        int need, cost;
        int enhance1, enhance2, count;
        string msg;

        if (n > 500) n = 500;
        need = 300 - n / 2;
        cost = 300 - n / 3;

        if (me->is_busy())
        {
                write("( 你上一個動作還沒有完成，不能施展會心一擊。)\n");
                return;
        }

        if (couple->is_busy())
        {
                write("你的伴侶現在正忙，無法配合你進行會心一擊。\n");
                return;
        }

        if (! couple->is_fighting(target))
                couple->fight_ob(target);

        message_combatd(HIY "$N" HIY "和$n" HIY "兩人眼神一交，心意已"
                        "然相通，不由的會心一笑，只見二人身形一錯，霎時\n"
                        "已經向" + target->name() + "攻出數招！\n" NOR,
                        me, couple);

        enhance1 = ((int)couple->query_skill("force") + n / 10) / 5;
        enhance2 = ((int)me->query_skill("force") + n / 10) / 5;
        count = 2 + random(5 + n / 50);
        if (count > 6)
                count = 6;
        addn_temp("apply/attack", enhance1, me);
        addn_temp("apply/attack", enhance2, couple);
        while (count--)
        {
                if (me->is_fighting(target) && (count % 2) == 0)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                else
                if (couple->is_fighting(target))
                        COMBAT_D->do_attack(couple,target,query_temp("weapon", couple),0);
                else
                        break;
        }

        me->start_busy(2);
        couple->start_busy(2);
        addn_temp("apply/attack", -enhance1, me);
        addn_temp("apply/attack", -enhance2, couple);
        return;
}

int help (object me)
{
        write(@HELP
指令格式：spattack [<施用對象>]

如果你結婚了，就可以使用會心一擊，聯手打擊對你正在攻擊的對手，
即使你的伴侶不在你的身邊，也可以運用靈力穿過遙遠的時空給與你
支持，當然這需要耗費精力，兩個人靈肉結合的次數越多，耗費的精
力就越少。如果你的伴侶就在你的身邊，則可以一起施展招數攻擊對
手，不需要耗費精力，招數的威力與兩的人靈肉結合的次數于伴侶的
內功等級相關。
HELP );
        return 1;
}
