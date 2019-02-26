// team command: kill

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object env;
        object obj;
        object tob;
        object *t;
        int i;

        // team kill 命令使用的標誌
        int kill_flag;
        int want_kill_flag;

        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("你這個隊伍中現在"
                                   "沒有別人，想出手就直接下KILL命令吧。\n");

        if (! me->is_team_leader())
                return notify_fail("只有隊伍的領袖才能下命令攻擊別人。\n");

        if (! arg)
                return notify_fail("你想率領隊伍攻擊誰？\n");

        env = environment(me);
        t = filter_array(t, (: objectp($1) && living($1) &&
                               environment($1) == $(env) :));
        if (! sizeof(t))
                return notify_fail("你這個隊伍中現在"
                                   "沒有人能夠聽你的號令，還是靠自己吧。\n");

        if( query("no_fight", env) )
                return notify_fail("這裏不能戰鬥。\n");

        if (! objectp(obj = present(arg, env)))
                return notify_fail("你想攻擊誰？\n");

        if (! obj->is_character() || obj->is_corpse())
                return notify_fail("看清楚了，那不是活人！\n");

        if (obj == me)
                return notify_fail("什麼？你要自殺也不要叫上這麼多人啊！\n");

        if (member_array(obj, me->query_team()) != -1)
                return notify_fail("你想攻擊隊伍中的人？好像沒人會聽你的話。\n");

        if (query_temp("warquest/group", obj) && query("qi", obj) > query("max_qi", obj) )
                return notify_fail("你想率領幾個人的隊伍攻擊軍隊？恐怕不行吧！\n");

        if( query("can_speak", obj) )
        {
                if (random(3) > 1)
                        message_vision("\n$N大聲喊道：“大家上啊，對付" + obj->name() +
                                       "這種人不必講究什麼江湖道義！”\n\n",
                                       me, obj);
                else
                        message_vision("\n$N扯着嗓子喊道：“大家並肩"
                                       "子上啊！一起除掉" + obj->name() +
                                       "這" + RANK_D->query_rude(obj) +
                                       "！”\n\n", me, obj);
        } else
                message_vision("\n$N一揮手，喝道：“滅了這畜生！”\n\n",
                               me, obj);

        switch (obj->accept_kill(me))
        {
        case 0:
                return (! objectp(obj));
        case -1:
                if (objectp(obj) &&
                    !me->is_killing(query("id", obj)) )
                {
                        // 因為某種原因戰鬥沒有發生
                        return 1;
                }
        default:
        }

        // 戰鬥已經發生，隊伍中所有的人蔘與戰鬥
        message("vision", HIR "你和大家一起跟着" + me->name(1) +
                          HIR "衝了上去，圍着" + obj->name() +
                          "就是一頓亂砍。\n" NOR, t, ({ me }));

        // 判斷是否是我先主動想殺死對方
        if (userp(me) && userp(obj))
        {
                // 對方想殺害的人和我們對我中的成員
                string *obj_wants;
                object *all_team;
                object *ts;

                // 重新取隊伍的人員 - 因為隊伍中暈倒的成員
                // 沒有包含在 t 數組中。
                all_team = me->query_team();
                all_team -= ({ 0 });
                obj_wants = obj->query_want() - ({ 0 });
                ts = ({});
                for( i=0; i<sizeof(t); i++ )
                        ts += ({ query("id", t[i]) });
                if (sizeof(obj_wants - ts) != sizeof(obj_wants))
                {
                        // 對方想殺害我們對我中的某一些人，
                        // 因此認為是對方想殺害我們，否則
                        // 反之
                        want_kill_flag = 0;
                } else
                {
                        me->want_kill(obj);
                        want_kill_flag = 1;
                }
        }

        // 判斷對方是否會殺死我
        if (living(obj) && ! userp(obj))
        {
                // 對方會殺死我們
                obj->kill_ob(me);
                kill_flag = 1;
        } else
        {
                // 對方不會殺死我們，只是攻擊我們
                obj->fight_ob(me);
                kill_flag = 0;
        }

        // 驅動隊伍中所有的人
        foreach (tob in t)
        {
                // 殺人方向和隊長保持一致：如果對方
                // 主動攻擊隊伍中的某一個人，則設置
                // 是對方挑釁
                if (want_kill_flag)
                        tob->want_kill(obj);

                tob->kill_ob(obj);

                // 設置對手的攻擊狀態和隊長保持一致
                if (kill_flag)
                        obj->kill_ob(tob);
                else
                        obj->fight_ob(tob);
        }

        return 1;
}
