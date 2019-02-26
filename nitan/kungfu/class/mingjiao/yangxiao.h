// YangXiao.h

#include <ansi.h>

string* names = ({
        "zhuang zheng",
        "wen cangsong",
        "tang yang",
        "xin ran",
        "yan yuan",
        "xie xun",
        "wei yixiao",
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
                "已然闖過光明聖火陣，可不要拿楊逍開這等玩笑。";

        if( query("guilty", fighter)>0 )
                return RANK_D->query_respect(fighter) +
                "你累犯數戒，身帶重罪，我如何能准許你闖光明聖火陣！";

        if( query("assigned_fighter", me) )
                return RANK_D->query_respect(fighter) +
                "，今日已有人挑戰光明聖火陣，你過一段時間再來吧。";

        set_temp("yangxiao-asked", 1, fighter);

        say("\n楊逍説道：好吧，我召集謝韋二法王和五旗使在東側殿集合，你稍候到前
邊找我。\n");

        set("assigned_fighter",query("id",  fighter), me);

        if( !query_temp("fanyao-asked", fighter) )
        say("\n楊逍又道：請你速去告知範右使，請他即刻招集教主殷法王和五散人於西
側殿集合。\n");

        message_vision("\n楊逍往南離開。\n\n", fighter);

// 1.
        if(!( room = find_object("/d/mingjiao/rjqdating")) )
        room = load_object("/d/mingjiao/rjqdating");
        me->move(room);
        if( !objectp(monk = present(names[0], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，五旗使中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 2.
        if(!( room = find_object("/d/mingjiao/jmqdating")) )
        room = load_object("/d/mingjiao/jmqdating");
        me->move(room);
        if( !objectp(monk = present(names[1], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，五旗使中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 3.
        if(!( room = find_object("/d/mingjiao/hsqdating")) )
        room = load_object("/d/mingjiao/hsqdating");
        me->move(room);
        if( !objectp(monk = present(names[2], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，五旗使中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 4.
        if(!( room = find_object("/d/mingjiao/lhqdating")) )
        room = load_object("/d/mingjiao/lhqdating");
        me->move(room);
        if( !objectp(monk = present(names[3], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，五旗使中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 5.
        if(!( room = find_object("/d/mingjiao/htqdating")) )
        room = load_object("/d/mingjiao/htqdating");
        me->move(room);
        if( !objectp(monk = present(names[4], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，五旗使中有人不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 6.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[5], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，謝法王不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);
// 7.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[6], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n楊逍走了過來。\n\n", fighter);
                return "真是對不起，韋法王不在，無法舉行光明聖火陣。\n";
        }
        message("vision","\n楊逍走了過來，跟"+query("name", monk)+"俯耳輕聲説了幾句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"點了點頭，快步走了出去。\n",room,monk);

        me->move("/d/mingjiao/qiandian");
        call_out("waiting", 1, me);
        return "好！大家都出來了。\n";
}

int waiting(object me)
{
        object fighter;
        int wait_time;

        if( wait_time == 300 )
        {
                say( "楊逍説道：看來他不會來了，我們回去罷！\n\n");
                call_out("do_back", 0, me);
        }

        if( !objectp(fighter=present(query("assigned_fighter", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me);
        }
        else if( !present("fanyao",environment(me)) || !query_temp("fanyao-asked", fighter) )
        {
                if( random(10) == 0 )
                say("\n楊逍説道：" + RANK_D->query_respect(fighter) + "去請了範右使沒有？ 照理他現在該到了罷？\n");

                wait_time++;
                call_out("waiting", 1, me);
        }
        else         call_out("preparing", 1, me, fighter);

        return 1;
}

int preparing(object me, object fighter)
{
        object monk, room, ob;

        if(!( room = find_object("/d/mingjiao/qiandian")) )
        room = load_object("/d/mingjiao/qiandian");

        message("vision", HIY "\n楊逍大聲宣佈：東光明聖火陣合圍！\n" NOR, room);
        message("vision", "\n只聽四周響起沙沙的腳步聲，三法王五散人五旗使們個個神情肅殺，\n"
                "或赤手空拳，或手持兵器，慢慢地圍了上來，堵住了通路。\n\n", room);
        delete("exits", room);

        say( "楊逍又道：準備，光明聖火陣即刻發動！\n\n");

        delete_temp("yangxiao-asked", fighter);
        delete_temp("beat_count", fighter);
        set_temp("fighting", 1, fighter);

        call_out("fighting", 10, me, fighter, 0);
        return 1;
}

int fighting(object me, object fighter, int count)
{
        object monk1, monk2, room1, room2;

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        if(!( room2 = find_object("/d/mingjiao/qiandian")) )
        room2 = load_object("/d/mingjiao/qiandian");

        if( count <= 6 )
        {
                message("vision", "\n光明聖火陣急速地旋轉着，一層層地向內收緊！\n" NOR, room2);
                monk1 = present(names[count], room1);
                if (monk1) monk1->move(room2);
        }

        if( count >= 1 && count <= 7 ) {
                monk2 = present(names[count-1], room2);
                if (monk2) monk2->move(room1);
        }

        if( !find_player(query("assigned_fighter", me)) || 
        !living(fighter) || query("qi", fighter) <= 1 )
        {
                if( objectp(present(query("assigned_fighter", me),environment(me)))){
                        delete_temp("fighting", fighter);
                        delete_temp("beat_count", fighter);
                }
                monk1->move(room1);

                say( "楊逍搖了搖頭，説道：想不到 ... 唉！\n\n");
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
                command("bow");
                say("楊逍説道：" + RANK_D->query_respect(fighter) + "此番過陣，當對本身修行大有助益，百尺竿頭，更進一步，楊逍就此別過！\n");
                call_out("do_back", 5, me );
        }
        else
        {
                say("\n楊逍説道：恭喜你闖過了光明聖火陣！本教有此等傑出弟子，屆時必當為武林放一異彩！\n");
                call_out("do_back", 5, me );
        }
        return 1;
}

int do_back(object me)
{
        object monk, room1, room2;
        int i;

        message("vision", "\n楊逍揮了揮手， 五旗使和二法王隨即魚貫離開前殿。\n", environment(me) );

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        for(i = 1; i <= 7; i ++)
        {
                switch (i)
                {
                case 1:
                        if(!( room2 = find_object("/d/mingjiao/rjqdating")) )
                        room2 = load_object("/d/mingjiao/rjqdating");
                        break;
                case 2:
                        if(!( room2 = find_object("/d/mingjiao/jmqdating")) )
                        room2 = load_object("/d/mingjiao/jmqdating");
                        break;
                case 3:
                        if(!( room2 = find_object("/d/mingjiao/hsqdating")) )
                        room2 = load_object("/d/mingjiao/hsqdating");
                        break;
                case 4:
                        if(!( room2 = find_object("/d/mingjiao/lhqdating")) )
                        room2 = load_object("/d/mingjiao/lhqdating");
                        break;
                case 5:
                        if(!( room2 = find_object("/d/mingjiao/htqdating")) )
                        room2 = load_object("/d/mingjiao/htqdating");
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
