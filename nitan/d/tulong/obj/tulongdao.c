#include <weapon.h>
#include <ansi.h>
inherit BLADE;
inherit F_UNIQUE;
inherit F_NOCLONE;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "屠龍刀" NOR, ({ "tulong blade" , "blade" ,"dao", "tulong" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這便是號稱武林至尊的屠龍寶刀，四尺來長的單刀，竟達一百多斤之重。\n相傳其中藏有曠世的大秘密。\n" NOR);
                set("value", 100000);
                set("no_sell", "這樣東西不能賣。\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", HIY "$N一聲狂笑，從背後抽出那柄號稱“"NOR+HIR"武林至尊"NOR+HIY"”的屠龍寶刀高高舉起。\n" NOR);
                set("unwield_msg", HIY "$N哈哈一笑，將屠龍寶刀插回背後。\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));
        init_blade(5000);
        setup();
        start_borrowing();
        check_clone();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_str()*100;
        victim->receive_damage("jing",dam * 2);
        return HIM "屠龍刀夾帶著刺耳的破空聲劃出一道道長虹，$n只感到心神意亂，勉強作出抵擋。\n" NOR;
}

void init()
{
        add_action("do_open","duikan");
}

int do_open(string arg, object me)
{
        object pai,ob;
        if(arg != "yitian sword" || !ob = present("yitian sword", environment(this_object()))) 
        {
                return notify_fail("你要砍什麼？\n");
        }
        else if( query("jiali", this_player()) <= 160 )
                return notify_fail(WHT "\n你提起屠龍刀對準倚天劍用力的砍了下去！"NOR+HIR"\n\n只聽“鏹”的一聲脆響，飛濺出幾點火星。\n" NOR);
        {
                pai = new("/d/tulong/obj/duan1");
                pai->move(this_player());
                pai = new("/d/tulong/obj/duan2");
                pai->move(this_player());
                pai = new("/d/tulong/obj/zhenjing");
                pai->move(this_player());
                pai = new("/d/tulong/obj/miji");
                pai->move(this_player());
                pai = new("/d/tulong/obj/yishu");
                pai->move(this_player());
                message_vision(WHT "\n$N提起屠龍刀對準倚天劍用力的砍了下去！\n\n"NOR+HIW"只聽一聲悶響，$N手臂一震，屠龍刀和倚天劍已經斷了。你發現刀劍中竟然夾藏著幾卷帛絹。\n"NOR,this_player());
                destruct (ob);
                destruct(this_object());
                return 1;
        }
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/tulong/obj/ding")
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
                message("vision", "忽然一個人走了過來，撿起"+name()+"，嘆了口氣，搖搖頭走了。\n", me); 
        } 

        move("/clone/misc/void");
        call_out("real_back", random(2));
}

void real_back()
{
        object room, ding;

        room = get_object("/d/binghuo/wangpangu2");
        ding = present("ding", room);
        move(ding);
        start_borrowing();
} 
