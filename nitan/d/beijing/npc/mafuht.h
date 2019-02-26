int do_rideht()
{
        string hname;
        object ob = this_player();
        int i;
        string *bj_gw=({
                HIC"鳥市"NOR,
                HIC"西單"NOR,
                HIC"西單"NOR,
                HIC"西長安街"NOR,
                HIC"西長安廣場"NOR,
                HIC"天安門廣場"NOR,
                HIC"東長安廣場"NOR,
                HIC"東長安街"NOR,
                HIC"王府井大街"NOR,
                HIC"王府井大街"NOR,
                HIC"王府井大街"NOR,
                HIC"朝陽道"NOR,
                HIC"朝陽道"NOR,
                HIC"朝陽門"NOR,
                HIC"大驛道"NOR,
                HIC"大驛道"NOR,
                HIC"大驛道"NOR,
                HIC"老龍頭"NOR,
                HIC"山海關"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"寧遠"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"木橋"NOR,
                HIC"南城"NOR,
                HIC"集市"NOR,
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
"馬伕隨手給$N牽來一匹"+hname+"。$N翻身躍上馬背。動作瀟灑利索。路邊行人一陣
起鬨: 喔噢喔噢。\n"NOR , ob );
        message_vision("\n只見$N騎兩腿一夾，"+hname+"穿過客店而去。\n",ob);
        for (i = 0; i < sizeof(bj_gw);i++)
                tell_object(ob,bj_gw[i] + "\n");
        ob->move("/d/guanwai/majiu");
        tell_room(environment(ob),query("name", ob)+"騎着"+hname+"一路順利到達赫圖阿拉。\n");
        message_vision("\n$N身形一轉，躍下馬來，姿態十分優美。閒人也給$N一大哄 !\n" ,ob);
        delete_temp("marks/horserent", ob);
        return 1;
}
