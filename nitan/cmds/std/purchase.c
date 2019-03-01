// purchase.c

#include <ansi.h>
#include <config.h>

inherit F_CLEAN_UP;

int do_purchase(object me, string from, string item, int count, string money);

mapping items = ([
        "sword"    : "/clone/weapon/changjian",
        "blade"    : "/clone/weapon/gangdao",
        "staff"    : "/clone/weapon/gangzhang",
        "club"     : "/clone/weapon/tiegun",
        "hammer"   : "/clone/weapon/hammer",
        "dagger"   : "/clone/weapon/dagger",
        "pin"      : "/clone/misc/pin",
        "whip"     : "/clone/weapon/changbian",
        "throwing" : "/clone/weapon/tielianzi",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string item;
        object ob;
        string from;
        int    count;
        string money;
        int    pay;

        if (! arg)
                return notify_fail("你打算購買什麼？\n");

        if (sscanf(arg, "%s from %s with %d %s", item, from, count, money) == 4)
                return do_purchase(me, from, item, count, money);

        if (sscanf(arg, "%*s from %*s") == 2)
                return notify_fail("你打算花多少錢？\n");

        if (arg == "cancel")
        {
                string target;
                object target_ob;

                if( !stringp(target=query_temp("pending/purchase", me)) )
                        return notify_fail("你現在並沒有打算和別人購買什麼啊！\n");

                if (objectp(target_ob = present(target, environment(me))))
                        tell_object(target_ob,
                                    YEL + me->name(1) + "打消向你購買東西的念頭。\n" NOR);
                tell_object(me, YEL "你打消了交易的念頭。\n" NOR);
                delete_temp("pending/purchase", me);
                delete_temp("pending/info", me);
                return 1;
        }

        if( query("doing", me) != "scheme" )
                return notify_fail("只有在計劃中才能使用這條命令購買道具。\n");

        if (undefinedp(item = items[arg]))
                return notify_fail("現在沒法購買這種道具。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙，沒空購買道具。\n");

        pay = 10000;
        if( query("family/family_name", me) == "段氏皇族" )
                pay = 2000;
        else
                pay = pay * 100 / (me->query_skill("higgling", 1) + 100);
        if (MONEY_D->player_pay(me, 10000 + item->value()) != 1)
                return notify_fail("你身上的錢不夠，沒法托人購買道具。\n");

        ob = new(item);
        message_vision("$N找了一個打雜的，讓他幫助你購買" + item->name() + "。\n", me);
        ob->move(me, 1);
        write("你成功的買到了一"+query("unit", ob)+item->name()+"。\n");
        me->start_busy(20);
        return 1;
}

int do_purchase(object me, string from, string item, int count, string money)
{
        int     amount;
        object  from_ob;
        object  item_ob;
        object  money_ob;
        object* total_obs;
        int     total;
        int     combined;

        if (sscanf(item, "%d %s", amount, item) != 2)
                amount = 1;

        from_ob = present(from, environment(me));
        if (! objectp(from_ob))
                return notify_fail("這裡沒有這個人。\n");

        if (from_ob == me)
                return notify_fail("左手和右手做生意？好主意，不過這幫不了你練左右互搏。\n");

        if (! playerp(from_ob))
                return notify_fail("人家似乎懶得理你。\n");

        if (! interactive(from_ob))
                return notify_fail("人家現在沒法和你答話。\n");

        if( query_temp("pending/purchase", me) == query("id", from_ob) )
                return notify_fail("你現在等別人回話呢。\n");

        item_ob=query_temp("handing", from_ob);
        if (! objectp(item_ob) || (item != "?" && ! item_ob->id(item)))
                return notify_fail("人家並沒有亮出來這樣東西。\n");

        if (item_ob->is_item_make())
                return notify_fail("這可是別人煉制的物品，不太妥吧。\n");

        if( query("money_id", item_ob) )
                return notify_fail("錢你也想買？\n");

        if( query("no_drop", item_ob) )
                return notify_fail("這個物品不能用來交易。\n");

        if (amount < 1)
                return notify_fail("你想買多少"+query("units", item_ob)+
                                   item_ob->name() + "？\n");

        if (! undefinedp(total = item_ob->query_amount()))
                combined = 1;
        else
        {
                string iname;

                iname = base_name(item_ob);
                total_obs = filter_array(all_inventory(from_ob),
                                         (: base_name($1) == $(iname) :));
                total = sizeof(total_obs);
                combined = 0;
        }

        if (amount > total)
                return notify_fail("人家身上沒有那麼多" + item_ob->name() + "啊！\n");

        if (count < 1)
                return notify_fail("你要出多少錢？\n");

        money_ob = present(money, me);
        if (! objectp(money_ob))
                return notify_fail("你身上並沒有這種錢啊。\n");

        if( !query("money_id", money_ob) )
                return notify_fail("你想自己印鈔票？\n");

        if (count > money_ob->query_amount())
                return notify_fail("你身上沒那麼多" + money_ob->name() + "。\n");

        message_vision("$N想用" + chinese_number(count) +
                    query("base_unit", money_ob)+money_ob->name()+
                    "向$n購買" + chinese_number(amount) +
                    (combined?query("base_unit", item_ob):query("unit", item_ob))+
                    item_ob->name() + "。\n" NOR, me, from_ob);
        tell_object(from_ob, YEL "你同意(right)還是不同意(refuse)" + me->name(1) +
                             YEL"("+query("id", me)+YEL")的要求？\n"NOR);
        set_temp("pending/answer/"+query("id", me)+"/right",
                          bind((: call_other, __FILE__, "do_right", from_ob, me :), from_ob), from_ob);
        set_temp("pending/answer/"+query("id", me)+"/refuse",
                          bind((: call_other, __FILE__, "do_refuse", from_ob, me :), from_ob), from_ob);
        set_temp("pending/purchase",query("id",  from_ob), me);
        set_temp("pending/purchase_info",
                     ([ "item"   : base_name(item_ob),
                        "amount" : amount,
                        "money"  : money,
                        "count"  : count ]), me);
        tell_object(me, YEL + "你向" + from_ob->name(1) + "提出了要求。\n" NOR);
        return 1;
}

int do_refuse(object me, object ob)
{
        if (! objectp(ob))
                return notify_fail("這裡沒有人等你回話了。\n");

        if( query_temp("pending/purchase", ob) != query("id", me) )
                return notify_fail("人家已經不打算和你做買賣了。\n");

        delete_temp("pending/purchase", ob);
        tell_object(ob, me->name(1) + "對你道：“你想買，我倒不想賣，算了吧。”\n");
        tell_object(me, "你拒絕了" + ob->name(1) + "的要求。\n");
        return 1;
}

int do_right(object me, object ob)
{
        string  item;
        object  item_ob;
        int     amount;
        string  money;
        object  money_ob;
        int     count;
        object* total_obs;
        int     total;
        int     combined;
        object  temp_ob;

        if (! objectp(ob))
                return notify_fail("這裡沒有人等你回話了。\n");

        if( query_temp("pending/purchase", ob) != query("id", me) )
                return notify_fail("人家已經不打算和你做買賣了。\n");

        item=query_temp("pending/purchase_info/item", ob);
        amount=query_temp("pending/purchase_info/amount", ob);
        money=query_temp("pending/purchase_info/money", ob);
        count=query_temp("pending/purchase_info/count", ob);
        delete_temp("pending/purchase_info", ob);
        delete_temp("pending/purchase", ob);

        if (! stringp(item))
        {
                tell_object(me, "你現在沒有人家感興趣的東西了。\n");
                tell_object(ob, "人家現在已經沒有你感興趣的東西了。\n");
                return 1;
        }

        foreach (item_ob in all_inventory(me))
                if (base_name(item_ob) == item)
                        break;

        if (base_name(item_ob) != item)
        {
                tell_object(me, "你現在沒有人家感興趣的東西了。\n");
                tell_object(ob, "人家現在已經沒有你感興趣的東西了。\n");
                return 1;
        }

        if( query("money_id", item_ob) )
                return notify_fail("錢你也想賣？\n");

        if (amount < 1)
        {
                tell_object(me, "你不知道人家究竟買多少" +
                                item_ob->name() + "。\n");
                tell_object(ob, "人家不清楚你究竟要買多少" +
                                item_ob->name() + "。\n");
                return 1;
        }

        if (! undefinedp(total = item_ob->query_amount()))
                combined = 1;
        else
        {
                string iname;

                iname = base_name(item_ob);
                total_obs = filter_array(all_inventory(me),
                                         (: base_name($1) == $(iname) :));
                total = sizeof(total_obs);
                combined = 0;
        }

        if (amount > total)
        {
                tell_object(me, "你現在身上沒有那麼多" + item_ob->name() + "了。\n");
                tell_object(ob, "人家現在身上沒有那麼多" + item_ob->name() + "了。\n");
                return 1;
        }

        if (count < 1)
        {
                tell_object(me, "你不知道人家想要出多少錢。\n");
                tell_object(ob, "人家不知道你想要出多少錢。\n");
                return 1;
        }

        if (! stringp(money) || ! objectp(money_ob = present(money, ob)) ||
            !query("money_id", money_ob) || count>money_ob->query_amount() )
        {
                tell_object(me, "人家現在身上沒有錢了。\n");
                tell_object(ob, "人家同意了，可是你現在身上沒有錢了。\n");
                return 1;
        }

        if( query("base_weight", money_ob)*count+
            me->query_encumbrance() > me->query_max_encumbrance())
        {
                tell_object(me, "你現在接不下這麼多" + money_ob->name() + "。\n");
                tell_object(ob, "人家現在接不下你這麼多" + money_ob->name() + "。\n");
                return 1;
        }

        if (! combined && amount + sizeof(all_inventory(ob)) > MAX_ITEM_CARRIED ||
            (combined && sizeof(all_inventory(ob)) >= MAX_ITEM_CARRIED &&
             ! item_ob->can_combine_to(ob)))
        {
                tell_object(me, "人家你現在接不下這麼多" + item_ob->name() + "。\n");
                tell_object(ob, "你身上的東西太多了，現在接不下那麼多" + money_ob->name() + "。\n");
                return 1;
        }

        tell_object(me, "你同意了" + ob->name(1) + "的要求。\n");
        tell_object(ob, me->name(1) + "同意了你的要求。\n");
        message_vision("$N接過了$n的" + money_ob->name() + "，把" +
                       item_ob->name() + "遞給了$n。\n", me, ob);

        // 對方支付錢
        if (count == money_ob->query_amount())
                money_ob->move(me, 1);
        else
        {
                temp_ob = new(base_name(money_ob));
                temp_ob->set_amount(count);
                money_ob->add_amount(-count);
                temp_ob->move(me, 1);
        }

        // 本方提供物品
        if (combined)
        {
                if (amount == item_ob->query_amount())
                        item_ob->move(ob, 1);
                else
                {
                        temp_ob = new(base_name(item_ob));
                        temp_ob->set_amount(amount);
                        item_ob->add_amount(-amount);
                        temp_ob->move(ob, 1);
                }
        } else
        {
                while (amount--)
                        total_obs[amount]->move(ob, 1);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : purchase [數量] <名字> [from <玩家> with <數量> <貨幣>]
           purchase cancel

在你執行計劃的過程中，你可以通過這條指令來購買你需要的各種武
器道具，來滿足你計劃的需要。

另外，你也可以使用這個命令，使用貨幣求購另外一個玩家身上的物
品。這個物品必須是對方亮出來的，即拿(hand)在手裡的。如果你輸
入的名字是 ？ 則表示購買對方手裡的東西，為了保險起見，輸入英
文代號更好一些。如果你提出要求以後後悔了，可以輸入 cancel 參
數打消這個念頭。

see also : scheme

HELP );
        return 1;
}
