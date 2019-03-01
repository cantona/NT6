
#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

void create()
{
        set_name(HIY "炎黃金條" NOR, ({ "yhhero goldbar", "yhhero", "goldbar" }) );
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一根金燦燦的金條，拿在手裡頗為舒適。\n"
                            "使用 changing 指令將炎黃金條兌換為十萬YSG，會員可兌換十一萬YSG。\n" 
                            "如果暫時不使用，最好將金條存入倉庫，以免丟失。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "根");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_changing", "changing");
        }
}

int do_changing(string arg)
{
        object me;
        object ob;
        string enid, obid;
        int point, cur_firm;

        me = this_player();
                
        if (! MEMBER_D->is_valib_member(me->query("id")))
        {
                me->add("stocks/balance", 100000);
                write(HIG "成功將一跟炎黃金條兌換為十萬YSG並存入了您的銀庫。\n" NOR);
                write(HIY "您目前在炎黃銀庫存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);

        }
        else
        {
                me->add("stocks/balance", 110000);
                write(HIG "成功將一跟炎黃金條兌換為十一萬YSG並存入了您的銀庫。\n" NOR);
                write(HIY "您目前在炎黃銀庫存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);
        }

        destruct(this_object());
        me->save();

        return 1;
}

int query_autoload()
{
         return 1;
}
