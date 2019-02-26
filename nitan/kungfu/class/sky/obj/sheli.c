#include <ansi.h> 
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "xi");
}

void create()
{
        set_name(CYN "魔尊舍利" NOR, ({"mozun sheli", "sheli"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", CYN "一個渾圓的暗色球體，通體透明。這便是傳説\n"
                            "中的魔教至寶——魔尊舍利。相傳其中藴藏着\n"
                            "無比巨大的能量，武功高強者可以吸取(xi)其\n"
                            "中的能量來增強功力。\n" NOR);
                set("value", 1000000);
        }
        setup();
}

int do_eat(string arg)
{
        object ob;
        object me = this_player();

        if (!id(arg))
                return notify_fail("你要幹什麼？\n");

        if( me->is_busy() )
                return notify_fail("你現在正忙着呢。\n");

        if( me->query("power/魔尊舍利") )
                return notify_fail("你已經吸取過一次了，恐怕不能再次經受能量的衝擊。\n");

        message_vision (HIY "\n$N" HIY "將雙手緊緊貼住魔尊舍利，"
                        "只見一股光芒從中透出，甚至可以看到能"
                        "量在兩者間奔流竄動。\n" NOR, me);
        me->start_busy(60);
        remove_call_out("xiqu1");
        call_out("xiqu1", 5, me);
        return 1;
}

void xiqu1(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIB "\n只見一股光芒從魔尊舍利中流入$N" HIB
                       "的身子……\n" NOR, me);
        remove_call_out("xiqu2");
        call_out("xiqu2", 4, me);
}

void xiqu2(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIY "\n幾許後，又一股光芒從$N" HIY "的身"
                       "體裏流出，進入魔尊舍利……\n" NOR, me);
        remove_call_out("xiqu3");
        call_out("xiqu3", 4, me);
}

void xiqu3(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIR "\n過了一會兒，又是一股光芒從魔尊舍利"
                       "中慢慢流出，流入了$N" HIR "的身體……\n"
                       NOR, me);
        remove_call_out("xiqu4");
        call_out("xiqu4", 4, me);
}

void xiqu4(string arg)
{
        object ob;
        object me = this_player();

        message_vision(MAG "\n隨即又見一股光芒從$N" MAG "的身體"
                       "轉入魔尊舍利……\n" NOR, me);
        remove_call_out("xiqu5");
        call_out("xiqu5", 4, me);
}

void xiqu5(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIM "\n剎那間光華暴漲，光芒又從魔尊舍利"
                       "中流到$N" HIM "的身體……\n" NOR, me);
        remove_call_out("xiqu6");
        call_out("xiqu6", 4, me);
}

void xiqu6(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n只見$N" HIW "和舍利同時發出無"
                        "比耀眼的光華。剎那間空氣熾熱，幾欲"
                        "沸騰，彷彿連天地都快被燒焦一般……\n" NOR, me);
        remove_call_out("xiqu7");
        call_out("xiqu7", 2, me);
}

void xiqu7(string arg)
{
        object ob;
        object me = this_player();
        int exp, pot, li1, li2, max;

        exp = 30000 + random(10000);
        pot = 5000 + random(3000);
        li1 = 300 + random(100);
        li2 = 300 + random(100);

        if ( me->query("max_neili") > 5000
          && me->query("max_jingli") > 1200
          && me->query("combat_exp") > 2000000
          && (int)me->query_skill("force") > 330
          && me->query("power/何氏壁") )
        {
                message_vision(HIW "\n光華稍退，猶見$N" HIW "全身晶瑩"
                               "剔透，竟發出寶石光澤，似乎已和魔尊舍利"
                               "合為一體了。\n\n" NOR, me);

                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("max_neili", li1);
                me->add("max_jingli", li2);
                if (me->query("potential") > me->query_potential_limit()) 
                me->set("potential", me->query_potential_limit());

                tell_object(me, HIY "你感到魔尊舍利中的能量源源不絕的流"
                                "入了你的丹田，頓時有一陣説不出的舒服。\n"
                                NOR);

                max = me->query("max_qi");
                me->set("eff_qi", max);
                me->set("qi", max);
                max = me->query("max_jing");
                me->set("eff_jing", max);
                me->set("jing", max);
                me->set("neili", me->query("max_neili"));
                me->set("jingli", me->query("max_jingli"));

                max = me->max_food_capacity();
                me->set("food", max);
                max = me->max_water_capacity();  
                me->set("water", max);
                me->clear_condition();
                me->set("power/魔尊舍利", 1);

                tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗、" + chinese_number(pot) + "點"
                                "潛能、" + chinese_number(li1) + "點最"
                                "大內力和" + chinese_number(li2) + "點"
                                "最\n大精力。\n" NOR);
        } else
        {
                message_vision(HIR "\n只聽$N" HIR "一聲慘叫，經受不住能"
                               "量的衝擊，頓時全身筋脈盡斷，鮮血狂噴，身"
                               "體被炸了個粉碎。\n" NOR, me);
                me->set_temp("die_reason", "妄圖吸取魔尊舍利，結果全身筋脈盡斷而亡。");
                me->die(); 
        }
        message_vision (WHT "\n魔尊舍利上的光華漸漸消逝，變成了一"
                        "堆粉末。\n" NOR, me);
        destruct(this_object());
        return 0;
}

