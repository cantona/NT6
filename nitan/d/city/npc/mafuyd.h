int do_rideyd()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_yd = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"北大街"NOR,
                HIC"北門"NOR,
                HIC"草地"NOR,
                HIC"草地"NOR,
                HIC"樹林"NOR,
                HIC"樹林"NOR,
                HIC"田地"NOR,
                HIC"田地"NOR,
                HIC"田地"NOR,
                HIC"黃河岸邊"NOR,
                HIC"渭汾流域"NOR,
                HIC"黃河"NOR,
                HIC"河套"NOR,
                HIC"黃土高原"NOR,
                HIC"黃河"NOR,
                HIC"黃河"NOR,
                HIC"永登"NOR,
                HIC"客店"NOR,
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
        for ( i = 0;i < sizeof(yz_yd); i++)
                tell_object(ob,yz_yd[i] + "\n");
        ob->move("/d/huanghe/majiu");
        tell_room(environment(ob),query("name", ob)+"騎着"+hname+"一路順利到達永登。\n");
        message_vision("\n$N身形一轉，躍下馬來，姿態十分優美。閒人也給$N一大哄 !\n" ,ob);
        delete_temp("marks/horserent", ob);
        return 1;
}