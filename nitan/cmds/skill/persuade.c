// du.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object ob, victim;
        int sp, dp;

        object where = environment(me);
        
        seteuid(getuid());

        if( query("family/family_name", me) != "峨嵋派" )
                return notify_fail("只有峨嵋派才能用渡世濟人！\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不會有人打鬥！\n");

        if( query_temp("dushi", me) )
                return notify_fail("你已經在勸人家罷鬥了！\n");

        if (! arg || sscanf(arg, "%s stop", who) != 1)
                return notify_fail("指令格式：persuade|quanjia <人物> stop\n");

        victim = present(who, where);

        if (! victim || victim == me)
                return notify_fail("你想找的對象不在這裏。\n");

        if (! living(victim))
                return notify_fail("他目前這個樣子似乎已經不能戰鬥了。\n");

        if (! victim->is_fighting())
                return notify_fail("人家沒在打鬥啊？\n");

        if( query("family/family_name", victim) == "峨嵋派" )
                return notify_fail("你不能向本派的使用渡世濟人！\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("玩家不能勸巫師罷鬥。\n");

        if (me->is_fighting())
                return notify_fail("一邊打架一邊勸別人罷鬥？你真是虛偽到家了！\n");

        sp=me->query_skill("persuading",1)+query("kar", me)*5;
        if (sp < 1) sp = 1;
        dp=query("jing", victim);

        tell_object(me, "你搖搖了頭，慢慢地向" + victim->name() +
                    "走過去，雙手合十，開始唸誦佛經...\n\n");
        tell_object(victim, me->name() + "搖搖了頭向你慢慢走過來，"
                    "雙手合十，説道：我佛慈悲普度渡眾生, 還請" +
                    RANK_D->query_respect(victim) +
                    "罷鬥, 免增罪孽吧...\n\n");

        message("vision", "只見" + me->name() + "搖搖了頭，慢慢地向" +
                victim->name() + "走過去，\n雙手合十，説道：請" +
                RANK_D->query_respect(victim) + "，停手吧 ...\n\n",
                where, ({ me, victim }));

        set_temp("dushi", 1, me);
        call_out("compelete_dushi", 3, me, victim, ob, sp, dp);

        return 1;
}

protected void compelete_dushi(object me, object victim, object ob, int sp, int dp)
{
        int amount;
        object ob1;

        if (objectp(me))
                delete_temp("dushi", me);
        else
                return;

        if (! objectp(victim))
                return;

        if (environment(victim) != environment(me))
        {
                tell_object(me, "很可惜，你要找的人已經不在這裏了。\n");
                return;
        }

        if (living(victim) && (random(sp + dp) > dp))
        {
                victim->remove_all_enemy(1);
                tell_object(me, victim->name() + "低頭想了一會，又看了"
                            "看你，搖搖頭，歎了口氣，停止了打鬥。\n");
                tell_object(victim, "你聽了之後，心中不覺一緊，不再想繼續打下去了。\n");

                me->improve_skill("persuading",2*random(query("int", me)));
                if( me->query_potential_limit()>query("potential", me) )
                        addn("potential", 1, me);
                addn("combat_exp", 2, me);
                if (! me->is_busy())
                        me->start_busy(3);
        } else 
        {
                if (random(sp) > dp / 2)
                {
                        message_vision("$n狠狠地瞪了$N一眼，喝道：滾！"
                                       "$N歎了口氣轉身走開了。\n", me, victim);
                        return;
                }
        
                tell_object(me, victim->name() + "扭過頭去，對你理都不理。\n");
                tell_object(victim, "你扭過頭去，對" + me->name() + "理都不理。\n");
                message("vision", victim->name() + "扭過頭去，對" + me->name() + "理都不理。\n", 
                        environment(me), ({ me, victim }));

        }
}

int help(object me)
{
        write(@HELP
指令格式 : persuade | quanjia <某人> stop

HELP );
        return 1;
}