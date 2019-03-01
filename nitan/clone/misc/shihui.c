// dust.c

#include <ansi.h>
inherit ITEM;
void setup()
{}
void create()
{
        set_name(HIC"石灰粉"NOR, ({"shihui fen", "shihui", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包用來延緩物品腐爛的的石灰粉，只要把物品裹(guo)上石灰就可以了！\n");
                set("value", 30);
        }
        set("pour_type", "1");
        setup();
}

void init()
{
        if( this_player()==environment() )
                add_action("do_guo", "guo");
}
                                                                
int do_guo(string arg)
{
        object ob, me = this_player();

        if( !arg ) return notify_fail("你要用石灰粉包裹什麼東西？\n");
        if(!present(this_object(), me)) return 0;
        if( me->is_busy() ) return notify_fail("你正忙著其它事呢。\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("這裡沒有這樣東西。\n");
        if( living(ob) || !ob->id("head") )
                return notify_fail("石灰粉只能用來包裹頭顱。\n");
        message_vision("$N掏出一把石灰粉，把$n厚厚實實地包上。\n", me, ob);
        set("shihui", 1, ob);
        destruct(this_object());
        return 1;
}
