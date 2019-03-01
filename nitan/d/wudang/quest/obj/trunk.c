// trunk.c
// Modified by haiyan

inherit ITEM;

void create()
{
        set_name("桃樹枝", ({ "trunk" }));
        set_weight(1200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根從桃樹上砍下來的樹枝，可以把它削成桃木劍。\n");
                set("value", 0);
                set("material", "bamboo");
        }
}

void init()
{
        if (this_player() == environment())
        {
            add_action("do_make", "zao");
            add_action("do_make", "zuo");
            add_action("do_make", "xiao");
        }
}

int do_make(string arg)
{
        object me, weapon;
        object where, sword;
        me = this_player();
        weapon=query_temp("weapon", me);
        if (! arg || ! id(arg))
             return notify_fail("你要用什麼做劍？\n");

        if (! objectp(weapon))
             return notify_fail("你不用工具就能做劍？\n");

        if( query("skill_type", weapon) != "dagger" )
             return notify_fail(weapon->name()+"用起來好像不太順手。\n");

        where = environment(me);
        message_vision("$N舉起手中的" + weapon->name() +
                       "，幾下就把桃樹枝削成了一把劍，並刻上了一些驅鬼的符號。\n", me);
        sword = new("/d/wudang/quest/obj/ghost_sword");
        sword->move(me);
        destruct(this_object()); 
        return 1;
}
