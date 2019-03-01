
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "綠玉天寶" NOR, ({ "lvyu tianbao" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "這是一顆綠色寶石，據說擁有著奇幻的力量。\n"
                                                "輸入指令 up9lv <你的兵器ID> 可將你的兵器升級為9級兵器。\n" NOR);
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
                add_action("do_up9lv", "up9lv");
        }
}

int do_up9lv(string arg)
{
                object me;
                object weapon;
                
                string result;

                me = this_player();

                if (! arg)return notify_fail("指令格式: up9lv <你兵器的ID>\n");

                if (! objectp(weapon = present(arg, me)))
                        return notify_fail("你身上沒有這樣道具。\n");
           
            if (! weapon->is_item_make())
                        return notify_fail("無法在此道具上完成。\n");

            if (weapon->weapon_level() >= 50000)
                        return notify_fail("你的兵器已經是九級兵器了，不需要再升級了。\n");

        // 
                weapon->set("owner/combat", 6000000);
                weapon->set("combat/MKS",100);
                weapon->set("combat/PKS", 100);
                if (weapon->query("owner/" + me->query("id")) < 4000000)
                        weapon->set("owner/" + me->query("id"), 4000000);

                weapon->save();
            
        tell_object(me, HIC "你感受" + weapon->name() + HIC "發生了"
                    "不可言喻的變化。\n" NOR);

                destruct(this_object());
                return 1;
}

int query_autoload()
{
         return 1;
}
