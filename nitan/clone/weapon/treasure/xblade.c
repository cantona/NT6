// xue-dao.c 血刀
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit BLADE;
inherit F_UNIQUE;

void create()
{
        set_name( HIR"血刀"NOR , ({ "blood blade", "blade", "dao" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIR "這是一把纏在腰間的寶刀，刀鋒帶着淡淡的血影。\n" NOR );
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        init_blade(200);
        setup();
}
/*
void init()
{
        add_action("do_wield", "wield");
        add_action("do_unwield", "unwield");
}

int do_wield(string arg)
{
        object me=this_player();

        object ob;
        string str;
        int i, count;

        if (!id(arg)) return notify_fail("你要裝備什麼？\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你已經裝備著了。\n");


        if( ob->wield() ) {
              if( !stringp(str=query("wield_msg", ob)) )
                        str = "$N裝備$n作武器。\n";
              message_vision(str, me, ob);
              if ( me->query_skill("xue-dao")
              && me->query_skill_mapped("blade") == "xue-dao" )
                        addn_temp("apply/damage", 380, me);

              return 1;
        }
        else
                return 0;
}

int do_unwield(string arg)
{
        object me=this_player();
        object ob, *inv;
        string str;
        int i;

        if( !arg ) return notify_fail("你要脱掉什麼？\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上沒有這樣東西。\n");

        if( query("equipped", ob) != "wielded" )
                return notify_fail("你並沒有裝備這樣東西作為武器。\n");

        if( ob->unequip() ) {
                if( !stringp(str=query("unwield_msg", ob)) )
                        str = "$N放下手中的$n。\n";
                message_vision(str, me, ob);
                if ( me->query_skill("xue-dao")
                        && me->query_skill_mapped("blade") == "xue-dao" )
                        addn_temp("apply/damage", -380, me);
                return 1;
        } else return 0;
}
*/