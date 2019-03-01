// dingyangdan.c 定陽丹

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"玄門定陽丹"NOR, ({"dingyang dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "一顆火紅色的丹藥。此乃全真異寶。\n");
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_get", 1);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;

        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if ( (int)me->query_condition("quanzhen_drug" ) > 0 )
                return notify_fail("你是否才煉丹藥或才服食了丹藥？你的全身氣血未歸位，不宜吃丹藥。\n");

        if ( me->query_skill_mapped("force") != "xiantian-qigong" )
        {
                addn("max_neili", -10, me);
                message_vision(HIR "$N吃下一顆玄門定陽丹，只覺得腹痛如攪，全身如被抽氣般的空虛。原來此丹不適你所練內功，結果大損真元！\n" NOR, me);
                me->start_busy(10);
                return 1;
        }
        else
        {
                me->start_busy(2);
                if ( neili_limit <= force_limit  )
                {
                        addn("max_neili", 5, me);
                        message_vision(HIG "$N吃下一顆玄門定陽丹，只覺得體內真力源源滋生，過紫宮，入泥丸透十二重樓，遍布奇筋八脈，全身功力頓然提高！\n"NOR,me);
                }
                else
                        message_vision(HIG "$N吃下一顆玄門定陽丹，不過好象沒什麼作用。\n" NOR, me);

                me->apply_condition("quanzhen_drug", 60);
        }
        
        destruct(this_object());
        return 1;
}
