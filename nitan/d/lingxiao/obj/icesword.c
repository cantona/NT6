// Obj: /d/lingxiao/obj/icesword.c
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIW "冰劍" NOR, ({"ice sword", "sword", "jian"}));
        set_weight(5000);
        set("unit", "把");
        set("long", "一把散發著森森寒氣的冰劍,令人望之生寒。\n");
        set("value", 8);
        set("material", "ice");
        set("wield_msg", "$N「唰」地一聲抽出一把$n握在手中，只覺一股寒氣撲面而來！\n");
        set("unwield_msg", "$N將手中的$n插入腰間，覺得暖和多了。\n");
        init_sword(50);
        if( clonep(this_object()) )
        {
                set_default_object(__FILE__);
        }
        setup();
}  
void init()
{

        remove_call_out("do_melt");
        call_out("do_melt", 1);
}

void do_melt()
{
        if(this_object()) call_out("melt", 40+random(40));
}

void melt()
{
        object env;

        if(!this_object()) return;
        env=environment(this_object());

        if( env->is_character() )
        {
//a player or a NPC.
                if( (int)env->query_skill("bingxue-xinfa", 1) < 20 )
                {
                        if(environment(env))
                        message_vision("$N覺得身上涼涼的，濕濕的，原來是冰劍化了。\n", env);
                        destruct(this_object());
                        return;
                }
        }
        else if( (int)env->query_max_encumbrance() > 0 && !environment(env) )
        {
//a room.
                if( query("outdoors", env) != "lingxiao" )
                {
                        tell_object(env,"冰劍終于化成了一灘水，流得到處都是。\n");
                        destruct(this_object());
                        return;
                }
        } 
}

