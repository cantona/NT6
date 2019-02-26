// sheerkou.c 蛇兒口
#include <ansi.h>
inherit ITEM;

#define max_poison 24
#define least_poison 8

void init()
{
        add_action("do_shot","shot");
}

void create()
{
        set_name(HIM"蛇兒口"NOR, ({ "sheer kou", "sk" }) );
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("value", 0);
                set("material", "steel");
                set("long", "這是傳説中古老而神祕的暗器--蛇兒口。\n");
        }
        setup();
}

int do_shot(string arg)
{
        object obj,weapon;
        object me = this_player();
        int lv1,lv2,lv3,lv4,damage;
        int tired;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");
        if( !arg)
                return notify_fail("你要攻擊誰？\n");
        if( !objectp(obj = present(arg, environment(me)) ))
                return notify_fail("這裏沒有這個人！\n");
        if(!present(this_object(), me))
                return notify_fail("這裏沒有這個人！\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( !obj->is_character() || obj->is_corpse() )
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");
        if (obj == me)
                return notify_fail("對自己下毒手？別想不開啊。\n");

        tired=query("total_tired", obj);
        message_vision(HIM "$N手一揚，一股粉紅色的煙霧將$n包圍在其中，$n一陣迷亂之下，好像感覺到煙霧中\n"+"有許多蛇正在爭先恐後地纏繞着自己！\n" NOR, me, obj);
        obj->apply_condition("snake_poison",random(max_poison) + random(least_poison * tired));

        destruct(this_object());
        return 1;
}
