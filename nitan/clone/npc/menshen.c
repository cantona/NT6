// menshen.c

#include <ansi.h>
#include <room.h>

inherit ITEM;

void setup() {}

void create()
{
        set_name(HIM "門神" NOR, ({ "men shen", "menshen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張畫的五顏六色的門神，常常"
                            "被人貼在門上用來驅除妖邪。\n");
                set("unit", "張");
        }

        set("no_get", 1);
        setup();
}

void init()
{
        object env;
        object me;

        if (! objectp(env = environment()))
                return;

        if (! clonep(env) || base_name(env) != CHAT_ROOM)
                return;

        if( !stringp(query("owner_id", env)) || 
            !stringp(query("startroom", env)) )
                return;

        me = this_player();
        if (! interactive(me) || wizardp(me) || env->welcome(me))
                return;

        message_vision("門神大喝一聲：“何方妖孽，也"
                       "敢來此？”説罷手中銅錘一蕩，"
                       "將$N一錘打得飛了出去！\n", me);
        
        if( query("id", me) != "rcwiz" )
                 me->move(query("startroom", env));

        else message_vision(HIC "門神見闖了禍，退在一邊再也不敢説什麼了！\n" NOR, me);
        me->start_busy(3);
    
        if( query("id", me) != "rcwiz" )
                message("vision", "只聽“蓬”一聲，" + me->name() +
                        "飛了出來，身上青一塊兒紫一塊兒的。\n",
                        environment(me), ({ me }));
}
