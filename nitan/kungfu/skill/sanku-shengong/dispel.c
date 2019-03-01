// dispel.c

#include <ansi.h>

int exert(object me, object target)
{
        int i;
        string force_name;
        mapping conditions;

        if( query("neili", me)<300 )
        {
                write("你的內力不足，無法運滿一個周天。\n");
                return 1;
        }

        force_name = to_chinese(me->query_skill_mapped("force"));

        if (me == target)
        {
                message_vision(HIW "$N" HIW "深吸一口氣，又緩緩的吐了出來。\n" NOR, me);
                tell_object(me, YEL "你默運" + force_name +
                            "，開始排除身體中的異常症狀。\n" NOR);
                 addn("neili", -100, me);
        } else
        {
                message_vision(HIW "$N" HIW "深吸一口氣，將手掌粘到$n"
                               HIW "的背後。\n" NOR,
                               me, target);
                tell_object(me, YEL "你默運" + force_name + "，開始幫助" +
                            target->name() + "排除身體中的異常症狀。\n" NOR);
                tell_object(target, YEL + me->name() +
                            "正在運功幫助你排除身體中的異常症狀。\n" NOR);
                addn("neili", -250, me);
        }

        conditions = target->query_condition(); 
        if (conditions)
        {
                target->clear_condition();
                
                tell_object(target, YEL + me->name() + "正在運功將你身體中的異常症狀盡數排除。\n" NOR);
                if (me == target)
                {
                        tell_object(me, WHT "你調息完畢，將內力收回丹"
                                        "田。\n" NOR);
                        me->start_busy(1 + random(2));
                } else
                {
                        tell_object(me, WHT "你調息完畢，將內力收回"
                                        "丹田。\n" NOR);
                        tell_object(target, WHT "你覺得內息一暢，看來是" +
                                            me->name() + "收功了。\n");
                        me->start_busy(2 + random(3));
                        if (! target->is_busy())
                                target->start_busy(1 + random(2));
                        message_vision(WHT "$N將手掌從$n背後收了回"
                                       "來。\n" NOR, me, target);
                }
        }
        else
        {
                if (me == target)
                {
                        tell_object(me, "結果你沒發現自己有任何異常。\n");
                        message_vision(WHT "$N" WHT "眉角微微一動，隨即恢"
                                       "復正常。\n" NOR, me);
                        me->start_busy(1);
                } else
                {
                        tell_object(me, "結果你沒發現" + target->name() +
                                   "有任何異常。\n");
                        tell_object(target, "你覺得內息一暢，看來是" +
                                    me->name() + "收功了，大概你本來沒有什"
                                    "麼異常吧。\n");
                        message_vision(WHT "$N" WHT "將手掌從$n背後收了"
                                       "回來。\n" NOR, me, target);
                        me->start_busy(2);
                        if (! target->is_busy())
                                target->start_busy(1);
                }

        }

        return 1;
}
