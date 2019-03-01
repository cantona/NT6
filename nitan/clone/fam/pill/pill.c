#include <ansi.h>
inherit COMBINED_ITEM;

string query_autoload()
{
        return query_amount() + "";
}

void create()
{
        set_name(HIY "補藥" NOR, ({ "pill" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一顆增加內功的補藥。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);

                // 增加技能的種類
                set("pill_skill", "force");

                // 是否為特殊武功
                set("skill_mapped", 1);

                // 技能的增加效果
                set("pill_point", 20000);

                // 功力的增加效果
                set("force_point", 3);

                // 服用成功的描述
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出"
                                 "的舒服受用。\n" NOR);

                // 服用失敗的描述
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了"
                                 "完全的補充。\n" NOR);

                // 增加功力的描述，如果有前面兩條信息，則應作缺省
                set("pill_msg3", HIM "你感到內力又雄厚了一些。\n" NOR);
                set("pill_msg4", HIR "你感到內息澎湃，難以吸收藥力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        string skill;
        int pot1, pot2, time;
        mapping my = me->query_entire_dbase();

        pot1 = query("pill_point");
        pot2 = query("force_point");
        time = query("pill_point") / 100;

        // 非技能型的藥物重新計算效用時間
        if (! query("pill_point"))
                time = 40 + query("force_point");

        // 本草知識增加藥物效果
        if( query("special_skill/herb", me) )
        {
                pot1 += pot1 / 2;
                pot2 += pot2 / 2;
                time -= time / 2;
        }

        if ((int)me->query_condition("pill_drug") > 0)
        {
                write("你覺得現在內息未定，經脈隱隱還能感到真氣"
                      "沖盪，不敢貿然服食。\n");
                return 1;
        }

        // 增加藥物效用時間，該時段裡不能再次服用
        me->apply_condition("pill_drug", time);

        message_vision(HIY "$N" HIY "服下一" + query("base_unit") +
                       name() + HIY "，急忙開始運功吸收藥力。\n"
                       NOR, me);

        // 如果該藥物有增加技能的功能，則加之
        if (query("pill_skill") && query("pill_point"))
        {
                // 判斷增加的技能是否為特殊技能
                if (query("skill_mapped") >= 1)
                        skill = me->query_skill_mapped(query("pill_skill"));
                else
                        skill = query("pill_skill");

                // 可以增加該技能
                if (stringp(skill) && me->can_improve_skill(skill))
                {
                        tell_object(me, query("pill_msg1"));
                        me->improve_skill(skill, pot1);
                } else
                        tell_object(me, query("pill_msg2"));
        }


        // 如果該藥物有增加功力的功能，則加之
        if (query("pill_skill") && query("force_point"))
        {
                // 內功型藥物增加內力，否則則增加精力
                if (query("pill_skill") == "force")
                {
                        // 提供出信息
                        if( query("max_neili", me)<me->query_neili_limit( )
                           && query("pill_msg3"))
                                tell_object(me, query("pill_msg3"));
                        else
                        if( query("max_neili", me) >= me->query_neili_limit( )
                           && query("pill_msg4"))
                                tell_object(me, query("pill_msg4"));

                        me->improve_neili(pot2 + random(pot2));

                        if( query("neili", me)<query("max_neili", me) )
                                my["neili"]  = my["max_neili"];
                } else
                {
                        // 提供出信息
                        if( query("max_jingli", me)<me->query_jingli_limit( )
                           && query("pill_msg3"))
                                tell_object(me, query("pill_msg3"));
                        else
                        if( query("max_jingli", me) >= me->query_jingli_limit( )
                           && query("pill_msg4"))
                                tell_object(me, query("pill_msg4"));

                        me->improve_jingli(pot2 + random(pot2));

                        if( query("jingli", me)<query("max_jingli", me) )
                                my["jingli"]  = my["max_jingli"];
                }
        }
        me->start_busy(random(3) + 3);

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