int do_ridedl()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_dl = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"中央廣場"NOR,
                HIC"南大街"NOR,
                HIC"南大街"NOR,
                HIC"南門"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"三不管"NOR,
                HIC"大道"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"青石階"NOR,
                HIC"青石階"NOR,
                HIC"青石階"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"南詘德化碑"NOR,
                HIC"太和城"NOR,
                HIC"大理城北"NOR,
                HIC"北門"NOR,
                HIC"牌坊"NOR,
                HIC"太和街口"NOR,
                HIC"中心廣場"NOR,
                HIC"十字路口"NOR,
                HIC"大和街"NOR,
                HIC"兵營"NOR,
        });
        if( query_temp("marks/horserent", ob) != 1 && query("age", ob)>14 )
                return notify_fail("小孩子才可以免費坐馬！你要交錢！\n");
        switch (random(3))
        {
                case 1:
                        hname=MAG"紫騮馬"NOR;
                        break;
                case 2:
                        hname=RED"棗紅馬"NOR;
                        break;
                default:
                        hname=HIY"黃驃馬"NOR;
                        break;
        }
        message_vision(
"馬夫隨手給$N牽來一匹"+hname+"。$N翻身躍上馬背。動作瀟洒利索。路邊行人一陣
起哄: 喔噢喔噢。\n"NOR , ob );
        message_vision("\n只見$N騎兩腿一夾，"+hname+"穿過客店而去。\n",ob);
        for (i = 0;i < sizeof(yz_dl);i ++)
                tell_object(ob,yz_dl[i] + "\n");
        ob->move("/d/dali/majiu");
        tell_room(environment(ob),query("name", ob)+"騎著"+hname+"一路順利到達大理城。\n");
        message_vision("\n$N身形一轉，躍下馬來，姿態十分優美。閒人也給$N一大哄。\n",ob);
        delete_temp("marks/horserent", ob);
        return 1;
}