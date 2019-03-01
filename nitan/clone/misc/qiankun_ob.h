// Written by Lonely@chinamud.cn
// cruise_ob.c

#include <ansi.h>
#include <config.h>

inherit ITEM;
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_cruise_ob() { return 1; }
int clean_up() { return 1; }
int store_item(object me, object ob, int amount);

class store {
        string name;
        string id;
        string *ids;
        string file;
        mapping data;
        mapping temp_data;
        int amount;
}
nosave class store *all = ({});
mixed query_store() { return all; }

void create()
{
        set_name(HIC"如意"HIM"乾坤袋" NOR, ({ "qiankun bag", "qiankun", "bag" }));
        set_weight(100);
        set("long", "一個四周邊緣環繞著神秘光環的如意乾坤袋，大千世界盡可藏在其中。據說"
                    "可以將東西無限制的存（store）進去,不會丟失，且無論什麼時候都可以取"
                    "（take）出來，最關鍵是還可以使用它將物品漫遊到其他站。");

        set("unit", "個");
        set("no_sell", 1);
        set("no_get", 1);
        set("no_put", 1);
        set("no_give", 1);
        set("no_store", 1);
        setup();

        ::restore();
}

string extra_long()
{
        mixed ob_name_real_len;
        string msg;

        if( !all || sizeof(all) < 1 )
                return "目前沒有存放任何物品在如意乾坤袋裡。\n";

        msg = HIW "\n目前你存放的物品有：\n編號  物品                                      數量\n"
                  "────────────────────────────────\n" NOR;
        for( int i=0; i<sizeof(all); i++ ) {
#ifdef LONELY_IMPROVED
                ob_name_real_len = 0;
#else
                ob_name_real_len = color_len(all[i]->name + "(" + all[i]->id + ")");
#endif
                msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s      %-11d\n",
                               i+1, all[i]->name + "(" + all[i]->id + ")",
                               all[i]->amount);
                if (all[i]->amount == 0)
                        all[i] = 0;
        }
        msg += HIW "────────────────────────────────\n" NOR;
        all -= ({ 0 });
        return msg;
}

void init()
{
        add_action("do_store", ({ "store", "cun" }));
        add_action("do_take",  ({ "take",  "qu"  }));
}

int do_take(string arg)
{
        object me, ob;
        object *obs;
        int n, amount, num;
        mapping fun_data;
        string *ks;
        string k;

        me = this_player();

        if( me->is_busy() ) return notify_fail("你正忙著呢。\n");

        if( !arg || sscanf(arg, "%d %d", n, amount) != 2 )
                return notify_fail("格式錯誤，請用 take 編號 數量 來取回物品。\n");

        if( amount < 1 || amount > 10000 )
                return notify_fail("每次取物品的數量不得小于一同時也不能大于一萬。\n");

        if( n < 1 ) return notify_fail("你要取第幾號物品？\n");

        if( !all || sizeof(all) < 1 || n > sizeof(all) )
                return notify_fail("你的如意乾坤袋裡沒有存放這項物品。\n");
        n--;
        if( amount > all[n]->amount )
                // return notify_fail("這樣物品你沒有那麼多個。\n");
                amount = all[n]->amount;

        if( !(ob = new(all[n]->file)) ) {
                all[n] = 0;
                all -= ({ 0 });
                tell_object(me, "無法取出該物品，系統自動清除之。\n");
                return 1;
        }

        obs=filter_array(all_inventory(me),(:!query("equipped", $1):));
        if (sizeof(obs) >= MAX_ITEM_CARRIED &&
            ! ob->can_combine_to(me))
                return notify_fail("你身上的東西實在是太多了，沒法再拿東西了。\n");

        if( me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance() ) {
                tell_object(me, "你的負重不夠，無法一次取出這麼多物品。\n");
                destruct(ob);
                return 1;
        }

        if( ob->query_amount() ) {
                all[n]->amount -= amount;
                if( all[n]->amount == 0 ) {
                        all[n] = 0;
                        all -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me, 1);
                save();

                message_vision("$N從如意乾坤袋裡取出一" +
                                query("unit", ob)+query("name", ob)+"。\n",me);
                return 1;
        }
        destruct(ob);

        if( amount > 100 ) amount = 100;
        all[n]->amount -= amount;
        num = amount;
        while( num-- ) {
                if( !all[n]->data && !all[n]->temp_data ) {
                        ob = new(all[n]->file);
                        ob->move(me, 1);
                        continue;
                }

                if( all[n]->data ) {
                           ob = TEMPLATE_D->create_object(all[n]->file, all[n]->id, all[n]->data);
                           ob->set_name(query("name", ob),all[n]->ids);
                }
                else
                           ob = new(all[n]->file);

                if( all[n]->temp_data )
                        ob->set_temp_dbase(all[n]->temp_data);

                if( mapp(fun_data=query("function", ob)) && sizeof(fun_data)){
                        ks = keys(fun_data);
                        foreach (k in ks)
                                call_other(ob, k, fun_data[k]);
                }

                if( query("bind_owner", ob) && 
                    query("bind_owner", ob) != query("id", me)){
                        all[n]->amount += amount;
                        tell_object(me, ob->name() + "已經綁定，無法移動。\n");
                        destruct(ob);
                        return 1;
                }

                if( query("equipped", ob))delete("equipped", ob);
                ob->move(me, 1);
        }

        message_vision("$N從如意乾坤袋裡取出" + chinese_number(amount) +
                        query("unit", ob)+query("name", ob)+"。\n",me);

        if( !wizardp(me) && random(2) )
                me->start_busy(1);

        if( all[n]->amount == 0 ) {
                all[n] = 0;
                all -= ({ 0 });
        }
        save();
        return 1;
}

int do_store(string arg)
{
        int i, n, k, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if( !arg ) return notify_fail("你要存放什麼東西？\n");

        if( me->is_busy() ) return notify_fail("你正在忙著呢！\n");

        n = 100;
        if( MEMBER_D->is_valid_member(me) )
                n += 200;
        if( k = me->qiankun_volume_srv() )
        {
                if( k > 3 ) k = 3;
                n += 200 * k;
        }
        if( sizeof(all) >= n )
        {
                return notify_fail("如意乾坤袋最多只能存入 " + n + " 個格子，請整理你的如意乾坤袋。\n");
        }

        if( arg == "all" ) {
                inv = all_inventory(me);
                inv -= ({ this_object() });
                inv -= ({ 0 });
                inv = filter_array(inv, (: !query("equipped", $1) :));
                n = sizeof(inv);
                if( n > 100 )
                {
                        tell_object(me, "你身上的物品太多了，很容易搞混，你還是一個一個存吧。\n");
                        return 1;
                }

                if( n < 1 )
                {
                        tell_object(me, "你身上沒有任何物品。\n");
                        return 1;
                }

                for( i=0; i<n; i++ )
                {
                        do_store(query("id", inv[i]));
                }
                return 1;
        } else if (sscanf(arg, "%d %s", amount, item) == 2) {
                if( !objectp(ob1 = present(item, me)) )
                        return notify_fail("你身上沒有這樣東西。\n");

                if( !ob1->query_amount() )
                        return notify_fail(ob1->name() + "不能被分開存放。\n");

                if( amount < 1 )
                        return notify_fail("存東西的數量至少是一個。\n");

                if( amount > ob1->query_amount() )
                        return notify_fail("你沒有那麼多的" + ob1->name() + "。\n");

                if( amount == (int)ob1->query_amount() ) {
                        return store_item(me, ob1, amount);
                } else {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if( !store_item(me, ob2, amount) ) {
                                ob2->move(me, 1);
                                return 0;
                        }
                        return 1;
                }
        }

        if( !objectp(ob1 = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if( ob1->query_amount() )
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        class store item;
        mapping data, temp_data;
        object obj;
        int i, n;
        string file, name, id;

        if( !objectp(ob) ) {
                error("no this object!\n");
                return 0;
        }

        if( file_size(base_name(ob) + ".c") < 0 )
                return 0;

        if( inherits(F_SILENTDEST, ob) ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if( member_array(ITEM + ".c", deep_inherit_list(ob)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob)) == -1 ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if( query("task_ob", ob) || query("unique", ob) || 
            query("no_store", ob) || ob->is_no_clone() || query("hj_game", ob) || 
            query("maze_item", ob) || ob->is_money() || query("no_put", ob)){
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if( ob->is_character() || ob->is_item_make() || !clonep(ob) ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if( sscanf(base_name(ob), "/data/%*s") && !ob->is_inlaid() ) {
                tell_object(me,"如意乾坤袋不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        switch(query("equipped", ob)){
        case "worn":
                tell_object(me, ob->name() + "必須先脫下來才能存放。\n");
                return 0;
        case "wielded":
                tell_object(me, ob->name() + "必須先解除裝備才能存放。\n");
                return 0;
        }

        if( sizeof(all_inventory(ob)) ) {
                tell_object(me,"請你先把"+query("name", ob)+"裡面的東西先拿出來。\n");
                return 0;
        }

        name=query("name", ob);
        file = base_name(ob);
        id=query("id", ob);
        data = ob->query_entire_dbase();
        temp_data = ob->query_entire_temp_dbase();

        map_delete(data, "equipped");
        map_delete(data, "who_get");   // 去掉裝備掉落時候get時間限制
        n = sizeof(all);
        obj = new(file);

        if( !ob->query_amount() && (query("set_data", ob) || !mapping_eqv(temp_data, obj->query_entire_temp_dbase())
        ||  !mapping_eqv(data, obj->query_entire_dbase())) ) {
                destruct(obj);
                if( !undefinedp(data["shadow_ob"]) ) data["shadow_ob"] = 0;
                for( i=0;i<n;i++ ) {
                        if( all[i]->file == file &&
                            all[i]->id == id &&
                            all[i]->name == name ) {
                                if( mapping_eqv(data, all[i]->data) &&
                                    mapping_eqv(temp_data, all[i]->temp_data) ) {
                                        all[i]->amount += amount;
                                        save();
                                        message_vision("$N存入"+chinese_number(amount)+query("unit", ob)+
                                                        query("name", ob)+"到如意乾坤袋裡。\n",me);
                                        destruct(ob);
                                        return 1;
                                }
                        }
                }

                item = new(class store);
                item->file = file;
                item->name = name;
                item->id = id;
                item->ids = ob->my_id();
                item->data = data;
                item->temp_data = temp_data;
                item->amount = amount;
                all += ({ item });
                save();
                message_vision("$N存入"+chinese_number(amount)+query("unit", ob)+
                                query("name", ob)+"到如意乾坤袋裡。\n",me);
                destruct(ob);
                return 1;
        }
        destruct(obj);

        for( i=0;i<n;i++ ) {
                if( all[i]->file == file &&
                    all[i]->id == id &&
                    all[i]->name == name &&
                    !all[i]->data && !all[i]->temp_data ) {
                        all[i]->amount += amount;
                        save();
                        message_vision("$N存入"+chinese_number(amount)+query("unit", ob)+
                                        query("name", ob)+"到如意乾坤袋裡。\n",me);
                        destruct(ob);
                        return 1;
                }
        }

        item = new(class store);
        item->file = file;
        item->name = name;
        item->id = id;
        item->ids = ob->my_id();
        item->amount = amount;
        all += ({ item });
        save();
        message_vision("$N存入"+chinese_number(amount)+query("unit", ob)+
                        query("name", ob)+"到如意乾坤袋裡。\n",me);
        destruct(ob);
        return 1;
}

int receive_summon(object me)
{
        object env;

        if( (env = environment()) && env == me ) {
                write(name() + "不就在你身上嘛？你召喚個什麼勁？\n");
                return 1;
        }

        if( env == environment(me) ) {
                message_vision(HIG "只見地上的" + name() +
                               HIG "化作一道光芒，飛躍至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else {
                if( env ) {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道"
                                HIG "光芒消失了！\n\n" NOR, env);

                        if( interactive(env = environment()) ) {
                                tell_object(env, HIM + name() +
                                                 HIM "忽然離你而去了！\n" NOR);
                        }
                }

                message_vision(HIG "一道光芒劃過，只見$N"
                               HIG "掌中多了一個$n" HIG "！\n\n" NOR,
                               me, this_object());
        }

        //move(me, 1);
        if( !this_object()->move(me) )
                tell_object(me, HIR "由于你的負重太高，"+this_object()->name()+HIR "化作一道光芒，已然了無蹤跡。\n" NOR);
        return 1;
}

int hide_anywhere(object me)
{
        if( query("jingli", me)<100){
                tell_object(me, "你試圖令" + name() +
                            "遁去，可是精力不濟，難以發揮它的能力。\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "輕輕一旋" + name() +
                       HIM "，已然了無蹤跡。\n", me);
        save();
        destruct(this_object());
        return 1;
}

int receive_dbase_data(mixed data)
{
        if( !mapp(data) || sizeof(data) < 1 )
                return 0;

        if( data["all"] )
                all = data["all"];

        return 1;
}

mixed save_dbase_data()
{
        mapping data;

        data = ([]);

        if( sizeof(all) > 0 )
                data += ([ "all" : all ]);

        return data;
}
