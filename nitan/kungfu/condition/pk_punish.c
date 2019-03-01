int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, "你禁閉完畢，可以離開了！\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "因為" + me->name(1) + "誠心悔過，被解除禁閉了。");
                return 0;
        }
        me->apply_condition("pk_punish", duration - 1);
        return 1;
}
