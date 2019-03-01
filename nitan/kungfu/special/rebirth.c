// rebirth.c 六道輪回

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "六道輪回" NOR; }
#define HUI "「" HIR "六道輪回" NOR "」"

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage;

        if (! me->is_fighting())
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        target = me->select_opponent();

        if (! target || ! target->is_character()
            || query("not_living", target) )
                return notify_fail("你打算對誰施展" HUI  "？\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" HUI "。\n");

        wn = weapon->name();

        message_combatd(HIW "$N" HIW "面露拈花之意，祭起手中" + wn +
                        HIW "，霎時碧波流轉，華光萬丈，說不盡的祥和。"
                        "\n" NOR, me, target);

        //  記錄下最初的房間
        if (! objectp(sroom = environment(me)))
                return 1;

        ap = me->query_skill("martial-cognize", 1) +
             me->query_skill("jingyi-shengong", 1);

        dp = target->query_skill("martial-cognize", 1) +
             target->query_skill("jingyi-shengong", 1);

        damage = ap * 10 + random(ap * 10);

        // 六道輪回之人間道
        room = find_object("/d/death/liudaolunhui/rendao");
        if (! room) room = load_object("/d/death/liudaolunhui/rendao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n$N" HIY "左手輕輕一撥，右手所持的" + wn +
                       HIY "叮呤做響，劍姿說不出的瀟洒妙曼。\n" NOR, me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack1, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 六道輪回之畜生道
        room = find_object("/d/death/liudaolunhui/chushengdao");
        if (! room) room = load_object("/d/death/liudaolunhui/chushengdao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n卻見$N" HIY "面無表情，將手中" + wn +
                       HIY "猛的往前一遞，猶如毒蛇般噬向$n" HIY "。\n"
                       NOR, me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack2, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 六道輪回之餓鬼道
        room = find_object("/d/death/liudaolunhui/eguidao");
        if (! room) room = load_object("/d/death/liudaolunhui/eguidao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n$N" HIY "一聲長嘆，左手捏著劍訣，忽聞" +
                       wn + HIY "上血腥之氣漸濃，朝$n" HIY "迎頭斬落。\n"
                       NOR, me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack3, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 六道輪回之修羅道
        room = find_object("/d/death/liudaolunhui/xiuluodao");
        if (! room) room = load_object("/d/death/liudaolunhui/xiuluodao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n忽見$N" HIY "身形微晃，頓時幻出十數個身"
                       "影，十數柄" + wn + HIY "齊向$n" HIY "刺去。"
                       "\n" NOR, me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack4, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 六道輪回之地獄道
        room = find_object("/d/death/liudaolunhui/diyudao");
        if (! room) room = load_object("/d/death/liudaolunhui/diyudao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n緊接著$N" HIY + wn + HIY "一顫，有若龍吟"
                       "，劍身騰起一道滔天寒流，向四周擴散開去。\n" NOR,
                       me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack5, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 六道輪回之天極道
        room = find_object("/d/death/liudaolunhui/tiandao");
        if (! room) room = load_object("/d/death/liudaolunhui/tiandao");

        me->move(room);
        target->move(room);

        message_vision(HIY "\n$N" HIY "身外化身，劍外化劍，手中" + wn +
                       HIY "便似蛟龍騰空，撥雲見日，天地為之失色。\n"
                       NOR, me, target);

        if (ap + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           (: attack6, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收斂心神，奮力招"
                      "架，將劍招卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        me->start_busy(3 + random(3));

        // 為什麼提行？為了畫面更為賞心悅目而已
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

        // 轉移回最初的房間
        me->move(sroom);
        target->move(sroom);

        // 不能通過斷線來保命
        if( query("qi", target)<0 )
                target->die(me);

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "只覺心頭一陣凄苦，竟忍不住要落"
              "下淚來，喉嚨一甜，嘔出一口鮮血。\n" NOR;

        if( !query_temp("liudaolunhui", target) )
        {
                msg += WHT "$p忽然察覺到全身的力氣竟似一絲"
                       "絲遠離自己而去，無助之極。\n" NOR;

                addn_temp("apply/attack", -damage, target);
                addn_temp("apply/parry", -damage, target);
                addn_temp("apply/dodge", -damage, target);
                set_temp("liudaolunhui", 1, target);
        }
        return msg;
}

string attack2(object me, object target, int damage)
{
        object weapon;
        string wn, msg;

        msg = HIR "忽然間$n" HIR "感到胸口處一陣火熱，劍氣"
              "襲體，帶出一蓬血雨。\n" NOR;

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                wn = weapon->name();
                msg += WHT "忽聽「鏘鏘鏘」幾聲脆響，$n" WHT "的" + wn +
                       WHT "竟被$N" WHT "絞成了塊塊碎片。\n" NOR;

                set("consistence", 0, weapon);
                weapon->move(target);
        }
        return msg;
}

string attack3(object me, object target, int damage)
{
        int shd;
        string msg;

        msg = HIR "劍鋒過處，卷起漫天血浪，$n" HIR "只感頭暈目"
              "眩，四肢乏力，難以再戰。\n" NOR;

        if( query_temp("shield", target) )
        {
                shd=query_temp("apply/armor", target);

                addn_temp("apply/armor", -shd, target);
                delete_temp("shield", target);

                msg += WHT "$N" WHT "氣勁湧至，宛若刀割，頓時將$n"
                       WHT "的護體真氣摧毀得盪然無存。\n" NOR;
        }
        return msg;
}

string attack4(object me, object target, int damage)
{
        object cloth, armor;
        string cn, an, msg;

        msg = HIR "$n" HIR "頓時大驚失色，瞬間已被$N" HIR "連中"
              "數劍，直削得血肉模糊。\n" NOR;

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                cn = cloth->name();
                msg += WHT "忽聽轟然聲大作，$n" WHT "身著的" + cn +
                       WHT "在$N" WHT "內力激盪下，竟被震得粉碎。\n"
                       NOR;

                set("consistence", 0, cloth);
                cloth->move(target);
        } else
        if( objectp(armor=query_temp("armor/armor", target)) )
        {
                an = armor->name();
                msg += WHT "忽聽「哧啦」一聲脆響，$n" WHT "身著的" +
                       an + WHT "竟被$N" WHT "震裂，化成塊塊碎片。\n"
                       NOR;

                set("consistence", 0, armor);
                armor->move(target);
        }
        return msg;
}

string attack5(object me, object target, int damage)
{
        string msg;

        msg = HIR "只見$n" HIR "全身一陣抽搐，被劍鋒所攜的極寒氣流"
              "包裹其中，刺痛難當。\n" NOR;

        if (! target->query_condition("poison"))
        {
                target->affect_by("poison",
                        ([ "level"    : damage * 2,
                           "name"     : "煉獄寒燄",
                           "id":query("id", me),
                           "duration" : damage / 20 ]));

                msg += WHT "霎時間$n" WHT "忽覺一股奇寒散入七經八脈"
                       "，仿佛連血液都停止了流動。\n" NOR;
        }
        return msg;
}

string attack6(object me, object target, int damage)
{

        string msg;

        msg = HIR "$N" HIR "劍勢迅猛之極，令$n" HIR "毫無招架余地，"
              "竟鎮怯當場，素手待斃。\n" NOR;

        if( !query_temp("no_exert", target )
            || !query_temp("no_perform", target) )
        {
                set_temp("no_exert", 1, target);
                set_temp("no_perform", 1, target);

                msg += WHT "$n" WHT "只感到全身真氣渙散，丹元瓦解，似"
                       "乎所有的武功竟都消逝殆盡。\n" NOR;
        }
        return msg;
}
