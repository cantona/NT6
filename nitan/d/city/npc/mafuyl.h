int do_rideyl()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_yl = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"中央廣場"NOR,
                HIC"西大街"NOR,
                HIC"西大街"NOR,
                HIC"西門"NOR,
                HIC"西門大道"NOR,
                HIC"長安東城門"NOR,
                HIC"長安西城門"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"六盤山"NOR,
                HIC"嘉峪關"NOR,
                HIC"絲綢之路"NOR,
                HIC"絲綢之路"NOR,
                HIC"絲綢之路"NOR,
                HIC"絲綢之路"NOR,
                HIC"天山腳下"NOR,
                HIC"伊犁"NOR,
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
        for ( i = 0;i < sizeof(yz_yl);i++)
                tell_object(ob,yz_yl[i]+"\n");
        ob->move("/d/xingxiu/majiu");
        tell_room(environment(ob),query("name", ob)+"騎着"+hname+"一路順利到達天山腳下的伊犁鎮。\n");
        message_vision("\n$N身形一轉，躍下馬來，姿態十分優美。閒人也給$N一大哄。\n",ob);
        delete_temp("marks/horserent", ob);
        return 1;
}
