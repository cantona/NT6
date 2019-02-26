
#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

void create()
{
        set_name(HIY "炎黃金塊" NOR, ({ "yanhuang jinkuai", "yanhuang", "jinkuai" }) );
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一塊金燦燦的金塊，拿在手裏非常沉重。\n"
                            "使用 changing 指令將炎黃金條兑換為一百萬黃金（YSG）。\n" 
                            "如果暫時不使用，最好將金塊存入倉庫，以免丟失。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "塊");
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
                
        if (! MEMBER_D->is_valib_member(me->query("id")) || 1)
        {
                me->add("stocks/balance", 1000000);
                write(HIG "成功將一塊炎黃金塊兑換為一百萬YSG並存入了您的銀庫。\n" NOR);
                // 春節活動期間加送10W
                //me->add("stocks/balance", 100000);
                //write(HIR "活動贈送：春節活動期間加送10%即100000 YSG，祝春節快樂！\n" NOR);
                write(HIY "您目前在炎黃銀庫存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);

        }/*
        else
        {
                me->add("stocks/balance", 110000);
                write(HIG "成功將一跟炎黃金條兑換為十一萬YSG並存入了您的銀庫。\n" NOR);
                write(HIY "您目前在炎黃銀庫存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);
        }
*/
        destruct(this_object());
        me->save();

        return 1;
}

int query_autoload()
{
         return 1;
}
