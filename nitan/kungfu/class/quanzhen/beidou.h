// /d/zhongnan/beidou.h
// 天罡北鬥陣
// sdong 08/15/98

#include <ansi.h>

//inherit F_DBASE;
inherit F_SSERVER;
string *position = ({
        "天權","天樞","天璇","天璣","玉衡","開陽","搖光"
});

string *sword = ({
        "劍尖顫了幾顫，一招巧妙無比的「分花拂柳」，似左實右往空中刺去。",
        "使一招「琴心三疊」，身形向上飄起，手中劍虛虛實實幻出三點寒光射向空中。",
        "身形一轉，猛然一式「罡風掃葉」，舞出滿天劍影，挾著勁風向前掃去。",
        "仰天長笑，身形飄然而起，在半空中身子一旋，一式「狂歌痛飲」狂風般地擊向空中。",
        "左手捏著劍訣，右足踏開一招“定陽針”向上斜刺。",
        "向前邁去一大步，使出「探海屠龍」，手中劍舞成一個光球，迅若奔雷擊出。",
        "運力一抖劍，一時「馬蹴落花」，劍幻出點點劍花，飄然刺出。",
        "手中劍一指，縱起丈余，一時「橫行漠北」，雷霆般擊出。",
        "身形向上飄起，突然一轉身，頭下腳上，手握劍，一招「絮墜無聲」，無聲無息地攻出。",
        "大喝一聲，一招「白虹經天」，劍閃電般劃出一道大圓弧劈下。",
        "忽然身形高高躍起，使出「浪跡天涯」，手中劍幻出漫天花瓣，迅如雷霆射出。"
});

string *zhen =  ({
        "天罡北鬥陣法滾滾推動，攻勢連綿不絕，瞬間將敵人圍在垓心。",
        "天罡北鬥陣氣勢宏大，前攻後擊，連環相接，讓人眼花撩亂，方寸頓失。",
        "只見天罡北鬥陣暗合五行八卦之理，陣中人步法精妙，攻守配合得天衣無縫，威力之大，讓人嘆為觀止。",
        "天罡北鬥陣越縮越小，無形劍氣象浪潮一般逼向中央，令人有窒息之感。"
});

int beidouzhen(object me);
int halt_beidouzhen(object me);
int do_beidouzhen(string arg);
int beidouzhen(object me);
int halt_beidou(object me);
int stop_beidou();

void init()
{
                  add_action("stop_beidou", "stop");
}

int check_ob(object ob,object me)
{
        string ob_name;
        object weapon;
        if( !objectp(ob) )
        {
                return notify_fail("可惜沒有這個人。\n");
        }
        ob_name=query("name", ob);

        if( !present(query("id", ob),environment(me)) )
        {
                return notify_fail("可惜"+ob_name+"不在這裡。\n");
        }

        if( query("family/family_name", ob) != "全真教" )
        {
                return notify_fail("可惜"+ob_name+"不是全真弟子，不會「天罡北鬥陣」。\n");
        }

        if ( ob->query_skill("quanzhen-jian",1) <60 ||
             query("combat_exp", ob)<50000 || 
             ob->query_skill("dodge") <60)
        {
                return notify_fail("可惜"+ob_name+"武功太差，不會「天罡北鬥陣」。\n");
        }
        return 1;
}

void start_beidouzhen(object ob, int mypos,int beidou_time )
{
        set_temp("pending/beidou", 1, ob);
        set_temp("beidou_time", beidou_time*2, ob);
        set_temp("bd_pos", mypos, ob);
        set_temp("bd_power", beidou_time, ob);
        ob->start_busy((: beidouzhen :), (:halt_beidou:));
}


int do_beidouzhen(string arg)
{
        object ob,me = this_player(),weapon;
        int beidou_time,i,mypos=0,power;
        object where;
        string ob_name;
        string name1,name2,name3,name4,name5,name6;
        object ob1,ob2,ob3,ob4,ob5,ob6;

        seteuid(getuid());
        where = environment(me);


        if( me->is_busy() || query_temp("pending/beidouzhen", me) )
                return notify_fail("你現在正忙著呢。\n");

        if( !arg || sscanf(arg, "%s %s %s %s %s %s", name1,name2,name3,name4,name5,name6)!=6 )
                return notify_fail("「天罡北鬥陣」要有七人組成。你要和誰擺「天罡北鬥陣」？\n");

        if( query_temp("pending/beidou", me) )
                return notify_fail("你正在擺「天罡北鬥陣」。\n");

        ob_name=query("name", me);
        if( query("family/family_name", me) != "全真教" )
        {
                return notify_fail("可惜你不是全真弟子，不會「天罡北鬥陣」。\n");
        }

        if ( me->query_skill("quanzhen-jian",1) <60 ||
             query("combat_exp", me)<50000 || 
             me->query_skill("dodge") <60)
                return notify_fail("可惜你武功太差，不會「天罡北鬥陣」。\n");

        if( !(ob1 = present(name1, environment(me)) ) )
                ob1 = find_player(name1);
        i = check_ob(ob1,me);
        if(  i !=1) return i;

        if( !(ob2 = present(name2, environment(me)) ) )
                ob2 = find_player(name2);
        i = check_ob(ob2,me);
        if(  i !=1) return i;

        if( !(ob3 = present(name3, environment(me)) ) )
                ob3 = find_player(name3);
        i = check_ob(ob3,me);
        if(  i !=1) return i;

        if( !(ob4 = present(name4, environment(me)) ) )
                ob4 = find_player(name4);
        i = check_ob(ob4,me);
        if(  i !=1) return i;

        if( !(ob5 = present(name5, environment(me)) ) )
                ob5 = find_player(name5);
        i = check_ob(ob5,me);
        if(  i !=1) return i;

        if( !(ob6 = present(name6, environment(me)) ) )
                ob6 = find_player(name6);
        i = check_ob(ob6,me);
        if(  i !=1) return i;

        power = me->query_skill("force") +
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
        power += me->query_skill("sword")+
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
        power+=query("str", me)+
               query("str", ob1)+
               query("str", ob2)+
               query("str", ob3)+
               query("str", ob4)+
               query("str", ob5)+
               query("str", ob6);
        power+=query("dex", me)+
               query("dex", ob1)+
               query("dex", ob2)+
               query("dex", ob3)+
               query("dex", ob4)+
               query("dex", ob5)+
               query("dex", ob6);
        power = power / 140;

        if (power>50) power=50;
        if (power<18) power=18;

        set_temp("ob1",query("id", me));
        set_temp("ob2",query("id", ob1));
        set_temp("ob3",query("id", ob2));
        set_temp("ob4",query("id", ob3));
        set_temp("ob5",query("id", ob4));
        set_temp("ob6",query("id", ob5));
        set_temp("ob7",query("id", ob6));

        message_vision(HIM"$N突然身形移動，發動眾全真弟子搶佔位置，左邊四人，右邊三人，" + "
                      正是擺的「天罡北鬥陣」陣法。\n"NOR, me);

        start_beidouzhen(me,0,power);
        start_beidouzhen(ob1,1,power);
        start_beidouzhen(ob2,2,power);
        start_beidouzhen(ob3,3,power);
        start_beidouzhen(ob4,4,power);
        start_beidouzhen(ob5,5,power);
        start_beidouzhen(ob6,6,power);

        return 1;
}

int do_beidouzhen2(string arg)
{
        object ob,me,weapon;
        int beidou_time,i,mypos=0,power,bd_power;
        object here;
        string ob_name;
        string name0,name1,name2,name3,name4,name5,name6;
        object ob1,ob2,ob3,ob4,ob5,ob6;

        here = environment( this_player() );

        if( !arg || sscanf(arg, "%s,%s,%s,%s,%s,%s,%s", name0,name1,name2,name3,name4,name5,name6)!=7 )
                return notify_fail("「天罡北鬥陣」要有七人組成。你要和誰擺「天罡北鬥陣」？\n");

        if( !(me = present(name0, here) ) )
        {
                message_vision( name0+"怎麼不在？\n");
                return 0;
        }

        if( !(ob1 = present(name1, environment(me)) ) )
                ob1 = find_player(name1);
        i = check_ob(ob1,me);
        if(  i !=1) return i;

        if( !(ob2 = present(name2, environment(me)) ) )
                ob2 = find_player(name2);
        i = check_ob(ob2,me);
        if(  i !=1) return i;

        if( !(ob3 = present(name3, environment(me)) ) )
                ob3 = find_player(name3);
        i = check_ob(ob3,me);
        if(  i !=1) return i;

        if( !(ob4 = present(name4, environment(me)) ) )
                ob4 = find_player(name4);
        i = check_ob(ob4,me);
        if(  i !=1) return i;

        if( !(ob5 = present(name5, environment(me)) ) )
                ob5 = find_player(name5);
        i = check_ob(ob5,me);
        if(  i !=1) return i;

        if( !(ob6 = present(name6, environment(me)) ) )
                ob6 = find_player(name6);
        i = check_ob(ob6,me);
        if(  i !=1) return i;

        power = me->query_skill("force") +
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
        power += me->query_skill("sword")+
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
        power+=query("str", me)+
               query("str", ob1)+
               query("str", ob2)+
               query("str", ob3)+
               query("str", ob4)+
               query("str", ob5)+
               query("str", ob6);
        power+=query("dex", me)+
               query("dex", ob1)+
               query("dex", ob2)+
               query("dex", ob3)+
               query("dex", ob4)+
               query("dex", ob5)+
               query("dex", ob6);
        power = power / 140;

        if (power>50) power=50;
        if (power<18) power=18;

        set_temp("ob1",query("id",  me), here);
        set_temp("ob2",query("id",  ob1), here);
        set_temp("ob3",query("id",  ob2), here);
        set_temp("ob4",query("id",  ob3), here);
        set_temp("ob5",query("id",  ob4), here);
        set_temp("ob6",query("id",  ob5), here);
        set_temp("ob7",query("id",  ob6), here);

        message_vision(HIM"$N突然身形移動，發動眾全真弟子搶佔位置，左邊四人，右邊三人，" + "
                      正是擺的「天罡北鬥陣」陣法。\n"NOR, me);

        start_beidouzhen(me,0,power);
        start_beidouzhen(ob1,1,power);
        start_beidouzhen(ob2,2,power);
        start_beidouzhen(ob3,3,power);
        start_beidouzhen(ob4,4,power);
        start_beidouzhen(ob5,5,power);
        start_beidouzhen(ob6,6,power);

        return 1;
}

int do_beidou(string arg)
{
        object ob,weapon,me = this_player();
        int beidou_time,i,mypos=0,power;
        object where;
        string ob_name;
        string name1,name2,name3,name4,name5,name6,name0;
        object ob0,ob1,ob2,ob3,ob4,ob5,ob6;

        seteuid(getuid());
        where = environment(me);

        if( me->is_busy() || query_temp("pending/beidouzhen", me) )
                return notify_fail("你現在正忙著呢。\n");


        if( !arg || sscanf(arg, "%s %s %s %s %s %s %s", name0,name1,name2,name3,name4,name5,name6)!=7 )
                return notify_fail("「天罡北鬥陣」要有七人組成。你要和誰擺「天罡北鬥陣」殺誰？ \n" +
                                     "beidou enemy name1 name2 name 3 name4 name 5 name 6\n");

        if( query_temp("pending/beidou", me) )
                return notify_fail("你正在擺「天罡北鬥陣」。\n");

        ob_name=query("name", me);
        if( query("family/family_name", me) != "全真教" )
                return notify_fail("可惜你不是全真弟子，不會「天罡北鬥陣」。\n");

        if ( me->query_skill("quanzhen-jian",1) <60 ||
             query("combat_exp", me)<50000 || 
             me->query_skill("dodge") <60)
                return notify_fail("可惜你武功太差，不會「天罡北鬥陣」。\n");

        if( !(ob0 = present(name0, environment(me)) ) )
                return notify_fail("可惜你要殺的人不在這裡！\n");

        if( !(ob1 = present(name1, environment(me)) ) )
                ob1 = find_player(name1);
        i = check_ob(ob1,me);
        if(  i !=1) return i;

        if( !(ob2 = present(name2, environment(me)) ) )
                ob2 = find_player(name2);
        i = check_ob(ob2,me);
        if(  i !=1) return i;

        if( !(ob3 = present(name3, environment(me)) ) )
                ob3 = find_player(name3);
        i = check_ob(ob3,me);
        if(  i !=1) return i;

        if( !(ob4 = present(name4, environment(me)) ) )
                ob4 = find_player(name4);
        i = check_ob(ob4,me);
        if(  i !=1) return i;

        if( !(ob5 = present(name5, environment(me)) ) )
                ob5 = find_player(name5);
        i = check_ob(ob5,me);
        if(  i !=1) return i;

        if( !(ob6 = present(name6, environment(me)) ) )
                ob6 = find_player(name6);
        i = check_ob(ob6,me);
        if(  i !=1) return i;

        power = me->query_skill("force") +
               ob1->query_skill("force")+
               ob2->query_skill("force")+
               ob3->query_skill("force")+
               ob4->query_skill("force")+
               ob5->query_skill("force")+
               ob6->query_skill("force");
        power += me->query_skill("sword")+
               ob1->query_skill("sword")+
               ob2->query_skill("sword")+
               ob3->query_skill("sword")+
               ob4->query_skill("sword")+
               ob5->query_skill("sword")+
               ob6->query_skill("sword");
        power+=query("str", me)+
               query("str", ob1)+
               query("str", ob2)+
               query("str", ob3)+
               query("str", ob4)+
               query("str", ob5)+
               query("str", ob6);
        power+=query("dex", me)+
               query("dex", ob1)+
               query("dex", ob2)+
               query("dex", ob3)+
               query("dex", ob4)+
               query("dex", ob5)+
               query("dex", ob6);
        power = power / 140;

        if (power>50) power=50;
        if (power<18) power=18;

        set_temp("ob1",query("id", me));
        set_temp("ob2",query("id", ob1));
        set_temp("ob3",query("id", ob2));
        set_temp("ob4",query("id", ob3));
        set_temp("ob5",query("id", ob4));
        set_temp("ob6",query("id", ob5));
        set_temp("ob7",query("id", ob6));

        start_beidouzhen(me,0,power);
        start_beidouzhen(ob1,1,power);
        start_beidouzhen(ob2,2,power);
        start_beidouzhen(ob3,3,power);
        start_beidouzhen(ob4,4,power);
        start_beidouzhen(ob5,5,power);
        start_beidouzhen(ob6,6,power);

        me->kill_ob(ob0);
        ob1->kill_ob(ob0);
        ob2->kill_ob(ob0);
        ob3->kill_ob(ob0);
        ob4->kill_ob(ob0);
        ob5->kill_ob(ob0);
        ob6->kill_ob(ob0);

        ob0->kill_ob(me);
        ob0->kill_ob(ob1);
        ob0->kill_ob(ob2);
        ob0->kill_ob(ob3);
        ob0->kill_ob(ob4);
        ob0->kill_ob(ob5);
        ob0->kill_ob(ob6);

        return 1;
}

void destruct_me(object me)
{
        destruct(me);
}

void check_leaving(object me)
{
        string name=query("id", me);

        if( name == "yin zhiping" ||
            name == "shen zhifan" ||
            name == "li zhichang" ||
            name == "chen zhiyi" ||
            name == "cui zhifang" )
        {
                object enemy = offensive_target(me);
                if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
                {
                        message_vision(HIY"\n$N作了個楫道：貧道先告退了！說完就快步離開了。\n"NOR, me);
                        call_out("destruct_me",10,me);
                        return;
                }

                call_out("check_leaving",5,me);
        }
}

int beidouzhen(object me)
{
        object  where = environment(this_player());
        int beidou_time=query_temp("beidou_time", me);
        object room, obj,enemy,weapon;
        int cost,bonus,mypos=query_temp("bd_pos", me);
        int power;
        object ob1,ob2,ob3,ob4,ob5,ob6,ob7;


        if( !(room = environment(this_player())) )
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                {
                        message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                        "退出「天罡北鬥陣」。\n"NOR, me);
                }
                else
                        message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                        "退出「天罡北鬥陣」。\n"NOR, me);
                if (userp(me))
                        /*log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
                me->remove_all_enemy();
                delete_temp("pending/beidou", me);
                delete_temp("beidou_time", me);
                delete_temp("bd_pos", me);
                delete_temp("bd_power", me);
                call_out("check_leaving",2,me);
                return 0;
        }

        enemy = offensive_target(me);

        if ( beidou_time < 1 &&
             !me->query_enemy()&&
             !objectp(enemy) &&
             !me->is_busy() &&
             !me->is_fighting() )
        {
                if( !objectp(weapon=query_temp("weapon", me)) || 
                   query("skill_type", weapon) != "sword" )
                {
                        message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                    "退出「天罡北鬥陣」。\n"NOR, me);
                }
                else
                        message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                   "退出「天罡北鬥陣」。\n"NOR, me);

                if (userp(me))
                        /*log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
                me->remove_all_enemy();
                delete_temp("pending/beidou", me);
                delete_temp("beidou_time", me);
                delete_temp("bd_pos", me);
                delete_temp("bd_power", me);
                call_out("check_leaving",10,me);

                return 0;
        }

        if( query("neili", me)<60 || query("jingli", me)<50 )
        {
                if( !objectp(weapon=query_temp("weapon", me)) || 
                   query("skill_type", weapon) != "sword" )
                {
                        message_vision(HIY"\n$N體力不支，只好身子向後一縱，使一招『收山式』，右拳劃了一圈，" +
                                         "左掌往懷中一抱，退出「天罡北鬥陣」。\n"NOR, me);
                }
                else
                        message_vision(HIY"\n$N體力不支，只好身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，" +
                                         "往懷中一抱，退出「天罡北鬥陣」。\n"NOR, me);

                if (userp(me))
                        /*log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
                me->remove_all_enemy();
                delete_temp("pending/beidou", me);
                delete_temp("beidou_time", me);
                delete_temp("bd_pos", me);
                delete_temp("bd_power", me);
                call_out("check_leaving",2,me);

                return 0;
        }

        if( !(query_temp("ob1", room) && 
                objectp(ob1=present(query_temp("ob1", room),where)) && 
                query_temp("beidou_time", ob1) && 
                objectp(ob2=present(query_temp("ob2", room),where)) && 
                query_temp("beidou_time", ob2) && 
                objectp(ob3=present(query_temp("ob3", room),where)) && 
                query_temp("beidou_time", ob3) && 
                objectp(ob4=present(query_temp("ob4", room),where)) && 
                query_temp("beidou_time", ob4) && 
                objectp(ob5=present(query_temp("ob5", room),where)) && 
                query_temp("beidou_time", ob5) && 
                objectp(ob6=present(query_temp("ob6", room),where)) && 
                query_temp("beidou_time", ob6) && 
                objectp(ob7=present(query_temp("ob7", room),where)) && 
                query_temp("beidou_time", ob7)) )
        {
                if( !objectp(weapon=query_temp("weapon", me)) || 
                   query("skill_type", weapon) != "sword" )
                {
                        message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                        "退出「天罡北鬥陣」。\n"NOR, me);
                }
                else
                        message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                        "退出「天罡北鬥陣」。\n"NOR, me);
                if (userp(me))
                        /*log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
                me->remove_all_enemy();
                delete_temp("pending/beidou", me);
                delete_temp("beidou_time", me);
                delete_temp("bd_pos", me);
                delete_temp("bd_power", me);
                delete_temp("ob1", room);
                delete_temp("ob2", room);
                delete_temp("ob3", room);
                delete_temp("ob4", room);
                delete_temp("ob5", room);
                delete_temp("ob6", room);
                delete_temp("ob7", room);
                call_out("check_leaving",2,me);

                return 0;
        }


        beidou_time = beidou_time-1;
        set_temp("beidou_time", beidou_time, me);
        bonus=random((query("int", me)+query("con", me)+25)/30)+
                 (query("int", me)+query("con", me)+25)/30;
        if( bonus > 4 ) bonus = 4;

        if( query("potential", me)<me->query_potential_limit() )
                addn("potential", random(bonus), me);
        addn("combat_exp", random(bonus), me);
        if (me->query_skill("beidou-zhenfa",1) < me->query_skill("array",1))
        {
                me->improve_skill("beidou-zhenfa", me->query_int() / 5 +
                                random(query("int", me)+me->query_skill("beidou-zhenfa",1)/8));
        }
        addn_temp("qz/jobpot", bonus, me);
       addn_temp("qz/jobexp", bonus*3/2, me);

        enemy = offensive_target(me);

        power=query_temp("bd_power", me)*4;

        addn_temp("apply/parry", power, me);
        addn_temp("apply/armor", power, me);

        if( random(14)==1 )
        {
                tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());

                if( objectp(enemy) && objectp( present( query("id", enemy),environment(me) )) && !enemy->is_busy() )
                        enemy->start_busy( 1+random(2) );
        }

        if( objectp(enemy) && objectp( present( query("id",enemy),environment(me) )) )
        {
                if( random(5)==1 )
                {
                        if(random(2)==0)
                                message_vision("\n" + position[mypos] + "位上的$N氣沉丹田，暗運神功，" +
                                                "猛然吐氣開聲，身形往前一縱, 但見", me);
                        else message_vision("\n" + position[mypos] + "位上的$N挺身而出，步法精妙，" +
                                                "長袖飄飄，攻勢如虹。只見", me);

                        addn_temp("apply/damage", power/2, me);
                        addn_temp("apply/attack", power/2, me);
                        COMBAT_D->do_attack(me,enemy,query_temp("weapon", me));
                        addn_temp("apply/damage", -power/2, me);
                        addn_temp("apply/attack", -power/2, me);
                        addn("jingli", -15-random(15), me);
                        addn("neili", -20-random(20), me);
                }
        }
        else
        {
                if ( random(6)==1 )
                {
                        if( (weapon=query_temp("weapon", me) )
                                 && query("skill_type", weapon) == "sword" )
                        {
                                message_vision("\n" + position[mypos] + "位上的$N"+ sword[random(10)]+"\n", me);
                        }

                        addn("jingli", -15-random(10), me);
                        addn("neili", -20-random(15), me);
                }
        }

        addn_temp("apply/parry", -power, me);
        addn_temp("apply/armor", -power, me);

        if (beidou_time > -1)
                return 1;

        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);

        if( !objectp(weapon=query_temp("weapon", me) )
          || query("skill_type", weapon) != "sword" )
        {
                message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);

/*
                if (userp(me))
                        log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
        }
        else
        {
                message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);

/*
                if (userp(me))
                        log_file("job/qz-lianzhen",
                                sprintf("[%s] %s(%s) 在 %d 秒內 Lianzhen 得到 %d 經驗和 %d 潛能。\n",
                                        ctime(time()),
                                        me->name(),
                                        getuid(me),
                                        time()-query_temp("qz/jobtime", me),
                                        query_temp("qz/jobexp", me),
                                        query_temp("qz/jobpot", me)));//addlogfile.*/
        }
        call_out("check_leaving",5,me);
        return 0;
}

void restart (object me)
{
        start_beidouzhen(me, query_temp("bd_pos",me), query_temp("beidou_time",me) );
}

int halt_beidou(object me)
{
        object weapon;
        int beidou_time=query_temp("beidou_time", me);
        if (beidou_time > 0)
        {
                if( !living(me) ) return 1;

                if(random(2)==1)
                {
                        message_vision(HIG"\n$N踉蹌了一步，差點摔出北鬥陣。\n"NOR, me);
                }
                else message_vision(HIG"\n$N被打的晃了幾晃，不過又站穩了步子。\n"NOR, me);
                call_out("restart",4,me);
                return 1;
        }

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
        {
                message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);
        }
        else
                message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);
        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);
        delete_temp("bd_power", me);
        return 1;
}

int stop_beidou()
{
        object weapon,me=this_player();
        if( !query_temp("pending/beidou", me) )
                return notify_fail("停什麼？你不在運行「天罡北鬥陣」。\n");
        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
        {
                message_vision(HIG"\n$N身子向後一縱，使一招『收山式』，右拳劃了一圈，左掌往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);
        }
        else
                message_vision(HIG"\n$N身子向後一縱，使一招『收劍式』，將劍挽了一個劍花，往懷中一抱，" +
                                "退出「天罡北鬥陣」。\n"NOR, me);
        me->remove_all_enemy();
        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);
        delete_temp("bd_power", me);
        return 1;
}
