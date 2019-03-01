// missyu.c
// By haiyan

#include <ansi.h>
inherit NPC;

int over();
int do_end();
int do_stopcai();
void check_time();

int save()
{
        string file;
        file = "/data/npc/missdata";
        return save_object(file);
}

int restore()
{
        string file;
        file = "/data/npc/missdata.o";
        if (file_size(file) > 0)    return restore_object(file);
        else   return 0;
}

void create()
{
        set_name("于小姐", ({ "miss yu", "miss", "yu" }));
        set("gender", "女性");
        set("age", 20);
        set("title", HIG "武林大會" NOR);
        set("nickname", HIY "籌備處秘書" NOR);
        set("str", 25);
        set("con", 25);
        set("spi", 25);
        set("dex", 25);
        set("int", 25);
        set("per", 30);
        set("long", "她是一個很精明能幹的人。\n");
        set("combat_exp", 1000000);
        set("class", "fighter");
        set("attitude", "herosim");
        set("shop_id","beijing");

        set("giftyx", 300);
        set("giftwx", 300);

        set("inquiry", ([
                "彩票" : "彩票十兩白銀一張。",
        ]));

        restore();

        if (clonep(this_object()))
        {
               set("chat_chance", 100);
               set("chat_msg", ({ (: check_time :) }));
               keep_heart_beat();
        }

        setup();
        carry_object("/clone/cloth/female3-cloth")->wear();
        carry_object("/clone/cloth/female-shoe")->wear();
}

void init()
{
        object ob = this_player();

        add_action("do_baoming", "baoming");

        if (ob && wiz_level(ob) > 3)
        {
                add_action("do_start", "start");
                add_action("do_chakan", "chakan");
                add_action("do_finish", "finish");
        }
}

void die()
{       
        return;
}

void unconcious()
{
        die();
}

int do_start()
{
        object me = this_player();
        int times;

        if (query("start_baoming"))
                return notify_fail(HIY "報名進程已經開放了。\n" NOR);

        set("start_baoming", 1);
        set("y_start", 1);
        set("caipiao", 0);
        set("bm_time", time());
        set("c_time", time());
        times = (int)query("bisai_times") + 1;
        set("bisai_times", times);
        set("wizard",query("id", me));
        save();
        tell_object(me, HIY "報名進程啟動成功，現在開放報名。\n" NOR);
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：好消息！華夏第" + chinese_number(times) + "屆武林大會即將召開，" +
                "各路武林高手踴躍報名，競奪武林五絕！\n" NOR,
                 all_interactive());
        return 1;
}

int do_end()
{
        int n = query("bisai_times");

        set("start_baoming", 0);
        set("caipiao", 1);
        set("cp_time", time());
        save();
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：華夏第" + chinese_number(n) + "屆武林大會報名已" +
                "經結束，有獎競猜活動正式開始！發財良機，不容錯失！\n" NOR,
                 all_interactive());
        return 1;       
}

int do_stopcai()
{
        int n = query("bisai_times");

        set("caipiao_end", 1);
        set("caipiao", 0);
        delete("bm_time");
        delete("cp_time");
        delete("c_time");
        save();
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：華夏第" + chinese_number(n) + "屆武林大會正式召開。\n" NOR,
                 all_interactive());
        return 1;
}

int do_finish()
{
        int n = query("bisai_times");
        int i, yx = 0, wx = 0;
        int *win, sp, x, y, r;
        object ob;
        mapping caipiao, winner;
        string *player;
        string *cpwxwin = ({}), *cpyxwin = ({});
        string *par, msg = "";

        if (! query("y_start"))
               return notify_fail(HIY "比武大會進程並沒有啟動。\n" NOR);

        if( query("wizard") != query("id", this_player()) )
               return notify_fail(HIY "只能由主持比武大會的巫師才能結束。\n" NOR);

        winner=query("winner", this_player());
        if (! mapp(winner))
              return notify_fail(HIY "你還沒有名次數據，不能結束！\n" NOR);

        tell_object(this_player(), HIY "第" + chinese_number(n) +
                    "屆比賽宣布結束。\n" NOR);

        caipiao = query("xuancp");
        if (! mapp(caipiao))
        {
              tell_object(this_player(), HIY "沒有人參加競猜活動。\n" NOR);
              message("vision", HIW "【武林盛會】" + this_object()->name() +
                      "：本屆比武大會沒有人參加彩票競猜活動。\n" NOR,
                      all_interactive());

              over();
              return 1;
        }

        player = keys(caipiao);
        win = keys(winner);
        par = values(winner);

        for (x = 0; x < sizeof(win); x++)
        {
             for (y = x + 1; y < sizeof(win); y++)
             {
                  if (win[x] > win[y])
                  {
                        r = win[x];
                        win[x] = win[y];
                        win[y] = r;
                  }
             }
        }

        for (i = 0; i < sizeof(player); i++)
        {
            if (caipiao[player[i]][0] == "有序")
            {
                 yx ++;
                 if (caipiao[player[i]][1] == winner[win[0]] &&
                     caipiao[player[i]][2] == winner[win[1]] &&
                     caipiao[player[i]][3] == winner[win[2]] &&
                     caipiao[player[i]][4] == winner[win[3]] &&
                     caipiao[player[i]][5] == winner[win[4]])
                     cpyxwin += ({ player[i] });
            } else
            {
                 wx ++;
                 if (member_array(caipiao[player[i]][1], par) != -1 &&
                     member_array(caipiao[player[i]][2], par) != -1 &&
                     member_array(caipiao[player[i]][3], par) != -1 &&
                     member_array(caipiao[player[i]][4], par) != -1 &&
                     member_array(caipiao[player[i]][5], par) != -1)
                     cpwxwin += ({ player[i] });
            }
        }

        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：華夏第" + chinese_number(n) + "屆武林大會共收到有效彩票" +
                chinese_number(sizeof(player)) + "張。\n" NOR, all_interactive());
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：其中，有序玩法" + chinese_number(yx) + "張，無序玩法" +
                chinese_number(wx) + "張。\n" NOR, all_interactive());

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：本屆彩票競猜無人中獎，獎池金共" +
                chinese_number(query("giftyx") + query("giftwx")) +
                "兩黃金均滾入下屆。\n" NOR, all_interactive());
                addn("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);
                addn("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);
                over();
                return 1;
        }

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) != 0)
        {
                message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：有序玩法無人中獎，獎池金" + chinese_number(query("giftyx")) +
                "兩黃金滾入下屆。\n" NOR, all_interactive());
                addn("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);

                sp = query("giftwx") / sizeof(cpwxwin);
                if (sp < 1)  sp = 1;

                message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：無序玩法共有" + chinese_number(sizeof(cpwxwin)) +
                "人中獎，單注獎金" + chinese_number(sp) + "兩黃金，已存" +
                "入中獎人帳號。\n" NOR, all_interactive());

                for (i = 0; i < sizeof(cpwxwin); i++)
                {
                      ob = find_player(cpwxwin[i]);
                      if (objectp(ob))
                      {
                          addn("balance", sp*10000, ob);
                          command("tell"+query("id", ob)+"恭喜中獎！"+
                                  "您的獎金" + chinese_number(sp) + "兩黃金已存入"
                                  "您的帳號了。");
                      }
                }
                over();
                return 1;
        }

        if (sizeof(cpyxwin) != 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：無序玩法無人中獎，獎池金" + chinese_number(query("giftwx")) +
                "兩黃金滾入下屆。\n" NOR, all_interactive());
                addn("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);

                sp = query("giftyx") / sizeof(cpyxwin);
                if (sp < 1)  sp = 1;

                for (i = 0; i < sizeof(cpyxwin); i++)
                {
                      ob = find_player(cpyxwin[i]);
                      if (objectp(ob))
                      {
                           addn("balance", sp*10000, ob);
                           command("tell"+query("id", ob)+"恭喜中獎！"+
                                   "您的獎金" + chinese_number(sp) + "兩黃金" +
                                   "已存入您的帳號了。");
                           msg+=query("name", ob)+"("+query("id", ob)+")"+",";
                      }  else   msg += cpyxwin[i] + ",";
                }

                message("vision", HIW "【武林盛會】" + this_object()->name() +
                        "：有序玩法中獎人名單：" + msg[0..strlen(msg)-2] + "。\n" NOR,
                        all_interactive());
                message("vision", HIW "【武林盛會】" + this_object()->name() +
                        "：單注獎金" + chinese_number(sp) + "兩黃金，已存入中獎人" +
                        "帳號，恭喜！\n" NOR, all_interactive());
                over();
                return 1;
        }

        sp = query("giftwx") / sizeof(cpwxwin);
        if (sp < 1)  sp = 1;

        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：無序玩法共有" + chinese_number(sizeof(cpwxwin)) +
                "人中獎，單注獎金" + chinese_number(sp) + "兩黃金，已存" +
                "入中獎人帳號。\n" NOR, all_interactive());

        for (i = 0; i < sizeof(cpwxwin); i++)
        {
              ob = find_player(cpwxwin[i]);
              if (objectp(ob))
              {
                   addn("balance", sp*10000, ob);
                   command("tell"+query("id", ob)+"恭喜中獎！"+
                           "您的獎金" + chinese_number(sp) + "兩黃金" +
                           "已存入您的帳號了。");
              }
        }

        sp = query("giftyx") / sizeof(cpyxwin);
        if (sp < 1)  sp = 1;

        for (i = 0; i < sizeof(cpyxwin); i++)
        {
              ob = find_player(cpyxwin[i]);
              if (objectp(ob))
              {
                    addn("balance", sp*10000, ob);
                    command("tell"+query("id", ob)+"恭喜中獎！"+
                            "您的獎金" + chinese_number(sp) + "兩黃金" +
                            "已存入您的帳號了。");
                    msg+=query("name", ob)+"("+query("id", ob)+")"+",";
              }  else   msg += cpyxwin[i] + ",";
        }

        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：有序玩法中獎人名單：" + msg[0..strlen(msg)-2] + "。\n" NOR,
                all_interactive());
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：單注獎金" + chinese_number(sp) + "兩黃金，已存入中獎人" +
                "帳號，恭喜！\n" NOR, all_interactive());
        over();
        return 1;
}

int do_baoming(string arg)
{
        object me = this_player();
        int mca, mcb;
        string ipn, msg;
        mapping baoming_list;

        if( query("combat_exp", me)<500000 )
             return notify_fail("于小姐白了你一眼：就你這兩下子，去搬個凳子坐在擂台下看看算了。\n");

        if (! query("start_baoming"))
        {
             if (query("caipiao"))
             {
                   command("say 這位" + RANK_D->query_respect(me) +
                           "你來晚了，報名時間已過，不如買張彩票玩玩吧。");
                   return 1;
             }
             if (query("caipiao_end"))
             {
                   command("say 比武大會已經開始，你只有等下次再來了。");
                   return 1;
             }
             command("say 這位" + RANK_D->query_respect(me) +
                     "別著急呀，還沒有到武林大會召開的時間呢。");
             return 1;
        }

        if (! arg || sscanf(arg, "%d %d", mca, mcb) != 2)
        {
             msg = "指令格式：baoming <欲參賽的名次一> <欲參賽的名次二>\n";
             msg += "說明：每個ID可以參加兩個名次的角逐。\n例如：你想參加";
             msg += "第一名和第三名的比賽，則打入 baoming 1 3\n";
             me->start_more(msg);
             return 1;
        }

        if (mca < 1 || mca > 5 || mcb < 1 || mcb > 5)
        {
             command("?"+query("id", me));
             command("say 你到底要參加第幾名的比賽呀？");
             return 1;
        }

        if (query("baoming") &&
            member_array(query("id", me),keys(query("baoming"))) != -1 )
        {
             command("say 這位" + RANK_D->query_respect(me) +
                     "，你已經報過名了，快去準備準備吧。");
             return 1;
        }

        ipn = query_ip_number(me);
        if (!query("baoming"))  baoming_list = ([]);
        else baoming_list = query("baoming");
        baoming_list+=([query("id", me):({mca,mcb,ipn})]);
        set("baoming", baoming_list);
        save();
        tell_object(me, HIY "您報名參加第" + chinese_number(mca) +
                    "名和第" + chinese_number(mcb) + "名的比賽，祝你成功！\n"NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        object piao;
        mapping cai, bm;
        string *xs;
        int i;

        if( query("money_id", ob) )
        {
              if (query("caipiao"))
              {
                   if (ob->value() >= 1000 )
                   {
                         bm = query("baoming");
                         xs = keys(bm);
                         for (i = 0; i < sizeof(xs); i++)
                         {
                              if (bm[xs[i]][2] == query_ip_number(me))
                              {
                                   tell_object(me, "于小姐對你道：你的IP" +
                                       "有人參加比賽，你不能參與競猜。\n");
                                   return 0;
                              }
                         }
                         piao = new(__DIR__"obj/piao");
                         set("baoming", query("baoming"), piao);
                         piao->move(me);
                         message_vision("于小姐撕下一張彩票遞給$N。\n", me);
                         destruct(ob);
                         return 1;
                   } else
                   {
                         command("say 才給這麼點錢？你也太窮酸了吧。");
                         return 0;
                   }
              }

              if (query("start_baoming"))
              {
                   command("say 現在正在報名中，等報名結束才能賣彩票。");
                   return 0;
              }

              if (query("caipiao_end"))
              {
                   command("say 比武大會已經開始了，你等下次吧。");
                   return 0;
              }

              command("say 現在不出售彩票，等比武大會開始報完名後再來買吧。");
              return 0;
        }

        if( query("id", ob) == "caipiao" )
        {
              if( !query("done", ob) )
              {
                    command("say 這張彩票什麼也沒填，填好了再給我吧。");
                    return 0;
              }

              if (query("caipiao_end"))
              {
                    command("say 比武大會已經開始，你這張彩票作廢了。");
                    message_vision("$N接過$n的彩票幾下撕成了碎片。\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              if (! query("caipiao"))
              {
                    command("say 你這張彩票已經過期作廢了。");
                    message_vision("$N接過$n的彩票幾下撕成了碎片。\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              bm = query("baoming");
              xs = keys(bm);
              for (i = 0; i < sizeof(xs); i++)
              {
                   if (bm[xs[i]][2] == query_ip_number(me))
                   {
                        tell_object(me, "于小姐對你道：你的IP" +
                                    "有人參加比賽，你不能參與競猜。\n");
                        return 0;
                   }
              }

              if (!query("xuancp"))  cai = ([]);
              else
              {
                   cai = query("xuancp");
                   if( member_array(query("id", me),keys(cai)) != -1 )
                   {
                         tell_object(me, "你已經投過注了。\n");
                         return 0;
                   }
              }
              cai+=query("array", ob);
              set("xuancp", cai);
              save();
              destruct(ob);
              command("say 祝你好運！");
              return 1;
        }
        return 0;
}

int do_chakan()
{
        mapping bm;
        string *rs, msg = "\n";
        int i, j;

        bm = query("baoming");
        if (! mapp(bm))
             return notify_fail(HIY "現在沒有人報名。\n" NOR);

        rs = keys(bm);
        for (i = 1; i <= 5; i++)
        {
             msg += "參加第" + chinese_number(i) + "名比賽的有：\n";
             for (j = 0; j < sizeof(rs); j++)
             {
                  if (bm[rs[j]][0] == i || bm[rs[j]][1] == i)
                       msg += rs[j] + " ";
             }
             msg += "\n\n";
        }
        this_player()->start_more(HIY + msg + NOR);
        return 1;
}

int over()
{
        int n = query("bisai_times");
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：下屆有序玩法獎池金為：" + chinese_number(query("giftyx")) +
                "兩黃金；無序玩法獎池金為：" + chinese_number(query("giftwx")) +
                "兩黃金。\n" NOR, all_interactive());
        message("vision", HIW "【武林盛會】" + this_object()->name() +
                "：熱烈祝賀華夏第" + chinese_number(n) + "屆武林大會圓滿結束"
                "。\n" NOR, all_interactive());
        set("caipiao", 0);
        set("y_start", 0);
        delete("xuancp");
        delete("winner");
        delete("baoming");
        delete("wizard");
        delete("caipiao_end");
        save();
        delete("winner", this_player());
        return 1;
}

void check_time()
{
        int n, tm;

        n = query("bisai_times");
        if (query("c_time") && (time() - query("c_time") >= 300))
        {
              if (query("start_baoming"))
              {
                    if (query("bm_time") && (time() - query("bm_time") < 82800))
                    {
                        message("vision", HIW "【武林盛會】" + this_object()->name() +
                        "：華夏第" + chinese_number(n) + "屆武林大會即將召開，" +
                        "各路武林高手已開始踴躍報名，競奪武林五絕！\n" NOR,
                        all_interactive());
                    }  else
                    if (query("bm_time") && (time() - query("bm_time") >= 82800) &&
                       (time() - query("bm_time") < 86400))
                    {
                        tm = 86400 - (time() - query("bm_time"));
                        if (tm >= 300)  tm /= 60;
                        else tm = 5;

                        message("vision", HIW "【武林盛會】" +
                                this_object()->name() + "：距第" +
                                chinese_number(n) + "屆武林大會報" +
                                "名結束時間還剩" + chinese_number(tm) +
                                "分鐘！\n" NOR, all_interactive());
                    }  else   do_end();

                    set("c_time", time());
                    save();
                    return;
              }

              if (query("caipiao"))
              {
                    if (query("cp_time") && (time() - query("cp_time") < 5400))
                    {
                        if (random(3) > 0)
                            message("vision", HIW "【武林盛會】" + this_object()->name() +
                            "：華夏第" + chinese_number(n) + "屆武林大會報名已" +
                            "經結束，有獎競猜活動正在舉行！發財良機，不容錯失！\n" NOR,
                            all_interactive());
                        else
                            message("vision", HIW "【武林盛會】" + this_object()->name() +
                                    "：本屆武林大會獎池金額為：有序玩法" +
                                    chinese_number(query("giftyx")) +
                                    "兩黃金；無序玩法" + chinese_number(query("giftyx")) +
                                    "兩黃金。\n" NOR, all_interactive());
                    }  else
                    if (query("cp_time") && (time() - query("cp_time") >= 5400) &&
                       (time() - query("cp_time") < 7200))
                    {
                        tm = 7200 - (time() - query("cp_time"));
                        if (tm >= 300)   tm /= 60;
                        else  tm = 5;

                        message("vision", HIW "【武林盛會】" +
                                this_object()->name() + "：還有" +
                                chinese_number(tm) + "分鐘，第" +
                                chinese_number(n) + "屆武林大會將" +
                                "正式召開！\n" NOR, all_interactive());
                    }  else   do_stopcai();

                    set("c_time", time());
                    save();
                    return;
              }
        }
        return;
}

void reset()
{
        restore();
}
