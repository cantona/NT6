// wushe-qu.c 舞蛇曲

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "guzheng-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("guzheng-jifa", 1) < 100)
                return notify_fail("你的古箏技法水平不夠，還是先練好再説吧！\n");

        if (me->query_skill("guzheng-jifa", 1) < me->query_skill("wushe-qu", 1))
                return notify_fail("你的古箏技法水平有限，無法領會更精妙的舞蛇曲。\n");

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

        me->receive_damage("jing", 25);
        me->receive_damage("qi", 15);

        return 1;
}

void do_effect(object me)
{
        object env;
        int lvl;
        mapping rs;
        string *st;
        object snake;
        int i;
        int sum;

        lvl = me->query_skill("guzheng-jifa", 1) / 2 +
              me->query_skill("wushe-qu", 1);

        if( (env=query("no_fight", environment(me))) )
                return;

        if (lvl < 50)
        {
                write(HIC "你滿頭大汗的彈了半天，好像沒有什麼作用。\n" NOR);
                return;
        }

        if( query("neili", me)<50 )
        {
                set("neili", 0, me);
                write(HIC "你隱隱覺得內力有些不濟。\n" NOR);
                return;
        }

        addn("neili", -20-random(10), me);

        if( !mapp(query("quarrys", env)) )
        {
                write(HIY "你彈了半天，但是沒有一條蛇出來。\n" NOR);
                return;
        }

        // 調用該地圖的蛇類
        rs=query("quarrys", env);

        st = keys(rs);
        sum = 0;

        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(rs[st[i]]))
                        rs[st[i]] = 0;

                sum += rs[st[i]];
        }

        if (! sum)
        {
                write(HIY "你彈了半天，但是似乎沒有什麼蛇出來。\n" NOR);
                return;
        }

        sum = random(sum);

        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < rs[st[i]])
                {
                        catch(snake = new("/clone/beast/" + st[i]));

                        if (! objectp(snake) || ! snake->is_snake())
                        {
                                write(HIY "你彈了半天，但是似乎沒有什麼蛇出來。\n" NOR);
                                return;
                        }

                        snake->add("snake_poison/level"+random(lvl/5));
                        snake->move(env);
                        write(HIR "你彈了一曲，只聽一陣嗤嗤做響，一條" +
                              snake->name() + HIR "從草叢中竄了出來。\n" NOR);
                        return;
                }
                sum -= rs[st[i]];
        }
}