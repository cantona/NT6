#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "神聖血清" NOR, ({ "god blood", "god", "blood" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一瓶神聖血清，似乎可以飲用。\n" NOR);
                set("unit", "瓶");
                set("value", 300000);
        }
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        object me = this_player();

        string mapsk;
        string na, un;
        mapping my = me->query_entire_dbase();

        na = query("name");
        un = query("unit");

        if (! arg || ! id(arg))
                return notify_fail("你要喝什麼東西？\n");

        if (me->is_busy())
                return notify_fail("急什麼，小心別噎着了。\n");

        my = me->query_entire_dbase();

        if( time()-query_temp("last_eat/blood", me)<1800 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/blood", time(), me);


        message_vision(HIY "$N" HIY "一仰脖，將一整" + un + na +
                       HIY "飲下，再也感覺不到任何疲憊。\n" NOR, me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] += my["max_jing"]/2;
        if( my["eff_jing"] > my["max_jing"] ) my["eff_jing"] = my["max_jing"];
        my["eff_qi"] += my["max_qi"]/2;
        if( my["eff_qi"] > my["max_qi"] ) my["eff_qi"] = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
