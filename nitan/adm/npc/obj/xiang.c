// by Lonely 2005.1
// updated by Lonely 2007.11.2
// xiang.c

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define TO_STORE(x, y) (["name" : query("name",ob), "id" : query("id",ob), "file" : base_name(ob), "amount" : x, "sign" : y])

nosave int load;
mapping *store;
mapping *data_dbase;
mapping *temp_dbase;

int do_store(string arg);
int do_take(string arg);
int do_lock(string arg);
int do_open(string arg);
int get_passwd(string pass, object ob);
int confirm(string yn, object me);
int set_passwd(string pass, object ob);
int store_item(object me, object obj, int amount);
int store_data(object me, object ob, int sn);

int clean_up() { return 1; }

mixed *store_signs()
{
        string *sn = ({});

        if (! store || sizeof(store) < 1)
                return sn;

        for (int i = 0; i < sizeof(store); i++)
                sn += ({ store[i]["sign"] });

        return sn;
}

void create()
{
        set_name(HIM "聚寶箱" NOR, ({ "ju baoxiang", "baoxiang", "xiang" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", sort_string(HIW "一個四周邊緣環繞著神秘光環的箱子，據說"
                                "可以將東西無限制的存（store）進去,不會"
                                "丟失，且無論什麼時候都可以取（take）出"
                                "來，還可以使用密碼鎖（lock）防盜。" NOR, 38, 0));

                set("value", 100);
                set("unit", "個");
        }
        set("no_get", 1);
        setup();
}

string extra_long()
{
        mixed ob_name_real_len;
        string msg, ob_name;

        if (query("open") || wizardp(this_player()))
        {
                if (! store || sizeof(store) < 1)
                        return "目前沒有存放任何物品在箱子裡。\n";

                msg = HIW "\n目前你存放的物品有：\n編號  物品                                      數量\n"
                          "──────────────────────────────────\n" NOR;

                for (int i = 0; i < sizeof(store); i++)
                {
                        ob_name = filter_color(store[i]["name"] + "(" + store[i]["id"] + ")");
                        ob_name_real_len = color_len(store[i]["name"] + "(" + store[i]["id"] + ")");
                        msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s     %5d\n",
                                        i + 1, store[i]["name"] + "(" + store[i]["id"] + ")",
                                        store[i]["amount"]);
                        if (store[i]["amount"] == 0)
                                store[i] = 0;
                }
                msg += HIW "──────────────────────────────────\n" NOR;

                store -= ({ 0 });
        if (sizeof(data_dbase))
                data_dbase -= ({ 0 });
        if (sizeof(temp_dbase))
                temp_dbase -= ({ 0 });
                return msg;
        } else
        {
                if (query("closed"))
                        msg = HIW "箱子目前是關著的，似乎還上了密碼鎖，你需要先打"
                        "開（open）箱子才可以查看（look）箱子裡的物品。" NOR;
                else
                        msg = HIW "箱子目前是關著的，不過沒有上密碼鎖，你需要先打"
                        "開（open）箱子才可以查看（look）箱子裡的物品。" NOR;

                return sort_string(msg, 38, 0);
        }
}

void init()
{
        string owner;
        object env;

        if (! load)
        {
                env = environment(this_object());
                if( stringp(owner=query("room_owner_id", env)) )
                        set("owner", owner);

                restore();
                set("shadow_ob", this_object()->query_defual_ob());
                set("shadow_ob", this_object()->query_default_object());
                load = 1;
        }

        add_action("do_store", ({ "store", "cun" }));
        add_action("do_take",  ({ "take",  "qu"  }));
        add_action("do_lock",  ({ "lock",  "suo" }));
        add_action("do_open",  ({ "open",  "kai" }));
}

int do_open(string arg)
{
        string f, pass, new_pass, st_pass;
        object me;
        int st_stat;

        me = this_player();

        if (! id(arg))
                return notify_fail("你要想打開什麼？\n");

        if( query("closed") && query("owner", this_object()) != me )
        {
                write("箱子已經上了暗鎖，請輸入開箱密碼：");
                input_to((: get_passwd :), me);
                return 1;
        }

        set("open", 1);
        set("closed", 0);
        save();
        write(HIG "箱子已經成功打開，可輸入 look 查看箱子裡裝的東西！\n" NOR);
        return 1;
}

int get_passwd(string pass, object ob)
{
        if (crypt(pass, query("passwd")) == query("passwd"))
        {
                set("open", 1);
                set("closed", 0);
                save();
                write(HIG "箱子已經成功解鎖，可輸入 look 查看箱子裡裝的東西！\n" NOR);
                return 1;
        } else
        {
                write("密碼錯誤，請核對密碼後再試！\n");
                return 1;
        }
}

int do_lock(string arg)
{
        string f, pass, new_pass, st_pass;
        object me;
        int st_stat;

        me = this_player();

        if (! id(arg))
                return notify_fail("你要想鎖上什麼？\n");

        if (query("closed") && ! query("open"))
                return notify_fail("箱子已經上了暗鎖。\n");

        set("open", 0);

        if( query("owner", this_object()) != query("id", me) )
        {
                if (query("passwd"))
                        set("closed", 1);
                save();

                write("你把箱子合上" + (query("passwd") ? "並加上了暗鎖！" : "。") + "\n");
                return 1;
        }

        write("箱子已經合上，你需要給箱子更換暗鎖嗎？（" HIR "y" HIG "/" HIY "n" HIG "）\n" NOR);
        input_to((: confirm :), me);
        return 1;
}

int confirm(string yn, object me)
{
        if (upper_case(yn) == "Y")
        {
                write(HIW "請設定箱子暗鎖的密碼：" NOR);
                input_to((: set_passwd :), 1, me);

                return 1;
        } else
        {
                if (query("passwd"))
                {
                        set("closed", 1);
                        save();
                        return 1;
                }
                write(HIG "您選擇了放棄加暗鎖。\n" NOR);
                return 1;
        }
}

int set_passwd(string pass, object ob)
{
        write("\n");

        if (strlen(pass) < 5)
        {
                write("管理密碼的長度至少要五個字元，請重設您的暗鎖密碼：\n");
                input_to((: set_passwd :), 1, ob);
                return 1;
        }

        set("closed", 1);
        set("passwd", crypt(pass, 0));
        save();
        write(HIG "箱子已經成功鎖上，請記住你設定的密碼！\n" NOR);
        return 1;
}

int do_take(string arg)
{
        object me, ob;
        int i, j, sn, amount, amount1;
        mapping data, tmp_data;
        mapping function_data;
        string *ks;
        string *format;
        string key;
        object shadow_ob;

        me = this_player();

        if (query("open") != 1 && ! wizardp(me))
                return notify_fail("箱子已經上鎖，請先解鎖。\n");

        if (! arg || sscanf(arg, "%d %d", sn, amount) != 2)
                return notify_fail("格式錯誤，請用 take 編號 數量 來取回物品。\n");

        if (amount < 1 || amount > 10000)
                return notify_fail("每次取物品的數量不得小于一同時也不能大于一萬。\n");

        if (sn < 1) return notify_fail("你要取第幾號物品？\n");

        if (! store || sizeof(store) < 1 || sn > sizeof(store))
                return notify_fail("你的箱子裡沒有存放這項物品。\n");

        if (amount > store[sn-1]["amount"])
                // return notify_fail("這樣物品你沒有那麼多個。\n");
                amount = store[sn-1]["amount"];

        if (! (ob = new(store[sn-1]["file"])))
        {
                store[sn-1] = 0;
                store -= ({ 0 });
                tell_object(me, "無法取出該物品，系統自動清除之。\n");
                return 1;
        }

        if (me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance())
        {
                tell_object(me, "你的負重不夠，無法一次取出這麼多物品。\n");
                destruct(ob);
                return 1;
        }

        if (ob->query_amount())
        {
                store[sn-1]["amount"] -= amount;
                if (store[sn-1]["amount"] == 0)
                {
                        store[sn-1] = 0;
                        store -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me, 1);
                save();
                message_vision("$N從箱子裡取出一"+query("unit", ob)+query("name", ob)+"。\n",me);
                return 1;
        }

        destruct(ob);
        if( amount > 200 ) {
                amount = 200;
                tell_object(me, "該物品每次最多只能取200個。\n");
        }

        store[sn-1]["amount"] -= amount;
        amount1 = amount;

        while (amount1--)
        {
                reset_eval_cost();
                ob = new(store[sn-1]["file"]);
                if (store[sn-1]["sign"] == 0)
                {
                        ob->move(me, 1);
                        continue;
                }

                if (data_dbase && sizeof(data_dbase) > 0)
                {
                        for (i = 0; i < sizeof(data_dbase); i++)
                        {
                                if (data_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        data = copy(data_dbase[i]);
                                        ks = keys(data);
                                        for (j = 0; j < sizeof(ks); j++)
                                        {
                                                if (ks[j] == "sign") continue;
                                                set(ks[j], data[ks[j]], ob);
                                        }
                                        data_dbase[i] = 0;
                                        if( shadow_ob = ob->query_default_object() ) 
                                                set("shadow_ob", shadow_ob, ob);
                                }
                        }
                        data_dbase -= ({ 0 });
                }

                if (temp_dbase && sizeof(temp_dbase) > 0)
                {
                        for (i = 0; i < sizeof(temp_dbase); i++)
                        {
                                if (temp_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        tmp_data = copy(temp_dbase[i]);
                                        ks = keys(tmp_data);
                                        for (j = 0; j < sizeof(ks); j++)
                                        {
                                                if (ks[j] == "sign") continue;
                                                set_temp(ks[j], tmp_data[ks[j]], ob);
                                        }
                                        temp_dbase[i] = 0;
                                }
                        }
                        temp_dbase -= ({ 0 });
                }

                if( mapp(function_data=query("function", ob)) && sizeof(function_data) )
                {
                        format = keys(function_data);
                        foreach (key in format)
                                call_other(ob, key, function_data[key]);
                }

                if( query("id", ob) != store[sn-1]["id"] || 
                    query("name", ob) != store[sn-1]["name"] )
                {
                        //amount1++;
                        destruct(ob);
                        continue;
                }

                if( query("bind_owner", ob) && 
                    query("bind_owner", ob) != query("id", me) )
                {
                        tell_object(me, ob->name() + "已經綁定，無法移動。\n");
                        store_item(me, ob, 1);
                        continue;
                }

                if (member_array(F_NAME, deep_inherit_list(ob)) != -1)
                        ob->set_name(query("name", ob),({query("id", ob)}));

                ob->move(me, 1);
        }

        if (store[sn-1]["amount"] == 0)
        {
                store[sn-1] = 0;
                store -= ({ 0 });
        }
        save();
        if( ob )
        message_vision("$N從箱子裡取出" + chinese_number(amount) +
                        query("unit", ob)+query("name", ob)+"。\n",me);
        return 1;
}

int do_store(string arg)
{
        int i, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if (! arg) return notify_fail("你要存放什麼東西？\n");

        if (me->is_busy()) return notify_fail("你正在忙著呢！\n");

        if (query("open") != 1 && ! wizardp(me))
                return notify_fail("箱子是合上的，請先打開（open）後再放入物品。\n");

        if (store && sizeof(store) > 500)
                return notify_fail("箱子最多只能存入五百個格子，現在箱子已經滿了。\n");

        if (arg == "all")
        {
                inv = all_inventory(me);
                if (sizeof(inv) > 100)
                        return notify_fail("你身上的物品太多了，很容易搞混，你還是一個一個存吧。\n");

                for(i = 0; i < sizeof(inv); i++)
                {
                        reset_eval_cost();
                        do_store(query("id", inv[i]));
                }
                return 1;
        } else
        if (sscanf(arg, "%d %s", amount, item) == 2)
        {
                if(! objectp(ob1 = present(item, me)))
                        return notify_fail("你身上沒有這樣東西。\n");

                if (! ob1->query_amount())
                        return notify_fail(ob1->name() + "不能被分開存放。\n");

                if (amount < 1)
                        return notify_fail("存東西的數量至少是一個。\n");

                if (amount > ob1->query_amount())
                        return notify_fail("你沒有那麼多的" + ob1->name() + "。\n");

                if (amount == (int)ob1->query_amount())
                        return store_item(me, ob1, amount);
                else
                {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if(! store_item(me, ob2, amount))
                        {
                                ob2->move(me);
                                return 0;
                        }
                        return 1;
                }
        }

        if(! objectp(ob1 = present(arg, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        if (ob1->query_amount())
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        object obj;
        int i, n, sn;

        if (! objectp(ob))
        {
                error("no this object!\n");
                return 0;
        }

        if (inherits(F_SILENTDEST, ob))
        {
                tell_object(me,"箱子不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if (member_array(ITEM + ".c", deep_inherit_list(ob)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob)) == -1)
        {
                tell_object(me,"箱子不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if (member_array(MONEY+ ".c", deep_inherit_list(ob)) != -1)
        {
                tell_object(me,"箱子不保存"+query("name", ob)+"，要存錢的話請去錢莊吧。\n");
                return 0;
        }

        if( query("task_ob", ob) || 
            query("unique", ob) || 
            query("no_store", ob) || 
            ob->is_no_clone() ||
            query("maze_item", ob) )
        {
                tell_object(me,"漫遊包不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if (ob->is_character() ||
            ob->is_item_make() ||
            ! clonep(ob))
        {
                tell_object(me,"漫遊包不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        if (sscanf(base_name(ob), "/data/%*s") &&
            ! ob->is_inlaid())
        {
                tell_object(me,"漫遊包不保存"+query("name", ob)+"，請你自己妥善處理。\n");
                return 0;
        }

        switch(query("equipped", ob) )
        {
        case "worn":
                tell_object(me, ob->name() + "必須先脫下來才能存放。\n");
                return 0;
        case "wielded":
                tell_object(me, ob->name() + "必須先解除裝備才能存放。\n");
                return 0;
        }

        if (sizeof(all_inventory(ob)))
        {
                tell_object(me,"請你先把"+query("name", ob)+"裡面的東西先拿出來再存放。\n");
                return 0;
        }

        if (! store) store = ({});

        n = sizeof(store);

        if (! ob->query_amount())
        {
                obj = new(base_name(ob));
                if (! mapping_eqv(ob->query_entire_temp_dbase(), obj->query_entire_temp_dbase()) ||
                    ! mapping_eqv(ob->query_entire_dbase(), obj->query_entire_dbase()))
                {
                        while(1)
                        {
                                sn = time() + random(99999999);
                                if (member_array(sn, store_signs()) == -1)
                                        break;
                        }
                        store += ({ TO_STORE(amount, sn)});
                        store_data(me, ob, sn);
                        save();
                        message_vision("$N存入"+chinese_number(amount)+query("unit", ob)+
                                        query("name", ob)+"到箱子裡。\n",me);
                        destruct(ob);
                        destruct(obj);
                        return 1;
                }
                destruct(obj);
        }

        for (i = 0; i < n; i++)
        {
                if( store[i]["id"] == query("id", ob) && 
                    store[i]["name"] == query("name", ob) && 
                    store[i]["file"] == base_name(ob))
                {
                        store[i]["amount"] += amount;

                        message_vision("$N存入" + (amount > 1 ? "一" : chinese_number(amount)) +
                                        query("unit", ob)+query("name", ob)+"到箱子裡。\n",me);
                        destruct(ob);
                        save();
                        return 1;
                }
        }

        store += ({TO_STORE(amount, 0)});
        save();

        message_vision("$N存入" + (amount > 1 ? "一" : chinese_number(amount)) +
                        query("unit", ob)+query("name", ob)+"到箱子裡。\n",me);

        destruct(ob);
        return 1;
}

int store_data(object me, object ob, int sn)
{
        mapping data;

        if (! data_dbase)
                data_dbase = ({});
        data = ob->query_entire_dbase();
        data += ([ "sign" : sn ]);
        data_dbase += ({ data });

        if (! temp_dbase)
                temp_dbase = ({});

        data = ob->query_entire_temp_dbase();

        if (! data) return 1;

        data += ([ "sign" : sn ]);
        temp_dbase += ({ data });

        return 1;
}

int remove() { save(); }

string query_save_file()
{
        string id;

        if (! stringp(id = query("owner")) ) return 0;
        return DATA_DIR + "room/" + id + "/" + "xiang";
}
