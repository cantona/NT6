// yanlian.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int practicing(object me);
int halt_practice(object me);

int main(object me, string arg)
{
        seteuid(getuid());

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("你在這裏演練也不怕吵到別人？\n");

        if (! arg)
                return notify_fail("你想演練什麼？\n");

        if (file_size(SKILL_D(arg) + ".c") <= 0)
                return notify_fail("沒聽説過有這種武功。\n");
               
        if (! mapp(SKILL_D(arg)->query_sub_skills()))
                return notify_fail("這種武功無需演練，還是勤加練習吧。\n");

        if ((int) me->query_skill(arg, 1) > 0)
                return notify_fail("你已經會" + to_chinese(arg) +
                                   "了，不必再演練了，還是多練習吧。\n");

        if (! SKILL_D(arg)->get_ready(me))
                return 1;

        set_temp("pending/practice", 1, me);
        set_temp("pending/practicing_skill", arg, me);
        me->start_busy((: practicing :), (: halt_practice :));

        write("你開始演練" + to_chinese(arg) + "。\n");
        return 1;
}

int practicing(object me)
{
        int i;
        int lvl;
        int step;
        int cost;
        string skill;
        string sub_skill;
        string action_msg;
        mapping action;
        mapping sub_skills;
        string  *skill_names;
        string  *color_msg = ({HIY, HIG, HIW, HIM, HIC});

        step=query_temp("pending/practice", me);
        skill=query_temp("pending/practicing_skill", me);
        if (! step || ! stringp(skill))
                return 0;
        if (! mapp(sub_skills = SKILL_D(skill)->query_sub_skills()))
                return 0;

        skill_names = keys(sub_skills);
        if (step <= sizeof(sub_skills))
        {
                sub_skill = skill_names[step - 1];
                if (! me->query_skill(sub_skill, 1))
                {
                        write("你正欲繼續演練，突然一楞，這才發現自己不會運用" +
                              to_chinese(sub_skill) + "\n");
                        return 0;
                }
                if (file_size(SKILL_D(sub_skill) + ".c") <= 0)
                {
                        write("嗯、怎麼回事？怎麼" + to_chinese(sub_skill) +
                              "這種武功好像失傳了？\n");
                        return 0;
                }
                action=SKILL_D(sub_skill)->query_action(me,query_temp("weapon", me));
                action_msg = action["action"];
                action_msg = replace_string(action_msg, "$n", "虛空");
                action_msg = replace_string(action_msg, "$l", "無盡處");
                cost = action["force"] * 8 / sizeof(sub_skills);
                if( query("neili", me)<cost )
                {
                        write("你剛欲出招，忽然間丹田真氣不繼，難以施為。\n");
                        return 0;
                }
                addn("neili", -cost, me);
                cost = action["force"] / 10;
                if( query("qi", me)<cost )
                {
                        write("你覺得氣力不加，疲憊不堪，無法再出招。\n");
                        return 0;
                }
                addn("qi", -cost, me);
                cost=action["force"]*8/query("int", me)/sizeof(sub_skills);
                if( query("jing", me)<cost )
                {
                        write("一陣煩惡湧上心頭，你幾欲嘔吐。\n");
                        return 0;
                }
                addn("jing", -cost, me);

                message_vision(color_msg[random(sizeof(color_msg))] + action_msg +
                               "。\n\n" NOR, me);
                if (me->query_skillo(sub_skill, 1) <
                    (int) sub_skills[sub_skill])
                {
                        write("你演練完" + to_chinese(sub_skill) + "這一招，"
                              "覺得有些迷茫，一時無法繼續演練下去。\n");
                        return 0;
                }
        } else
        {
                message_vision("$N緩緩的收住步伐，似有所思。\n", me);
                set_temp("pending/practice", 0, me);
                if (SKILL_D(skill)->get_finish(me))
                {
                        write("恭喜你練成" + to_chinese(skill) + "！\n");
                        lvl = 0;
                        for (i = 0; i < sizeof(sub_skills); i++)
                        {
                                lvl += me->query_skillo(skill_names[i], 1);
                                me->delete_skill(skill_names[i]);
                        }
                        lvl /= sizeof(sub_skills);
                        me->set_skill(skill, lvl);
                }
                return 0;
        }

        step++;
        set_temp("pending/practice", step, me);
        return 1;
}

int halt_practice(object me)
{
        write("你收住意念，不再繼續演練。\n");
        set_temp("pending/practice", 0, me);
        set_temp("pending/practicing_skill", 0, me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : yanlian <技能>

這個指令可以讓你將某些武功合而為一，成為一種強大得多的新技能。比如六
脈神劍。當你把六脈劍法一一學全後，你就可以演練六脈神劍(six-finger)，
一旦成功，你將領悟到一種全新的技能。演練將耗費精、氣、內力、潛能。如
果因為這些因素不能滿足，演練將失敗。
HELP
        );
        return 1;
}
