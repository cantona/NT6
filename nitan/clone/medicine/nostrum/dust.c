// dust.c
#include <ansi.h>
inherit ITEM;
void setup()
{}
void create()
{
        set_name(HIC"化屍粉"NOR, ({"dust"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包用毀屍滅跡的化屍粉，只要一丁點就可以化去(dissolve)一具屍體！\n");
                set("value", 50);
        }
        set("pour_type", "1");
        setup();
}

void init()
{
        if( this_player()==environment() )
                add_action("do_dissolve", "dissolve");
}
                                                                
int do_dissolve(string arg)
{
        object ob, me = this_player();

        if( !arg ) return notify_fail("你要用化屍粉溶解什麼東西？\n");
        if(!present(this_object(), me)) return 0;
        if( me->is_busy() ) return notify_fail("你正忙着其它事呢。\n");

        if( !objectp(ob = present(arg, environment(me))) )
                return notify_fail("這裏沒有這樣東西。\n");
        if( !ob->is_corpse() )
                return notify_fail("化屍粉只能用來溶解屍體。\n");
        message_vision(
                "$N用指甲挑了一點化屍粉在$n上，只聽見一陣「嗤嗤」聲響帶着\n"
                "一股可怕的惡臭，$n只剩下一灘黃水。\n", me, ob);
        destruct(ob);
        return 1;
}
