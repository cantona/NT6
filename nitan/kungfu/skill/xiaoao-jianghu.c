#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa" ||
                                        usage == "tanqin-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("tanqin-jifa", 1) < 50 &&
            me->query_skill("chuixiao-jifa", 1) < 50)
                return notify_fail("你的吹蕭和彈琴的技法水平都太差，還是先練好再說吧！\n");

        if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qingxin-pushan", 1) &&
            me->query_skill("cuhixiao-jifa", 1) < me->query_skill("qingxin-pushan", 1))
                return notify_fail("在掌握更嫻熟的吹蕭技法或彈琴技法之前，你無法領會更精妙的笑傲江湖曲。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_qin() &&
            ! ob->valid_as_xiao())
                return notify_fail("你手上即沒有簫，也沒有琴，怎麼練習？\n");

        if( query("jing", me)<100 )
                return notify_fail("你的精神不夠好，沒法練習了。\n");

        if( query("qi", me)<50 )
                return notify_fail("你現在實在是太累了，練不動了。\n");

        me->receive_damage("jing", 60);
        me->receive_damage("qi", 40);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        object ob;
        string type;
        string other;
        int amount;
        int lvl;
        int i;

        lvl = me->query_skill("xiaoao-jianghu", 1);

        if (lvl < 100)
                return;

        if (previous_object() == find_object(SKILL_D("chuixiao-jifa")))
        {
                type = "xajh/xiao";
                other = "xajh/qin";
        } else
        if (previous_object() == find_object(SKILL_D("tanqin-jifa")))
        {
                type = "xajh/qin";
                other = "xajh/qin";
        } else
                return;

        // special effort
        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                ob = obs[i];
                if (ob == me || ! ob->is_character() || ! living(ob))
                        continue;

                if( query_temp("xajh/powerup", ob) || 
                    time()-query_temp(other, ob)>30 || 
                    !stringp(query_temp("xajh/player", ob)) || 
                    query_temp("xajh/player", ob) == query("id", me) )
                {
                        set_temp(type, time(), ob);
                        set_temp("xajh/player",query("id",  me), ob);
                        set_temp("xajh/player_name", me->name(), ob);
                        message("visoin", HIG "你聽了" + me->name() +
                                HIG "的曲子，覺得非常的慷慨豪邁。\n" NOR, ob);
                } else
                {
                        // 雙人合奏
                        amount = lvl;
                        if (amount > ob->query_skill("force"))
                                amount = ob->query_skill("force");
                        amount /= 6;
                        delete_temp(other, ob);
                        delete_temp(type, ob);
                        addn_temp("apply/attack", amount, ob);
                        addn_temp("apply/dodge", amount, ob);
                        set_temp("xajh/powerup", 1, ob);
                
                        call_out("remove_effect", lvl / 2, ob, amount);
                        message("vision", HIG "你聽了" + me->name() +
                                HIG"和"+query_temp("xajh/player_name", ob)+
                                "合奏的笑傲江湖，只覺得心潮澎湃，充滿了力量。\n" NOR, ob);
                        delete_temp("xajh/player", ob);
                        delete_temp("xajh/player_name", ob);
                }
        }
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))
                return;
        if( query_temp("xajh/powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                delete_temp("xajh/powerup", me);
                tell_object(me, "你的心情漸漸的平息下來。\n");
        }
}