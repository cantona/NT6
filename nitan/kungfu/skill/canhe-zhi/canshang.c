
#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "參商劍氣" NOR; }

int perform( object me, object target)
{
        int lvl, str, dex, skill;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("參商劍氣只能對戰鬥中的對手使用！\n");

        if( query_temp("canshang", me) )
                return notify_fail("你已經在使用參商劍氣了！\n");

        if( objectp(query_temp("weapon", me)) )
                        return notify_fail("參商劍氣需要你空手才能施展！\n");

        if( me->query_skill_mapped("finger") != "canhe-zhi" )
                return notify_fail("你所使用的並非參合指，不能施展參商劍氣！\n");

        if( me->query_skill_prepared("finger") != "canhe-zhi" )
                return notify_fail("你所備的並非參合指，不能施展參商劍氣！\n");

        if( me->query_skill_mapped("force") != "shenyuan-gong" )
                return notify_fail("你所激發的內功並非神元功，施展不出參商劍氣！\n");

        if( me->query_skill("force") < 140 )
                return notify_fail("你的內功火候不到，無法施展慕容家傳絕學！\n");

        if( me->query_int() < 22 )
                return notify_fail("你的悟性太差，不能施展姑蘇慕容家傳絕學！\n");

        if( (lvl=me->query_skill("finger")) < 100 )
                return notify_fail("參商劍氣需要精深的指力方能奏效！\n");

        if( query("neili", me) <= lvl*3/2 )
                return notify_fail("你的內力不足以使用慕容絕學參商指法！\n");

        if( query("jingli", me)<lvl )
                return notify_fail("你的精力不足以使用慕容絕學參商指法！\n");

        message_combatd(HIM "$N" HIM "口中默唸“動靜如參商”，心隨意轉，勁跟力發。只聽得內力破空之聲呲呲作響！\n"
                        HIM "內力化作一股劍氣直奔$n" HIM "射去！\n" NOR, me, target);
        str = me->query_str()/2;
        dex = me->query_dex()/3;
        addn_temp("apply/str", str, me);
        addn_temp("apply/dex", dex, me);
        set_temp("canshang", 1, me);

        skill = (me->query_skill("canhe-zhi",1)+me->query_skill("beidou-xianzong" ,1)) / 2;

        me->start_call_out( (: call_other, __FILE__, "end_perform", me, str, dex :),skill/8);

        addn("neili", -lvl, me);
        addn("jingli", -lvl, me);
        return 1;
}

void end_perform( object me, int str, int dex)
{
        addn_temp("apply/str", -str, me);
        addn_temp("apply/dex", -dex, me);
        delete_temp("canshang", me);

        tell_object(me, HIY "你緩緩收住身形，輕籲一口氣，將內力收回丹田。\n" NOR);
}