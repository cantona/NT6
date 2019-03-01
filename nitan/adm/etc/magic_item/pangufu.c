// 上古十大神器之 盤古斧 
// Create by Rcwiz for Hero.cn 2003/08

#include <ansi.h>

#include <weapon.h>
inherit HAMMER;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + WHT + "盤古斧" NOR, ({ "pangu fu", "pangu", "fu" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", NOR + WHT "這是一把巨大的斧頭，周身泛著眩目的光華，據說\n"
                                      "此斧乃盤古開天辟地時辟開混沌天地時所用。\n"
                                      "可用之來辟開(pi)太虛，進入太虛境界。\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + WHT "$N" NOR + WHT "將盤古斧握在手中，猶如"
                                           "盤古再現，威風凜凜。\n" NOR);
                set("unwield_msg", NOR + WHT "$N" NOR + WHT "將手中盤古斧收回。\n" NOR);
                set("stable", 100);

        }
        init_hammer(400);
        setup();
}

void init()
{
        add_action("do_pi", "pi");       
}

int do_pi(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("pangu fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("你得先到戶外去。\n");
                 
        message_sort(NOR + WHT + "\n$N" NOR + WHT "雙手揮舞著手中的盤古巨斧，用力劈下，"
                     "剎那間天空中露出一道裂痕，盤古斧化做一道奇異的光芒將$N" NOR + WHT +
                     "卷進太虛之中。\n" NOR, me);
                
        me->move("/kungfu/class/sky/taixu");
        destruct(this_object());

        return 1;
}
