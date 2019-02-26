// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);

int main(object me, string arg)
{
        object ob,env;
        mapping q,quest;
        string master,msg,*place;
        int tag_fam = 0;
        int flag_zs = 0;
        int flag_bh = 0;
        int i;

        while (arg)
        {
                if (arg == "cancel")
                {
                        if( !stringp(master=query("quest/master_id", me)) )
                                return notify_fail("有人向你下任務了嗎？\n");

                        if (! objectp(ob = present(master, environment(me))))
                                return notify_fail("給你下任務的那個人現在不在這裏吧？\n");
                } else
                if (! objectp(ob = present(arg, environment(me))))
                        return notify_fail("這裏沒有這個人，你怎麼領任務？\n");

                if (! living(ob))
                        return notify_fail("你還是等" + ob->name() +
                                           "醒了再説吧！\n");

                if (me->is_fighting())
                        return notify_fail("專心打你的架！\n");

                if (me->is_busy())
                        return notify_fail("你還是有空了再和" + ob->name() +
                                           "談這些問題吧！\n");

                if (ob->is_fighting())
                        return notify_fail("你還是等" + ob->name() +
                                           "打完架再説吧！\n");

                if (ob->is_busy())
                        return notify_fail(ob->name() +
                                           "正忙着呢，沒功夫理你。\n");

                notify_fail(ob->name() + "望着你呵呵的傻笑。\n");
                return (arg == "cancel" ? ob->cancel_quest(me)
                                        : ob->ask_quest(me));
        }
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
                if (quest["id"] == "xc")
                {
                        place = ({});
                        place = quest["place"];
                        if (sizeof(place))
                        {
                                msg = "你還需要巡邏這些地方：";
                                for (i = 0;i < sizeof(place);i++)
                                {
                                        env = get_object(place[i]);
                                        msg += env->short() + " ";
                                }
                                write(msg + "\n");
                        } else write("你可以回去交差了！\n");
                }
         }

        if (!flag_bh) write("你目前沒有從幫會那裏接任務！\n");

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
                      "據説此人前不久曾經在" + q["place"] + "出沒。\n");
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

        if( query("questdg_times", me) )
                     write("獨孤求敗交給你的任務，你已連續完成"+query("questdg_times", me)+"個了。\n");
        if( query("questkh_times", me) )
                     write("葵花太監交給你的任務，你已連續完成"+query("questkh_times", me)+"個了。\n");
        if( query("questsn_times", me) )
                     write("南海神尼交給你的任務，你已連續完成"+query("questsn_times", me)+"個了。\n");;
        if( query("quesths_times", me) )
                 write("黃裳交給你的任務，你已連續完成"+query("quesths_times", me)+"個了。\n");

        msg = "";
        // 獨孤求敗
         if( mapp(quest=query("quest_dg", me)) )
         {
                flag_zs = 1;
                msg = quest["dgmsg"];
                write("你剛才領的任務：\n"+msg+"\n");
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
                write("你剛才領的任務：\n"+msg+"\n");
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
                write("你剛才領的任務：\n"+msg+"\n");
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
                write("你剛才領的任務：\n"+msg+"\n");
         }

        if (!flag_zs) write("你目前沒有從任何宗師那裏接任務！\n");
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
指令格式 : quest  這個指令可以用來向你的門派的掌門或世家長輩
領取任務，如果不加任何參數則顯示出你當前的任務。

從宗師那裏領取任務只需要到宗師所在地方輸入quest，不需要加任何
參數。

HELP );
        return 1;
}