
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "幹將精元" NOR, ({ "ganjiang jingyuan" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一顆晶瑩無瑕的寶石，據說擁有著奇幻的力量。\n"
                                "輸入指令 use <你的九級兵器ID> 可將九級兵器提升到待鑲嵌狀態。\n"
                                "只要進行最後一步鑲嵌即可將你的九級兵器提升為十級神器。        十級神\n"
                                "器擁有著超凡的力量。\n"
                                "有關最後一步鑲嵌及十級神器介紹請參見幫助文件 help weapon | help enchase\n" NOR);
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
                add_action("do_use", "use");
        }
}

int do_use(string arg)
{
                object me;
                object weapon;
                
                string result;

                me = this_player();

                if (! arg)return notify_fail("指令格式: use <你九級兵器的ID>\n");

                if (! objectp(weapon = present(arg, me)))
                        return notify_fail("你身上沒有這樣道具。\n");

            if (! weapon->is_item_make())
                        return notify_fail("無法在此道具上完成。\n");

            if (weapon->weapon_level() < 12000)
                        return notify_fail("只能九級兵器才能進行該項操作。\n");

                weapon->set("magic/imbue_ok", 1);
                weapon->set("owner/" + weapon->item_owner(), 5000000);
                
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
