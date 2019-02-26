#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE; 
inherit F_NOCLONE; 
inherit SWORD;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "倚天劍" NOR, ({ "yitian sword", "jian", "sword" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這便與天下至尊的屠龍寶刀並稱的倚天劍。\n相傳讓刀劍對砍(duikan)可以得到曠世的武林祕籍。\n" NOR);
                set("value", 100000);
                set("no_sell", "這樣東西不能賣。\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1); 
                set("replica_ob","/d/city/npc/obj/changjian"); 
                set("enchase/flute", 9);    
                set("material", "steel");
                set("wield_msg", HIW "只聽“嗖”的一聲破空聲響，號稱天下第一神兵的倚天劍已被$N握在手中。\n" NOR);
                set("unwield_msg", HIW "$N將倚天劍插回腰間，天地又漸漸放出光芒。\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));

        init_sword(5000);
        setup();
        start_borrowing();
        check_clone(); 
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_dex() * 100;
        addn("neili", -dam*10, victim);

        if( query("neili", victim)<0 )
        set("neili", 0, victim);

        return HIW "倚天劍攜着颼颼刺骨風聲，直直刺向$n，$n只感到全身的內力竟一絲絲隨着劍鋒湧出。\n" NOR;
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/yitian/obj/shelf")
        {
                call_out("return_to_back",3600+random(3600));
                return ;
        }
        
        if (playerp(me)) 
        { 
                if (me->is_fighting()) 
                { 
                        call_out("return_to_back", 1); 
                        return; 
                } 
                //是否應該執行unwield
                tell_object(me, HIR"\n一條人影從你眼前一閃而過：" +
                            "“多謝替老夫取回" NOR + name() + HIR
                            "，就此謝過，咱們後會有期！”\n\n"NOR);
        } else 
        { 
                message("vision", "忽然一個人走了過來，撿起"+name()+"，歎了口氣，搖搖頭走了。\n", me); 
        } 

        move("/clone/misc/void");
        call_out("real_back", random(2));
}

void real_back()
{
        object room, shelf;

        room = get_object("/d/tulong/yitian/was_lou4");
        shelf = present("shelf", room);
        move(shelf);
        start_borrowing();
} 
