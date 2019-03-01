// This program is a part of NT MudLIB

#include <ansi.h>
#define BATTLEFIELD2_D    "/adm/daemons/battlefieldd2.c"

inherit F_CLEAN_UP;

int help(object me)
{
        write(@HELP
戰場指令，可以報名與離開戰場

fbattle info                          - 顯示目前戰爭資訊
fbattle join                          - 報名參加下一場次的戰場
fbattle cancel                        - 取消報名

HELP );
        return 1;
}

int main(object me, string arg)
{
        switch(arg)
        {
                case "info":
                {
                        string msg;
                        string *players = BATTLEFIELD2_D->get_sorted_players();
                        string score = "";
                        string ppl = "";
                        int count = 0;
                        
                        msg = "目前共 "+sizeof(players)+" 位玩家參與戰爭，"+(member_array(me->query_id(1), players)==-1?"你未參與戰爭":"你是其中之一")+"。\n";
                                                
                        if( sizeof(players) > 0 )
                        {
                                object player;
                
                                foreach(string id in players)
                                {
                                        if( !objectp(player = find_player(id)) )
                                                continue;
                        
                                        if( ++count <= 3 )
                                                score += player->query_idname()+"、";
                                        
                                        ppl += player->query_idname()+NOR"("+BATTLEFIELD2_D->get_player_score(id)+")、";
                                        if( count % 5 == 0 )
                                                ppl += "\n";
                                                                                                      
                                }
                                
                                msg += "參與者戰績統計：\n"+ppl[0..<3]+"。\n";
                                
                                msg += "目前戰爭績分排名前三名為："+score[0..<3]+"。\n";
                        }
                        
                        tell_object(me, msg);
                        break;
                }
                case "join":
                        BATTLEFIELD2_D->join_battle(me);
                        break;
                case "cancel":
                        BATTLEFIELD2_D->cancel_battle(me);
                        break;
                default:
                        tell_object(me, "請輸入正確的指令格式(help fbattle)。\n");
                        break;
        }
        return 1;
}
