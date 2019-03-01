// xianxing.c 現形炸彈

#include <ansi.h>

inherit ITEM;

int filter_user(object ob);

void create()
{
        set_name(HIR "現形炸彈" NOR, ({ "visible bomb", "bomb" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "聽說這是可以讓人原形畢露的炸彈。\n");
                set("value", 1);
                set("no_sell", 1);
                set("unit", "顆");
        }
}

void init()
{
        add_action("do_bomb", "bomb");
}

int do_bomb()
{
        object me;
        object *ob;
        string msg;

        me = this_player();
        message_vision(HIM "$N大喝道：“統統給我現形！”說罷把手中的炸彈"
                       "一扔，就聽“轟”的一聲！\n" NOR, me);

        ob = filter_array(all_inventory(environment(me)), (: filter_user :));
        switch (sizeof(ob))
        {
        case 0:
                msg = HIG "一陣煙霧過後，什麼變化也沒有，只見$N呵呵的不住傻笑。\n" NOR;
                break;
        case 1:
                if (ob[0] == me)
                        msg = HIC "一陣煙霧過後，只有$N" HIC "自己被炸得渾"
                               "身是煙，原形畢露。\n" NOR;
                else
                        msg = HIC "一陣煙霧過後，" HIG + ob[0]->name() +
                               HIC "被炸得渾身是煙，躺在地上“嗷嗷”直叫。\n" NOR;
                break;
        default:
                msg = HIC "一陣煙霧過後，一堆人被炸得渾身是煙，原形畢"
                       "露。\n" NOR;
                break;
        }

        message_vision(msg, me);
        destruct(this_object());
        return 1;
}

int filter_user(object ob)
{
        if (! userp(ob))
                return 0;

        if( query("env/invisible", ob) )
        {
                delete("env/invisible", ob);
                CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + ob->name(1) +
                                      HIM "被炸得現了形。");
                return 1;
        }

        if( !undefinedp(query_temp("apply/name", ob)) )
        {
                object mask;
                string msg;

                msg = "聽說" + ob->name(1) + HIM "假扮" + ob->name() +
                      HIM "被炸出了原形，渾身上下都是小煙";
                delete_temp("apply/name", ob);
                delete_temp("apply/id", ob);
                delete_temp("apply/short", ob);
                delete_temp("apply/long", ob);
                if (objectp(mask = present("mian ju", ob)))
                {
                        msg += "，連" + mask->name() + HIM "都被燒壞了。";
                        destruct(mask);
                } else
                        msg += "。";
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                return 1;
        }

        return 0;
}
