#include <ansi.h> 

int help(object me);
int main(object me, string arg)
{
        object *virlist;
        object ob;
        object eob;
        string str;
        string target;
        int option = 0;
        int amount;
        int i;

        amount = query("flowers/amount", me);
        if( !arg || arg == "" )
        {
                write(HIW "你目前擁有 " + amount + " 張新手導師評價票。\n" NOR);
                if( sizeof(virlist = DB_D->query_data("virlist/teacher")) )
                {
                        str = HIC "\n≡"  + HIM "遊戲中所有在職導師" + HIC + "≡\n" NOR;  
                        for (i = 0; i < sizeof(virlist);i ++) 
                        {
                                if( objectp(eob = find_player(virlist[i])) )
                                {
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ")--在線--"; 
                                        str += HIY "鮮花 " + query("flowers/recognition", eob) + " 朵--"; 
                                        str += HIY "臭雞蛋 " + query("flowers/antipathy", eob) + " 個\n" NOR; 
                                }
                                else
                                {
                                        eob = UPDATE_D->global_find_player(virlist[i]); 
                                        if( !objectp(eob) ) continue; 
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ") --離線時間：" + NOR; 
                                        str += HIY + sprintf("%d", (time() - query("last_on", eob)) / 86400) + "天--";
                                        str += HIY "鮮花 " + query("flowers/recognition", eob) + " 朵--"; 
                                        str += HIY "臭雞蛋 " + query("flowers/antipathy", eob) + " 個\n" NOR; 
                                        UPDATE_D->global_destruct_player(eob, 1); 
                                }
                        }
                        write(str);
                }
                return 1;
        }

        if( amount < 1 )
                return notify_fail(HIW "你目前擁有 0 張新手導師評價票。\n" NOR);

        if( sscanf(arg, "-a %s", target) )
                option = 1;
        else if( sscanf(arg, "-o %s", target) )
                option = 0;
        else
                return help(me);

        if( !objectp(ob = UPDATE_D->global_find_player(target)) ) 
                return notify_fail("沒有這個人！\n"); 

        if( query("viremploy/job", ob) != "新手導師" )
        {
                UPDATE_D->global_destruct_player(ob, 1);
                write("他不是新手導師，你只能給新手導師投評價票。(who -v可查詢新手導師)\n");
                return 1;
        }

        addn("flowers/amount", -1, me);
        if( option )
        {
                addn("flowers/recognition", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "對新手導師" + ob->query_idname()+"的工作表示認可，送上"
                        HIW"一朵"HIY"美麗"HIW"的"HIG"鮮"HIR"花"NOR"。\n");
        }
        else
        {
                addn("flowers/antipathy", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "對新手導師" + ob->query_idname()+"的工作極不滿意，扔給"
                        HIW"一個"HIY"極臭"HIW"的"HIG"臭"HIR"雞蛋"NOR"。\n");
        }

        UPDATE_D->global_destruct_player(ob, 1);  
        return 1; 

}

int help(object me)
{
        write("flowers                 查詢自己擁有新手導師評價票數\n"
              "flowers -a <id>         投給新手導師一張滿意的評價票\n"
              "flowers -o <id>         投給新手導師一張不滿意的評價票\n");
        return 1;
}
