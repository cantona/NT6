// Code of ShenZhou
// stone.c
// Jay 7/4/96

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

string* names = ({
        "鵝卵石","石塊","大石頭",
});

string* longs = ({
        "這是一塊不太大的鵝卵石。\n",
        "這是一塊有著棱角的石塊。\n",
        "這是一塊沉甸甸的大石頭。\n",
});

void create()
{
    int i = random(sizeof(longs));

    set_name(names[i], ({"shikuai", "shi", "stone"}));
    set_weight(i*500 + 300); 
    if( clonep() )
       set_default_object(__FILE__);
    else {
       set("long", longs[i]);
        set("unit","塊");
        set("wield_msg","$N搬起一塊石頭準備戰鬥。\n");
        set("material", "stone");
    }
    init_hammer(i+1);
    setup();
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object obj, me;

        if (!arg || (arg != "stone" && arg != "shikuai"))
                return notify_fail("什麼？\n");

        me = this_player();
        if( query("neili", me)<500 )
                return notify_fail("你功力不足，不能擊石成粉！\n");
        message_vision(HIW"$N氣沉丹田，運足真氣，向石頭擊去！\n"NOR,me); 
        write(HIW"只聽得“□”的一聲，石頭被擊成碎塊！\n"NOR);
        obj = new("/d/taohua/obj/shizi2");
        obj->move(me);
        addn("neili", -(100+random(100)), me);
        destruct(this_object());
        return 1;
}