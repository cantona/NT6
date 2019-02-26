// mian.c

inherit ITEM;

void create()
{
        set_name("面", ({ "mian" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗熱氣騰騰的湯麪。\n");
                set("unit", "碗");
                set("value", 100);
                set("remaining", 2);
                set("food_supply", 25);
                set("water_supply", 10);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("food", me) >= me->max_food_capacity() )
                return notify_fail("你已經吃太飽了，再也吃不下了。\n");

        set("value", 0);
        addn("food", query("food_supply"), me);
        if( query("water", me)<me->max_water_capacity()-query("water_supply") )
                addn("water", query("water_supply"), me);

        if (me->is_fighting())
                me->start_busy(2);

        addn("remaining", -1);
        if (query("remaining"))
                message_vision("$N端起湯麪，狼吞虎嚥地吃起來。\n", me);
        else 
        { 
                message_vision("$N端起碗來，把剩下的面連湯吞了。\n"
                               "$N將碗往後一扔，抹了抹嘴，讚道：好香！\n", me);
                destruct(this_object());
        }

        return 1;
}
