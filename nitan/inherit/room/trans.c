// trans.c
// by doing

#pragma save_binary

#include <room.h>
#include <ansi.h>

inherit ROOM;

void init_connections();

// 交通要點，所有交通信息保存在 MAP_D 中，本地連接情況保存在
// F_DBASE 中的 trans 變量中，前為所去地點，後為價格。

// 提示給顧客的信息
string trans_prompt()
{
        string msg;
        mapping trans;
        string to;
        mixed pos;

        if (! mapp(trans = query("trans")) || sizeof(trans) < 1)
                return "本店正在維修中，暫時不提供交通服務。\n";

        msg = "本店現在開通了去以下地方的通路：\n"
              "-----------------------------------\n";
        foreach (to in keys(trans))
        {
                if (! mapp(pos = MAP_D->query_trans_info(to)))
                        continue;

                msg += sprintf("%-16s %s\n",
                               pos["name"] + "(" + to + ")",
                               MONEY_D->price_str(trans[to]));
        }
        msg += "-----------------------------------\n"
               "即來即走(goto)，無需等待。\n本店價格優惠，童叟無欺。\n";

        return msg;
}

void setup()
{
        ::setup();
        init_connections();
}

// 初始化連接
void init_connections()
{
        mapping trans;
        mixed   conn;
        mixed   item;
        mapping pos;
        string  here;

        pos = MAP_D->query_trans_info();
        foreach (item in keys(pos))
        {
                if (stringp(pos[item]["room"]) &&
                    find_object(pos[item]["room"]) == this_object())
                {
                        // 確定了自己的位置
                        here = item;
                        break;
                }
        }

        if (here && arrayp(conn = MAP_D->query_connect_info()))
        {
                trans = ([ ]);
                foreach (item in conn)
                        if (item[0] == here)
                                trans[item[1]] = item[2];
                        else
                        if (item[1] == here)
                                trans[item[0]] = item[2];
                if (sizeof(trans))
                        set("trans", trans);
        }
        set("item_desc/paizi", trans_prompt());
}

void init()
{
        add_action("do_goto", "goto");
}

int do_goto(string arg)
{
        mixed  pos;
        object me;
        object cart;
        object *obs;
        int pay;

        if (! arg)
                return notify_fail("你要去哪裡？\n");

        if (undefinedp(pay = query("trans/" + arg)))
                return notify_fail("看清楚牌子(paizi)，上面哪裡有這個地方？\n");

        me = this_player();
        if (me->is_busy())
                return notify_fail("什麼都等你忙完了再說吧。\n");

        if (me->query_condition("killer"))
                return notify_fail("你有命案在身呢，你想肆無忌憚的在官道上溜達？！\n");

        pos = MAP_D->query_trans_info(arg);
        if (! mapp(pos) || ! stringp(pos["name"]))
        {
                write("馬夫大呼道：“BUG！BUG！”\n");
                return 1;
        }

        if (! stringp(pos["room"]))
        {
                write("馬夫大苦笑道：“那個地方去不了哦。”\n");
                return 1;
        }

        if (wiz_level(me) > 0)
        {
                write("馬夫笑道：“原來是巫師啊，你不會飛麼？既然非要走路，那就不收錢了。”\n");
                pay = 0;
        } else
        if( query("family/family_name", me) == "段氏皇族" )
        {
                pay = 0;
                write("馬夫道：“呦，是您啊，您就走吧，我怎好意思收您的錢。”\n");
        } else
        if( query("age", me) <= 14 )
        {
                pay = 0;
                write("馬夫訝道：“小小年紀就出來了？算了，我就不收你的錢了。”\n");
        } else
        if (me->query_skill("higgling", 1) >= 30)
        {
                pay = pay * 100 / (me->query_skill("higgling", 1) + 100);
                switch (random(5))
                {
                case 0:
                        write("你道：看在我常年照顧你生意份上，還不給點折扣？\n");
                        break;

                case 1:
                        write("你道：你們老板可是我的熟人啊。\n");
                        break;

                case 2:
                        write("你道：這位兄弟好，最近生意好吧，給點折扣如何？\n");
                        break;

                case 3:
                        write("你道：太貴了，便宜點，便宜點我就走了。\n");
                        break;

                case 4:
                        write("你道：我這是急事，您就行個好，便宜點吧。\n");
                        break;
                }

                pay /= 10;
                pay *= 10;
                if (pay < 10) pay = 10;
                write("馬夫無奈道：“好吧，好吧，那就" + MONEY_D->price_str(pay) +
                      "算了。”\n");
        }

        if (pay > 0)
        {
                if (MONEY_D->player_pay(me, pay) != 1)
                        return 0;
                message_vision("$N付了帳，對馬夫說了兩句什麼。\n", me);
        }

        message_vision("馬夫一聲招呼，開過來一輛大車，$N"
                       "上了車就出發了。\n", me);
        cart = new("/clone/misc/trans_cart");
        obs = filter_array(all_inventory(),
                           (: $1 == $(me) || $1->query_leader() == $(me) &&
                                          ! playerp($1) &&
                                          ! $1->is_killing(query("id", $(me))) :));
        obs->move(cart);
        me->start_call_out((: call_other, __FILE__, "arrival", me, cart, pos :), 2);
        return 1;
}

void arrival(object me, object cart, mapping pos)
{
        object *obs;

        if (! objectp(me) || ! objectp(cart))
                return;

        if (environment(me) != cart)
                return;

        obs = filter_array(all_inventory(cart),
                           (: $1 == $(me) || $1->query_leader() == $(me) &&
                                          ! playerp($1) &&
                                          ! $1->is_killing(query("id", $(me))) :));
        tell_object(me, "你到了" + pos["name"] + "，下了車。\n");
        obs->move(pos["room"]);
        message("vision", "吱呀吱呀一輛大車趕了過來，隨即就見" +
                          me->name() + "跳了下來。\n",
                environment(me), me);

        if (sizeof(obs = all_inventory(cart)) > 0)
        {
                message("vision", "只聽稀裡嘩啦一陣響，從車上扔下一堆東西來。\n",
                        environment(me), me);
                obs->move(pos["room"]);
        }

        if (objectp(cart))
                destruct(cart);
}

void reset()
{
        ::reset();
        init_connections();
}
