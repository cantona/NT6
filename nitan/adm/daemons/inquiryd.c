#include <ansi.h>

int parse_inquiry(object me, object ob, string topic)
{
        switch (topic)
        {
        case "name":
                message_vision(CYN "$N" CYN "向$n" CYN "問道：敢問" +
                               RANK_D->query_respect(ob) + "尊姓大"
                               "名？\n" NOR, me, ob);
                return 1;

        case "here":
                message_vision(CYN "$N" CYN "向$n" CYN "問道：這位" +
                               RANK_D->query_respect(ob) + "，" +
                               RANK_D->query_self(me) + "初到貴寶地"
                               "，不知這裏有些什麼風土人情？\n" NOR,
                               me, ob);
                return 1;
        
        case "all":
                message_vision(CYN "$N" CYN "向$n" CYN "問道：這位" + 
                               RANK_D->query_respect(ob) + 
                               "，你都知道些什麼事情呀？\n" NOR, 
                               me, ob);
                return 1;
                        
        case "clue":
        case "線索":
                message_vision(CYN "$N" CYN "向$n" CYN "打聽道：" +
                               RANK_D->query_self(me) + "從旁人處得"
                               "知" + RANK_D->query_respect(ob) +
                               "有些線索，能否告知在下？\n" NOR, me, ob);
                return 1;

        case "rumor":
        case "rumors":
        case "消息":
                message_vision(CYN "$N" CYN "向$n" CYN "問道：這位" +
                               RANK_D->query_respect(ob) + "，不知"
                               "最近有沒有聽説什麼消息？\n" NOR, me,
                               ob);
                return 1;

        case "marry":
                message_vision(CYN "$N眯着一雙賊眼，不懷好意的向$n"+ 
                               CYN"問道：敢問這位"+RANK_D->query_respect(ob) +
                               "是否婚配？\n" NOR,me,ob);
                return 1;
        
        case "food":
                message_vision(CYN "$N可憐兮兮的向$n"+CYN"問道：“不知這位"+
                               RANK_D->query_respect(ob) +
                               "是否能給我點吃的, 在下已經三天沒有進食了？”\n" NOR,
                               me,ob);
                return 1;
        
        case "water":
                message_vision(CYN "$N可憐兮兮的向$n"+CYN"問道：“不知這位"+
                               RANK_D->query_respect(ob) +
                               "是否能給我點喝的, 在下口渴得很？”\n" NOR,
                               me,ob);
                return 1;
        
        case "money":
                message_vision(CYN "$N雙手抱拳向$n"+CYN"問道：“在下初來咋到，行走江湖缺了些盤纏,這位"+
                               RANK_D->query_respect(ob) +
                               "是否能施捨一二, 在下不甚感激？”\n" NOR,
                               me,ob);
                return 1;
                
        case "friend":
                message_vision(CYN "$N雙手抱拳向$n"+CYN"説道：“四海之內皆兄弟也,這位"+
                               RANK_D->query_respect(ob) +
                               ",不知願否與在下交個朋友”\n" NOR,
                               me,ob);
                return 1;
                
        default:
                return 0;
        }
}