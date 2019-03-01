// 店舖繼承
// Create by smallfish.
// Update by jjgod.
// Update by Lonely@nitan.org

inherit ROOM;
inherit F_SAVE;

#include <ansi.h>
#include <config.h>

class goods
{
        mapping data; // 動態物品數據
        string name;
        string id;
        string *ids;
        string type;
        string file;
        string unit;
        int amount;  // 數量
        mixed value;   // intp為gold，stringp為$NT
        int number;  // 編號
}

class goods *all_goods = ({});

mixed query_goods() { return all_goods; }
void init_goods() { all_goods = ({}); }
int clean_up() { return 1; }

int add_one_good(object obj, mixed price, int amount)
{
        mapping data, temp;
        string id, name;
        string file;
        object obn;
        class goods item;
        string type;
        int i, n;

        if( !objectp(obj) )
                return 0;

        if( obj->is_weapon() )           type = "武器";
        else if( obj->is_armor() )       type = "防具";
        else if( obj->is_liquid() )      type = "飲具";
        else if( obj->is_food() )        type = "食物";
        else if( obj->is_container() )   type = "容器";
        else if( obj->is_book() )        type = "書籍";
        else                             type = "其它";

        file = base_name(obj);
        id=query("id", obj);
        name=query("name", obj);
        data = obj->query_entire_dbase();
        obn = new(file);
        temp = obn->query_entire_dbase();
        destruct(obn);

        if( !all_goods ) all_goods = ({});
        n = sizeof(all_goods);
        for( i = 0; i < n; i++ )
        {
                if( all_goods[i]->file == file &&
                    all_goods[i]->id == id &&
                    all_goods[i]->name == name ) {
                        if( obj->query_amount() || mapping_eqv(data, temp) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
                                destruct(obj);
                                return 1;
                        }

                        if( all_goods[i]->data && mapping_eqv(data, all_goods[i]->data) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
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
        item->unit=query("base_unit", obj)?
                     query("base_unit", obj):query("unit", obj);
        item->amount = amount;
        item->value = price ? price :
                     (query("base_value", obj)?query("base_value", obj):
                                                 query("value", obj));
        item->number = sizeof(all_goods) + 1;
        if( !mapping_eqv(data, temp) )
                item->data = copy(data);
        all_goods += ({ item });
        destruct(obj);
        return 1;
}

public string do_stock(object ob, object me, string arg)
{
        object obj, item;
        mixed value;
        object room;
        string name;

        room = environment(ob);

        // intp(value) 為gold, stringp(value) 為$NT
        if( !query("shop_type", room) )
                return "對不起，該店舖目前已經被巫師關閉。\n";

        if (! arg || (sscanf(arg, "%s value %d", arg, value) != 2 &&
            sscanf(arg, "%s nt %s", arg, value) != 2) )
                return "指令格式：stock <貨物> value * ( 其中 * 是以銅板作單位的價格 )或\n"
                       "          stock <貨物> nt * ( 其中 * 是以 $NT 作單位的價格 )\n";

        if (! value)
                return "指令格式：stock <貨物> value * ( 其中 * 是以銅板作單位的價格 )或\n"
                       "          stock <貨物> nt * ( 其中 * 是以 $NT 作單位的價格 )\n";

        if (intp(value) && value > 100000000 && !wizardp(me))
                return "店舖最多標價一萬兩黃金，你就別那麼心黑了吧。\n";

        if (stringp(value) && to_int(value) < 0 || to_int(value) > 1000000)
                return "店舖最多標價一百萬$NT，你就別那麼心黑了吧。\n";

        if (! (item = present(arg, me)) || ! objectp(item))
                return "你身上並沒有這個貨物啊！\n";

        if( query("no_sell", item) )
                return "這個東西太招搖了，還是別拿出來販賣。\n";

        if( query("no_get", item) || query("no_drop", item) || 
            query("no_put", item) || query("no_beg", item) || 
            query("no_steal", item) || query("no_drop", item) || 
            query("item_make", item) || query("owner", item) )
                return "這個東西擺不上貨架，就暫時別拿出來賣啦。\n";

        if (item->is_item_make())
                return "這個東西太招搖了，還是別拿出來販賣。\n";

        if( query("wiz_only", item) && !wizardp(me) )
                return "這個東西只能在巫師商店裡賣。\n";

        if (item->is_character())
                return "你不能販賣活物。\n";

        if( query("money_id", item) )
                return "你把錢也拿來出售？\n";

        switch(query("equipped", item)){
        case "worn":
                return item->name() + "必須先脫下來才能存放。\n";

        case "wielded":
                return item->name() + "必須先解除裝備才能存放。\n";
        }

        if (sizeof(all_goods) >= 80)
                return "你店舖上的東西太多了，先收幾種貨物再擺吧。\n";

        if (item->query_amount() && item->query_amount() > 1)
        {
                obj = new(base_name(item));
                obj->set_amount((int)item->query_amount() - 1);
                item->set_amount(1);
                obj->move(me, 1);
        }

        name = item->name(1);
        add_one_good(item, value, 1);

        message_vision(HIW "$N" HIW "將『" HIG + name + HIW "』標上" HIY +
                (intp(value) ? MONEY_D->price_str(value) : (value+"NT")) + HIW "的價格開始出售。\n" NOR, me);
        room->save();

        return "你擺置好了貨物。\n";
}

public string do_unstock(object ob, object me, string arg)
{
        object item, room;
        int i, n;

        seteuid(getuid());
        room = environment(ob);
        if( !query("shop_type", room) )
                return "對不起，該店舖目前已經被巫師關閉。\n";

        if (! arg)
                return "指令格式：unstock <貨物>\n";

        if (! (n = sizeof(all_goods)))
                return "你現在還沒有擺上任何貨物。\n";

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED && !wizardp(me))
                return "你身上的東西太多了，沒法從貨架上取東西。\n";

        for( i = 0; i < n; i++ )
        {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                {
                        if( !(all_goods[i]->amount) ) {
                                all_goods[i] = 0;
                                return "現在"+query("short", room)+"的貨架上並沒有這樣貨物。\n";
                        }

                        all_goods[i]->amount -= 1;

                        if( !all_goods[i]->data )
                                item = new(all_goods[i]->file);
                        else
                        {
                                item = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                item->set_name(query("name", ob),all_goods[i]->ids);
                        }

                        if( all_goods[i]->amount == 0 )
                                all_goods[i] = 0;
                        break;
                }
        }
        all_goods -= ({ 0 });

        message_vision(HIW "$N" HIW "將『" HIG + item->name(1) + HIW"』從貨架上取下來不賣了。\n" NOR, me);

        room->save();

        if (! item->move(me))
        {
                item->move(environment(me));
                tell_object(me, "可是你已經拿不動了，只好把" + item->name(1) + NOR "放在地上。\n");
        }
        return "你取好了貨物。\n";
}

public varargs string do_list(object ob, object me, string arg)
{
        string output, desc;
        class goods item;
        object room;

        if( !wizardp(me) && me->query_condition("killer") )
                return CYN "店舖不做殺人犯的生意！\n" NOR;

        if( me->is_busy() ) {
                return BUSY_MESSAGE;
        }

        room = environment(ob);
        if( !query("shop_type", room) )
                return "對不起，該店舖目前已經被巫師關閉。\n";

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
                return "你是這家店舖不受歡迎的人物，無法購買東西。\n";

        if( !sizeof(all_goods) ) {
                return "現在"+query("short", room)+"目前並沒有出售任何貨物。\n";
        }

        output = "該店舖目前出售以下物品：\n";

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
                                  stringp(item->value) ? item->value + "$NT" : MONEY_D->price_str(item->value),
                                  desc);
        }

        if (query("invite/" + query("id",me),room))
                output += WHT"您是本店貴賓，購買所有貨物均享受"HIW+chinese_number(query("invite/"+query("id",me),room))+HIW"折"NOR+WHT"的優惠。\n" NOR;
        return output;
}

public int do_buy(object obj, object me, string arg)
{
        mixed value;
        object ob;
        int i, n;
        object room;

        room = environment(obj);
        if( !query("shop_type", room) )
        {
               tell_object(me, "對不起，該店舖目前已經被巫師關閉。\n");
               return 1;
        }

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
        {

               tell_object(me, "你是這家店舖不受歡迎的人物，無法購買東西。\n");
               return 1;
        }

        if(me->is_busy())
        {
                tell_object(me, "什麼事都得等你忙完再說吧！\n");
                return 1;
        }

        if (! arg)
        {
                tell_object(me, "你要買什麼東西？\n");
                return 1;
        }

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, "你身上的東西太多了，先處理一下再買東西吧。\n");
                return 1;
        }

        n = sizeof(all_goods);
        if( !n ) {
                tell_object(me, "目前%s沒有可以賣的東西。\n");
                return 1;
        }


        {
                tell_object(me, "該店舖並沒有出售這樣貨物。\n");
                return 1;
        }

        for( i = 0; i < n; i++ ) {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg) {
                        if( !(all_goods[i]->amount) ) {
                                tell_object(me, sprintf("目前這%s" CYN "缺貨，您過一段時間再來吧",
                                        all_goods[i]->name));
                                return 1;
                        }
                        break;
                }
        }

        value = all_goods[i]->value;

        // 如果是貴賓，則有優惠
        if (query("invite/" + query("id",me),room))
        {
                if (intp(value))
                        value = value * query("invite/" + query("id",me),room) / 10; 
                else
                        value = to_string(to_int(value) * query("invite/" + query("id",me), room) / 10); 
        }

        if (intp(value))
        {
                switch (SHOP_D->player_pay(me, obj, value))
                {
                case 0:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：窮光蛋，一邊呆著去。\n" NOR);
                        return 1;

                case 2:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "皺眉道：您還有沒有零錢啊？銀票我可找不開。\n" NOR);
                        return 1;

                default:
                        if( !all_goods[i]->data )
                                ob = new(all_goods[i]->file);
                        else
                        {
                                ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                ob->set_name(query("name", ob),all_goods[i]->ids);
                        }
                        all_goods[i]->amount -= 1;
                        if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                        if (ob->query_amount())
                        {
                                message_vision("$N從$n那裡買下了" + ob->short() + "。\n", me, obj);
                        }
                        else
                        {
                                message_vision("$N從$n那裡買下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                        }

                        ob->move(me, 1);
                }
        } else
        {
                string owner=query("owner", environment(obj));
                if (!MEMBER_D->player_pay(me, to_int(value), owner))
                {
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "冷笑道：你沒有足夠的$NT，還是先去沖值吧。\n" NOR);
                        return 1;
                }
                if( !all_goods[i]->data )
                        ob = new(all_goods[i]->file);
                else
                {
                        ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                        ob->set_name(query("name", ob),all_goods[i]->ids);
                }

                all_goods[i]->amount -= 1;
                if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                if (ob->query_amount())
                {
                        message_vision("$N從$n那裡買下了" + ob->short() + "。\n", me, obj);
                }
                else
                {
                        message_vision("$N從$n那裡買下了一"+query("unit", ob)+query("name", ob)+"。\n",me,obj);
                }

                ob->move(me, 1);

        }
        all_goods -= ({ 0 });
        me->start_busy(1);
        room->save();
        return 1;
}

string short()
{
        if (stringp(query("apply/short")))
                return query("apply/short");

        return query("short");
}

string long()
{
        switch (query("shop_type"))
        {
        // 店舖關閉時的描述
        case 0  : return query("long");
        // 店舖開放時的描述
        default :
                if (stringp(query("apply/long")))
                        return sort_string(query("apply/long"), 60, 4);
                else
                // 默認描述
                if (! stringp(query("open_long")))
                        return @LONG
這裡是一間裝飾得非常豪華的店舖，舖面寬敞明亮，櫃子
上擺滿了各式各樣、琳琅滿目的貨物。此時一位伙計正忙裡忙
外地招呼著客人。
LONG;
                // 特殊描述
                else return query("open_long");
        }
}

void setup()
{
        object waiter, ob;
        string *props;
        string prop;
        mapping m;

        ::setup();
        if (! restore())
                save();

        ob = this_object();
        waiter = present("huo ji", ob);

        if (waiter)
        {
                if( !mapp(m=query("waiter", ob)))return ;
                props = keys(m);

                if (! props) return;
                foreach (prop in props)
                {
                        if (prop == "name")
                                waiter->set_name(query("waiter/"+prop, ob),
                                                 waiter->parse_command_id_list());
                        set(prop,query("waiter/"+prop,  ob), waiter);
                }
        }
}

string query_save_file()
{
        string id;

        sscanf(base_name(this_object()), "/%*s/%*s/%s_shop", id);

        if (! stringp(id)) return 0;

        return sprintf(DATA_DIR "/shop/%s", id);
}

int save()
{
        string file;

        if (stringp(file = this_object()->query_save_file()))
        {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()) &&
            file_size(file + __SAVE_EXTENSION__) > 0)
                return restore_object(file);

        return 0;
}
