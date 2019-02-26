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
        set_name(HIW "何氏壁" NOR, ({"heshi bi", "heshi", "bi"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一塊晶瑩剔透的寶玉，其中一角鑲嵌着一塊黃\n"
                                "金，寶玉上雕刻着盤龍，這便是傳説可以號令\n"
                                "天下的何氏壁。相傳寶玉中藴藏着奇異的能源，\n"
                                "武功高強者可以吸取(xi)其中的能量來增強功\n"
                                "力。\n" NOR);
                set("value", 3000000);
                set("unit", "塊");
                set("item_origin", 1);
                set("material_attrib", "heshi bi");
                set("material_name", HIW "何氏壁" NOR);
                set("can_make", "all");
                set("not_make", ({ "鞭", "甲"}));
                set("power_point", 80);
        }
}

int do_eat(string arg)
{
        object ob;
        object me = this_player();

        if (!id(arg))
                return notify_fail("你要幹什麼？\n");

        if( me->is_busy() )
                return notify_fail("你現在正忙着呢。\n");

        if( me->query("power/何氏壁") )
                return notify_fail("你已經吸取過一次了，恐怕不能再次經受能量的衝擊。\n");

        message_vision (HIW "\n$N" HIW "將雙手緊緊貼住何氏壁一側，"
                        "只見一股白色光芒從寶玉中澎湃而出，奪目"
                        "的光華將四周照射得一片明亮。\n" NOR, me);
        me->start_busy(60);
        remove_call_out("xiqu1");
        call_out("xiqu1", 5, me);
        return 1;
}

void xiqu1(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n只見一股光芒從何氏壁中流入$N" HIW
                       "的身子……\n" NOR, me);
        remove_call_out("xiqu2");
        call_out("xiqu2", 4, me);
}

void xiqu2(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n幾許後，又一股光芒從$N" HIW "的身"
                       "體裏流出，進入何氏壁……\n" NOR, me);
        remove_call_out("xiqu3");
        call_out("xiqu3", 4, me);
}

void xiqu3(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n過了一會兒，又是一股光芒從何氏壁"
                       "中慢慢流出，流入了$N" HIW "的身體……\n"
                       NOR, me);
        remove_call_out("xiqu4");
        call_out("xiqu4", 4, me);
}

void xiqu4(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n隨即又見一股光芒從$N" HIW "的身體"
                       "轉入何氏壁……\n" NOR, me);
        remove_call_out("xiqu5");
        call_out("xiqu5", 4, me);
}

void xiqu5(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIW "\n剎那間光華暴漲，光芒又從何氏壁"
                       "中流到$N" HIW "的身體……\n" NOR, me);
        remove_call_out("xiqu6");
        call_out("xiqu6", 4, me);
}

void xiqu6(string arg)
{
        object ob;
        object me = this_player();

        message_vision(HIY "\n只見$N" HIY "和何氏壁同時發出無"
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
          && (int)me->query_skill("force") > 330)
        {
                message_vision(HIC "\n光華稍退，猶見$N" HIC "全身晶瑩"
                               "剔透，竟發出寶石光澤，似乎已和何氏壁"
                               "合為一體了。\n\n" NOR, me);

                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("max_neili", li1);
                me->add("max_jingli", li2);
                if (me->query("potential") > me->query_potential_limit()) 
                me->set("potential", me->query_potential_limit());

                tell_object(me, HIY "你感到何氏壁中的能量源源不絕的流"
                                "入了你的丹田，全身暖洋洋的，説不出的"
                                "舒服受用。\n" NOR); 

                me->improve_skill("force", 20000);
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
                me->set("power/何氏壁", 1);

                tell_object(me, HIC "你獲得了" + chinese_number(exp) +
                                "點經驗、" + chinese_number(pot) + "點"
                                "潛能、" + chinese_number(li1) + "點最"
                                "大內力和\n" + chinese_number(li2) + "點"
                                "最大精力。\n" NOR);
        } else
        {
                message_vision(HIR "\n只聽$N" HIR "一聲慘叫，經受不住能"
                               "量的衝擊，頓時全身筋脈盡斷，鮮血狂噴，身"
                               "體被炸了個粉碎。\n" NOR, me);
                me->set_temp("die_reason", "妄圖吸取何氏壁，結果全身筋脈盡斷而亡。");
                me->die(); 
        }
        message_vision (WHT "\n何氏壁上的光華漸漸消逝，變成了一"
                        "堆粉末。\n" NOR, me);
        destruct(this_object());
        return 0;
}

