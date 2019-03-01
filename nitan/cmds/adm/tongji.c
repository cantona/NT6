// tongji.c

#include <ansi.h>

inherit F_CLEAN_UP;

int sort_skill(object a, object b, string str);
int main(object me, string str)
{
        object *players;
        object *users;
        int j;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;                      

        if (! str)
                return notify_fail("你要統計什麼技能？\n");

        if (file_size("/kungfu/skill/" + str + ".c") == -1)
                return notify_fail("沒有這個技能存在！\n");                

        // users = all_interactive();
        users = users();

        j = 0;
        write(HIW "\n以下為本 MUD 中掌握 " + HIM + CHINESE_D->chinese(str) + HIW + " 的在線玩家。\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        players = ({});
        foreach (object player in users)
        {
                if (player->query_skill(str, 1))
                {
                        players += ({ player });
/*
                        write(sprintf(HIC "%-21s年齡：%-10d所屬門派：%-16s等級：%-10d\n" NOR,
                                      player->name()+"("+query("id", player)+")",
                                      query("age", player),
                                      query("family/family_name", player),
                                      player->query_skill(str, 1)));
                        j ++;
*/
                }
         
        }

        players = sort_array(players, (: sort_skill :), str);    
        foreach (object player in players)
        {
                if (player->query_skill(str, 1))
                {
                        write(sprintf(HIC "%-21s年齡：%-10d所屬門派：%-16s等級：%-10d\n" NOR,
                                      player->name()+"("+query("id", player)+")",
                                      query("age", player),
                                      query("family/family_name", player),
                                      player->query_skill(str, 1)));
                        j ++;
                }
         
        }
        write(HIW "\n總共 " HIR + j + HIW " 位玩家掌握" + HIM + CHINESE_D->chinese(str) + "\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        return 1;
}

int sort_skill(object a, object b, string str)
{
        return b->query_skill(str, 1) - a->query_skill(str, 1);
}