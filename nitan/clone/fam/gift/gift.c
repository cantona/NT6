#include <ansi.h>
inherit COMBINED_ITEM;

string query_autoload()
{
        return query_amount() + "";
}

void create()
{
        set_name(HIY "仙丹" NOR, ({ "gift" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一顆增加容貌的仙丹。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);

                // 增加天賦的種類
                set("gift_type", "per");

                // 天賦種類的名稱
                set("gift_name", "容貌");

                // 成功的機率
                set("gift_point", 100);

                // 成功的描述
                set("gift_msg", HIC "突然間你的皮膚透過一道光澤。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        int point;

        point = query("gift_point");

        // 真命天子提升成功機率
        if( query("special_skills/emperor", me) )
                point += 35;

        // 天煞孤星提升成功機率
        if( query("special_skills/lonely", me) )
                point += 10;

        // 福星高照提升成功機率
        if( query("special_skill/lucky", me) )
                point += 5;

        message_vision(WHT "$N" WHT "一仰脖，吞下了一" +
                       query("base_unit") + name() + WHT
                       "。\n" NOR, me);

        if( query("gift/" + query("gift_type") + "/all", me) >= 1 ||
            query("gift/" + query("gift_type") + "/succeed", me) >= 6 )
        {
                tell_object(me, "你覺得這藥好像沒什麼效果。\n");
        } else
        if (random(100) >= point)
        {
                tell_object(me, HIR "不過你覺得這藥好像沒起到什麼"
                                "作用。\n" NOR);

                // 記錄失敗的記號
                addn("gift/"+query("gift_type")+"/fail", 1, me);
        } else
        {
                tell_object(me, query("gift_msg"));
                tell_object(me, HIC "你的" + query("gift_name") +
                                HIC "永久增加一點。\n" NOR);

                // 記錄成功的記號
                addn("gift/"+query("gift_type")+"/succeed", 1, me);

                // 增加相應的天賦屬性
                addn(query("gift_type"), 1, me);
        }

        // 記錄入吃丹的總量
        /*
        if( !query("gift/" + query("gift_type") + "/all", me) ) 
                addn("gift/"+query("gift_type")+"/all", 1, me);
        */

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

void autoload(string param)
{
        int amt;

        if (sscanf(param, "%d", amt) == 1)
                set_amount(amt);
}

void setup()
{
        set_amount(1);
        ::setup();
}
