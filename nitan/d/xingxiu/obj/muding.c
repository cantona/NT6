#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"神木王鼎"NOR,({ "shenmu wangding", "wangding", "shenmu" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一隻雕琢而成的暗黃色小木鼎, 木理之間隱隱泛出紅絲。鼎側有五個銅錢大的圓孔，木鼎齊頸出有一道細縫，似乎上下分為兩截。\n");
                set("value", 5);
                set("muding/remaining", 0);                
        }
}

void init()
{
    add_action("do_suck", "suck");
}

int do_suck(string arg)
{
        object me = this_player();

        if ( arg != "blood" || !living(this_player()))
        return notify_fail("你要吸什麼？\n");

        if( this_player()->is_busy() )
                return notify_fail("你上一個動作還沒有完成, 不能運功練毒。\n");
        if ( me->is_fighting())
        return notify_fail("你在戰鬥中不能運功練毒。\n");

        if(query("muding/remaining") < 1)
                return notify_fail("木鼎中沒有血水了。\n");

        message_vision("$N伸掌將血液接住，盤膝運功，將血液吸入掌內。\n", me);
           me->receive_damage("jing", 10);
           me->receive_damage("jingli", 10);
           me->receive_damage("qi", 15);
           me->receive_damage("neili", 3);

        addn("muding/remaining", -1);
        if ((int)me->query_skill("poison", 1) <= 30){
              me->apply_condition("xx_poison", 5);
              return 1;
              }
        if ((int)me->query_skill("poison", 1) > 50 ) return 1;

        if(random(10) > 6){
          switch(random(3)) {
            case 0:
                  me->improve_skill("poison",(query("int", me)/2));
                  write (RED"你只覺掌中微微一涼，一股陰氣順着脈絡侵入腦髓。\n"NOR"你對基本毒技的領會又加深了一些！\n");
                  break;
            case 1:
                  me->improve_skill("chousui-zhang",(query("int", me)/2));
                  write (RED"你只覺掌中微微一癢，一股毒氣自掌沿手臂上升。\n"NOR "你對抽髓掌的領會又加深了一些！\n");
                  break;
            case 2:
                  me->improve_skill("huagong-dafa",(query("int", me)/2));
                  write (RED"你只覺掌中微微一癢，一股陰毒之氣自掌沿手臂上升，直達丹田。\n"NOR "你對化功大法的領會又加深了一些！\n");
                  break;
                  }
            }
         return 1;
}