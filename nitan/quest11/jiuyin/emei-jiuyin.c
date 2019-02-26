// emei-jiuyin.c 
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG"九陰真經速成篇"NOR, ({ "jiuyin sucheng", "book"}));
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "卷");
                set("long", "這是名震江湖之九陰真經的速成篇。你可以研讀以下的技能：\n"
                            "九陰身法       (jiuyin-shenfa) \n"
                            "九陰真功       (jiuyin-zhengong) \n"
                            "道德經         (daode-jing) \n"
                            "催心掌         (cuixin-zhang) \n"
                            "九陰銀龍鞭     (yinlong-bian) \n"
                            "九陰白骨爪     (jiuyin-baiguzhua) \n"
                );
                set("treasure", 1);
                set("unique", 1);
                set("value", 0);
                set("material", "paper");
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}

void init()
{
       add_action("do_study",({"study", "du", "read"}));
}

int do_study(string arg)
{
       int cost, my_skill;
       object me=this_player();
       object where = environment(me);

       if (!arg) return notify_fail("你要讀什麼？\n");

       if (me->is_busy())
            return notify_fail("你現在正忙着呢。\n");

       if(where->query("sleep_room")|| where->query("no_fight"))
          return notify_fail("這裏你不能讀書。\n");

       if( me->is_fighting() )
            return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");

       if( !me->query_skill("literate", 1) )
            return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

       if(! me->query("quest/jiuyin2/pass"))
          return notify_fail("你從哪裏偷來的九陰真經，無法研讀。\n");

       if( this_object()->query("owner") != me->query("id"))
          return notify_fail("你從哪裏偷來的九陰真經，無法研讀。\n");

       if( (int)me->query("potential") < 1 )
            return notify_fail("你的潛能已經用完了，再怎麼讀也沒用。\n");

       if( (int)me->query("combat_exp") < 1000000 )
            return notify_fail("你的實戰經驗不足，再怎麼讀也沒用。\n");

       if( me->query_int(1) < 35 )
            return notify_fail("以你目前的領悟能力，還沒有辦法學這個技能。\n");

       cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
       if (cost < 20) cost = 20;
       me->set_temp("last_damage_from", "研讀高深武功，熬盡心機累");
      
       if( me->query("neili") < cost * 2 + 300)
           return notify_fail("你的內力不夠，無法領會這個技能。\n");

       switch (arg) {
         case "jiuyin-baiguzhua":
            my_skill = me->query_skill("jiuyin-baiguzhua", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也許是缺乏實戰經驗，你對經書上面所説的東西總是無法領會。\n");
            else write("你研讀着有關九陰白骨爪的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-baiguzhua", ((int)me->query_skill("literate", 1)/5+1) );
            me->receive_damage("jing", cost );
            me->add("neili", -cost * 2);
            me->add("potential", - random(2));
            break;             
         case "cuixin-zhang":
            my_skill = me->query_skill("cuixin-zhang", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也許是缺乏實戰經驗，你對經書上面所説的東西總是無法領會。\n");
            else write("你研讀着有關催心掌的技巧，似乎有些心得。\n");
            me->improve_skill("cuixin-zhang", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "jiuyin-shenfa":
            my_skill = me->query_skill("jiuyin-shenfa", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德經太淺，不能學到什麼東西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也許是缺乏實戰經驗，你對經書上面所説的東西總是無法領會。\n");
            else write("你研讀着有關九陰身法的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "jiuyin-zhengong":
            my_skill = me->query_skill("jiuyin-zhengong", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德經太淺，不能學到什麼東西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也許是缺乏實戰經驗，你對經書上面所説的東西總是無法領會。\n");
            else write("你研讀着有關九陰真功的技巧，似乎有些心得。\n");
            me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "yinlong-bian":
            my_skill = me->query_skill("yinlong-bian", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            if( my_skill >= me->query_skill("daode-jing",1))
                return notify_fail("你的道德經太淺，不能學到什麼東西。\n");
            else
            if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
                return notify_fail("也許是缺乏實戰經驗，你對經書上面所説的東西總是無法領會。\n");
            else write("你研讀着有關九陰銀龍鞭的技巧，似乎有些心得。\n");
            me->improve_skill("yinlong-bian", ((int)me->query_skill("literate", 1)/5+1) );
            me->add("neili", -cost * 2);
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
         case "daode-jing":
            my_skill = me->query_skill("daode-jing", 1);
            if( my_skill >= 180)
                return notify_fail("你覺得這經書上所寫的已經太淺了，不能學到什麼東西。\n");
            write("你研讀着道德經，似乎有些心得。\n");
            me->improve_skill("daode-jing", ((int)me->query_skill("literate", 1)/5+5) );
            me->receive_damage("jing", cost );
            me->add("potential", - random(2));
            break;
       }
       return 1;
}

