// Code of ShenZhou
// zuixianmi.c
// fixed bug, sdong, 7/16/1999

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"醉仙蜜"NOR, ({"zuixian mi", "mi"}));
        set_weight(40);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                        "這是一包石樑派溫家祖傳的迷藥。\n" );
                set("unit", "包");
                set("value", 1000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

void init()
{
        add_action("do_pour", "pour");
}

int do_pour(string arg)
{
        int da;
        string me, what;
        object ob;
        function f;

        if( !arg
        ||      sscanf(arg, "%s in %s", me, what)!=2
        ||      !id(me) )
                return notify_fail("命令格式: pour <藥> in <物品>。\n");

        ob = present(what, this_player());
        if( !ob )
                return notify_fail("你身上沒有" + what + "這樣東西。\n");
        if( !query("liquid/remaining", ob) )
                return notify_fail(ob->name() + "裡什麼也沒有，先裝些酒水才能溶化藥粉\n");
        da=query("liquid/drunk_apply", ob);

        if (da > 8 )da = 8; // must set uplimit, otherwise pour in jiuping with guiyuan dan can add nieli 100M

        set("liquid/drunk_apply", da*5, ob);
        set("zuixian", 1, ob);
        message_vision("$N將一包"+ name() + "倒進" + ob->name() 
                + "搖晃了幾下。\n", this_player());
        destruct(this_object());
        return 1;
}