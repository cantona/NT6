// poison_dust.c

inherit COMBINED_ITEM;

void create()
{

        set_name("蒙汗藥", ({ "menghan yao", "yao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                        "這是極普通的蒙汗藥\n" );
                set("unit", "包");
                set("base_value", 700);
                set("base_unit", "");
                set("base_weight", 30);
        }
        set_amount(1);
}

void init()
{
        add_action("do_pour", "pour");
}

int do_pour(string arg)
{
        string me, what;
        object ob;
        function f;

        if( !arg
        ||        sscanf(arg, "%s in %s", me, what)!=2
        ||        !id(me) )
                return notify_fail("命令格式: pour <藥> in <物品>。\n");

        ob = present(what, this_player());
        if( !ob )
                return notify_fail("你身上沒有" + what + "這樣東西。\n");
        if( !query("liquid/remaining", ob) )
                return notify_fail(ob->name() + "裏什麼也沒有，先裝些酒水才能溶化藥粉\n");
        f = (: call_other, __FILE__, "drink_drug" :);
        set("liquid/drink_func", bind(f,ob), ob);
        addn("liquid/slumber_effect", 100, ob);
        message_vision("$N將一些" + name() + "倒進" + ob->name() 
                + "搖晃了幾下。\n", this_player());
        add_amount(-1);
        return 1;
}

int drink_drug(object ob)
{
        this_player()->apply_condition("slumber_drug",
                (int)this_player()->query_condition("slumber_drug") 
                +query("liquid/slumber_effect", ob));
        return 0;
}