// Code of ShenZhou
//化屍粉

inherit COMBINED_ITEM;

void create()
{

        set_name("化屍粉", ({ "huashi fen", "fen" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                        "這是一包江湖中人聞而色變的化屍粉，發出熒熒的黃光。\n" );
                set("unit", "包");
                set("base_value", 1000);
                set("base_unit", "份");
                set("no_sell", 1);
                set("base_weight", 30);
                set("medicine", 1);
        }
        set_amount(1);
}

void init()
{
        add_action("do_pour", "pour");
        add_action("do_pour", "dao");
        add_action("do_cast", "cast");
        add_action("do_cast", "tu");
}

int do_pour(string arg)
{
        string me, what;
        object ob;
        function f;

        if( !arg
        ||        sscanf(arg, "%s in %s", me, what)!=2
        ||        !id(me) )
                return notify_fail("命令格式: pour/dao <藥> in <物品>\n");

        ob = present(what, environment(this_player()));
        if( !ob || query("id", ob) != "corpse" )
                return notify_fail("你只能把化屍粉倒在你周圍地上的屍體上。\n");
        message_vision("$N把一份化屍粉撒在$n上，片刻之間，$n化作一灘黃水，消失得無影無蹤了。\n",
                this_player(), ob);
        destruct(ob);
        addn("potential", 1, this_player());
        add_amount(-1);
        return 1;
}

int do_cast(string arg)
{
        string me, what;
        object ob;
        function f;

        if( !arg
        ||      sscanf(arg, "%s on %s", me, what)!=2
        ||      !id(me) )
                return notify_fail("命令格式: cast/tu <藥> on <物品>\n");

        ob = present(what, this_player());
        if( !ob)
                return notify_fail("你身上沒有這個東西。\n");
        if( query("id", ob) != "clothpiece" )
                return notify_fail("化屍粉只能塗在布條上。\n");
        message_vision("$N將一些" + name() + "塗在" + ob->name()
                + "上。\n", this_player());
        add_amount(-1);
        ob->set("hsf",this_player()->query_skill("poison",1 )
                        +this_player()->query_skill("hamagong",1));
        set("long", "這根布條有些異樣，似乎特別的黃，且泛著熒光。\n", ob);
        return 1;
}