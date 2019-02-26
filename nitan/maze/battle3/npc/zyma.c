#include <command.h>
#include <dbase.h>
#include <origin.h>
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW"照玉獅子馬"NOR, ({"shizi ma", "horse", "ma"}));
        set("race", "野獸");
        set("age", 3);

        set("combat_exp", 2000000);
        set("long",
                "一匹高頭大馬，全身雪白的毛髮，煞是神俊。\n");

        set("limbs", ({ "頭部", "身體", "蹄子", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("str", 20+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));         
        set("ridable", 1); 
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("ride_prop/dodge",120);
        set("ride_prop/defense",120);
        set("ride_prop/attack",100);
        set("start_room","/maze/battle3/majiu");
        set("no_get",1);
        set("no_drop",1);
        set("no_put",1);

        set("chat_chance", 5);
        set("chat_msg", ({
                 HIC "照玉獅子馬不住地低鳴，蹄子不停地刨打着地面。\n" NOR,
        }) );

        setup();
}

void init()
{
        add_action("do_ride", "ride");
        add_action("do_ride", "qi");
}

int do_ride(string arg)
{
        object me = this_player(1);

        if (! arg) return 0;

        if (me != WAR_D->query_marshal())  
        { 
                message_vision(HIY "$N一聲嘶鳴，把$n掀翻在地，頓時$n滿嘴是泥！！\n" NOR, 
                        this_object(), me);
                return 1;
        }                            
        if (this_object()->id(arg))
        {
                if ("/cmds/std/ride"->main(me, query("id")))
                {
                        if (file_name(environment(me)) == "/maze/battle3/majiu")
                        {
                                remove_call_out("heading_for");
                                call_out("heading_for", 2, me);
                        }
                        return 1;
                }
                return 1;
        } else
        return 0;
}

void heading_for(object me)
{
        if (! objectp(me)) return;
        message_vision(
                HIW "$N快馬加鞭，連夜飛弛，終於趕到了宋軍大營！\n" NOR, me);
        me->move("/maze/battle3/sying1");
        return;
}

