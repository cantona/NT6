// shitou.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name(HIW"大石頭"NOR, ({ "shi tou"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        set("unit", "塊");
        set("long", "這是一平平常常的大石頭。\n");
        set("value", 0);
        set("material", "stone");
                set("wield_msg", "$N搬起一塊$n準備戰鬥。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(1);
        setup();
}

/*
void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object obj, me;

        if (!arg || (arg != "stone" && arg != "shi tou"))
                return notify_fail("什麼？\n");

        me = this_player();
        if( query("neili", me)<500 )
                return notify_fail("你功力不足，不能擊石成粉！\n");
        message_vision(HIW"$N氣沉丹田，運足真氣，向石頭擊去！\n"NOR,me); 
        write(HIW"只聽得“嘭”的一聲，石頭被擊成碎塊！\n"NOR);
        obj = new("/d/taohua/obj/shizi2");
        obj->move(me);
        addn("neili", -(100+random(100)), me);
        destruct(this_object());
        return 1;
}
*/
