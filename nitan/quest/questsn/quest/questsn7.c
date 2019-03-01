#include <ansi.h>
#define QUESTSN_D(x)      ("/quest/questsn/quest/questsn" + x)

mapping query_quest() 
{
        mapping questsn;
        if (random(50) > 35)
                questsn = QUESTSN_D("7find")->query_questsn();
        else if (random(2) == 1)
                questsn = QUESTSN_D("7find")->query_questsn();
        else
        questsn = QUESTSN_D("7kill")->query_questsn();
        if (questsn["type"] == "尋") 
        {
                if (random(5) == 3)
                {
                        questsn["type"] = "送";
                        questsn["name"] = "回執";
                }
        } 
        return questsn;
}
