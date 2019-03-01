//                標準描述長度示例                                   |
// 幻境﹒遙遠傳說之起緣﹒幽靈顯現 新增人物，用于檢測玩家是否 robot.  grin~
// 以奈何現在寫ROBOT的臭水平，只能想到這樣的寫法，不知道這樣的問題能
// 不能用 robot 來回答？ grin~
// ROBOT CHECK 程序在 2002 年底左右寫成，這裡是直接復制過來用的。

// by naihe  2003-10-22  于茂名

#include <ansi.h>
inherit NPC;

#include <set_del_color.h>
string ask_quest_again();
mapping get_question(int times);
string get_flag(string this_times);


#define        IS_TEST            0
// 不要測試就改 0 嘍
// 測試時使用  <testquest ID> 啟動測試。

#define        PIC_NUMBER        40
#define        AWARD_SCORE        30


int me_ok(object me)
{
    if( !me || query_temp("hj_hp", me)<1 || query_temp("huanjing", me) != "start"
       || !environment(me) || !query("room_mark", environment(me) )
          || !query("this_time_mark")
       || query("this_time_mark") != query_temp("this_time_mark", me) )
        return 0;

    return 1;
}

void create()
{
    set_name( "蒙面人", ({ "mengmian ren", "mmr" }) );
    set("long", "這是一個蒙著臉面的男人，嗓音沙啞，一副神秘兮兮的樣子。\n");
    set("hj_game/npc", "robot_checker");
    set("gender","男性");
    set("age", 41);
    set("no_refresh",1);
    set("inquiry",([
        "question" : (: ask_quest_again :),
        "問題"     : (: ask_quest_again :),
    ]));

    setup();
}

void init()
{
    add_action("do_look", "look");
    add_action("do_ans", "ans");
    add_action("do_test", "testquest");
}

int do_test( string arg )
{
    object who;

    if( !IS_TEST ) return 0;

    if( query("wait_ans") ) 
        return notify_fail("現在正在進行測試。\n");

    if( !arg ) return notify_fail("要對誰進行問題測試？\n");

    message_vision( "$N對著$n說道：“對"+arg+"進行測試問題。”\n", this_player(), this_object() );
    command( "ok" );

    who = present( arg, environment(this_object()) );
    if( !who )
    {
        command("say 這個人不在這裡耶。");
        return 1;
    }

    delete("ans_error");
    delete("quest_ok");
    delete("wait_ans");
    delete("ans_over");

    set("checking_player", who );
    remove_call_out("start_check");
    remove_call_out("delete_me");
    call_out("start_check", 1);
    return 1;
}


int do_ans( string arg )
{
    object me = this_player();
    int player_ans;

    if( query("ans_over") ) return 0;

    if( !query("checking_player") || me != query("checking_player")
        || !query("this_time_mark")
         || query("this_time_mark") != query_temp("this_time_mark", me) )
        return notify_fail("關你什麼事？又不是問你。\n");

    if( !arg )
    {
        message_vision("$N對著$n大聲說道：“我知道了！它根本就不在這裡！！！”\n", me, this_object() );
        command("kick"+query("id", me));
        command( "say 胡說！就在這裡，看仔細點！");
        return 1;
    }


    message_vision("$N對著$n大聲說道：“我知道了！它的位置是 "+arg+" ！”\n", me, this_object() );

    if( !query("wait_ans") )
    {
        command("say 急什麼，我都還沒問你！");
        return 1;
    }

    if( sscanf( arg, "%d", player_ans ) )
    {
        if( player_ans == query("quest_ans") )
        {
            command( "consider" );
            set("quest_ok", 1);
            remove_call_out("delete_me");
            call_out("delete_me", 1);
            return 1;
        }
        command("hmm"+query("id", me));
        if( !query("ans_error") )
        {
            set( "ans_error", 1);
            command("say 看仔細點！！！從左往右數！！！沒看清就多問我一次(ask mengmian ren about 問題)！！！");
            return 1;
        }
        command("faint"+query("id", me));
        set("ans_over", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 1);
        return 1;
    }

    command("say 亂說！看仔細點！");
    return 1;
}


void delete_me()
{
    object me = query("checking_player"), ob = this_object();
    int hp;

    if( IS_TEST )
    {
        message_vision("\n", this_object() );
        if( query("quest_ok") )
            command("say 恩，回答正確。");
        else command("say 錯了！是 "+query("quest_ans")+" 才對！");
        delete("wait_ans");
        return;
    }

    if( !me || !me_ok(me) )
        message_vision("$N左右張望了一下，急急離開了。\n", ob );

    else if( query( "quest_ok" ) )
    {
        command("say“"+delcolor(query("name", me))+"，好樣的！謝謝你了！”\n");
        message_vision("$n拍了拍$N的頭，滿意地離開了。\n", me, ob );
        hp = AWARD_SCORE + random( AWARD_SCORE );
        addn_temp("hj_score", hp, me);
        tell_object( me, HIR"遊戲提示：你的得分增加了 "+hp+" 點！\n"NOR);
    }
    else
    {
        ob->move( environment(me) );
        message_vision( "$n對著$N劈頭大罵道：“豈有此理，問你那麼簡單的問題都不會，該罰！”\n說罷，$n對著$N踢了一腳，$N只痛得嗷嗷大叫。\n$n罵道：“我都看出來了，是 "+query("quest_ans")+" 嘛！！！”$n說完，氣憤地離開了！\n", me, ob);
        tell_object( me, HIR"遊戲提示：你的氣息大大降低了！！！\n"NOR );

        hp=query_temp("hj_hp", me);
        hp = hp / 5;
        if( hp < 1 ) hp = 1;
        set_temp("hj_hp", hp, me);
    }

    destruct( ob );
}

int do_look(string arg)
{
    if( !arg || !id(arg) ) return 0;

    write( query("long") );
    return 1;
}


string ask_quest_again()
{
    object me = this_player();
    if( me != query("checking_player") )
        return "不關你事。";

    if( !query("wait_ans") )
        return "急什麼，我忘了我要問什麼了。";

    command("say 看清楚點啊。");
    return query("quest");
}


void start_check()
{
    mapping question_info;
    object me;
    string shows_all, shows_color, shows_flag;

    if( !environment(this_object() ) ) return;

    me = query("checking_player");
    if( !me || ( !IS_TEST && !me_ok(me) ) ) return;

    question_info = get_question( PIC_NUMBER );

    message_vision("只見一個$n急急忙忙地走了過來，直沖到$N面前，張口就問了一個問題。\n",
        me, this_object() );

    tell_object(me,query("name")+"說道：“"+query("name", me)+"，我有一個問題想請教你，請你"HIR"務必要在三分鐘內回答"NOR"我。”\n");

    tell_object( me,  question_info [ "shows_all" ] );
    tell_object( me,  query("name")+"說道：“我看不出來 "+question_info[ "shows_color" ] +" 這個顏色的 "+question_info[ "shows_flag" ] + " 圖案在哪裡，你能告訴我它在什麼位置嗎？”\n");
    tell_object( me,  query("name")+"繼續說道：“從左往右數，你把它的位置告訴我就行了。”(ans 數字)\n");
    tell_object( me,  query("name")+"不厭其煩地說道：“如果你沒看清，你可以問我，我重復一次。”(ask mengmian ren about 問題)\n");

    set( "quest", question_info[ "shows_all" ] + "\n顏色："+ question_info[ "shows_color" ]+" 圖案："+question_info[ "shows_flag" ] + " ，請回答它的位置（從左到右數，<ans 數字>）。\n" );
    set( "quest_ans", question_info[ "answer" ] );
    set("wait_ans", 1);
    remove_call_out("delete_me");
    call_out("delete_me", 180 );
}

mapping get_question(int times)
{
    string
*show=({ }),
*flags=({"☆","★","○","●","◎","◇","◆","□","■","△","▲","□",}),
flag,
*cls=({HIR,HIC,HIG,HIY,HIW,HIM,}),
cl,
*bcls = ({HBRED,HBCYN,HBGRN,HBYEL,HBWHT,HBMAG,}),
bcl,
temp,
shows = "  ";

    string real_flag;
    int i,j,answer,temp_hh;

    if(!times || times < 5 || times > 100)
        times = 100;

    j = random( 6 );
    flag = flags[random(sizeof(flags))];
    cl = cls[ j ];
    bcl = bcls[ j ];

    real_flag = cl+flag+NOR;

    for(i=0;i<times;i++)
    {
        temp = get_flag(real_flag);
        show += ({ temp });
    }

    answer = 1+random(times);

    show[ answer-1 ] = real_flag;

    shows += "\n";
    for(i=0;i<sizeof(show);i++)
    {
        temp_hh ++;
        shows += show[i];
        if( temp_hh >= PIC_NUMBER / 2 )
        {
            temp_hh = 0;
            shows += "\n";
        }
    }
    shows += "\n\n";

    return ([ "shows_color": bcl+"    "+NOR,"shows_flag": flag+NOR,"shows_all" : shows,"answer":answer ]);

/************************************************
 格式說明：需要調用本函數時，需加參數：“次數”。
 返回值元素說明：
 shows_color :  玩家提示，顏色
 shows_flag  :  玩家提示，圖案
 shows_all   :  玩家提示，總圖
 answer      :  正確答案

演示流程：
1、先得到此函數返回值：
mapping test = SHOOTING_D->get_question(random(100));

2、在調用端操作，以顯示至表層：
string shows_all = test[ "shows_all" ];
string shows_color = test[ "shows_color" ];
string shows_flag = test[ "shows_flag" ];
int answer = test[ "answer" ];

write( shows_all );
write("這次的顏色是："+shows_color+"，圖案是："+shows_flag+"。\n");

3、正確答案，即 該圖案的正確位置，即“answer”值。

*************************************************/

}

string get_flag(string this_times)
{
    string
*flags=({"☆","★","○","●","◎","◇","◆","□","■","△","▲","□",}),
temp_flag,
*cls=({HIR,HIC,HIG,HIY,HIW,HIM,}),
temp_cls,
temp_wahaha;

    temp_wahaha = cls[random(sizeof(cls))] + flags[random(sizeof(flags))]+NOR;

    while( temp_wahaha == this_times )
        temp_wahaha = cls[random(sizeof(cls))] + flags[random(sizeof(flags))]+NOR;

    if( !random(2) ) temp_wahaha += " ";

    return temp_wahaha;
}