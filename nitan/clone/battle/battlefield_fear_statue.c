#include <ansi.h>

#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"
inherit ITEM;

void delay_destruct()
{
        destruct(this_object());
}

void init(object me)
{
        object target;
        string* players;

        if( !me ) me = this_player();
        if( !userp(me) ) 
                return;

        if( !BATTLEFIELD2_D->in_battle(me) )
                return;

        if( query_temp("used") )
                return tell_object(me, name(1)+"的強大能力已經被使用。\n");

        players = BATTLEFIELD2_D->get_sorted_players();

        for(int i=0;i<sizeof(players);++i)
        {
                if( players[i] == me->query_id(1) )
                        continue;

                target = find_player(players[i]);
                if( !objectp(target) || !BATTLEFIELD2_D->inside_battlefield(target) )
                        continue;

                if( objectp(target) && BATTLEFIELD2_D->in_battle(target) )
                        break;
        }

        BATTLEFIELD2_D->add_bonus_score(me, 100);
        tell_object(me, "你因為碰觸"+name(1)+"而獲得 "HIY"100"NOR" 點戰績紅利。\n");
        if( target )
        tell_object(me, "你觸動了戰爭恐懼石碑的力量讓"+target->query_idname()+NOR"變得虛弱起來。\n");

        tell_object(target, HIR+me->query_idname()+HIR"使用了戰爭恐懼石碑的力量讓你變得虛弱起來。\n" NOR);
        target->set_weak(10);

        call_out((: delay_destruct :), 0);

        set_temp("used", 1);
}

void create()
{
        set_name(RED"戰爭恐懼石碑"NOR, ({ "battlefield fear statue", "statue" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "使用這個石碑的人可以大幅降低另一位戰場中玩家的能力。");
                set("value", 1000000);
                set("unit", "個");
                set("no_get", 1);
        }
}

