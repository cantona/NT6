#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_NOCLONE;

void start_borrowing() 
{
     remove_call_out("return_to_aobai"); 
     call_out("return_to_aobai", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "玄鐵" WHT "匕首" NOR,  ({ "bi shou", "sword", "jian" }));

        set_weight(12000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("no_sell", "這柄爛劍你自個留着吧。\n");
                set("value", 100000);
                set("material", "xuantie");
                set("wield_msg", HIR "$N" HIR "抽出一柄黑黝黝的"
                                 "匕首拿在手中，只感到一陣寒氣撲面而來。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "將手中的匕首插回靴中。\n" NOR);
                set("stable", 100);
        }

        init_sword(200);

        setup();
        move("/d/beijing/aofu_mishi");
        start_borrowing();
        check_clone();
}

int query_unique() { return 1; } // add by shure@tomud.com

void return_to_aobai() 
{ 
     object me; 

     me = environment(); 
     if (! objectp(me)) 
             return; 

     while (objectp(environment(me)) && ! playerp(me)) 
             me = environment(me); 

        if(base_name(me)=="/d/beijing/aofu_mishi")
        {
                call_out("return_to_aobai",3600+random(3600));
                return ;
        }
        
     if (playerp(me)) 
     { 
             if (me->is_fight()) 
             { 
                     call_out("return_to_aobai", 1); 
                     return; 
             } 
             //是否應該執行unwield
             message_vision("忽然$N覺得身上少了件什麼東西似的。\n", me); 
     } else 
     { 
             message("vision", "忽然一個人走了過來，撿起"+name()+"，歎了口氣，搖搖頭走了。\n", me); 
     } 

        move("/clone/misc/void");
        call_out("real_back",random(600));
}

void real_back()
{
     move("/d/beijing/aofu_mishi");
     start_borrowing();
} 