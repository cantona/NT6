// business.c

inherit F_CLEAN_UP;

#define PAY_MONEY        500000 
nomask int main(object me, string arg)
{
	   int tt;
     string msg;
     if(!find_object(FWAR_D)) return notify_fail("目前搶旗戰尚未開始。\n");
    switch(arg) {
    	case "join":
    		if(!FWAR_D->query_flagwar_data("can_accept")) return notify_fail("本場搶旗戰尚未開放報名。\n");
    		if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) != -1) return notify_fail("你已經報名本場的搶旗戰了。\n");
          switch(MONEY_D->player_pay(me, PAY_MONEY)) {
           case 0:
           case 2:
           	return notify_fail("參加搶旗戰需支付"+MONEY_D->money_str(PAY_MONEY)+"。\n");
           break;
           default:
           if(!FWAR_D->add_player(me, PAY_MONEY)) return notify_fail("報名搶旗戰出現問題，請使用 sos post 回報。\n");
           break;           
           }
    	break;
    	case "leave":
    		// 報名階段
    		if(!FWAR_D->query_flagwar()) {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return notify_fail("你本來就沒有報名搶旗戰。\n");
    			FWAR_D->leave_player(me->query("id"));
    		} else {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return 0;
    			FWAR_D->leave_player(me->query("id"));
    		}
    	break;
    	default:
     if(!FWAR_D->query_flagwar()) {
     	tt = FWAR_D->query_flagwar_time();
      if(tt == -1) return notify_fail("搶旗戰已經在報名階段。\n");
      else if(tt == -2) return notify_fail("搶旗戰正在準備。\n");
     	else return notify_fail("目前搶旗戰尚未開始，距離下次開始還有"+CHINESE_D->chinese_period(tt)+"。\n");
     }
     msg = " "+FWAR_D->query_party_score_total();
     msg += "┌─────────────────────────────────┐\n";
     msg += " "+FWAR_D->query_party_score("red");
     msg += " ────────────────────────────────── \n";
     msg += " "+FWAR_D->query_party_score("blue");
     msg += "└─────────────────────────────────┘\n";
     me->start_more(msg);    		
    	break;
    }
     
     
     
     return 1;
}

int help(object me)
{
        write(@HELP
指令格式：flag score | join | leave

此指令用來查看搶旗戰的狀況。

參數： score : 查看搶旗戰的狀況。
       join  : 報名參加搶旗戰。
       leave : 離開搶旗戰或取消報名。
HELP);
        return 1;
}

