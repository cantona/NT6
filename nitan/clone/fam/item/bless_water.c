// 乾坤聖水用于聖化兵器

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "乾坤聖水" NOR, ({ "bless water", "water" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一瓶瑩剔透聖水，散射出絢目的光彩。\n"
                            "他可以用來聖化（bless）兵器或防具。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }

        setup();
}

/*
void init()
{
        if (this_player() == environment())
        {
                add_action("do_bless", "bless");
        }

}
*/

int do_bless(string arg)
{
        object me;
        object ob;
        string msg;
        me = this_player();

        if (! arg || ! objectp(ob = present(arg, me)))
                return notify_fail("你要聖化什麼？\n");

        if (ob == me)
                return notify_fail("你腦潮啊？\n");

        if (! ob->is_item_make())
                return notify_fail("你只能聖化自造兵器或防具！\n");
        
        if (! stringp(ob->item_owner()) ||
              ob->item_owner() != query("id", me) )
                return notify_fail("你只能聖化自己的兵器或防具！\n");

        if( query("bless", ob) >= 30 )
                return notify_fail("一件兵器或防具最多只能聖化三十次！\n");

        message_vision(HIW "\n$N將乾坤聖水緩緩洒在" + ob->name() + HIW "上，頃刻間"
                       + ob->name() + HIW "猶如烈火中重生一般，散發出絢目的光彩！\n\n", me);
        addn("bless", 1, ob);
        set("consistence", 100, ob);
        addn("stable", 1, ob);

        msg = HIG "通過聖化，你的" + ob->name() + "\n";
        msg += HIG "堅固度得到提升！\n";
        msg += HIG "耐久度得到提升！\n";
        msg += HIG "攻防效果得到修正！\n\n";

        tell_object(me, msg);

        destruct(this_object());
        ob->save();
        return 1;
}

int query_autoload()
{
         return 1;
}