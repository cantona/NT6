inherit ROOM;

#include <ansi.h>

int TEST_FLAG = 0;

public void set_test_flag(int n){TEST_FLAG = n;}

string show_jiqi();
int do_duoqu(string arg);
mapping data = ([]);

void create()
{
        set("short", HIY "祭台" NOR);
        set("long",@LONG
你站在祭台上，感覺腳下異常冰冷。祭台上雜亂不堪，正
中插着一面祭旗（jiqi），上面似乎已經染滿了鮮血。這裏似
乎發生過激烈的打鬥，不知道是為了爭奪什麼。你不由思緒萬
千，“塵歸塵，土歸土 …… 世人究竟為了哪般？”
LONG);

        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("binghuo", 1);           // 表示在冰火島
        
        set("no_die", 1);

        set("no_clean_up", 1);

        set("exits", ([ 
                "down"     : __DIR__"jitaiqian",
        ]));
        
        set("item_desc", ([ 
                "jiqi"   :  (: show_jiqi :),
        ]));

        setup();

        set_heart_beat(1);
}

string show_jiqi()
{
        int i;
        string *key;
        string  str;
        object  me = this_player();
        object  ob;
        string  team_name;
        
        if( !sizeof(data) )
                return HIG "現在還沒有幫派奪取祭旗，趕緊奪取(duoqu jiqi)吧。\n" NOR;

        str = HIG "現在祭旗奪取的情況如下：\n" NOR;
        str += sprintf(HIC "%-20s%-20s\n" NOR, "幫派", "奪旗時長");
        str += HIC "-------------------------------\n" NOR;
        key = keys(data);
        
        for (i = 0; i < sizeof(key); i ++)
                str += sprintf("%-20s%-20s\n", key[i], time_period(data[key[i]]));

        str += HIC "-------------------------------\n" NOR;
        if( objectp(ob = query("jiqi_owner")) )
        {
                team_name = query("bunch/bunch_name", ob);
                str += HIC "現在祭旗正被" HIY +"【" + team_name + "】的" + ob->name() +
                       HIY "(" + query("id", ob) + ")" HIC + "奪取中！\n" NOR;
        }
        else
        {
                str += HIG "現在祭旗沒有被奪取，趕緊奪取（duoqu jiqi）吧！\n" NOR;
        }
        return str;
}

void init()
{
        add_action("do_duoqu", "duoqu");
}

// 奪取旗幟
int do_duoqu(string arg)
{
        object me = this_player();
        object ob;
        string team_name;

        if( !arg || arg != "jiqi" )
                return notify_fail("你要奪取什麼？\n");

        if( time() - query_temp("last_do_duoqu", me) < 10 )
                return notify_fail("你距離上次奪旗嘗試時間不足10秒，不能連續嘗試！\n");

        // 有人奪取時不能奪取
        if( objectp(ob = query("jiqi_owner")) )
        {
                me->set_temp("last_do_duoqu", time());
                return notify_fail(HIR "祭旗正被" + HIY + ob->name() + HIY "(" + query("id", ob) + ")" HIR "奪取中！\n" NOR);
        }
        
        // 無幫派人士不能奪取
        if( !query("bunch/bunch_name", me) )
        {
                me->move("/d/city/wumiao");
                tell_object(me, "你還是先加個幫派吧！\n");
                return 1;
        }

        // 非幫戰期間不能奪取
        if (! BUNCH_D->is_battle_start() && ! TEST_FLAG)
                return notify_fail("現在不處於幫戰期間，你奪取祭旗幹什麼！\n");
        
        // 奪取
        set("jiqi_owner", me);
        team_name = query("bunch/bunch_name", me);
        if( !undefinedp(data[team_name]) )
        {
                write(HIG "你奪取了祭旗，你的隊伍總共奪取祭旗時間為：" HIY + time_period(data[team_name]) + HIG "。\n" NOR);
                tell_room(this_object(), HIG + me->name() + HIG "奪取了祭旗，其所在幫派【" + team_name +
                          "】總共奪取祭旗時間為：" HIY + time_period(data[team_name]) + HIG "。\n" NOR, ({ me }));
        }
        else
        {
                write(HIG "你奪取了祭旗，開始統計記時。。。\n" NOR);
                tell_room(this_object(), HIG + me->name() + HIG "奪取了祭旗，其所在幫派【" + team_name + "】。\n" NOR, ({ me }));
        }
        
        // CHANNEL_D通告
        CHANNEL_D->channel_broadcast("war",HIG+me->name()+HIG"成功奪取祭旗，其所在幫派【"+query("bunch/bunch_name", me)+
                                     "】暫時取得祭旗控制權。\n" NOR);

        return 1;
}

void heart_beat()
{               
        int time;
        object me;
        string team_name;

        me = query("jiqi_owner");

        reset_eval_cost();
        
        // 非幫戰期間，清除之前的記錄
        if( !BUNCH_D->is_battle_start() && !TEST_FLAG )
        {
                if (query("jiqi_owner"))delete("jiqi_owner");
                if (sizeof(data)) data = ([]);
                return;
        }

        if( !objectp(me) ) return;
        
        if( !living(me) || environment(me) != this_object() )
        {
                delete("jiqi_owner");
                return;
        }
        
        BUNCH_D->add_bonus_score(me, 1);  // 提高個人幫派貢獻度
        
        // 無幫派
        team_name=query("bunch/bunch_name", me);
        if (! team_name)return;

        // 累計奪旗時間
        if( undefinedp(data[team_name]) )
                data[team_name] = 1;
        else
                data[team_name] += 1;

        time = data[team_name];
        
        if( time >= 600 )
        {
                BUNCH_D->win_battle(me, team_name);
                return;
        }

        if( time >= 540 )
        {
                if( !(time % 10) )
                        CHANNEL_D->channel_broadcast("war", HIR"幫派【"+team_name+HIR"】總共奪取"+query("short")+"祭旗時間為：" HIY +time_period(time) + HIR "，即將獲得最終勝利..."NOR);
        }
        return;
}       
