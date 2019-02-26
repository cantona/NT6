// shengjingdan.c 生精丹

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
        set_name(HIG"凌霄生精丹"NOR, ({"shengjing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "一顆碧綠色的丹藥。此乃全真異寶。\n");
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
        int taoism_limit, jingli_limit;
        object me = this_player();

        taoism_limit = me->query_skill("taoism", 1)*10;
        jingli_limit=query("max_jingli", me);
        
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if ( (int)me->query_condition("quanzhen_drug" ) > 0 )
                return notify_fail("你是否才煉丹藥或才服食了丹藥？你的全身氣血未歸位，不宜吃丹藥。\n");

        if ( me->query_skill_mapped("force") != "xiantian-qigong" )
        {
                addn("max_jingli", -10, me);
                message_vision(HIR "$N吃下一顆凌霄生精丹，只覺得腹痛如攪，全身如被抽氣般的空虛。原來此丹不適你所練內功，結果大損真元！\n" NOR, me);
                me->start_busy(10);
        }
        else
        {
                me->start_busy(2);
                if ( jingli_limit <= taoism_limit  )
                {
                        addn("max_jingli", 1, me);
                        message_vision(HIG "$N吃下一顆凌霄生精丹，只覺得體內精力源源滋生，全身頓時覺得舒暢無比！\n" NOR, me);
                }
                else
                        message_vision(HIG "$N吃下一顆凌霄生精丹，也沒覺得有什麼感覺。\n" NOR, me);

                me->apply_condition("quanzhen_drug", 50);
        }
        destruct(this_object());
        return 1;
}
