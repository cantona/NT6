// beg.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object ob, victim;
        int sp, dp;

        object where = environment(me);

        seteuid(getuid());

        if( query("family/family_name", me) != "丐幫" )
                  return notify_fail("只有乞丐才能乞討！\n");

        if( query("no_beg", environment(me)) || 
            query("no_fight", environment(me)) )
                return notify_fail("這裏不是你叫化子能來討飯的地方！\n");

        if( query_temp("begging", me) )
                return notify_fail("你已經在向人家乞討了！\n");

        if (! arg || sscanf(arg, "%s from %s", what, who) != 2)
                return notify_fail("指令格式：beg <物品> from <人物>\n");

        victim = present(who, environment(me));
        if (what != "gold" && what != "silver" && what != "coin")
                return notify_fail("你只能乞討硬通貨 :)\n");

        if (! victim || victim == me)
                return notify_fail("你想乞討的對象不在這裏。\n");

        if (! living(victim) || ! objectp(victim))
                return notify_fail("你要向誰乞討？\n");

        if( query("family/family_name", victim) == "丐幫" )
                return notify_fail("你不能向乞丐乞討！\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("玩家不能向巫師乞討。\n");

        if( query("env/no_beg", me) )
                return notify_fail(victim->name() + "對你的乞討理都不理！。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("一邊打架一邊要飯？你真是活膩了！\n");

        if (victim->is_fighting())
                return notify_fail(victim->name() + "正在打架，沒空理你！\n");

        ob = present(what, victim);
        if (! ob) ob = present("gold", victim);
        if (! ob) ob = present("silver", victim);
        if (! ob) ob = present("coin", victim);

        if (! ob)
                return notify_fail( victim->name() + "身上看起來沒有什麼讓你感興趣的東西。\n");

        if( query("equipped", ob) || query("no_drop", ob) )
                return notify_fail("這是那人的隨身傢伙，肯定不會給你。\n");

        sp = (int)me->query_skill("begging");
        sp = sp * sp * sp / 10;

        if (sp < 1) sp = 1;
        dp=query("jing", victim)+ob->value()/5;

        tell_object(me, "你裝出可憐巴巴的樣子，慢慢地向" + victim->name() + "走過去，伸出雙手，想要"
                        +query("unit", ob)+ob->name()+"...\n\n");
        tell_object(victim, me->name() + "可憐巴巴地向你慢慢走過來，伸出手，説道：" + RANK_D->query_respect(victim) + "行行好，給我"
                        +query("unit", ob)+ob->name()+"吧...！\n\n");
        message("vision", "只見" + me->name() + "裝出可憐巴巴的樣子，慢慢地向"
                + victim->name() + "走過去，\n伸出雙手，説道："
                + RANK_D->query_respect(victim) + "，行行好吧 ...\n\n", environment(me), ({ me, victim}) );

        set_temp("begging", 1, me);
        call_out( "compelete_beg", 3, me, victim, ob, sp, dp);
        return 1;
}

protected void compelete_beg(object me, object victim, object ob, int sp, int dp)
{
        int amount;
        int bcount;
        object ob1;
        object where;

        if (! objectp(me)) return;
        delete_temp("begging", me);

        where = environment(me);
        if (! objectp(ob) || ! living(me) || me->is_fighting())
                return;

        if (! victim || environment(victim) != environment(me))
        {
                tell_object(me, "太可惜了，你要乞討的人已經走了。\n");
                return;
        }

        if (environment(ob) != victim)
        {
                tell_object(me, "太可惜了，人家好像已經沒有" + ob->name() + "了。\n");
                return;
        }

        if (living(victim) && (random(sp + dp) > dp))
        {
                if( !query("money_id", ob) || !(amount=ob->query_amount()) )
                {
                        tell_object(me, "看來還是走吧，這家"
                                    "夥身上已經沒有多少油水可榨了。\n");
                        return;
                }

                bcount = amount / 5;
                if (! bcount) bcount = 1;
                ob->set_amount(amount - bcount);

                ob1=new("/clone/money/"+query("money_id", ob));
                ob1->set_amount(bcount);
                ob1->move(me);

                tell_object(me, victim->name() + "低頭想了一會，又看了看你，搖搖頭，歎了口氣，丟給你一" +
                                query("unit", ob1)+ob1->name()+"。\n");
                tell_object(victim, "你看着" +  me->name() +"的可憐樣，歎了口氣，丟給他一" +
                                query("unit", ob1)+ob1->name()+"。\n");

                      if (me->can_improve_skill("begging"))
                          me->improve_skill("begging",random(query("int", me)));

                      if( query("potential", me)<me->query_potential_limit() )
                        addn("potential", 1, me);

                addn("combat_exp", 1, me);
                if (! me->is_busy())
                        me->start_busy(3 + random(4));
        } else
        {
                if (random(sp) > dp / 2)
                {
                        message_vision(victim->name() + "狠狠"
                                       "地瞪了$N一眼，喝道：滾！"
                                       "$N嚇了一跳，急忙扭頭灰溜"
                                       "溜地走開了。\n", me);
                        if (! me->is_busy())
                                me->start_busy(3);
                        return;
                }

                tell_object(me, victim->name() + "扭過頭去，對你理都不理。\n");
                tell_object(victim, "你扭過頭去，對" + me->name() +
                            "理都不理。\n");
                message("vision", victim->name() + "扭過頭去，對" +
                        me->name() +  "理都不理。\n",
                        environment(me), ({ me, victim }) );

                if (! me->is_busy())
                        me->start_busy(3);
        }
}

int help(object me)
{
        write(@HELP
指令格式 : beg <某物> from <某人>

HELP );
        return 1;
}
