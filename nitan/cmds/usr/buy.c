#include <ansi.h>
#include <config.h>
inherit F_CLEAN_UP;

int player_pay(object who, object target, int amount);
void destruct_it(object ob);

int main(object me, string arg)
{
        mapping goods;
        int amount;
        int value, val_factor;
        string ob_file;
        object *obs;
        object ob, env, obj;
        string my_id;
        int i;
        
        if(me->is_busy())
                return notify_fail("什麼事都得等你忙完再說吧！\n");

        if (! arg)
                return notify_fail("指令格式：buy <物品> from <玩家>\n");

        if (! (sscanf(arg, "%s from %s", arg, my_id) == 2) )
                return notify_fail("指令格式：buy <物品> from <玩家>\n");

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                write("你身上的東西太多了，先處理一下再買東西吧。\n");
                return 1;
        }

        // no present or equipped
        env = environment(me);

        if (! (obj = find_player(my_id)) || ! (present(query("id", obj), env))) 
                return notify_fail("這裡沒有這個商人。\n");

        if (obj == me)
                return notify_fail("問自己買東西？吃飽了撐的？\n");

        if( !query("is_vendor", obj) )
                return notify_fail(obj->name(1) + "並不是商人。\n");

        if( !query_temp("on_baitan", obj) )
                return notify_fail(obj->name(1) + "並沒有擺攤。\n");

        if( !(goods=query("vendor_goods", obj)) )
                return notify_fail(obj->name(1) + "並沒有兜售任何貨物。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        ob = present(arg, obj);

        if (! ob || ! objectp(ob))
                return notify_fail(obj->name(1) + "並沒有兜售這樣貨物。\n");

        if (! goods[base_name(ob)])
                return notify_fail(obj->name(1) + "並沒有兜售這樣貨物。\n");

        value = goods[base_name(ob)];

        if (ob->query_amount())
        {
                object old_ob;
                ob = new(base_name(old_ob = ob));
                set_temp("moved_from", old_ob, ob);
                call_out("destruct_it", 0, ob);
        }

        switch (player_pay(me, obj, value))
        {
        case 0:
                write(CYN + obj->name(1) + CYN "冷笑一聲，罵道：窮"
                      "光蛋，一邊呆著去。\n" NOR);
                return 1;
        case 2:
                write(CYN + obj->name(1) + CYN "皺眉道：您還有沒有"
                      "零錢啊？銀票我可找不開。\n" NOR);
                return 1;
        default:
                if (ob->query_amount())
                {
                        message_vision("$N從$n那裡買下了" + ob->short() + "。\n",
                                        me, obj);
                } else
                {
                        message_vision("$N從$n那裡買下了一"+query("unit", ob)+
                                       query("name", ob)+"。\n",
                                       me, obj);
                }
                ob->move(me, 1);

                if( objectp(query_temp("moved_from", ob)) )
                {
                        query_temp("moved_from", ob)->add_amount(-1);
                        delete_temp("moved_from", ob);
                }

        }
        me->start_busy(2);
        return 1;
}

int player_pay(object who, object target, int amount)
{
        object t_ob, g_ob, s_ob, c_ob;
        int tc, gc, sc, cc, left;
        int v;

        seteuid(getuid());

        if (amount >= 100000 && t_ob = present("cash_money", who))
                tc = t_ob->query_amount();
        else
        {
                tc = 0;
                t_ob = 0;
        }

        if (g_ob = present("gold_money", who))
                gc = g_ob->query_amount();
        else
                gc = 0;

        if (s_ob = present("silver_money", who))
                sc = s_ob->query_amount();
        else
                sc = 0;

        if (c_ob = present("coin_money", who))
                cc = c_ob->query_amount();
        else
                cc = 0;
        
        v = cc + sc * 100 + gc * 10000;

        if (amount < 100000 && v < amount)
        {
                if (present("cash_money", who))
                        return 2;
                else
                        return 0;
        }

        v += tc * 100000;

        if (v < amount) 
                return 0;
        else {
                left = v - amount;
                if (tc)
                {
                        tc = left / 100000;
                        left %= 100000;
                }

                gc = left / 10000;
                left = left % 10000;
                sc = left / 100;
                cc = left % 100;

                if (t_ob && ! g_ob && gc)
                {
                        g_ob = new(GOLD_OB);
                        g_ob->move(who, 1);
                }

                if (t_ob)
                        t_ob->set_amount(tc);

                if (g_ob)
                        g_ob->set_amount(gc);
                else
                        sc += (gc * 100);

                if (s_ob)
                         s_ob->set_amount(sc);
                else
                if (sc)
                {
                        s_ob = new(SILVER_OB);
                        s_ob->set_amount(sc);
                        s_ob->move(who, 1);
                }

                if (c_ob)
                        c_ob->set_amount(cc);
                else
                if (cc)
                {
                        c_ob = new(COIN_OB);
                        c_ob->set_amount(cc);
                        c_ob->move(who, 1);
                }

                addn("balance", amount*19/20, target);
                     if (query_ip_number(target) != query_ip_number(who))

                addn("vendor_score", amount/2500, target);
                return 1;
        }
}

void destruct_it(object ob)
{
        if (! ob || environment(ob))
                return;

        destruct(ob);
}


int help (object me)
{
        write(@HELP
指令格式: buy <物品> from <玩家>

向一個玩家商人購買商品。

相關指令：list

HELP);
        return 1;
}
