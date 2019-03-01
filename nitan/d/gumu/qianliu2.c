// Room: /d/gumu/qianliu2.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"潛流"NOR);
        set("long", @LONG
你沒在水中，只覺水勢甚急，沖得你無法立足。你氣悶異常，只得屏氣摸
索潛行，當真是進退維谷。
LONG        );

        set("exits", ([
                "west"   : __DIR__"qianliu1",
                "eastup" : __DIR__"anhe2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2980);
        set("coor/y", -50);
        set("coor/z", -30);
        setup();
}
void init()
{
        object me;
        me = this_player();
        add_action("do_qian","qian");   
        me->receive_damage("qi", 50 );
        me->receive_damage("jing", 50 ); 
        message_vision(HIB"$N的真氣正在流失，呼吸十分困難。\n"NOR, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("die_reason", "在潛流中被淹死", me);
                me->unconcious();
                me->die();
                return ;   
        }    
}

int do_qian(string arg) 
{
        object me;      
        me=this_player();       
        if ( !arg || arg != "down" )    
                return notify_fail("你要往哪裡潛？\n"); 
        if ( me->is_busy() || me->is_fighting())        
                return notify_fail("你正忙著哪！\n");   
        if (arg =="down")
        {       
                if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() <= 50)        
                        return notify_fail("由于重力不夠，你無法繼續下潛!\n");  
                message_vision(HIG"$N一個猛栽，潛了下去。\n"NOR, me);   
                me->receive_damage("jing", 500);        
                me->receive_damage("qi", 500);          
                me->move(__DIR__"qianliu3");       
                tell_room(environment(me), me->name() + "從上面潛了下來。\n", ({ me }));        
                message_vision (HIB"$N只覺得頭暈暈的，身體浸在冰冷的水中，不住的顫抖。\n"NOR,me);       
                return 1;       
        }
        return 1;       
}
