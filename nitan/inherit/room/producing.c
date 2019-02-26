// inherit: producing.c

// 繼承房屋必須填寫的數據格式：
// product -+ mineral1 +-- name : 某產品
//          |          +-- rate : 生產率
//          |          +-- max  : 最大
//          |          +-- cost : 生產時消耗的資源種類
//          |
//          + mineral2 +-- ...
//          ..

#include <ansi.h>

inherit ROOM;

void start_heart_beat()
{
        // 每天(MUD單位)心跳一次
        set_heart_beat(120);
}

void setup()
{
        mapping product;
        string mine;
        int count;

        // 這裏的房間不能戰鬥，而且永不停息運轉
        set("no_fight", 1);
        set("no_clean_up", 1);

        ::setup();

        product = query("product");
        if (! mapp(product))
                return;

        foreach (mine in keys(product))
        {
                // 設置最初的產品
                count = product[mine]["max"] / 10;
                count = count / 2 + random(count);
                set_temp("stored/" + mine, count);
        }

        start_heart_beat();
}

void init()
{
        add_action("do_info", "info");
}

int query_product_amount(string name, int amount)
{
        return query_temp("stored/" + name);
}

// 如果amount < 0則表示消耗資源
void improve_product_amount(string name, int amount)
{
        mapping m;

        if (! mapp(m = query("product/" + name)))
                // 不提供這種資源
                return;

        amount += query_temp("stored/" + name);
        if (amount >= m["max"]) amount = m["max"];
        if (amount < 0) amount = 0;
        set_temp("stored/" + name, amount);
}

void heart_beat()
{
        int count;
        mapping product;
        string mine;
        mapping m;
        int rate;
        string cost;
        int cost_total;
        int eff;

        if (! mapp(product = query("product")))
        {
                set_heart_beat(0);
                return;
        }

        // 生產產品
        foreach (mine in keys(product))
        {
                // 每次心跳消耗一些原料，生產一些產品
                if (! mapp(m = product[mine]))
                {
                        map_delete(product, mine);
                        continue;
                }

                // 計算能夠生產的數量
                if (! intp(rate = m["rate"]) || rate < 1)
                        continue;

                count = rate / 2 + random(rate / 2);
                if (arrayp(m["cost"]))
                {
                        foreach (cost in m["cost"])
                                if (count > (cost_total = query_temp("stored/" + cost)))
                                        count = cost_total;

                        if (count < 1)
                                // 原料不足，無法生產
                                continue;

                        // 消耗原料
                        foreach (cost in m["cost"])
                                addn_temp("stored/" + cost, -count);
                }

                // 生產完畢
                improve_product_amount(mine, count);
        }
}

int do_info(string arg)
{
        mapping product;
        mapping stored;
        string mine;
        mapping m;
        string msg;

        if (arg && arg != "") return 0;

        msg = "當前各種資源的信息：\n";

        if (! mapp(stored = query_temp("stored")) ||
            ! mapp(product = query("product")))
        {
                write("目前沒有任何庫存資源。\n");
                return 1;
        }

        foreach (mine in keys(stored))
        {
                if (! mapp(m = product[mine]))
                        continue;

                msg += sprintf("%-8s  庫存量：" HIY "%-6d" NOR,
                               m["name"], stored[mine]);
                if (m["rate"])
                        msg += sprintf("  生產率：" HIC "%3d" NOR,
                                       m["rate"]);
                msg += "\n";
        }

        write(msg);
        return 1;
}
