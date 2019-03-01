// cha.c 奶茶

inherit ITEM;

void create()
{
        set_name("奶茶",({ "tea", "cha", "nai cha"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗濃濃的奶茶，散發出誘人的香氣。\n");
                set("unit", "碗");
                set("value", 300);
                set("remaining", 5);
                set("drink_supply", 60);
                set("only_do_effect", 1);
                set("can_drink", 1);
        }
        
        setup();
}

int do_effect(object me)
{
        if( query("water", me) >= me->max_water_capacity() )
                return notify_fail("你已經喝太多了，再也灌不下一滴水了。\n");

        set("value", 0);
        addn("water", query("drink_supply"), me);

        me->receive_heal("qi", 50);
        addn("remaining", -1);
        if (query("remaining"))
        {
                message_vision("$N端起奶茶，“咕咚咕咚”喝了幾口，覺"
                               "得體力充沛多了。\n", me);
        } else 
        { 
                message_vision("$N“咕咚咕咚”將剩下的奶茶一飲"
                               "而盡，只覺得一股力量湧了上來。\n", me);
                destruct(this_object());
        }
        return 1;
}
