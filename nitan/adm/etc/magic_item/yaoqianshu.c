// 上古十大神器之 搖錢樹 
// 可使用三次
// Create by Rcwiz for Hero.cn 2003/08

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "搖錢樹" NOR, ({ "yaoqian shu", "yaoqian", "shu" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");               
                set("long", NOR + YEL "這是一顆搖錢樹，有半人高，樹支上掛滿了各種\n"
                                      "金銀銅錢。\n"
                                      "可以將樹上的錢幣搖(yao)下來。\n" NOR);                
        }
        setup();
}

void init()
{
        add_action("do_yao", "yao");
}

int do_yao(string arg)
{
        object me, g;
        int i;
        
        me = this_player();
        
        if(! objectp(present("yaoqian shu", me)))return 0;

        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
       
        if (this_object()->query("count") >= 3)
                 return notify_fail("這顆搖錢樹已經不能再搖出任何東西了！\n");

         message_sort(NOR + YEL + "\n$N" NOR + YEL "雙手抱着搖錢樹使勁的搖動着，"
                      "一時間，金銀元寶紛紛落在地上，金光閃閃，令人砰然心動。\n" NOR, me);

        i = 500 + random(500);
        g = new("/clone/money/gold");
        g->set_amount(i);
        g->move(environment(me));

        this_object()->add("count", 1);
        if (this_object()->query("count") >= 3)
        {
                tell_object(me, HIG "伴隨着一道光芒化過，搖錢樹鑽入地下，消失了！\n" NOR);
                destruct(this_object());
        }
        
        return 1;
}
