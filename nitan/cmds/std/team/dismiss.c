// team command: dismiss

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;

        if (! pointerp(t = me->query_team()))
                return notify_fail("你現在並沒有參加任何隊伍。\n");

        if (me->is_team_leader())
        {
                message("team", me->name(1) + "將隊伍解散了。\n", t, me);
                write("你將隊伍解散了。\n");
        } else
        {
                message("team", me->name(1) + "決定脫離隊伍。\n", t, me);
                write("你脫離了你的隊伍。\n");
        }

        me->dismiss_team();
        return 1;
}
