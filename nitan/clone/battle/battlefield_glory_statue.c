#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"

inherit ITEM;

void delay_destruct()
{
        destruct(this_object());
}

void init(object ob)
{
        if( !ob ) ob = this_player();
        if( !userp(ob) )
                return;

        if( !BATTLEFIELD2_D->in_battle(ob) )
                return;


        if( query_temp("used") )
                return tell_object(ob, name(1)+"的強大能力已經被吸收。\n");

        //ob->start_condition(BATTLEFIELD_GLORY);
        BATTLEFIELD2_D->add_bonus_score(ob, 100);
        tell_object(ob, "你因為碰觸"+name(1)+"而獲得 "HIY"100"NOR" 點戰績紅利。\n");

        call_out((: delay_destruct :), 0);

        set_temp("used", 1);
}

void create()
{
        set_name(WHT"戰爭榮耀石碑"NOR, ({ "battlefield glory statue", "statue" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "第一個看到這個石碑的人可以獲得極強大的能力。");
                set("value", 1000000);
                set("unit", "個");
                set("no_get", 1);
        }
}

