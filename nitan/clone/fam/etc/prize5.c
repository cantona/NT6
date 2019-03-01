#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "朸吤悛" NOR, ({ "god blood", "god", "blood" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "稛岆珨朸吤悛ㄛ侔綱褫眕蚚﹝\n" NOR);
                set("unit", "");
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
                return notify_fail("斕猁瘓妦繫陲昹ˋ\n");

        if (me->is_busy())
                return notify_fail("摹妦繫ㄛ苤陑梗珥覂賸﹝\n");

        my = me->query_entire_dbase();

        if( time()-query_temp("last_eat/blood", me)<1800 )
        {
                write("斕試督蚚徹狻ㄛ剒狻俶楷閨俇虴蚚眕綴符夔樟哿督蚚﹝\n");
                return 1;
        }

        set_temp("last_eat/blood", time(), me);


        message_vision(HIY "$N" HIY "珨欯盛ㄛ蔚珨淕" + un + na +
                       HIY "窊狟ㄛ婬珩覜橇祥善睡措﹝\n" NOR, me);

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
