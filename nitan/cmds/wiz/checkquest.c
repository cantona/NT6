// checkquest.c
// Smallfish@Huaxia

#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);

int main(object who, string arg)
{
        object me,ob;
        mapping q,quest;
        string master,msg;
        int tag_fam = 0;
        int flag_zs = 0;
        int flag_bh = 0;

        if (! SECURITY_D->valid_grant(who, "(wizard)"))
                return 0;

        if (!arg) return notify_fail("指令格式：checkquest <ID>\n");
        if (!(me = find_player(arg))) return notify_fail(arg + "這個人並不在線啊！\n");

        write(HIY+"檢查對象："+HIW+me->name(1)+"("+query("id", me)+")"+NOR+"\n\n");

        write(HIR + "幫會任務系統：\n" + NOR);
        if( query_temp("finish_bunch_times", me) )
                write(sprintf("頭兒交給你的任務，你已經連續完成了 %d 個。\n",
                       query_temp("finish_bunch_times", me)));

        msg = "";
             if( mapp(quest=query("bunch_quest", me)) )
         {
                flag_bh = 1;
                msg = quest["type"] + "：" + quest["msg"];
                write("你剛才領的任務：\n"+msg+"\n");
         }

        if (!flag_bh) write("你目前沒有從幫會那裡接任務！\n");

        write(HIR + "\n門派任務系統：\n" + NOR);
        if( query("quest_count", me) )
                write(sprintf("師長交給你的任務，你已經連續完成了 %d 個。\n",
                       query("quest_count", me)));
 
        if( mapp(q=query("quest", me)) )
        {
                 switch (q["type"])
                { 
                  case "kill":
                        write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前割下" HIR + q["name"] + NOR "的人頭，回" + q["family"] + "交差。\n" +
                      "據說此人前不久曾經在" + q["place"] + "出沒。\n");
                      tag_fam = 1;
                      break;
                case "letter":
                      write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前把信件送到" HIC + q["name"] + NOR "手中，取回執交差。\n" +
                      "據聞不久前此人曾經在" + q["place"] + "。\n");
                      tag_fam = 1;
                      break;
                }
        }
        if (!tag_fam) write("你現在沒有領任何門派任務！\n");
        
        write(HIR + "\n宗師任務系統：\n" + NOR);

         if( query_temp("questdg_times", me) )
                     write("獨孤求敗交給你的任務，你已連續完成"+query_temp("questdg_times", me)+"個了。\n");
         if( query_temp("questkh_times", me) )
                     write("葵花太監交給你的任務，你已連續完成"+query_temp("questkh_times", me)+"個了。\n");
        if( query_temp("questsn_times", me) )
                     write("南海神尼交給你的任務，你已連續完成"+query_temp("questsn_times", me)+"個了。\n");;
        if( query_temp("quesths_times", me) )
                 write("黃裳交給你的任務，你已連續完成"+query_temp("quesths_times", me)+"個了。\n");

        msg = "";
        // 獨孤求敗
         if( mapp(quest=query("quest_dg", me)) )
         {
                flag_zs = 1;
                msg = quest["dgmsg"];
                write("你剛才領的任務："+msg+"\n");
         }

         msg = "";
        // 東方不敗
        if( mapp(quest=query("quest_kh", me)) )
         {
                flag_zs = 1;
                        msg = quest["khmsg"];
                if (quest["desc"] == "滅")
                           if(quest["time"] < time())
                                     msg += "\n你已經超過了規定時間了！";
                             else
                                            msg += "\n你還有"+time_period(quest["time"]-time())+"的時間。";
                write("你剛才領的任務："+msg+"\n");
         }

        msg = "";
        // 黃裳
         if( mapp(quest=query("quest_hs", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "收")
                {
                                     msg += "\n你已經完成了" + quest["ok"] + "個，";
                                            msg += "\n你還需要找" + (quest["want"] - quest["ok"]) + "個。";
                }
                write("你剛才領的任務："+msg+"\n");
         }

        msg = "";
        // 南海神尼
         if( mapp(quest=query("quest_sn", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "收")
                {
                                     msg += "\n你已經完成了" + quest["ok"] + "個，";
                                            msg += "\n你還需要找" + (quest["want"] - quest["ok"]) + "個。";
                }
                write("你剛才領的任務："+msg+"\n");
         }

        if (!flag_zs) write("你目前沒有從任何宗師那裡接任務！\n");
        return 1;
}

string time_period(int timep)
{
   int t, d, h, m, s;
   string time;
   t = timep;
   s = t % 60;             t /= 60;
   m = t % 60;             t /= 60;
   h = t % 24;             t /= 24;
   d = t;
 
   if(d) time = chinese_number(d) + "天";
   else time = "";
 
   if(h) time += chinese_number(h) + "小時";
   if(m) time += chinese_number(m) + "分";
   time += chinese_number(s) + "秒";
   return time;
}

int help(object me)
{
        write(@HELP
指令格式 : checkquest  <ID>
這個指令可以用來查詢某個玩家從所在門派的掌門或
世家長輩領取任務以及從宗師那裡領取得任務。

HELP );
        return 1;
}