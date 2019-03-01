// Room: /d/gumu/obj/huju-jia.c
// Last Modifyed by Winder on Jan. 14 2002
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "護具架" NOR, ({ "huju jia", "jia" }) );         
        set_weight(30000000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "個");
                set("long", "一個木頭制成的架子，上面掛著鐵甲(armor)等護具。你可以拿(na)些去用。\n");
                set("material","wood");
                set("no_get",1);
        }
        set("count", 4);
        setup();
}

void init()
{
        add_action("do_get","na");
}

int do_get(string arg)
{
        object ob, me=this_player();
        string arg1, arg2;

        if(query("count") < 0)
                return notify_fail("架上已經空空如也了。\n");
        if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
                return notify_fail("命令格式: na <護具名稱> from jia。\n");
        if (arg2!="jia")
                return notify_fail("命令格式: na <護具名稱> from jia。\n");
        if( query_temp("marks/拿", me) )
                return notify_fail("你怎麼這麼貪心，拿過了還要拿？\n");
        if( query("combat_exp", me)>120000 )
                return notify_fail("你武藝已到一定程度，還是自食其力吧。\n");
        if (arg1 =="armor")
        {
                ob=new(ARMOR_DIR"tiejia"); 
                ob->move(me);
                message_vision("$N從護具架上拿出一件$n。\n",me, ob); 
                set_temp("marks/拿", 1, me);
                addn("count", -1);
                return 1;
        }     
        return notify_fail("護具架上沒有你想要拿的東西。\n");
}
