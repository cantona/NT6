// bandage.c

#include <ansi.h>
inherit ITEM;
inherit F_EQUIP;
void create()
{
        set_name( HIW"手絹"NOR, ({ "shou juan", "piece"}) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "方");
                set("material", "cloth");
                set("long", "這是一方雪白的手絹。\n");               
                set("armor_type", "bandage");
                set("armor_prop/attack", -10);
                set("armor_prop/defense", -10);
                set("armor_prop/unarmed", -10);
        }
}

void init()
{
        add_action("do_bandage", "bandage");
        add_action("do_look", "look");
}

int wear() { return 0; }

int do_look(string arg)
{
        object me;
        me = this_player();
 
        if(!arg) return 0;
       
        if(id(arg)){
        if(query("blood_soaked") >= 2 && random(query("kar,me")) < 10 && !query("blooded"))
           {
            message_vision("$N正拿着張手絹仔細地端詳着。\n", me);
            if(!query_temp("blooded")){            
                 tell_object(me, HIY "\n你突然發現這張手絹有點奇怪，被染過血的地方有了點變化！\n\n"NOR);
                 set_temp("blooded", 1);
                 return 1;
                 }
            else if(query_temp("blooded") < 3){
                 tell_object(me, HIY "\n這張手絹被染過血的地方開始出現了點變化！\n"NOR);
                 addn_temp("blooded", 1);
                 return 1;
                 }
            else {                 
                 tell_object(me, HIY "\n你仔細研究了一下，才發現這是張地圖，被血浸了後才慢慢現出圖案來！\n\n"NOR);
                 set("blooded", 1);
                 delete_temp("blooded");
                 if( query("owner") == query("id", me) )
                   set_temp("li_meet", 2, me);
                 set("long", "這是一張被血染紅了的手絹，上面的圖象有些奇怪，好像是張地圖。\n");
                 return 1;
                }
            }
        else {
             write(query("long"));
             return 1;
             }
      }
        
}

int do_bandage(string arg)
{
        object ob;
        if( (int)query("blood_soaked") >= 2 )
                return notify_fail( name() + "已經被鮮血浸透，不能再用了。\n");

        if( query("equipped") )
                return notify_fail( name() + "已經裹在你的傷口上了，如果你要用來包紮別人，請你先把它除下來。\n");

        if( !arg ) ob = this_player();
        else {
                ob = present(arg, environment(this_player()));
                if( !ob || !userp(ob))
                        return notify_fail("你要替誰裹傷？\n");
        }

        if( this_player()->is_fighting()
        ||      ob->is_fighting() )
                return notify_fail("戰鬥中不能裹傷。\n");

        if( query("eff_qi", ob) == query("max_qi", ob) )
                return notify_fail( (ob==this_player()? "你" : ob->name())
                        + "並沒有受到任何外傷。\n");

        if( query_temp("armor/bandage", ob) )
                return notify_fail( ob->name() + "身上的傷已經裹著其他東西了。\n");

        if( !move(ob) ) return 0;

        if( ob==this_player() )
                message_vision("$N用" + name() + "替自己裹傷。\n", this_player());
        else
                message_vision("$N用" + name() + "替$n裹傷。\n", this_player(), ob);
        ::wear();
        ob->apply_condition("bandaged", 40);
        addn("blood_soaked", 1);
        
        return 1;
}

void remove(string euid)
{
        ::remove(euid);
        if( query("equipped") && environment() )
                environment()->apply_condition("bandaged", 0);
}
