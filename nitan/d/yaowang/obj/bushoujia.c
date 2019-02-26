// bushou jia.c 逮獸夾
// Create by Vin for Heros.cn
// 為藥王谷修改了一點 kar
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + CYN "捕獸夾" NOR, ({ "bushou jia", "bushou", "jia" }));
        set_weight(3000);
        set("long", NOR + CYN "夾齒鋒利的捕獸夾，你可通過它佈置("
                    HIY "snare" NOR + CYN ")陷阱來捕獵。\n" NOR);
        set("unit", "只");
        set("value", 10000);
        set("no_sell", 1);
        setup();
}

void init()
{
        add_action("do_snare", "snare");
}

int do_snare(string arg)
{
        object ob;
        object me;
        int time;

        me = this_player();

        if (me->query_skill("hunting", 1) < 20)
                return notify_fail("你的狩獵技巧不夠嫻熟，難以佈置陷阱。\n");

        if( query("family/family_name", me) != "藥王谷" )
                return notify_fail("你的不是藥王谷弟子，不能使用藥王谷的工具。\n");

        if( query_temp("id") != query("id", me )
           && query_temp("id")
           && environment() != me)
                return notify_fail("這是別人放置的捕獸夾，你動它做甚？\n");

        if( query("no_fight", environment(me) )
            || query("no_quarry", environment(me)) )
                return notify_fail("在這裏放置捕獸夾？不太好吧。\n");

        if (query_temp("snare"))
                return notify_fail("捕獸夾已安置妥善，就等獵物上鈎了。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢，等一會兒吧。\n");

        if (me->is_fighting())
                return notify_fail("還是先把你面前的傢伙放倒再説吧。\n");

        if (! objectp(ob = present("shi er", me))
           || ! ob->query_amount())
                return notify_fail("現在你身上沒有食餌，難以佈置陷阱。\n");

        ob->add_amount(-1);

        message_vision(HIR "\n$N" HIR "在" + name() + HIR "裏放上食餌，輕輕"
                       "安置在地上，等待獵物上鈎。\n\n" NOR, me);

        set_temp("snare", 1);
        set_temp("id",query("id", me));

        if (environment() == me)
        {
                this_object()->move(environment(me));
                set("no_get", "捕獸夾的彈簧已然繃緊，亂動小心受傷。\n");
        }

        me->move(environment(me));

        time = 12 + random(12);

        remove_call_out("catch_quarry");
        call_out("catch_quarry", time, me);
        me->start_busy(time / 2 + 1);
        return 1;
}

void back_owner(object me)
{
        if (environment() != me)
        {
                this_object()->move(me);

                if (! me->is_busy())
                        me->start_busy(1);
        }
}



void catch_quarry(object me)
{
        object env;
        object quarry;
        mapping rs;
        string *st, msg;
        int i;
        int sum;
        int lvm, lvq, dam;

        delete_temp("snare");
        delete_temp("id");
        delete("no_get");

        env = environment(this_object());
        if (! objectp(me) || environment(me) != env || ! living(me))
        {
                message_vision(CYN "只聽「喀嚓」一聲，捕獸夾自動"
                               "合攏了。\n" NOR, this_object());
                return;
        }

        if( !mapp(query("quarrys", env) )
            || query("no_quarry", env )
            || query("no_fight", env) )
        {
                message_vision(CYN "等了半天，只聽「喀嚓」一聲，捕獸"
                               "夾自動合攏了，啥也沒抓到。\n" HIC "看"
                               "來這個地方捕捉不了什麼，$N" HIC "歎了"
                               "口氣，將捕獸夾收回。\n" NOR, me);
                back_owner(me);
                return;
        }

        // 調用該地圖的獵物
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
                return;

        sum = random(sum);

        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < rs[st[i]])
                {
                        catch(quarry = new("/clone/quarry/" + st[i]));

                        if (! objectp(quarry))
                                catch(quarry = new("/clone/beast/" + st[i]));

                        if (! objectp(quarry))
                                break;

                        msg = HIY "\n過得良久，$N" HIY "身後忽然晃出一" +
                              query("unit", quarry)+HIY+quarry->name()+
                              HIY "，聞得餌香後朝捕獸夾慢慢靠近。" NOR;

                        // 設定呼出者，即捕獵的獎勵對象
                        set("owner",query("id",  me), quarry);
                        quarry->move(environment(me));

                        lvm = me->query_skill("hunting", 1) / 2;
                        lvq=query("power", quarry);
                        dam = lvm + random(lvm * 2);

                        if (lvm / 2 + random(lvm) < lvq && lvq <= 20)
                        {
                                msg += HIY "便在此時，忽聽「喀嚓」一聲，那"
                                       "捕獸夾竟然自動合上了。$n" HIY "受驚"
                                       "之下急忙奔逃，消失在了林子深處。\n"
                                       "\n" NOR;
                                message_sort(msg, me, quarry);
                                destruct(quarry);
                        } else
                        if (lvm / 2 + random(lvm) < lvq && lvq > 20)
                        {
                                msg += HIY "便在這個時候，忽然聽得「喀嚓」"
                                       "一聲，那隻捕獸夾竟然自動合上了。$n"
                                       HIY "受驚之下勃然大怒，朝$N" HIY "直"
                                       "撲而去。\n\n" NOR;
                                message_sort(msg, me, quarry);
                                quarry->kill_ob(me);
                        }  else
                        if (lvm / 2 + random(lvm) > lvq * 4)
                        {
                                msg += HIY "只聽「啪」的一聲，$n" HIY "只顧"
                                       "覓食，不留神間已中了捕獸夾上的陷阱。"
                                       "那陷阱設得頗為精妙，那$n" HIY "不住"
                                       "掙扎，鮮血濺得四處都是。但只過得片刻"
                                       "，就再沒了動靜。\n" NOR;
                                message_sort(msg, me, quarry);
                                quarry->die(me);
                        }  else
                        if (lvm / 2 + random(lvm) > lvq * 3)
                        {
                                msg += HIY "只聽「啪」的一聲，$n" HIY "只顧"
                                       "覓食，不留神間已中了捕獸夾上的陷阱，"
                                       "登時被夾得鮮血直流。那$n" HIY "不停"
                                       "掙扎企圖逃跑，結果觸動傷口，頓時痛得"
                                       "昏了過去。\n" NOR;
                                message_sort(msg, me, quarry);
                                quarry->unconcious(me);
                        } else
                        {
                                msg += HIY "只聽「啪」的一聲，$n" HIY "只顧"
                                       "覓食，不留神間已中了捕獸夾上的陷阱，"
                                       "登時被夾得鮮血直流，痛聲長呼。\n\n" NOR;
                                message_sort(msg, me, quarry);
                                quarry->receive_wound("qi", dam, me);
                                quarry->receive_wound("jing", dam, me);
                                quarry->kill_ob(me);
                        }
                        me->start_busy(1);
                        return;
                }
                sum -= rs[st[i]];
        }
        message_vision(CYN "等了半天，只聽「喀嚓」一聲，捕獸夾自動"
                       "合攏了，啥也沒抓到。\n" HIC "$N" HIC "呆了"
                       "半天，搖了搖頭，將捕獸夾收回。\n" NOR, me);
        back_owner(me);
}