// team.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        string team_cmd;

        if (! arg)
        {
                if (! pointerp(t = me->query_team()))
                        return notify_fail("你現在並沒有參加任何隊伍。\n");
                write(sort_msg("你現在隊伍中的成員有：\n  " +
                      implode(t->short(1), "\n  ") + "。\n"));
                return 1;
        }

        if (sscanf(arg, "%s %s", team_cmd, arg) != 2)
        {
                team_cmd = arg;
                arg = 0;
        }

        team_cmd = __DIR__"team/" + team_cmd + ".c";
        if (file_size(team_cmd) < 0)
                return notify_fail("你要發什麼隊伍命令？\n");

        return team_cmd->main(me, arg);
}

int help(object me)
{
        write( @HELP
隊伍指令使用方法:

team with <某人> - 跟某人組成隊伍. 必須要雙方都同意加入才會生效。
team dismiss     - 離開隊伍. 若下此指令的是領隊, 則整個隊伍會解散。
team talk <訊息> - 跟隊伍裡其他的人談話, 可以用 tt <訊息> 替代。
team form <陣法> - 如果隊伍的領隊學過陣法的話，可以將隊伍中的成員組織成
                   某種陣形，組成陣形的狀態只要領袖一移動就會解除。

team kill <某人> - 只有隊長才能夠下這個命令，隊伍中所有成員同時阻擊某人。
                   在使用到這個命令的時候，如果被阻擊對象預先主動發起攻
                   擊或試圖殺害本隊伍中的某一個成員的話，則隊長發起這個
                   命令以後，所有的成員雖然試圖殺死對方，但是不會被認為
                   是主動PK而招致張三李四的懲罰。這時候如果被阻擊的對象
                   在本次戰鬥中（即沒有停手過）打暈隊伍中的其他人（非原
                   先主動攻擊的玩家）也不會算是主動PK，也就是說你試圖殺
                   隊伍中某一個人而遭到對方的全體反撲的時候，殺絕對方你
                   的PK記錄也只增加一個。
                   另一種情況：如果隊長主動發出命令攻擊對方，則隊伍中所
                   有的成員都被認為是主動發起了攻擊，那麼對方不論打暈誰
                   都不認為是PK，即對方將整個隊伍全部幹掉，也不會遭受懲
                   罰。當然，任何情況下只要殺人官府都會追究。

team swear <名字>- 全隊結義。只有隊長才能夠使用這個命令，如果隊伍中的人
                   意氣相合，想結為兄弟同盟，則可以讓全體人員結義。同時
                   這個團伙將會賦予隊長指定的名字。注意：一個玩家只能加
                   入一個這樣的同盟，但是這並不影響你和其他玩家進行私人
                   之間的結拜。

直接下 team 指令時則會顯示你目前是否有加入隊伍及隊員名單。

注: team 跟 follow 是獨立的，你不一定要 follow 隊伍的領袖就可以跟隨隊長
一起行動。
HELP );
        return 1;
}