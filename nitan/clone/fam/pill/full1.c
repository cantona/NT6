#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(NOR + YEL "活骨靈藥" NOR, ({ "huogu lingyao", "huogu", "lingyao", "yao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一粒燦金色的藥丸，在武林中被喻為是療傷聖藥。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 10000);
                set("base_weight", 55);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;
        mapping my;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(full, me)")<240 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(full)", time(), me);

        message_vision(HIY "$N" HIY "吞下一" + un + na + HIY "，再也感覺"
                       "不到任何疲憊。\n" NOR, me);

        my["jing"]   = my["max_jing"];
        my["qi"]     = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];

        me->start_busy(5);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}