// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// dealer.c 商人
// 需加入價格變動體系price_ratio

#pragma save_binary

#include <config.h>
#include <command.h>
#include <dbase.h>
#include <name.h>

class goods
{
        mapping data; // 動態物品數據
        string name;
        string id;
        string *ids;
        string type;
        string file;
        string unit;
        //int carry;
        int amount;  // 數量
        int value;   // 價格
        int number;  // 編號
}

nosave int uptime;
nosave int no_trade = 0;
nosave int load_goods = 0;

protected class goods *all_goods = ({});
protected void init_goods();
protected int add_one_good(string file, int price, int amount);
int is_vendor() { return 1; }

/*
void setup()
{
        init_goods();
        ::setup();
        if( !uptime )
                uptime = time();
}

void init()
{
        //add_action("do_sell", ({ "sell" }) );
        add_action("do_buy", ({ "mai", "buy" }) );
        add_action("do_list", "list");
        add_action("do_look", ({"guankan", "kan"}));
}
*/

protected void init_goods()
{
        string *ks, file;
        mixed item;
        int price = 0;
        int amount = -1;
        int i;

        no_trade = 1;
        all_goods = ({});

        item = this_object()->query("vendor_goods");
        if( !arrayp(item) && !mapp(item) || !sizeof(item) )
        {
                no_trade = 0;
                load_goods = 1;
                return;
        }

        ks = mapp(item) ? keys(item) : item;
        for( i=0; i<sizeof(ks);i++ )
        {
                file = ks[i];
                if( mapp(item) ) // string為價格，int為數量
                {
                        if( intp(item[ks[i]]) && item[ks[i]] > 0 )
                                amount = item[ks[i]];
                        else if( stringp(item[ks[i]]) )
                                price = to_int(item[ks[i]]);
                }
                add_one_good(file, price, amount);
        }

        no_trade = 0;
        load_goods = 1;
}

protected int add_one_good(mixed obj, int price, int amount)
{
        string file;
        object ob, obn;
        class goods item;
        string type;
        int i, n;

        if( !stringp(obj) && !objectp(obj) )
                return 0;

        if( stringp(obj) ) file = obj;
        else file = base_name(obj);

        if( objectp(obj) )
                ob = obj;
        else
        {
                if( catch(call_other(file, "???")) 
                ||  !objectp(ob = find_object(file)) ) {
                        log_file("static/dealer", 
                                 sprintf("vendor good file:%s of %s does not exist\n",
                                         file, base_name(this_object())));
                        return 0;
                }
        }

        if( ob->is_weapon() )           type = "武器";
        else if( ob->is_armor() )       type = "防具";
        else if( ob->is_liquid() )      type = "飲具";
        else if( ob->is_food() )        type = "食物";
        else if( ob->is_container() )   type = "容器";
        else if( ob->is_book() )        type = "書籍";
        else                            type = "其它";

        if( objectp(obj) )
        {
                mapping data, temp;
                string id, name;

                id = obj->query("id");
                name = obj->query("name");
                data = obj->query_entire_dbase();
                catch(obn = new(file));
                if( !obn ) return;
                temp = obn->query_entire_dbase();
                destruct(obn);

                n = sizeof(all_goods);
                for( i = 0; i < n; i++ )
                {
                        if( all_goods[i]->file == file &&
                            all_goods[i]->id == id &&
                            all_goods[i]->name == name ) {
                                if( obj->query_amount() || mapping_eqv(data, temp) )
                                {
                                        if( all_goods[i]->amount != -1 )
                                                all_goods[i]->amount += amount;
                                        destruct(obj);
                                        return 1;
                                }

                                if( all_goods[i]->data && mapping_eqv(data, all_goods[i]->data) )
                                {
                                        if( all_goods[i]->amount != -1 )
                                                all_goods[i]->amount += amount;
                                        destruct(obj);
                                        return 1;
                                }
                        }
                }
                item = new(class goods);
                item->name = name;
                item->id = id;
                item->ids = obj->my_id();
                item->type = type;
                item->file = file;
                item->unit = obj->query("base_unit") ?
                             obj->query("base_unit") : obj->query("unit");
                item->amount = amount;
                item->value = price ? price :
                        (obj->query("base_value") ? obj->query("base_value"):
                                                    obj->query("value"));
                item->number = sizeof(all_goods) + 1;
                if( !mapping_eqv(data, temp) )
                        item->data = copy(data);
                all_goods += ({ item });
                destruct(obj);
                return 1;
        }

        item = new(class goods);
        item->name = ob->query("name");
        item->id = ob->query("id");
        item->ids = ob->my_id();
        item->type = type;
        item->file = file;
        item->unit = ob->query("base_unit") ? ob->query("base_unit")
                                            : ob->query("unit");
        item->amount = amount;
        item->value = price ? price :
                        (ob->query("base_value") ? ob->query("base_value"):
                                                   ob->query("value"));
        item->number = sizeof(all_goods) + 1;

        all_goods += ({ item });
        // destruct(ob);
        return 1;
}

string is_vendor_good(object ob)
{
        string name, id, file;
        int i, n;

        n = sizeof(all_goods);
        if ( !n ) return "";

        id = ob->query("id");
        name = ob->query("name");
        file = base_name(ob);

        for( i=0;i<n;i++ )
        {
                if( all_goods[i]->id == id &&
                    all_goods[i]->file == file &&
                    all_goods[i]->name == name ) {
                        if( all_goods[i]->data ||
                            all_goods[i]->amount != -1 )
                                return "";

                        return all_goods[i]->file;
                }
        }

        return "";
}

void add_carried_good()
{
        object *obs;
        int i;
        int amount;

        if( obs = all_inventory() )
        {
                for( i = 0; i < sizeof(obs); i++ )
                {
                        if( obs[i]->query("equipped")
                        ||  obs[i]->query("money_id")
                        ||  obs[i]->is_item_make()
                        ||  obs[i]->is_character() )
                                continue;

                        amount = obs[i]->query_amount() ?
                                 obs[i]->query_amount() : 1;

                        add_one_good(obs[i], 0, amount);
                }
        }
}

varargs int do_list(string arg)
{
        string output, desc;
        class goods item;
        object me;

        me = this_player();

        if( no_trade )
                return notify_fail("現在正在盤庫，請等一下再來。\n");

        if( !wizardp(me) && me->query_condition("killer") )
                return notify_fail(CYN "店鋪不做殺人犯的生意！\n" NOR);

        if( me->is_busy() ) {
                write(BUSY_MESSAGE);
                return 1;
        }

        // 處理同房間有一個以上 dealer 的情況。
        if( arg && !id(arg) && arg != query("name") )
                return 0;

        if( !load_goods ) {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        if( !sizeof(all_goods) ) {
                write(sprintf("目前%s沒有可以賣的東西。\n", query("name")));
                return 1;
        }

        output = this_object()->name() + "目前出售以下物品：\n";
        /*
        output += sprintf("%5s%-30s%-10s%-10s\n","序 號", "    商  品","  單  價","       數  量");
        output += "----------------------------------------------------------------\n";
        */
        foreach( item in all_goods ) {
                if( item->amount < 0 ) desc = "大量供應";
                else if( item->amount == 0 ) desc = "暫時缺貨";
                else if( item->amount < 11 )
                        desc = sprintf("僅剩%2d%2s", item->amount, item->unit);
                else if( item->amount < 31 )
                        desc = sprintf("還剩%2d%2s", item->amount, item->unit);
                else
                        desc = "貨源充足";

                output += sprintf("(%3d)%" + sprintf("%d", (30 + color_len(item->name))) +
                                  "-s：每%s%s" CYN "(現貨%s)\n" NOR,
                                  item->number,
                                  item->name + "(" + item->id + ")",
                                  item->unit,
                                  MONEY_D->price_str(item->value), desc);
        }

        write(output);
        return 1;
}

int do_buy(string arg)
{
        mapping room_obmap;
        string  bunch;
        object *obs;
        object  ob;
        object  room;
        object  me;
        mixed   value;
        int     amount;
        int     val_factor;
        int     i, j, n;
        string  my_id;
        string  start_room;

        if( !arg )
                return notify_fail("你想買什麼？\n");

        if( (me = this_player())->is_busy() ) {
                write("你正在忙着呢！\n");
                return 1;
        }

        if( no_trade )
                return notify_fail("現在正在盤庫，請等一下再來。\n");

        if( query_temp("busy") ) {
                write(CYN + name() + "不耐煩道：“沒看見我這"
                      "兒正忙着麼？”\n" NOR);
                return 1;
        }

        if( sscanf(arg,"%s from %s", arg, my_id) == 2 ) {
                if( !id(my_id) && my_id != query("name") )
                        return 0;
        }

        if( !query("carried_items") ) {
                if( stringp(start_room = query("startroom")) &&
                    (room = find_object(start_room)) != environment() ) {
                        // I am not in start room.
                        message_vision("$N大叫一聲：“不好，我怎麼跑到這兒來了？”\n"
                                       "説罷頭也不回的急急忙忙的溜走了。\n", this_object());
                        if( !objectp(room) ||
                            !mapp(room_obmap = room->query_temp("objects")) ||
                            member_array(this_object(), values(room_obmap)) == -1 ) {
                                destruct(this_object());
                        } else
                                this_object()->move(room);
                        return 1;
                }
        }

        if( sizeof(filter_array(all_inventory(me),
                (: !$1->query("equipped") :))) >= MAX_ITEM_CARRIED ) {
                write("你身上的東西太多了，先處理一下再買東西吧。\n");
                return 1;
        }

        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the items
                amount = 1;

        if( amount < 1 ) {
                write(CYN + name() + "疑惑的問道：“沒見過這種買法，你到底想買幾個單位呢？”\n" NOR);
                return 1;
        }

        if( amount > 5000 ) {
                write(CYN + name() + "忙道：“慢慢來，一次最多買五千個單位。”\n" NOR);
                return 1;
        }

        if( !load_goods ) {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("目前%s沒有可以賣的東西。\n", query("name")));
                return 1;
        }

        val_factor = 10;
        for( i = 0; i < n; i++ ) {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg) {
                        if( !(all_goods[i]->amount) ) {
                                command(sprintf("say 對不起，目前這%s" CYN "缺貨，您過一段時間再來吧",
                                        all_goods[i]->name));
                                return 1;
                        }

                        if( all_goods[i]->amount > 0 ) {
                                val_factor = 12;

                                if( amount > all_goods[i]->amount )
                                        amount = all_goods[i]->amount;
                        }

                        if( !function_exists("query_amount", get_object(all_goods[i]->file)) ) {
                                if( amount > 100 ) {
                                        amount = 100;
                                        write("這類物品限制一次最多買一百個單位。\n");
                                }
                        }

                        break;
                }
        }

        if( i >= n ) {
                write("你想買什麼？\n");
                return 1;
        }

        value = amount*all_goods[i]->value;
        value = value*val_factor/10;

        if( value > 1000000000 || value * val_factor / val_factor != value ) {
                write(CYN + name() + CYN "大驚失色道：這麼大一筆生意？我"
                      "可不好做。\n" NOR);
                return 1;
        }

        if( stringp(bunch = me->query("bunch/bunch_name")) &&
            bunch == (string)this_object()->query("bunch/bunch_name") )
                value = value * 90/100;

        else if( SHOP_D->is_owner(me->query("id")) )
                value = value * 90/100;
        else if( me->query_skill("higgling", 1) > 99 ) {
                if( me->query_skill("higgling", 1) > 399 )
                        value = value * 80/100;
                else if (me->query_skill("higgling", 1) > 199)
                        value = value * 85/100;
                else if (me->query_skill("higgling", 1) > 99)
                        value = value * 90/100;
        }

        if( value < 1 )
                value = 1;


        switch (MONEY_D->player_pay(me, value))
        {
        case 0:
                write(CYN + name() + "冷笑道：“窮光蛋，一邊呆着去！”\n" NOR);
                return 1;
        case 2:
                write(CYN + name() + "皺眉道：“您還有沒有零"
                      "錢啊？銀票我可找不開。”\n" NOR);
                return 1;
        case 3:
                write(CYN + name() + "皺眉道：“您還有沒有零"
                      "錢啊？鑽石我可找不開。”\n" NOR);
                return 1;
        default:
                set_temp("busy", 1);

                if (stringp(bunch = me->query("bunch/bunch_name")) &&
                    bunch == (string)this_object()->query("bunch/bunch_name")) {
                        BUNCH_D->add_bunch_info(bunch, "npc_money", value/5);
                        command("say 既然大家都是同幫兄弟，就給你打點折吧。");
                } else
                if( me->query_skill("higgling", 1) > 99 || SHOP_D->is_owner(me->query("id")) )
                {
                        switch (random(3))
                        {
                        case 0:
                                command("say 既然大家都是做買賣的，就給你打點折吧。");
                                break;
                        case 1:
                                command("say 也罷，既然是大老闆光顧，就便宜點賣給你吧。");
                                break;
                        default:
                                command("say 呵呵。大老闆又來採購麼？那麼就給你打點折吧。");
                                break;
                        }
                }

                if( function_exists("query_amount", get_object(all_goods[i]->file)) )
                {
                        ob = new(all_goods[i]->file);
                        ob->set_amount(amount);
                        ob->move(me, 1);
                } else
                {
                        for( j = 0; j < amount; j++ )
                        {
                                if( !all_goods[i]->data )
                                        ob = new(all_goods[i]->file);
                                else
                                {
                                        ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                        ob->set_name(ob->query("name"), all_goods[i]->ids);
                                }
                                ob->move(me, 1);
                        }
                }

                all_goods[i]->amount -= amount;
                message_vision(sprintf("$N從$n那裏買下了%s%s%s%s。\n",
                        all_goods[i]->amount == 0 ? "最後" : "",
                        chinese_number(amount),
                        all_goods[i]->unit,
                        all_goods[i]->name), me, this_object());
        }

        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

        return 1;
}

void destruct_it(object ob)
{
        if( !ob || environment(ob))
                return;
        destruct(ob);
}

void enough_rest()
{
        delete_temp("busy");
}

int do_look(string arg)
{
        string who;
        object ob, me;
        int i, n;

        if( (me = this_player())->is_busy() )
        {
                write(BUSY_MESSAGE);
                return 1;
        }

        if( !arg || arg == "" )
        {
                write("你想看什麼？\n");
                return 1;
        }

        // 處理同房間有一個以上 dealer 的情況。
        if( sscanf(arg,"%s from %s", arg, who) == 2 )
        {
                if( !id(who) && who != query("name"))
                        return 0;
        }

        if( !load_goods )
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }

        add_carried_good();

        n = sizeof(all_goods);
        if( !n )
        {
                write(sprintf("目前%s沒有可以賣的東西。\n", query("name")));
                return 1;
        }

        for( i = 0; i < n; i++ )
        {
                if( all_goods[i]->amount == 0 )
                        continue;

                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                {
                        if( !all_goods[i]->data )
                        {
                                ob = get_object(all_goods[i]->file);
                                LOOK_CMD->look_item(me, ob);
                                //destruct(ob);
                                return 1;
                        }
                        else
                        {
                                ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                LOOK_CMD->look_item(me, ob);
                                destruct(ob);
                                return 1;
                        }
                }
        }

        if( i >= n )
        {
                write("你想看什麼？\n");
                return 1;
        }
}

int do_value(string arg)
{
        object ob;
        int value;
        mixed ns;

        if( !arg || !(ob = present(arg, this_player())) )
        {
                return notify_fail("你要估什麼的價？\n");
        }

        if( ob->query("money_id") )
        {
                write(CYN + name() + "道：你沒用過錢啊？\n" NOR);
                return 1;
        }

        if( ob->is_character() )
        {
                write(CYN + name() + "道：這你也拿來估價？\n" NOR);
                return 1;
        }

        if( ob->query_amount() )
                value = ob->query("base_value");
        else
                value = ob->query("value");

        if( ob->query("consistence") )
                value = value * ob->query("consistence") / 100;

        if( value < 1 )
                write(CYN + name() + "道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        if( ob->query("no_drop") || (ns = ob->query("no_sell")) )
        {
                if( stringp(ns) )
                {
                        write(CYN + name() + "道：" + ns + "\n" NOR);
                        return 1;
                }
                write(CYN + name() + "道：“這東西有點古怪，我可不好估價。”\n" NOR);
        } else
                write(CYN + name() + "道：“" + ob->query("name") + CYN "值" +
                        MONEY_D->price_str(value * 50 / 100) + "。”\n" NOR);
        return 1;
}

int do_sell(string arg)
{
        object me;
        object ob;
        object nob;
        string my_id;
        int amount;
        int value;
        int res;
        int max_count;
        mixed ns;

        if( !arg )
                return notify_fail("你要賣什麼？\n");

        if( sscanf(arg,"%s to %s", arg, my_id) == 2 )
        {
                if( !id(my_id) && my_id != query("name"))
                        return 0;
        }

        if( sscanf(arg, "%d %s", amount, arg) != 2 )
                // not indicate the amount of the goods
                amount = 1;

        if( amount < 1 )
        {
                write(CYN + name() + "疑惑的問道：“沒見過這種賣法，你到底想賣幾件呢？”\n" NOR);
                return 1;
        }

        me = this_player();
        if( !(ob = present(arg, me)) )
        {
                write("你身上沒有這種東西啊！\n");
                return 1;
        }

        max_count = ob->query_amount();
        if( !max_count )
        {
                // not combined object
                if( amount > 1 )
                {
                        write(ob->name() + "這種東西不能拆開來賣。\n");
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if( amount > max_count )
                {
                        write("你身上沒有這麼多" + ob->name() + "。\n");
                        return 1;
                }
        }

        if( ob->query("money_id") )
        {
                write(CYN + name() + "道：“哈哈哈哈！你想賣「錢」？？”\n" NOR);
                return 1;
        }

        if( ob->is_character() )
        {
                write(CYN + name() + "道：“哼！我這裏做正經生"
                      "意，不販賣這些！”\n" NOR);
                return 1;
        }

        if( ob->query("unique")
        ||  ob->is_no_clone()
        ||  ob->query("no_pawn")
        ||  ob->query("replica_ob")
        ||  ob->query("bindable") )
        {
                write(CYN + name() + "搖搖頭，道：“這種東西我"
                      "不識貨，不敢要。”\n" NOR);
                return 1;
        }

        if( ob->query("no_drop") ||
            (ns = ob->query("no_sell")) )
        {
                if( stringp(ns) )
                {
                        command("say " + ns);
                        return 1;
                }
                write(CYN + name() + "搖搖頭，道：“這種東西我"
                      "不識貨，不敢要。”\n" NOR);
                return 1;
        }

        if( is_vendor_good(ob) != "" )
        {
                write(CYN + name() + "笑道：“我賣給你好不好？”\n" NOR);
                return 1;
        }

        if( ob->query("food_supply") )
        {
                write(CYN + name() + "不屑道：“嘿嘿，剩菜剩飯留給"
                      "您自己用吧。”\n" NOR);
                return 1;
        }

        if( ob->query("shaolin") )
        {
                write(CYN + name() + "驚道：“小的膽子很小，可"
                      "不敢買少林廟產。”\n" NOR);
                return 1;
        }

        if( ob->query("mingjiao") )
        {
                write(CYN + name() + "忙搖頭道：“小的只有一個腦袋，可"
                      "不敢買魔教的東西。”\n" NOR);
                return 1;
        }

        if( ob->query("consistence") )
                value = value * ob->query("consistence") / 100;

        if( max_count > 1 )
        {
                if( ob->query("base_value") * amount / amount != ob->query("base_value") )
                {
                        write(CYN + name() + CYN "大驚失色道：這麼大一筆生意？我"
                              "可不好做。\n" NOR);
                        return 1;
                }
                value = ob->query("base_value") * amount;
        }
        else
                value = ob->query("value");

        if( value < 2 )
                write(CYN + name() + "隨手一扔，道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        {
                if( max_count == amount )
                        res = ob->move(this_object());
                else
                {
                        nob = new(base_name(ob));
                        nob->set_amount(amount);
                        if( res = nob->move(this_object()) )
                                ob->add_amount(-amount);
                        else
                                destruct(nob);
                }

                if( res )
                {
                        message_vision("$N賣掉了一" + ob->query("unit") +
                                       ob->query("name") + "給$n。\n",
                                       this_player(), this_object());
                        MONEY_D->pay_player(this_player(), (value / 2));
                        ob->sold();
                } else
                        write(CYN + name() + "搖搖頭，道：“對不起，"
                              "我現在不收貨了。”\n" NOR);
        }
        //destruct(ob);
        return 1;
}

void reset()
{
        int i, t;
        object *obs;

        t = time();
        if( !uptime )
                uptime = t;

        if( t - uptime >= 3600 ) {
                uptime = t;
                init_goods();
        }

        obs = all_inventory();
        for( i = 0; i < sizeof(obs); i++ )
                if( i >= 100 || obs[i]->query_weight() >= 1000000 )
                        destruct(obs[i]);
}
