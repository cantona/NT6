#include <ansi.h>

void init()
{
        if (! interactive(this_player()))
                return;

        switch (NATURE_D->query_month())
        {
        case 12: case 1: case 2: case 3: case 4: case 5:
                remove_call_out("cold_effect");
                call_out("cold_effect", 4);
                break;
        }
}

void do_cold(object me, int scale, int con)
{
        int damage;
        int hour;
        string msg;

        hour = NATURE_D->query_hour();
        if (! con)
        {
                con = me->query_con();
                con = con / 2 + random(con);
        }
        damage=35-(con+query_temp("apply/warm", me)+query_temp("warm"));
        if( query("born", me) == "關外人氏")damage-=25;
        if (damage < 0) damage = 0;
        if (hour <= 6 || hour >= 18) damage += damage / 2;
        if (hour <= 4 || hour >= 22) damage += damage / 2;
        if (hour >= 11 && hour <= 13) damage -= damage / 2;
        damage *= scale;
        if (damage) me->receive_damage("qi", damage);
        if (damage > 80)
                msg = HIB "一股刺骨的寒風吹過，你只覺得渾身"
                      "的血液都快被凍住了！\n" NOR;
        else if (damage > 60)
                msg = HIB "一股刺骨的寒風吹過，你只覺得渾身"
                      "非常僵硬！\n" NOR;
        else if (damage > 40)
                msg = HIB "一股刺骨的寒風吹過，你只覺得冷氣"
                      "透過衣衫鑽了進來，渾身沒有半點熱氣！\n" NOR;
        else if (damage > 20)
                msg = HIB "一股刺骨的寒風吹過，你只覺得人都"
                      "要麻木了！\n" NOR;
        else if (damage > 10)
                msg = HIB "一股刺骨的寒風吹過，你只覺得天氣"
                      "非常的冷！\n" NOR;
        else if (damage > 0)
                msg = HIB "一股刺骨的寒風吹過，你感覺到有點"
                      "冷！\n" NOR;
        else
                msg = HIC "一股刺骨的寒風吹過，可是你身上還"
                      "是挺暖和的。\n" NOR;

        if( query("qi", me)<50 && damage>10 )
                me->apply_condition("ill_dongshang",
                        me->query_condition("ill_dongshang") + 5 + damage / 3);
        tell_object(me, msg);
}

void cold_effect()
{
        object *ob;
        object cloth;
        int con;
        int damage;
        int i;

        remove_call_out("cold_effect");
        ob = filter_array(all_inventory(), (: userp :));
        if (! sizeof(ob)) return;
        call_out("cold_effect", 4 + random(3));

        for (i = 0; i < sizeof(ob); i++)
        {
                con = ob[i]->query_con();
                con = con / 2 + random(con);
                do_cold(ob[i], 1, con);
        }
}

int valid_leave(object me, string dir)
{
        if (! interactive(me))
                return ::valid_leave(me, dir);

        switch (NATURE_D->query_month())
        {
        case 12: case 1: case 2: case 3: case 4: case 5:
                do_cold(me, 3, 0);
                break;
        }
        return ::valid_leave(me, dir);
}
