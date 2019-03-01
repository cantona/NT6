// shanshen.c 老山參

inherit ITEM;

void create()
{
        set_name("老山參", ({"laoshan shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株沾滿山泥的老山參。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me)>query("max_qi", me)-20 )
                return notify_fail("你現在沒有必要服用這支老山參。\n");

        addn("eff_qi", 200, me);

        message_vision("$N吃下一株老山參，只覺得渾身一股熱氣兜底冒了上來 !\n", this_player());
        destruct(this_object());
        return 1;
}