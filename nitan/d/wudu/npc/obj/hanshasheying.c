// hanshasheying.c 含沙射影

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name("含沙射影", ({ "han sha she ying", "hssy" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是五毒教的奇門暗器「含沙射影」，樣子象一條腰帶，可以束在腰間。\n帶中間有一個扁扁的小鐵盒，只要在腰間一按(shot)就可以發射出細如牛毛的毒針。\n") ;
                set("unit", "個");
                set("value", 0);
                set("zhen", 10);
                set("material", "iron");
                set("armor_prop/armor", 3);
        }
        setup();
}

void init()
{
        add_action("do_shot","shot");
}

int do_shot(string arg)
{
        object me,ob,target;
        int myskill , tgskill;
        int mylev ,damage;
        string fam;

        me = this_player();

        if( query_temp("armor/waist", me) != this_object() )
                return notify_fail("你對着你的腰間一摸，糟糕！你還沒把含沙射影裝上呢！\n");
        if( !arg ) return notify_fail("你想對誰發射含沙射影？\n");

        if( !objectp(target = present(arg, environment(me))) )
                return notify_fail("這裏沒有這個人。\n");

        if( query("id", target) == query("id", me) )
                return notify_fail("你想殺自己嗎？\n");

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("含沙射影只能對戰鬥中的對手使用。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail ("這裏不準戰鬥！\n");

        if( !target->is_character() || target->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");

        if(me->is_busy() )
                return notify_fail("你正忙着哪。\n");

        if( query("zhen", this_object())<1 )
        {
                remove_call_out("destroy_box");
                call_out ("destroy_box" , 0 ) ;
                return notify_fail("鐵盒中的毒針已經射光了。\n");
        }

        if( !objectp(ob = present("han sha she ying", me)) )
                return notify_fail("你沒有這種東西。\n");

        myskill = me->query_skill("five-poison",1) + me->query_skill("dodge",1);
        tgskill = target->query_skill("dodge",1);
        mylev = me->query_skill("five-poison");

        if( query("family/family_name", this_player()) != "五毒教" )
        {
                message_vision("\n$N左手在腰間一陣亂按！\n", me);
                return 1;
        }
        if( query("own_name", ob) != query("id", me) )
        {
                message_vision("\n$N左手在腰間一陣亂按！\n", me);
                remove_call_out("destroy_box");
                call_out ("destroy_box" , 0 ) ;
                return 1;
        }

        if ( mylev <= 50 )
                return notify_fail("你的毒技還不熟練，無法使用含沙射影！\n");

        addn("zhen", -1, this_object());
        message_vision(HIR"\n$N一聲輕笑，左手不經意的在腰間一按。只聽得一陣嗤嗤的破空聲。\n"NOR,me,target);
        me->start_busy(2+random(2)) ;
        if( !target->is_killing(me) ) target->kill_ob(me);
        if( random(myskill) < tgskill )
                message_vision("\n$n大叫一聲，猛的一個旱地拔葱身行衝起數丈來高，堪堪躲過了$N的毒針！\n",me,target);
        else {
                message_vision("\n$n躲閃不及，被無數細如牛毛的毒針打了一身，不由的發出一聲慘嚎！\n",me,target);
                tell_object (target, HIR "\n你只覺得臉上、胸前一痛，而後是奇癢難熬，一定是中毒了。\n"NOR);
                damage=me->query_skill("five-poison",1)*4-(query("max_neili", target)/5);
                if( damage < 100 ) damage = 100;
                if( damage > 800 ) damage = 800;
                target->receive_wound ("qi",damage) ;
                target->apply_condition("snake_poison", (int)target->query_condition("snake_poison") + damage/5 );
                target->apply_condition("wugong_poison", (int)target->query_condition("wugong_poison") + damage/5 );
                target->apply_condition("zhizhu_poison", (int)target->query_condition("zhizhu_poison") + damage/5 );
                target->apply_condition("xiezi_poison", (int)target->query_condition("xiezi_poison") + damage/5 );
                target->apply_condition("chanchu_poison", (int)target->query_condition("chanchu_poison")+damage/5 );
                target->start_busy (4);
                }
        return 1;
}

void destroy_box()
{
        message_vision("忽然"+query("name", this_object())+"掉在地上，摔成了一堆鐵片。\n",environment(this_object()));
        destruct(this_object());
}
