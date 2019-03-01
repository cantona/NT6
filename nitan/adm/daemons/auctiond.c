// auctiond.c
// 拍賣系統
// Written by jjgod for hell. 01/10/01.

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_DBASE;

int clean_up() { return 1; }

#define auction_info    my["auction_info"]
#define lot_percent     1 / 20

public  void   add_auction(object me, object ob, int money);
public  void   cancel_auction(object me);
public  void   decide_auction(object me, string player);
public  string check_auction_info();
private void   message_auction(string msg);
private string check_auction(object ob);

void create()
{
        mapping my;

        seteuid(getuid());

        set("channel_id", "拍賣師[Auctioneer]");
        CHANNEL_D->do_channel(this_object(), "sys", "拍賣精靈已經啟動。");

        my = query_entire_dbase();
        auction_info = ([ ]);
        set_heart_beat(1);
}

void heart_beat()
{
        mapping my;
        string *id;
        int i, money;
        object me;
        object ob;
        object obj;

        my = query_entire_dbase();

        if (! mapp(auction_info) || ! sizeof(auction_info))
                return;

        id = keys(auction_info);

        for (i = 0; i < sizeof(id); i++)
        {
                if (! objectp(me = find_player(id[i])))
                {
                        map_delete(auction_info, id[i]);
                        continue;
                }
                if (! objectp(obj = auction_info[id[i]]["goods"]) ||
                    ! environment(obj) || environment(obj) != me)
                {
                        map_delete(auction_info, id[i]);
                        message_auction(sprintf("由于%s(%s)的拍賣品突然失蹤，此次拍賣被取消。", me->name(), id[i]));
                        continue;
                }
                if (stringp(auction_info[id[i]]["now"]) &&
                    ! objectp(ob = find_player(auction_info[id[i]]["now"])))
                {
                        map_delete(auction_info[id[i]], "now");
                        continue;
                }

                if (time() - auction_info[id[i]]["time"] >= 30)
                {
                        auction_info[id[i]]["state"] += 1;
                        auction_info[id[i]]["time"] = time();
                        message_auction(sprintf("%s(%s)的%s，%s第%s次。",
                                                me->name(), id[i],
                                                filter_color(obj->short()),
                                                MONEY_D->money_str(auction_info[id[i]]["value"]),
                                                chinese_number(auction_info[id[i]]["state"])));
                        if (auction_info[id[i]]["state"] >= 3)
                        {
                                if (! stringp(auction_info[id[i]]["now"]) ||
                                    ! objectp(ob = find_player(auction_info[id[i]]["now"])))
                                {
                                        message_auction(sprintf("%s(%s)的%s無人競價，取消拍賣。",
                                                                me->name(), id[i],
                                                                filter_color(obj->short())));
                                        map_delete(auction_info, id[i]);
                                        continue;
                                }
                                else
                                {
                                        money = auction_info[id[i]]["value"];
                                        message_auction(sprintf("%s(%s)的%s與%s成交了。",
                                                                me->name(), id[i],
                                                                filter_color(obj->short()),
                                                                ob->name()));

                                        switch (MONEY_D->player_pay(ob, money))
                                        {
                                        case 0:
                                        case 2:
                                                if( query("balance", ob) < money )
                                                {
                                                        tell_object(me, "但是" + ob->name() + "付不起錢"
                                                                        "，只好作罷。\n");
                                                        tell_object(ob, "但是你付不起錢，只好作罷。\n");
                                                        map_delete(auction_info, id[i]);
                                                        continue;
                                                } else
                                                {
                                                        switch (MONEY_D->player_pay(me, money * lot_percent))
                                                        {
                                                        case 0:
                                                        case 2:
                                                                tell_object(ob, "但是" + me->name() + "付不起傭金"
                                                                                "，只好作罷。\n");
                                                                tell_object(me, "但是你付不起傭金，只好作罷。\n");
                                                                map_delete(auction_info, id[i]);
                                                                continue;
                                                        default:
                                                                addn("balance", -money, ob);
                                                                obj = auction_info[id[i]]["goods"];
                                                                tell_object(ob, "你收到了" + me->name() + "送來的" +
                                                                                obj->short() + "。\n");
                                                                tell_object(me, "你把" + obj->short() + "交人帶給"
                                                                                "了" + ob->name() + "。\n");
                                                                tell_object(me, "你的拍賣所得已經存入你的銀行帳戶。\n");
                                                                addn("balance", money, me);
                                                                map_delete(auction_info, id[i]);
                                                                obj->move(ob);
                                                                continue;
                                                        }
                                                }
                                        default:
                                                switch (MONEY_D->player_pay(me, money * lot_percent))
                                                {
                                                case 0:
                                                case 2:
                                                        tell_object(ob, "但是" + me->name() + "付不起傭金"
                                                                        "，只好作罷。\n");
                                                        tell_object(me, "但是你付不起傭金，只好作罷。\n");
                                                        map_delete(auction_info, id[i]);
                                                        continue;
                                                default:
                                                        // 交易完成
                                                        obj = auction_info[id[i]]["goods"];
                                                        tell_object(ob, "你收到了" + me->name() + "送來的" +
                                                                        obj->short() + "。\n");
                                                        tell_object(me, "你把" + obj->short() + "交人帶給"
                                                                        "了" + ob->name() + "。\n");
                                                        MONEY_D->pay_player(me, money);
                                                        map_delete(auction_info, id[i]);
                                                        obj->move(ob);
                                                        continue;
                                                }
                                        }
                                }
                        }
                }
        }
}

// 添加一個拍賣品
public void add_auction(object me, object ob, int money)
{
        mapping my;
        string id;
        string msg;

        my = query_entire_dbase();
        id=query("id", me);

        if (mapp(auction_info[id]))
        {
                tell_object(me, "你正在拍賣別的東西，不能添加新的拍賣品"
                                "。\n");
                return;
        }
        if (stringp(msg = check_auction(ob)))
        {
                tell_object(me, msg);
                return;
        }
        if (! me->can_afford(money * lot_percent))
        {
                tell_object(me, "你付不起傭金呀。\n");
                return;
        }

        auction_info[id] = ([ "goods" : ob,
                              "time"  : time(),
                              "value" : money,
                              "lot"   : money * lot_percent,
                              "state" : 1, ]);
        tell_object(me, "你開始拍賣" + ob->short() + NOR "，目前" +
                        (strlen(msg = MONEY_D->money_str(money * lot_percent)) ?
                        "你需要付出" + msg : "不需要付出") + "傭金。\n");
        message_auction(sprintf("%s(%s)開價%s拍賣%s。", me->name(),
                                id, filter_color(ob->short()),
                                MONEY_D->money_str(money),));
        return;
}

// 檢測拍賣物品
private string check_auction(object ob)
{
        string msg;

        if( !query("value", ob) && !query("base_value", ob) )
                return "這玩意兒可不值錢哪。\n";

        if( query("no_sell", ob) || query("no_drop", ob) || query("maze_item", ob) )
        {
                if( stringp(msg=query("no_sell", ob)) )
                        return msg;
                return "這個東西可不能賣了。\n";
        }

        if (ob->is_character())
                return "這你也拿來拍賣？\n";

        if( query("money_id", ob) )
                return "你沒用過錢啊？\n";

        if( query("food_supply", ob) )
                return "吃的喝的等賣出去都餿了。\n";
}

// 取消拍賣物品
public void cancel_auction(object me)
{
        mapping my;
        string id;
        string name;
        object ob;

        id=query("id", me);
        my = query_entire_dbase();

        if (! mapp(auction_info[id]))
        {
                tell_object(me, "你沒有在拍賣任何東西。\n");
                return;
        }

        if (objectp(ob = auction_info[id]["goods"]))
                name = filter_color(ob->short());
        else name = "拍賣品";

        tell_object(me, "你取消了拍賣。\n");
        message_auction(sprintf("%s(%s)取消了拍賣%s的%s。", me->name(), id,
                                gender_pronoun(query("gender", me)),name,));
        map_delete(auction_info, id);
        return;
}

// 決定拍賣物品給某人
public void decide_auction(object me, string player)
{
        mapping my;
        string id;
        string name;
        object ob, who;
        int money;

        id=query("id", me);
        my = query_entire_dbase();

        if (! mapp(auction_info[id]))
        {
                tell_object(me, "你沒有在拍賣任何東西。\n");
                return;
        }

        if (player == id )
        {
                tell_object(me, "你把自己的物品拍賣給自己？\n");
                return;
        }

        if (! objectp(who = find_player(player)))
        {
                tell_object(me, "此人已經離開遊戲。\n");
                return;
        }

        if (! stringp(auction_info[id]["now"]) ||
            player != auction_info[id]["now"])
        {
                tell_object(me, "此人並沒有參與競標或已經退出競標。\n");
                return;
        }

        money = auction_info[id]["value"];

        if (! objectp(ob = auction_info[id]["goods"]) ||
            ! environment(ob) || environment(ob) != me)
        {
                map_delete(auction_info, id);
                message_auction(sprintf("由于%s(%s)的拍賣品突然失蹤，此次拍賣被取消。", me->name(), id));
                return;
        }

        name = filter_color(ob->short());
        if (! name) name = "拍賣品";

        tell_object(me, "你決定把" + name + "拍賣給" + query("name", who) + "(" + player + ")。\n");

        message_auction(sprintf("%s(%s)決定將%s的%s拍賣給%s(%s)。", me->name(), id,
                                gender_pronoun(query("gender", me)),name,query("name", who),player,));

        switch (MONEY_D->player_pay(who, money))
        {
        case 0:
        case 2:
                if( query("balance", who)<money )
                {
                        tell_object(me, "但是" + who->name() + "付不起錢"
                                        "，只好作罷。\n");
                        tell_object(who, "但是你付不起錢，只好作罷。\n");
                        map_delete(auction_info, id);
                        return;
                } else
                {
                        switch (MONEY_D->player_pay(me, money * lot_percent))
                        {
                        case 0:
                        case 2:
                                tell_object(who, "但是" + me->name() + "付不起傭金"
                                                 "，只好作罷。\n");
                                tell_object(me, "但是你付不起傭金，只好作罷。\n");
                                map_delete(auction_info, id);
                                return;
                        default:
                                addn("balance", -money, who);
                                tell_object(who, "你收到了" + me->name() + "送來的" +
                                                 ob->short() + "。\n");
                                tell_object(me, "你把" + ob->short() + "交人帶給"
                                                "了" + who->name() + "。\n");
                                tell_object(me, "你的拍賣所得已經存入你的銀行帳戶。\n");
                                addn("balance", money, me);
                                ob->move(who);
                                map_delete(auction_info, id);
                                return;
                        }
                }
        default:
                switch (MONEY_D->player_pay(me, money * lot_percent))
                {
                case 0:
                case 2:
                        tell_object(who, "但是" + me->name() + "付不起傭金"
                                         "，只好作罷。\n");
                        tell_object(me, "但是你付不起傭金，只好作罷。\n");
                        map_delete(auction_info, id);
                        return;
                default:
                        // 交易完成
                        tell_object(who, "你收到了" + me->name() + "送來的" +
                                         ob->short() + "。\n");
                        tell_object(me, "你把" + ob->short() + "交人帶給"
                                        "了" + who->name() + "。\n");
                        MONEY_D->pay_player(me, money);
                        ob->move(who);
                        map_delete(auction_info, id);
                        return;
                }
        }
}

// 查看拍賣物品
public string check_auction_info()
{
        mapping my;
        string msg, name;
        string *id;
        object ob;
        int i;

        my = query_entire_dbase();

        if (! mapp(auction_info) || ! sizeof(auction_info))
                msg = "目前沒有任何正在拍賣的物品。\n";

        else
        {
                msg = "目前正在拍賣的物品有以下這些：\n";
                msg += HIC "≡" HIY "─玩家──────────物品─────────"
                       "───競價者───────價格──────" HIC "≡\n" NOR;

                id = keys(auction_info);
                for (i = 0; i < sizeof(id); i++)
                {
                        if (! find_player(id[i]))
                        {
                                map_delete(auction_info, id[i]);
                                continue;
                        }
                        if (! objectp(ob = auction_info[id[i]]["goods"]))
                        {
                                map_delete(auction_info, id[i]);
                                continue;
                        }

                        if (! stringp(auction_info[id[i]]["now"]) ||
                            ! objectp(find_player(auction_info[id[i]]["now"])))
                                name = "無";
                        else name = find_player(auction_info[id[i]]["now"])->name() +
                                    "(" + query("id", find_player(auction_info[id[i]]["now"])) +
                                    ")";

                        msg += sprintf(HIC "  %-20s %-30s %-20s %-20s\n" NOR,
                                       find_player(id[i])->name() + "(" +
                                       query("id", find_player(id[i])) + ")",
                                       filter_color(ob->short()),
                                       name,
                                       MONEY_D->money_str(auction_info[id[i]]["value"]));
                }
                msg += HIC "≡" HIY "──────────────────────────"
                       "───────────────────" HIC "≡\n" NOR;
                msg += sprintf("目前共有%s件拍賣品。\n", chinese_number(sizeof(auction_info)));
                if (! sizeof(auction_info)) msg = "目前沒有任何正在拍賣的物品。\n";
        }
        return msg;
}

// 參與競價
public void join_auction(object me, string name, int money)
{
        mapping my;
        object ob;
        object obj;

        my = query_entire_dbase();

        if (! mapp(auction_info[name]))
        {
                tell_object(me, "這個人沒有在拍賣什麼東西。\n");
                return;
        }
        if (! objectp(ob = find_player(name)))
        {
                tell_object(me, "這個人已經不在線了耶。\n");
                map_delete(auction_info, name);
                return;
        }
        if (! objectp(obj = auction_info[name]["goods"]))
        {
                tell_object(me, "這個人現在已經沒有這個東西了耶。\n");
                map_delete(auction_info, name);
                return;
        }
        if (money <= auction_info[name]["value"])
        {
                tell_object(me, "這個價人家恐怕不會要。\n");
                return;
        }
        if (stringp(auction_info[name]["now"]) &&
            auction_info[name]["now"] == query("id", me) )
        {
                tell_object(me, "好像上次出價的就是你吧。\n");
                return;
        }

        message_auction(sprintf("%s(%s)購買%s(%s)的%s，%s第一次。",
                                me->name(),query("id", me),ob->name(),
                                name, filter_color(obj->short()),
                                MONEY_D->money_str(money)));
        auction_info[name]["now"]=query("id", me);
        auction_info[name]["value"] = money;
        auction_info[name]["time"] = time();
        auction_info[name]["lot"] = money * lot_percent;

        return;
}

// 發送拍賣信息
private void message_auction(string msg)
{
        CHANNEL_D->do_channel(this_object(), "auc", msg);
}

string query_name()
{
        return "拍賣系統(AUCTION_D)";
}
