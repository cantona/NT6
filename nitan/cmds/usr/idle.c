// idle.c 發呆神功

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int lvl;
        int n;

        if (me->ban_say(0))
                return 0;

        if (! arg)
                return notify_fail("你要讓哪個玩家發呆？\n");

        if (sscanf(arg, "%s %d", arg, n) != 2)
                n = 1;

        if( n > 10 ) n = 10;
        if (! objectp(ob = find_player(arg)) || ! me->visible(ob))
                return notify_fail("你要讓哪個玩家發呆？\n");

        if (n < 1)
                return notify_fail("你要讓別人發呆多久？\n"); 

        if( time()-query_temp("last/idle", me)<10 )
                return notify_fail("如果你要連續使用發呆神功，請使用idle <玩家> <次數>\n");

        if (me == ob)
                return notify_fail("你大腦有水？\n");

        if (wizardp(ob))
                return notify_fail("你的發呆神功等級還沒有那麼高。\n");

        if( query("env/no_idle", ob) )
                return notify_fail("你不能讓這個人發呆...\n");

        lvl = me->query_skill("idle-force", 1);
        if (! lvl)
                return notify_fail("你的先學好了發呆神功再說。\n");

        if (lvl < 50)
                return notify_fail("你的發呆神功水平太差，無法施展絕技。\n");

        if (lvl < 300 && environment(ob) != environment(me))
                return notify_fail("你的發呆神功水平有限，無法施展奇術于千裡之外！\n");

        if( query("jing", me)<10*n )
                return notify_fail("你的精神太差，不能施展這一曠古神功。\n");

        if( query("learned_points", me)+n>query("potential", me) )
                return notify_fail("你的潛能不夠，無法施展這一曠古神功。\n");

        set_temp("last/idle", time(), me);

        me->receive_damage("jing", 10 * n);
        addn("learned_points", n, me);

        message_vision(HIM "$N" HIM "口中念念有詞：!@#$%^&，什麼意思？\n", me);
        if( random(lvl*lvl)+lvl*lvl<query("combat_exp", ob) || 
            random(lvl) + lvl / 2 < ob->query_skill("idle-force", 1))
        {
                write("沒有任何效果，看來你的發呆神功失敗了！\n");
                return 1;
        }

        switch(random(4))
        {
        case 0:
                message_vision(HIM "天空突然出現了一個人頭，惡狠狠的盯著$N"
                               HIM "，嚇得$P" HIM "目瞪口呆，一句話也說不上來。\n" NOR,
                               ob);
                break;
        case 1:
                message_vision(HIM "煙霧中突然竄出兩個小鬼，一把抓住$N"
                               HIM "，道：走，該你去報到了！嚇得$P"
                               HIM "口吐白沫，幾乎暈了過去。\n" NOR,
                               ob);
                break;
        case 2:
                message_vision(HIM "一個人飛也似的跑了過來，大聲喊道：" +
                               ob->name() + HIM "！" + ob->name() + HIM "！"
                               "你的股票又跌了！\n$P"
                               HIM "聽了一跤摔在了地上，不住的抽搐！\n" NOR,
                               ob);
                break;
        default:
                message_vision(HIM "忽然警鈴大作，由遠及近，越來越響，$N" +
                               HIM "登時臉色發白，說不出話來！\n" NOR,
                               ob);
                break;
        }

        if (lvl > 180) lvl = 180;
        lvl *= n;

        if (! ob->ban_say(1))
                CHANNEL_D->do_channel(this_object(), "rumor", "聽說" +
                                      me->name(1) + HIM "施展發呆神功，" +
                                      ob->name(1) + HIM "無辜受害。");
        ob->ban_say_until(lvl, "你被嚇傻了，現在說不上話來");
        write(HIC "你的發呆神功成功了，" + ob->name(1) +
              HIC "現在被嚇得說不上話來了！\n" NOR);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : idle <玩家> <次數>

這個指令可以讓你使某一個玩家不能說話，當你的發呆神功到了
三百級以後可以使不在你面前的玩家閉嘴。運用發呆神功的成功
率與自己的發呆神功等級和對方的經驗有關，每使用一次發呆神
功都會耗費一點潛能和一些精。
 
HELP );
        return 1;
}
