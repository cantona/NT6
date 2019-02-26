#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if( query("int", me)<24 && me->query_int()<35 )
                return notify_fail("就你那悟性？五音不全，學什麼彈琴？\n");

        return 1;
}

int play(object me, object ob, string arg)
{
        int lvl;
        int i;
        string m_name;

        if (! arg)
                return notify_fail("你要彈什麼曲子？\n");

        if (! (lvl = me->query_skill(arg, 1)))
                return notify_fail("你不會彈這首曲子。\n");

        if (! SKILL_D(arg)->valid_enable("tanqin-jifa"))
                return notify_fail("這不能用來彈奏。\n");

        lvl += me->query_skill("tanqin-jifa", 1) / 2;
        m_name = to_chinese(arg);

        if (me->is_busy())
                return notify_fail("你現在正忙，等會兒再彈琴吧。\n");

        if (lvl < 15)
        {
                message_vision(WHT "\n$N" WHT "胡亂撥了撥$n" WHT "，結果只是發"
                               "出了幾下刺耳的雜音。\n" NOR, me, ob);
        } else
        if (lvl < 30)
        {
                message_vision(WHT "\n$N" WHT "撥拉了一下$n" WHT "，發出幾聲怪"
                               "響，難聽的一塌糊塗。\n" NOR, me, ob);
        } else
        if (lvl < 60)
        {
                message_vision(WHT "\n$N" WHT "擺好$n" WHT "輕輕彈了幾下，聲音"
                               "還算清脆，不太難聽。\n" NOR, me, ob);
        } else
        if (lvl < 90)
        {
                message_vision(HIW "\n$N" HIW "擺好$n" HIW "彈了一首" + m_name +
                               HIW "，韻律洋洋灑灑，頗為不錯。\n" NOR, me, ob);
        } else
        if (lvl < 150)
        {
                message_vision(HIW "\n$N" HIW "擺好$n" HIW "彈了一首" + m_name +
                               HIW "，頗為動人，引人入勝。\n" NOR, me, ob);
        } else
        if (lvl < 225)
        {
                message_vision(HIW "\n$N" HIW "擺好$n" HIW "彈了一首" + m_name +
                               HIW "，聽得眾人感慨萬千，甚是投入。\n" NOR, me,
                               ob);
        } else
        if (lvl < 300)
        {
                message_vision(HIC "\n$N" HIC "擺好$n" HIC "彈了一首" + m_name +
                               HIC "，琴音宛若溪水蕩流，怡然陶趣，雅緻萬千。\n"
                               NOR, me, ob);
        } else
        {
                message_vision(HIG "\n$N" HIG "擺好$n" HIG "彈了一首" + m_name +
                               HIG "，宛若清溪流上心頭，令人無酒自醉，卻又似身"
                               "至仙境，心靈空明。\n" NOR, me, ob);
        }
        me->start_busy(3 + random(3));

        SKILL_D(arg)->do_effect(me);
        return 1;
}