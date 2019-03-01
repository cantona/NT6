// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string  msg;
        mapping ss;
        string  skill;
        object ob;
        string pro;
        int i;
        string tmp_msg;

        if (wizardp(me) && stringp(arg) &&
            objectp(ob = find_player(arg)))
                // 查看其他玩家的特殊技能
                arg = 0;
        else
                ob = me;

        pro = (ob == me) ? "你" : ob->name(1);

        if( !query("born", ob) )
                return notify_fail(pro + "還沒有出生吶，會什麼特技？\n");

        if( !mapp(ss=query("special_skill", ob)) || 
            ! sizeof(ss))
                return notify_fail(pro + "現在好像什麼特技都不會哦。\n");

        if (arg && (ob == me))
        {
                // 有參數，運用特技。
                if (me->is_busy())
                        return notify_fail("你現在忙著呢，不能使用特技。\n");

                if (sscanf(arg, "%s %s", skill, arg) != 2)
                        skill = arg;

                if( !query("special_skill/"+skill, me) )
                        return notify_fail("你不會這種特技啊！\n");

                if (file_size(SPECIAL_D(skill) + ".c") < 0 
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                        return notify_fail("好像沒有這種特技...\n");

                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                          return ("/kungfu/special2/" + skill)->perform(me, skill, arg);

                return SPECIAL_D(skill)->perform(me, skill, arg);
        }

        msg = pro + "現在會以下這些特技：\n";
        i = 1;
        foreach (skill in keys(ss))
        {
                if (file_size(SPECIAL_D(skill) + ".c") < 0
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                {
                        write("不存在技能：" + skill + "\n");
                        continue;
                }
                // 如果大于7個則每行顯示四個                                
                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")";
                                msg += sprintf("%-58s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")\n";
                        }
                }

                else
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")";
                                msg += sprintf("%-58s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
                        }
                }
                
                i += 1;
                
        }
        write(msg + "\n");
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : special <skill> | <玩家ID>

使用這條命令可以查看你的特技，如果要運用你的特技，則可以加上
參數指名使用什麼特技。比如：special hatred，運用殺氣。

巫師可以查看其他玩家所會的特殊技能。

HELP );
    return 1;
}
