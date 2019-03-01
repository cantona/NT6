// pill.c

inherit COMBINED_ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_pour", "pour");
}

int do_eat(string arg)
{
        object me = this_player();
        string what = query("cure");
        int howmuch = query("amount");

        if (!id(arg))
                return notify_fail("你想吃什麼？\n");

        if ((int)query("eff_qi", me) ==
            (int)query("max_qi", me))
                return notify_fail("你現在不需要用" + this_object()->name() + "。\n");
        else {
                me->receive_curing("qi", 50);
                message_vision("$N吃下一包金創藥，氣色看起來好多了。\n", me);
                destruct(this_object());
                return 1;
        }
}

int do_pour(string arg)
{
        string me, what;
        object ob;
        function f;

        if( !arg || sscanf(arg, "%s in %s", me, what)!=2 || !id(me) )
                return notify_fail("指令格式: pour <藥粉> in <物品>\n");
        ob = present(what, this_player());
        if( !ob ) return notify_fail("你身上沒有 " + what + " 這樣東西。\n");
        if( !query("pourable", ob) )
        {
                write(this_object()->name() + "似乎不能摻進水酒裡的。\n");
                return 1;
        }
        if( !query("liquid/remaining", ob) )
        {
                write(ob->name() + "裡什麼也沒有，先裝些水酒才能溶化掉"+this_object()->name()+"。\n");
                return 1;
        }
// We let call other to call the "master copy" of the object in case the
// powder object got destructed after used up.
        f = (: call_other, base_name(this_object()), "effect_in_liquid" :);
        set("liquid/drink_func", bind(f,ob), ob);
        message_vision("$N將一" +query("unit") + name() + "扔進" + ob->name() + "，搖晃了幾下。\n", this_player());
        destruct(this_object());
        return 1;
}
