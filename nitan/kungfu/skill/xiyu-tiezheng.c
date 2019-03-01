#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "guzheng-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("guzheng-jifa", 1) < 100)
                return notify_fail("你的古箏技法水平不夠，還是先練好再說吧！\n");

        if (me->query_skill("guzheng-jifa", 1) < me->query_skill("xiyu-tiezheng", 1))
                return notify_fail("你的古箏技法水平有限，無法領會更精妙的西域鐵箏音。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_zheng())
                return notify_fail("不拿出箏來，你怎麼練習？\n");

        if( query("jing", me)<80 )
                return notify_fail("你的精神不夠好，沒法練習了。\n");

        if( query("qi", me)<30 )
                return notify_fail("你現在實在是太疲憊了。\n");

        me->receive_damage("jing", 45);
        me->receive_damage("qi", 20);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        int lvl;
        int i;
        int damage;

        lvl = me->query_skill("guzheng-jifa", 1) / 2 +
              me->query_skill("xiyu-tiezheng", 1);

        if( query("no_fight", environment(me) )
            || query("skybook", environment(me) )
           || lvl < 150)
                return;

        lvl = lvl / 5 + me->query_skill("force");
        lvl /= 2;

        // special effort
        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                if (! obs[i]->is_character() || obs[i] == me || ! living(obs[i]))
                        continue;

                if (me->query_skill("xiyu-tiezheng") * 2 / 3 <
                    obs[i]->query_skill("xiyu-tiezheng"))
                        continue;

                if (lvl + random(lvl) < obs[i]->query_skill("force"))
                {
                        tell_object(obs[i], HIM "你聽了心中不禁微微一動，發現這曲子頗有奧妙之處。\n" NOR);
                        continue;
                }

                damage=query("max_neili", me)-query("max_neili", obs[i]);
                if (damage < 500)
                {
                        tell_object(obs[i], HIB "你忽然覺得一陣難受，連忙運了一口氣，才清醒過來。\n" NOR);
                        continue;
                }

                damage /= 10;
                me->want_kill(obs[i]);
                me->fight_ob(obs[i]);
                obs[i]->kill_ob(me);
                obs[i]->receive_damage("jing", damage, me);
                obs[i]->receive_wound("jing", damage / 3, me);
                tell_object(obs[i], HIB "你聽了這陣鬼哭狼嚎的聲音，不由得心浮氣躁……\n" NOR);
        }
}

string perform_action_file(string action)
{
        return __DIR__"xiyu-tiezheng/" + action; 
}