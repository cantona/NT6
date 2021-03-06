// FanYao.h
// 1997.05.10

#include <ansi.h>

string* names = ({
        "shuo bude",
        "zhou dian",
        "zhang zhong",
        "peng yingyu",
        "leng qian",
        "yin tianzheng",
        "zhang wuji",
});

string ask_me()
{
        mapping fam, my_fam, skl;
        object fighter, me, room, monk;
        string *sname;
        int i,j;

        fighter = this_player();
        me = this_object();
        my_fam=query("family", me);

        skl = fighter->query_skills();
        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(fighter) +
                "功力不夠，不夠資格闖光明聖火陣。";
        sname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if (skl[sname[i]] < 80)
                return RANK_D->query_respect(fighter) +
                "功力不夠，不夠資格闖光明聖火陣。";
        }

        if( query("guangming_winner", fighter) )
                return RANK_D->query_respect(fighter) +
                "已然闖過光明聖火陣，可不要拿範遙開這等玩笑。";

        if( query("guilty", fighter)>0 )
                return RANK_D->query_respect(fighter) +
                "你累犯數戒，身帶重罪，我如何能准許你闖光明聖火陣！";

        if( query("assigned_fighter", me) )
                return RANK_D->query_respect(fighter) +
                "，今日已有人挑戰光明聖火陣，你過一段時間再來吧。";

        set_temp("fanyao-asked", 1, fighter);

        say("\n範遙説道：好吧，我召集教主殷法王和五散人在西側殿集合，你稍
候到前邊找我。\n");

        set("assigned_fighter",query("id",  fighter), me);

        if( !query_temp("yangxiao-asked", fighter) )
        say("\n範遙又道：請你速去告知楊左使，請他即刻帶同謝韋二法王和五旗使到
東側殿來。\n");
        message_vision("\n範遙往南離開。\n\n", fighter);
// 1.2.3.4.
        if(!( room = find_object("/d/mingjiao/square")) )
        room = load_object("/d/mingjiao/square");
        me->move(room);
        for (j = 1; j < 5; j++)
        {
                if( !objectp(monk = present(names[j-1], room) ))
                {
                         me->move("/d/mingjiao/dadian");
                        message_vision("\n範遙走了過來。\n\n", fighter);
                        return "真是對不起，五散人中有人不在，無法舉行光明聖火陣。\n";
                }
                message("vision","\n範遙走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
                monk->move("/d/mingjiao/westdian");
                message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
        }
// 5.
        if(!( room = find_object("/d/mingjiao/xingtang")) )
        room = load_object("/d/mingjiao/xingtang");
        me->move(room);
        if( !objectp(monk = present(names[4], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n範遙走了過來。\n\n", fighter);
                return "真是對不起，五散人中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n範遙走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/westdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 6.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[5], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n範遙走了過來。\n\n", fighter);
                return "真是對不起，殷法王不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n範遙走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/westdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 7.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[6], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n範遙走了過來。\n\n", fighter);
                return "真是對不起，張教主不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n範遙走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/westdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);

        me->move("/d/mingjiao/qiandian");
        call_out("waiting", 1, me);
        return "好！大家都出來了。\n";
}

int waiting(object me)
{
        object fighter;
        int wait_time;

        if( wait_time == 100 )
        {
                say( "範遙説道：看來他不會來了，我們回去罷！\n\n");
                call_out("do_back", 0, me);
        }

        if( !objectp(fighter=present(query("assigned_fighter", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me);
        }
        else if( !present("yangxiao",environment(me)) || !query_temp("yangxiao-asked", fighter) )
        {
                if( random(10) == 0 )
                say("\n範遙説道：" + RANK_D->query_respect(fighter) + "去請了楊左使沒有？ 照理他現在該到了罷？\n");

                wait_time++;
                call_out("waiting", 1, me);
        }
        else         call_out("preparing", 0, me, fighter);
        return 1;
}

int preparing(object me, object fighter)
{
        object monk, room, ob;

        if(!( room = find_object("/d/mingjiao/qiandian")) )
        room = load_object("/d/mingjiao/qiandian");

        say( "範遙説道：不相干的人，如不欲現場觀摩光明聖火陣，請即刻離開此處。\n");

        message("vision", HIY "\n範遙大聲宣佈：西光明聖火陣合圍！\n\n" NOR, room);
        command("chat"+query("title", fighter)+query("name", fighter)+
                "於今日" + NATURE_D->game_time() + "挑戰明教光明聖火陣！\n");

        delete_temp("fanyao-asked", fighter);
        delete_temp("beat_count", fighter);
        set_temp("fighting", 1, fighter);

        call_out("fighting",  10, me, fighter, 0);
        return 1;
}

int fighting(object me, object fighter, int count)
{
        object monk1, monk2, room1, room2;

        if(!( room1 = find_object("/d/mingjiao/westdian")) )
        room1 = load_object("/d/mingjiao/westdian");

        if(!( room2 = find_object("/d/mingjiao/qiandian")) )
        room2 = load_object("/d/mingjiao/qiandian");

        if( count <= 6 )
        {
                message("vision", "\n光明聖火陣急速地旋轉着，一層層地向內收緊！\n" NOR, room2);
                monk1 = present(names[count], room1);
                monk1->move(room2);
        }

        if( count >= 1 && count <= 7 )
        {
                monk2 = present(names[count-1], room2);
                monk2->move(room1);
        }

        if( !find_player(query("assigned_fighter", me)) || 
        !living(fighter) || query("qi", fighter) <= 1 )
        {
                if( objectp(present(query("assigned_fighter", me),environment(me)))){
                        delete_temp("fighting", fighter);
                        delete_temp("beat_count", fighter);
                }
                monk1->move(room1);

                say( "範遙説道：是啊，可惜呀 ... 唉！\n\n");
                command("sigh");
                call_out("do_back", 5, me );
        }
        else if( count >= 7 )
        {
                if( query_temp("beat_count", fighter) >= 14 )
                        call_out("do_recruit", 5, me, fighter);
                else
                        call_out("do_back", 5, me );
        }
        else
        {
                count++;
                call_out("fighting", 2, me, fighter, count);
        }

        return 1;
}

int do_recruit(object me, object fighter)
{
        mapping ft_fam, my_fam;

        delete_temp("beat_count", fighter);
        delete_temp("fighting", fighter);
        addn("combat_exp", 10000, fighter);
        set("guangming_winner", 1, fighter);

        if( !(ft_fam=query("family", fighter)) || ft_fam["family_name"] != "明教" )
        {
                command("smile");
                say("範遙説道：" + RANK_D->query_respect(fighter) + "武功卓絕，兼又手下留情，品德更是過人一籌，範遙不勝佩服之至！\n");
                call_out("do_back", 5, me );
        }
        else
        {
                say("\n範遙説道：好，好，好！"+query("name", fighter)+"，沒想到教中出了你這樣一個人才？\n");
                call_out("do_back", 5, me );
        }
        return 1;
}

int do_back(object me)
{
        object monk, room1, room2;
        int i;

        message("vision", "\n範遙也揮了揮手， 五散人等隨即也離開前殿。\n", environment(me) );

        if(!( room1 = find_object("/d/mingjiao/qiandian")) )
        room1 = load_object("/d/mingjiao/qiandian");

        set("exits/southdown", "/d/mingjiao/square", room1);
        set("exits/north", "/d/mingjiao/dadian", room1);
        set("exits/east", "/d/mingjiao/eastdian", room1);
        set("exits/west", "/d/mingjiao/westdian", room1);

        if(!( room1 = find_object("/d/mingjiao/westdian")) )
        room1 = load_object("/d/mingjiao/westdian");

        for(i = 1; i <= 7; i ++)
        {
                switch (i)
                {
                case 1:
                case 2:
                case 3:
                case 4:
                        if(!( room2 = find_object("/d/mingjiao/square")) )
                        room2 = load_object("/d/mingjiao/square");
                        break;
                case 5:
                        if(!( room2 = find_object("/d/mingjiao/xingtang")) )
                        room2 = load_object("/d/mingjiao/xingtang");
                        break;
                case 6:
                case 7:
                        if(!( room2 = find_object("/d/mingjiao/dadian")) )
                        room2 = load_object("/d/mingjiao/dadian");
                        break;
                }
                if( objectp( monk = present(names[i-1], room1) ));
                monk->move(room2);
        }

        delete("assigned_fighter", me);
        me->move("/d/mingjiao/dadian");

        return 1;
}

#include "shizhe.h"
