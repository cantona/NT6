// Jay 3/17/96

#include <ansi.h>
#include <weapon.h>
inherit F_UNIQUE;
inherit WHIP;

void create()
{
        set_name("柔絲索", ({"rousi suo", "silk", "suo"}));
        set_weight(60);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "摞");
                set("rigidity", 1);
                set("unique", 1);
                set("long", "這是一摞微細透明, 幾非肉眼所能察見的絲索。\n");
                set("value", 10000);
                set("material", "leather");
                set("wield_msg", "$N輕輕抽出一摞$n套在手上。\n");
                set("unwield_msg", "$N將手中的$n捲成一團，放入袖中。\n");
        }
        init_whip(10);
        setup();
}

void init()
{
        add_action("do_tao","tao");
}

int do_tao(object me, object target)
{
        string msg;

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("你只能在戰鬥中的偷襲對手用。\n");

        if (me->is_busy()) 
                return notify_fail("你現在正忙着呢。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang" ||
            me->query_skill_mapped("strike") != "chousui-zhang" ||
            me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你必須先將化功大法功和抽髓掌法相互配合，才能使用柔絲索！。\n"); 
       
        if( (int)me->query_skill("huagong-dafa",1) < 80 )
                return notify_fail("你的化功大法功力不夠，使用不了柔絲索！\n");
        if( (int)me->query_skill("chousui-zhang",1) < 80 )
                return notify_fail("你的抽髓掌功力不夠，使用不了柔絲索！\n");

        if( query("combat_exp", me)<query("combat_exp", target)/2 )
                return notify_fail("你想偷襲自己根本打不過的人？找死啊？\n");
 

        tell_object(me, HIW "\n你悄悄放開柔絲索，催動內力毫不起眼地一擺。\n\n" NOR);
                 

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 && 
            random(10) > 5) 
               {
                msg = HIR"$n忽然動作一頓，竟然象被人綁住了一樣！\n" NOR;
                tell_object(target, HIB "\n你身子突然一緊，才發現自己不知不覺間被人用東西套住了！\n\n" NOR);
                target->start_busy(4);
                } 
          else {
                me->start_busy(2);
                msg = HIY"忽然陽光一閃，正好照見$N拋出了什麼東西，結果被$n機靈地躲了開去。\n" NOR;
                tell_object(me, HIB "\n你突然覺得陽光強了很多，糟糕！自己的企圖被發現了！\n\n" NOR);
                tell_object(target, HIB "\n你突然看見了一條銀白色的東西在陽光下一閃，馬上躍了開去！\n\n" NOR);
                }

        message_vision(msg, me, target);
        addn("neili", -50, me);
        addn("shen", -(random(200)), me);
        return 1;
}