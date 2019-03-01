// auction.c

#include <ansi.h>

#ifndef AUCTION_D
#define AUCTION_D       "/adm/daemons/auctiond"
#endif

inherit F_CLEAN_UP;

int help(object me);
int to_money(string str);

int main(object me, string arg)
{
        object ob;
        string name, str;
        int money;

        if (! arg) return help(me);

        if( query("no_bid", environment(me)) )
                return notify_fail("這裡禁止參與拍賣，省省吧！\n");

        if (me->is_ghost() || domain_file(base_name(environment(me))) == "death")
                return notify_fail("都做鬼了，還想參與拍賣？省省吧！\n");

        if (arg == "cancel")
        {
                AUCTION_D->cancel_auction(me);
                return 1;
        }

        if (arg == "check")
        {
                if (stringp(str = AUCTION_D->check_auction_info()))
                {
                        write(str);
                        return 1;
                }
                return notify_fail("目前沒有任何東西正在拍賣。\n");
        }

        if (sscanf(arg, "accept %s", name) == 1)
        {
                AUCTION_D->decide_auction(me, name);
                return 1;
        }

        if (sscanf(arg, "%s for %s", name, str) == 2)
        {
                if (! objectp(ob = present(name, me)))
                        return notify_fail("你身上沒有這個東西。\n");

                if (! intp(money = to_money(str)) || ! money
                        || money < 0 || money > 100000000)
                        return notify_fail("輸入價格錯誤。\n");

                AUCTION_D->add_auction(me, ob, money);
                return 1;
        }

        if (sscanf(arg, "%s to %s", str, name) == 2)
        {
                if (! intp(money = to_money(str)) || ! money
                        || money < 0 || money > 100000000)
                        return notify_fail("輸入價格錯誤。\n");

                if (! me->can_afford(money)
                 && query("balance", me)<money )
                        return notify_fail("你身上和你的銀行都沒有那麼多錢。\n");

                AUCTION_D->join_auction(me, name, money);
                return 1;
        }

        return help(me);
}

int to_money(string str)
{
        int money, gold, silver, coin;
        string type;

        if (sscanf(str, "%d gold %d silver %d coin",
                   gold, silver, coin) == 3)
                money = gold * 10000 + silver * 100 + coin;

        else if (sscanf(str, "%d gold %d silver",
                        gold, silver) == 2)
                money = gold * 10000 + silver * 100;

        else if (sscanf(str, "%d silver %d coin",
                        silver, coin) == 2)
                money = silver * 100 + coin;
        else
        {
                if (sscanf(str, "%d %s", money, type) != 2)
                        return 0;

                switch (type)
                {
                case "gold":
                        money *= 10000;
                        break;

                case "silver":
                        money *= 100;
                        break;

                case "coin":
                        break;

                default: money = 0;
                }
        }
        return money;
}

int help(object me)
{
        write(@HELP
指令格式 : auction <物品> for <數量> <錢的種類>
           拍賣出一件物品。

           auction <數量> <錢的種類> to <玩家>
           參與叫價。

           auction accept <玩家>
           決定把自己拍賣中的物品拍賣給某人。

           auction check
           察看目前所有正在拍賣的物品。

           auction cancel
           取消自己物品的拍賣。
HELP
    );
        return 1;
}
