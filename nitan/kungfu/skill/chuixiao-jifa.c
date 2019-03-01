#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if( query("int", me)<24 && me->query_int()<35 )
                return notify_fail("就你那悟性？五音不全，學什麼吹簫？\n");

        return 1;
}

int play(object me, object ob, string arg)
{
        int lvl;
        int i;
        string m_name;

        if (! arg)
                return notify_fail("你要吹什麼曲子？\n");

        if (! (lvl = me->query_skill(arg, 1)))
                return notify_fail("你不會吹這首曲子。\n");

        if (! SKILL_D(arg)->valid_enable("chuixiao-jifa"))
                return notify_fail("這也能當簫曲吹麼？\n");

        lvl += me->query_skill("chuixiao-jifa", 1) / 2;
        m_name = to_chinese(arg);

        if (me->is_busy())
                return notify_fail("你現在正忙，等會兒再吹簫吧。\n");

        if (lvl < 15)
        {
                message_vision(WHT "\n$N" WHT "鼓足氣吹了一下$n" WHT "，結果只"
                               "是發出幾下刺耳的嗚嗚聲。\n" NOR, me, ob);
        } else
        if (lvl < 30)
        {
                message_vision(WHT "\n$N" WHT "鼓足氣吹了一下$n" WHT "，發出幾"
                               "聲怪響，難聽的一塌糊塗。\n" NOR, me, ob);
        } else
        if (lvl < 60)
        {
                message_vision(WHT "\n$N" WHT "拿起$n" WHT "輕輕吹了幾聲，聲音"
                               "還算馬馬虎虎，不太難聽。\n" NOR, me, ob);
        } else
        if (lvl < 90)
        {
                message_vision(HIW "\n$N" HIW "拿起$n" HIW "吹了一首" + m_name +
                               HIW "，韻律洋洋洒洒，頗為不錯。\n" NOR, me, ob);
        } else
        if (lvl < 150)
        {
                message_vision(HIW "\n$N" HIW "拿起$n" HIW "吹了一首" + m_name +
                               HIW "，頗為動人，引人入勝。\n" NOR, me, ob);
        } else
        if (lvl < 225)
        {
                message_vision(HIW "\n$N" HIW "拿起$n" HIW "吹了一首" + m_name +
                               HIW "，聽得眾人感慨萬千，甚是投入。\n" NOR, me,
                               ob);
        } else
        if (lvl < 300)
        {
                message_vision(HIC "\n$N" HIC "拿起$n" HIC "吹了一首" + m_name +
                               HIC "，簫音如夢如幻，似乎有一股清香直沁心脾。\n"
                               NOR, me, ob);
        } else
        {
                message_vision(HIG "\n$N" HIG "拿起$n" HIG "吹了一首" + m_name +
                               HIG "，若哀若思，猶如身臨其境，忽悲忽喜，又如乘"
                               "風而行，不知蹤影。\n" NOR, me, ob);
        }
        me->start_busy(3 + random(3));

        SKILL_D(arg)->do_effect(me);
        return 1;
}