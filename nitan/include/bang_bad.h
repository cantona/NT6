void init()
{
        add_action("do_look","look");
        add_action("do_type","type");
}

int do_look(string arg)
{
        int i;
        string msg;
        mapping *bunch_quest,*bunch_zs;

        if (!arg || arg != "paizi")
                return 0;

        if( time()-query_temp("last_look_paizi", this_player())<2 )
        {
                tell_object(this_player(), "別擠，大家都要看！你剛看過了，等一下再看吧！\n");
                return 1;
        }

        bunch_zs = PARTY_QUEST_D->query_zhuisha_quest(TYPE);
        bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE);
        bunch_zs = sort_array(bunch_zs,(: sort_by_id :));
        bunch_quest = sort_array(bunch_quest,(: sort_by_id :));

        msg = HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  追殺令                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"編號","任務","難度","獎勵");
        if (sizeof(bunch_zs))
                for (i=0;i<sizeof(bunch_zs);i++)
                        msg += sprintf("%-10s%-50s%-10s%s\n",
                                          bunch_zs[i]["id"],
                                          "追殺"+bunch_zs[i]["name"],
                                          bunch_zs[i]["difficult"],
                                          bunch_zs[i]["reward"],
                                      );
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  任務表                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"編號","任務","難度","獎勵");
        if (sizeof(bunch_quest))
                for (i=0;i<sizeof(bunch_quest);i++)
                {
                        if (bunch_quest[i]["id"] == "xc" && !bunch_quest[i]["enable"]) continue;
                        msg += sprintf("%-10s%" + sprintf("%d", (50 + color_len(bunch_quest[i]["name"]))) + "-s%-10s%s\n",
                                          bunch_quest[i]["id"],
                                          bunch_quest[i]["name"],
                                          bunch_quest[i]["difficult"],
                                          bunch_quest[i]["reward"],
                                      );
                }
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += HIC "請用type <編號>查看每個任務的具體情況。\n"NOR;
        msg += HIC "請用choose <編號>選擇你要完成的任務，放棄任務用giveup指令。\n"NOR;

        set_temp("last_look_paizi", time(), this_player());
        this_player()->start_more(msg);
        return 1;
}

int do_type(string arg)
{
        string msg;
        mapping bunch_quest;

        if (!wizardp(this_player()) &&  
            (good_bunch(this_player()) || query("shen", this_player())>0) )
                return notify_fail("你一個正派人士到這裏來查什麼任務？\n");

        if (!wizardp(this_player()) && ! bad_bunch(this_player()))
                return notify_fail("你先加入黑道聯盟，才可以查看黑道的任務。\n");

        if (!arg) 
                return notify_fail("你想查看哪條任務的詳細信息？指令：type <編號>\n");

        bunch_quest = PARTY_QUEST_D->query_zhuisha_quest(TYPE,arg);

        if (!bunch_quest)     
                bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE,arg);

        if (!bunch_quest)
                return notify_fail("你所查詢的編號為"+arg+"的任務並不存在。\n");
        
        if (bunch_quest["id"] == "xc" && !bunch_quest["enable"]) 
                return notify_fail("今天已經有弟兄去巡城了，你等改天吧。\n");

        msg = HIC "\n----------------------------------------------------------------------------\n"NOR;
        msg += "任務編號：" + bunch_quest["id"] + "\n";
        msg += "任務類型：" + bunch_quest["type"] + "\n";
        msg += "任務名稱：" + bunch_quest["name"] + "\n";
        msg += "任務難度：" + bunch_quest["difficult"] + "\n";
        msg += "任務獎勵：" + bunch_quest["reward"] + "\n";
        msg += "任務信息: \n" + bunch_quest["msg"] + "\n";
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        this_player()->start_more(msg);
        return 1;
}

int sort_by_id(mapping quest1, mapping quest2)
{
          return strcmp(quest1["id"], quest2["id"]);
}