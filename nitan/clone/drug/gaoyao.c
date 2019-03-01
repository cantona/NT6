// Code of ShenZhou
// gaoyao.c

inherit ITEM;
inherit F_EQUIP;

void create()
{
        set_name("狗皮膏藥", ({ "goupi gaoyao", "gaoyao" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("value", 20);
                set("unit", "張");
                set("no_sell", 1);
                set("material", "cloth");
                set("armor_type", "bandage");
                set("armor_prop/attack", -10);
                set("armor_prop/defense", -10);
                set("armor_prop/unarmed", -10);
        }
}

void init()
{
        add_action("do_bandage", "bandage");
}

int wear() { return 0; }

int do_bandage(string arg)
{
        object ob;

        if( (int)query("blood_soaked") >= 2 )
                return notify_fail( name() + "已經被鮮血浸透，不能再用了。\n");

        if( query("equipped") )
                return notify_fail( name() + "已經貼在你的傷口上了，如果你要用來貼別人，請你先把它除下來。\n");

        if( !arg ) ob = this_player();
        else {
                ob = present(arg, environment(this_player()));
                if( !ob || !userp(ob))
                        return notify_fail("你要替誰貼傷？\n");
        }

        if( this_player()->is_fighting()
        ||        ob->is_fighting() )
                return notify_fail("戰鬥中不能貼傷。\n");

        if( query("eff_qi", ob) == query("max_qi", ob) )
                return notify_fail( (ob==this_player()? "你" : ob->name())
                        + "並沒有受到任何外傷。\n");

        if( query_temp("armor/bandage", ob) )
                return notify_fail( ob->name() + "身上的傷已經裹著其他東西了。\n");

        if( !move(ob) ) return 0;

        if( ob==this_player() )
                message_vision("$N把" + name() + "貼在傷口上。\n", this_player());
        else
                message_vision("$N把" + name() + "貼到$n的傷口上。\n", this_player(), ob);

        ::wear();
        ob->apply_condition("bandaged", 30);
        addn("blood_soaked", 1);

        return 1;
}

void remove(string euid)
{
        ::remove(euid);
        if( query("equipped") && environment() )
                environment()->apply_condition("bandaged", 0);
}

string query_autoload()
{
        if( query("equipped") ) return query("name");
}

void autoload(string arg)
{
        int i;

        set("name", arg);
        set("blood_soaked", 3);
        ::wear();
}
