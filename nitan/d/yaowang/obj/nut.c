// nut.c

inherit ITEM;

void create()
{
        set_name("海松子", ({ "hai song zi" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆小指甲蓋大的棕色果子。\n");
        }
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me = this_player();
        
        if(!id(arg))
                return 0;

        message_vision("$N把海松子放在嘴裏嚼了嚼，苦的皺起了眉頭。\n", me);

        me->apply_condition("mabi", 5);
        destruct(this_object());
        return 1;
}