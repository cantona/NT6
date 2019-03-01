// pine.c 鬆樹 
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit ITEM;

int start_collapse = 0;
int chop_times = 0; 

void create()
{
        set_name(HIR"紅鬆樹"NOR,({"pine"}));
        set_weight(900000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一棵古老的紅鬆樹。\n");
                set("unit", "棵");
                set("value", 8);
                set("no_get", 1);
            }
        
        setup();
}

void init()
{
        add_action("do_chop", "chop");
        add_action("do_chop", "砍");
}

int do_chop(string arg)
{
        object weapon, me = this_player();
        object piece;
        
        if( !arg || arg!="pine" && arg != "樹" )
                return notify_fail("你要砍甚麼？\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
        message_vision(HIR"$N揮手朝鬆樹一陣猛砍，弄得雙手鮮血淋淋。\n"NOR, me);
                me->receive_damage("qi", 50, "流血過多死了");
                return 1;
        }else if( query("skill_type", weapon) != "sword" && 
                        query("skill_type", weapon) != "blade" && 
                        query("skill_type", weapon) != "axe" )
                {
                        message_vision(HIW"$N揮起手中" + weapon->name() + HIW"朝鬆樹一陣猛砍。\n"NOR, me);
                        message_vision(HIW"結果「啪」地一聲，$N手中的" + weapon->name() + HIW"已經斷為兩截！\n"NOR , me );

                        weapon->unequip();
                        seteuid(getuid());
                        piece = new("/clone/misc/piece");
                        piece->set_name("斷掉的"+query("name", weapon),({query("id", weapon),"piece"}));
                        piece->move(environment(me));
                        destruct(weapon);
                        return 1;
                }

        message_vision(HIW"$N操起手中" + weapon->name() + HIW"，吭吃吭吃地砍樹。\n"NOR, me);
        me->receive_damage("qi",5+random(35-query("str", me)),"砍樹累死了");
        chop_times++;

        if ( !start_collapse && random(chop_times) ) 
        {
                start_collapse = 1;
                chop_times = 0;
                message_vision(HIC"鬆樹開始鬆動起來，吱吱呀呀發出響聲。\n"NOR, this_object());
                call_out("collapse", 20, me);
        }                

        return 1;
}  

void collapse(object me)
{
        object ob, obn;
        object *inv;
        int i;
        
        ob = this_object();
        if ( !objectp(me) ) return;

        if ( chop_times <= 0 || random(chop_times) < 2)
        {
                message_vision(HIC"鬆樹搖擺了兩下，又站住了。\n"NOR, ob);
                start_collapse = 0;        
                return;
        } 

        message_vision(RED"鬆樹轟的一聲倒了下來…\n"NOR, ob);

        if ( random(chop_times) > 5 ) 
        if ( present(me, environment(ob)) )   
        {
                message_vision(HIR"正砸在$n頭上！\n"NOR, ob, me);
                me->receive_damage("qi", 30*chop_times, "被鬆樹幹砸死了");
                me->receive_wound("qi", 20*chop_times, "被鬆樹幹砸死了");
        }
        else 
        {
                inv = all_inventory(environment(ob));
                
                for (i = 0; i < sizeof(inv); i++)
                if (userp(inv[i]))
                {
                        message_vision(HIR"正砸在$n頭上！\n"NOR, ob, inv[i]);
                        inv[i]->receive_damage("qi",30*chop_times, "被鬆樹幹砸死了");
                        inv[i]->receive_wound("qi", 20*chop_times, "被鬆樹幹砸死了");
                }
        }
        if (chop_times >= 13) chop_times = 13;
        set("wdjob/wage", chop_times, me);
        
        if ( objectp(environment(ob)) )
        {
                obn = new(__DIR__"pine_bole");
                obn->move(environment(ob));
        }
        destruct(ob);
}