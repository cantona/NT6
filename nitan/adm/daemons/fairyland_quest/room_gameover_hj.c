//                標準描述長度示例                                   |
// “幻境”尋寶系列主題之退出（統計成績並獎勵）房間
// by naihe  2002-11-01
// 03-10-23  這個和別的文件不同，這個幾乎全部改過了，其他的充其量優化
// 代碼、改改設置，加JOB減JOB而已，hohoho
// 所以寫個日期。


#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include "temp/ctime_format_func.h"

// 巫師可以用 <mewiz> 指令設置是否允許玩家領取獎品。具體操作，請輸入 <mewiz> 指令獲得

// ########################################################
// ########################################################
// ########################################################

#define            HJ_OUTROOM_DATA    "/data/fairyland/outroom_data"
// 存儲文件

#define            IS_TEST              0
#define            TEST_AWARD_GXD       1


// 測試狀態時，只能以每 500 點得分換取 TEST_AWARD_GXD 點貢獻度。
// 並且在測試狀態時，將會進行 ID 判斷，未登記參與測試的ID，
// 即 "z_test_id_list.h"  的  test_id_list  內未登記的ID，
// 不予記錄 log ，以及不能得到分數。

// 若希望在測試狀態時不給予任何獎勵，此值 set 0.

// ########################################################
// ########################################################
// ########################################################

#include    "z_test_id_list.h"
// 該文件內僅包含一個 string* 變量： test_id_list.


#include     "z_hj_log_func.h"
// 此文件中定義了LOG文件的文件名：HJ1_LOG_FILE
// 以及 hj_log_file(string log_msg) 函數。
// 本文件及 獎品轉讓處 都使用 hj_log_file() 函數，而不直接使用 log_file() .


// 各類最高分
string
    HighName1 = "無", HighId1 = "--",
    HighName2 = "無", HighId2 = "--",
    HighName3 = "無", HighId3 = "--";

int    HighScore1 = 0, HighScore2 = 0, HighScore3 = 0;


int OkTimes, FailTimes, AllTimes, FindTimes;

string GetAward = "允許";


// 這裏調用子目錄內的一個價格文件
#include "npc_obj/hj_settings/obj_values.h"

// 這些 id 需要與遊戲內道具同步。
// 使用 #define 的方式，是它不會被 restore() 強制恢復，而造成更改時必須
// 先刪除 .o 的麻煩。

#define        all_ids        ([ "dx shuijing":"dx","fx zhishi":"fx","tl shuijing":"tl","hg zhijing":"hg", "qd zhishi":"qd","zh zhihe":"zh","fd zhiqi":"fd","qz zhiqi":"qz", "xr shuijing":"xr","kt shuijing":"kt", "cs zhitong":"cs","dw zhiyi":"dw", "wm guo":"wmg","xr guo":"xrg","tq guo":"tqg","dl guo":"dlg","ys guo":"ysg", "sl guo":"slg", "qt jian":"qtj","lq jian":"lqj","by jian":"byj","yd jian":"ydj", "hj jian":"hjj","nl jian":"nlj","xy jian":"xyj","dh jian":"dhj","bs jian":"bsj", "kf sj":"kfsj","by sj":"bysj","ll sj":"llsj","yd sj":"ydsj","gs sj":"gssj","fh sj":"fhsj","dh sj":"dhsj", "hufeng shi":"hfzs","huanyu shi":"hyzs","luolei shi":"llzs","yindian shi":"ydzs","gunshi shi":"gszs","feihuo shi":"fhs","duohun shi":"dhzs","fuhuo shi":"fhzs" ])


string query_save_file()
{
    return HJ_OUTROOM_DATA;
}

void setlong();

int me_ok( object me )
{
    if( !me || !environment(me) || environment(me) != this_object()
       || query("is_checking") != query("id", me )
       || (query_temp("huanjing", me) != "fail" && query_temp("huanjing", me) != "over" )
    )
        return 0;
    return 1;
}

void create()
{
    restore();
    set("short",HIW"迴歸之路"NOR);
    setlong();
    delete("is_checking");
    // 這個一定要
    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);
    set("exits",([
        "out" : __DIR__"room_door_hj",
    ]));
    setup();
}

void init()
{
    if( wizardp(this_player()) )
        add_action("do_mewiz","mewiz");
    add_action("YEAH","YEAH");
    add_action("prize","YEAH!!!");
    add_action("outout", "outout");
    // 禁止指令
    add_action("no_do_cmds", ({ "get", "put", "drop" }) );
}

int do_mewiz(string arg)
{
    object me=this_player();
    string f_name, msg;

    if( !wizardp(me) )
        return 0;
    if( !arg )
        arg = ".";
    f_name = LOG_DIR + get_log_file_name() + ".c";
    if( arg == "cklog" )
    {
        if( IS_TEST )
            msg = "現在是測試狀態，默認的LOG文件是："+f_name+"\n";
        else
            msg = "現在是正常狀態，現在的LOG文件是："+f_name+"\n";
        me->start_more_file( f_name );
        write( msg );
        return 1;
    }
    if( arg == "允許" || arg == "不允許" )
    {
        if( GetAward == arg )
            return notify_fail("現在已經是這個設置了。\n");
        GetAward = arg;
        save();
        return notify_fail("設置成功！現在開始，符合條件的玩家 "+GetAward+" 領取獎品。\n請注意，這個設置將會在本房間重載後被取消，而恢復為默認設置。\n");
    }
    write("現在 "+GetAward+" 玩家領取獎品。以指令 <mewiz 允許/不允許> 來更改這個設置。\n現在默認的LOG文件是："+f_name+" 。\n以指令 <mewiz cklog> 快速查看這個文件。\n");
    return 1;
}

void reset()
{ 
    ::reset(); 
    set("no_clean_up", 1); 
}

int valid_leave(object me, string dir)
{
    object *all_mine;
    int temp, i;

    if( query("is_checking") == query("id", me) )
        return notify_fail("現在正在計算你的得分，請稍等再離開。\n");
    all_mine = deep_inventory(me);
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( query("hj_game", all_mine[i]) )
            {
                temp = 1;
                break;
            }
        }
    }
    if(temp)
        return notify_fail( HIR"你身上還攜帶着幻境相關的物品，請先計算得分再離開。\n"
            "若你執意要離開，可使用 outout 指令，那麼你的得分及所有攜帶的幻境物品將被清除。\n"NOR );
    if( query_temp("huanjing", me) == "fail" || query_temp("huanjing", me) == "over" )
        return notify_fail(HIR"你未曾計算你的遊戲得分，請先計算得分再離開。\n"
            "若你執意要離開，可使用 outout 指令，那麼你的得分及所有攜帶的幻境物品將被清除。\n"NOR);
    if( query_temp("hj_score", me) )
        return notify_fail(HIR"你未曾把你的得分全部兑獎！請先對獎完畢再離開。\n"
            "若你執意要離開，可使用 outout 指令，那麼你的得分及所有攜帶的幻境物品將被清除。\n"NOR);
    return ::valid_leave(me, dir);
}

int outout()
{
    object me = this_player(), *all_mine;
    int i;

    all_mine = deep_inventory(me);
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( query("hj_game", all_mine[i]) )
                destruct( all_mine[i] );
        }
    }
    delete_temp("hj_score", me);
    delete_temp("huanjing", me);
    message_vision( HIR"\n$N"HIR"使用了強制指令，離開了這裏。\n"NOR, me );
    me->move( query("exits/out") );
    message_vision( "$N走了過來。\n",me );
    return 1;
}

int no_do_cmds()
{
    if( !wizardp( this_player() ) )
    {
        write("在這裏你不允許使用這個指令。\n");
        return 1;
    }
    return 0;
}

string get_TOP_pic()
{
    string c1 = HIB, c2 = HIY, c3 = HIC, c4 = HIG;

    return sprintf(c1+"
 ┏━━━━┳━━━━━━━━━━┳━━━━━━┓
 ┃"+c2+"最高總分"+c1+"┃"+c2+"%|20s"+c1+"┃"+c2+"%|12d"+c1+"┃
 ┣━━━━╋━━━━━━━━━━╋━━━━━━┫
 ┃"+c3+"最高得分"+c1+"┃"+c3+"%|20s"+c1+"┃"+c3+"%|12d"+c1+"┃
 ┣━━━━╋━━━━━━━━━━╋━━━━━━┫
 ┃"+c4+"最高效率"+c1+"┃"+c4+"%|20s"+c1+"┃"+c4+"%6|d /小時"+c1+"┃
 ┣━━━━┻━━┳━━━━┳━━┻━┳━━━━┫
 ┃"HIW"總人次%|8d"+c1+"┃"HIC"勝%|6d"+c1+"┃"HIM"敗%|6d"+c1+"┃"HIY"寶%|6d"+c1+"┃
 ┗━━━━━━━┻━━━━┻━━━━┻━━━━┛\n"NOR, 

    HighName1+"("+HighId1+")", HighScore1,
    HighName2+"("+HighId2+")", HighScore2,
    HighName3+"("+HighId3+")", HighScore3,
    AllTimes, OkTimes, FailTimes, FindTimes);
}

void setlong()
{
    set("long", "
            "HIW"【 回 歸 現 實 之 路 】
"NOR+get_TOP_pic()+HIW"
      來吧，踏上回歸現實之路，忘掉你所經歷的
    幻境之事，從這裏的虛幻中走出，你將回歸你那
  美麗燦爛的陽光之地，你將會記得你真正應該的所在。
"NOR"
  計算你的得分與兑換遊戲獎勵：< "HIG"YEAH"NOR" / "HIY"YEAH!!!"NOR" >\n");
}


// ####################################################
// ############## 以下是計算得分的函數 ################
// ####################################################

int YEAH()
{
    int temp_score;
    object me = this_player();

    temp_score=query_temp("hj_score", me);

    if( !query_temp("huanjing", me) && temp_score )
        return notify_fail("你的得分已經計算過了。請輸入 <YEAH!!!> 指令查詢領獎。\n");

    if( query_temp("huanjing", me) != "fail" && query_temp("huanjing", me) != "over" )
    {
        delete_temp("hj_score", me);
        return notify_fail("快快回歸現實，莫要停留幻境！\n");
    }

    if( query("is_checking") )
        return notify_fail("現在正計算 "+query("is_checking")+" 的得分，請稍等。\n");
    set("is_checking",query("id", me));

    // 遊戲得分單項最高記錄
    message_vision(HIW"\n$N開始計算自己的得分……\n\n"NOR,me);
    message_vision(HIC"$N"HIC"的遊戲內得分為："HIY+temp_score+HIC" 點。\n"NOR, me);

    if( temp_score > HighScore2 )
    {
        if( query_temp("huanjing", me) == "fail" )
            message_vision(HIY"\n$N"HIY"的遊戲任務得分超過了最高記錄！只可惜是失敗歸來的。\n"NOR,me);
        else
        {
            message_vision(HIY"\n$N"HIY"打破了遊戲任務得分的單項最高記錄！\n"NOR, me);
            set("huanjing2003/gift", "打破任務得分單項最高記錄", me);
            HighScore2 = temp_score;
            HighName2=query("name", me);
            HighId2=query("id", me);
            setlong();
        }
    }
    write(HIW"\n現在計算你攜帶的 常規道具物品 加分……\n"NOR);
    remove_call_out("score_tools");
    call_out( "score_tools", 2, me);
    return 1;
}

void score_tools( object me )
{
    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "你的各類常規道具物品加分如下：\n\n");
    // 這裏用一個很羅嗦的判斷來寫，雖然比原先的耗N倍資源，又慢，但是
    // 我認為這樣有效果，有氣氛，就愛這麼做。
    remove_call_out("score_tools_go");
    call_out( "score_tools_go", 1, me, 0, 0);
}

void score_tools_go( object me, int score, int hj_obj_amount )
{
    object *inv_me, temp;
    int i, temp_score;
    string temp_id;

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    inv_me = all_inventory(me);
    if(inv_me && sizeof(inv_me) > 1)
    {
        for(i=0;i<sizeof(inv_me);i++)
        {
            temp = inv_me[i];

            if( !query("hj_game/obj", temp) )
                continue;

            set("value", 0, temp);
            temp_id=query("id", temp);

            if( !all_ids[temp_id] || !all_values[all_ids[temp_id]] )
                continue;

            hj_obj_amount ++;
            temp_score = all_values[all_ids[temp_id]] / 3;
            if( temp_score < 1 ) temp_score = 1;
            tell_object( me, sprintf("一%s %s(%s) ，可獲得 %d 點遊戲得分。\n",
            query("unit", temp),query("name", temp),query("id", temp),temp_score));
            destruct(temp);
            score += temp_score;
            remove_call_out("score_tools_go");
            call_out( "score_tools_go", 1, me, score, hj_obj_amount );
            return;
        }
    }

    message_vision("\n$N共有常規道具 "+hj_obj_amount+" 件，得分是 "+score+" 點。\n", me);
    addn_temp("hj_score", score, me);
    tell_object( me, HIW"\n現在計算你攜帶的 特殊物品 加分……\n"NOR);
    remove_call_out("score_special_tools");
    call_out("score_special_tools", 2, me );
}

void score_special_tools( object me )
{
    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "你的各類特殊道具物品加分如下：\n\n");
    // 同上邊一樣，我愛這樣做！！！
    remove_call_out("score_sp_tools_go");
    call_out( "score_sp_tools_go", 1, me, 0, 0);
}

void score_sp_tools_go( object me, int score, int hj_obj_amount )
{
    object *inv_me, temp;
    int i, temp_score;
    string temp_id, temp_msg;

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    inv_me = all_inventory(me);
    if(inv_me && sizeof(inv_me) > 1)
    {
        for(i=0;i<sizeof(inv_me);i++)
        {
            temp = inv_me[i];
            temp_msg = "none";

            if( !query("hj_game/obj", temp) )
                continue;

            hj_obj_amount ++;

            set("value", 0, temp);
            temp_id=query("id", temp);

            // 國家寶物額外加分
            if(temp_id == "tmxk yyf" || temp_id == "xlsq szl"
              || temp_id == "wm slzj" || temp_id == "sxzy dsg"
            )
            {
                // 若非本人的，或者有 “假”的標記，只加一部分(相對真的來説)。
                if( !query("host_id", temp )
                   || query("host_id", temp) != query("id", me )
                   || query("fake", temp )
                )
                {
                    temp_score = 500;
                    temp_msg = "並非你要找尋的";
                }
                // 否則就高分
                else
                {
                    // 這個標記是為了防止以 “寶物的累積 -> 一次性帶出” 的方法來衝擊高分記錄的 :)
                    // 雖然現在這樣也行，不過這可虧很多了，呵呵。
                    // 更詳細的信息可以看 _qxd_.c 的 3 號主文件
                    if( query("this_time_mark", temp) != 
                        query_temp("this_time_mark", me) )
                    {
                        temp_score = 500;
                        temp_msg = "不是你這一次要找尋的";
                    }
                    else
                    {
                        temp_score = 1500;
                        temp_msg = "屬於你的";
                        FindTimes ++;
                    }
                }
            }

            // 其他組成部分的額外加分
            if(temp_id=="tm shen" || temp_id=="sz zuoyi" || temp_id=="sz youyi"
              || temp_id=="lq shou" || temp_id=="jy lei" || temp_id=="mh xin"
              || temp_id=="sl jian" || temp_id=="dz shi" || temp_id=="rr shao"
              || temp_id=="hongse baoshi" || temp_id=="lanse baoshi" || temp_id=="lvse baoshi"
            )
            {
                // 若非本人的，扣分！
                if( !query("host_id", temp )
                   || query("host_id", temp) != query("id", me )
                )
                {
                    temp_score = -200;
                    temp_msg = "並非你要找尋的";
                }
                // 否則還是有一點獎勵的
                else
                {
                    temp_score = 200;
                    temp_msg = "屬於你的";
                }
            }
            // 各族權杖加分
            if( member_array( temp_id, ({ "manye quanzhang", "mengli quanzhang",
                "aiyao quanzhang", "shanguai quanzhang", "juren quanzhang",}) ) != -1
            )
            {
                temp_msg = "神祕的";
                temp_score = 50;
            }
            // 各族寶物加分
            if( member_array( temp_id, ({ "manye baowu", "mengli baowu",
                "aiyao baowu", "shanguai baowu", "juren baowu",}) ) != -1 )
            {
                temp_msg = "珍貴的";
                temp_score = 100;
            }
            // 其他的一律刪除，獎勵 1 分。
            if(temp_msg == "none" )
            {
                temp_msg = "已無用處的";
                temp_score = 1;
            }
            tell_object( me, sprintf("一%s "+temp_msg+" %s(%s) ，可獲得 %d 點遊戲得分。\n",
                query("unit", temp),query("name", temp),query("id", temp),temp_score));
            score += temp_score;
            destruct(temp);
            remove_call_out("score_sp_tools_go");
            call_out( "score_sp_tools_go", 1, me, score, hj_obj_amount );
            return;
        }
    }
    message_vision("\n$N共有特殊物品 "+hj_obj_amount+" 件，得分是 "+score+" 點。\n", me);
    addn_temp("hj_score", score, me);
    tell_object( me, HIW"\n現在計算你的最後得分……\n"NOR);
    remove_call_out("score_all");
    call_out("score_all", 2, me );
}


void score_all( object me )
{
    object *inv_me, temp;
    int i, hj_obj_amount, score, temp_score, e_time,o_time, g_time, xiaolv;
    string temp_id, temp_msg, msg = "";

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "你的其他加分以及最後得分如下：\n\n");

    // 級別加分
    temp_score=query("huanjing2003/lv", me)*20;//由50改為20naihe05-9-710:14
    if( temp_score == 450 )  // 9 級滿級
        temp_score = 200;                            // 由500改為200   naihe 05-9-7 10:14
    msg += "級別得分：" + temp_score+" 點。\n";
    score += temp_score;
    temp_score = 0;

    // 氣息加分
    temp_score=(query_temp("hj_hp_max", me )
            -(query_temp("hj_hp_max", me)-query_temp("hj_hp", me)))/10;
    if( temp_score < 0 ) temp_score = 0;
    msg += "氣息得分：" +temp_score+ " 點。\n";
    score += temp_score;
    temp_score = 0;

    // 力量加分
    temp_score=query_temp("hj_game_mepower", me)/2;
    if( temp_score < 0 ) temp_score = 0;
    msg += "力量得分："+ temp_score +" 點。\n";
    score += temp_score;
    temp_score = 0;

    addn_temp("hj_score", score, me);
    tell_object( me, msg );

    // 計算完畢！計算效率
    score=query_temp("hj_score", me);
    e_time=query_temp("hj_enter_time", me);
    o_time=query_temp("hj_out_time", me);
    if( e_time && o_time && o_time > e_time ) g_time = o_time - e_time;

    if( g_time )
    {
        xiaolv = score * 3600 / g_time;
        msg=sprintf("遊戲時間共%d小時%d分%d秒，依此推算，$N"HIC"的幻境遊戲得分效率為每小時 %d 點！",
            g_time / 3600, g_time % 3600 / 60, g_time % 3600 % 60, xiaolv);
    }
    else
    {
        xiaolv = 0;
        msg = "由於$N"HIC"沒有進入或退出遊戲的時間記錄，無法計算效率。";
    }

    message_vision(HIC"\n$N"HIC"的最終得分是："+score+" 點！\n"+msg+"\n\n"NOR, me);
    if( score > HighScore1 )
    {
        if( query_temp("huanjing", me) == "fail" )
            message_vision(HIY"$N"HIY"的最終得分超過了最高記錄，只可惜是失敗歸來的。\n"NOR, me);
        else
        {
            message_vision(HIY"$N"HIY"打破了總成績的最高記錄！！！\n"NOR, me);
            set("huanjing2003/gift", "打破總成績最高記錄", me);
            HighScore1 = score;
            HighName1=query("name", me);
            HighId1=query("id", me);
            setlong();
        }
    }

    if( xiaolv > HighScore3 )
    {
        if( query_temp("huanjing", me) == "fail" )
            message_vision(HIY"$N"HIY"的效率超過了最高記錄，只可惜是失敗歸來的。\n"NOR,me);
        else
        {
            message_vision(HIY"$N"HIY"打破了效率最高記錄！\n"NOR, me);
            set("huanjing2003/gift", "打破效率最高記錄", me);
            HighScore3 = xiaolv;
            HighName3=query("name", me);
            HighId3=query("id", me);
            setlong();
        }
    }

    // 失敗否？
    if( query_temp("huanjing", me) == "fail" )
    {
        FailTimes ++;
        message_vision(HIR"很遺憾，$N"HIR"是失敗歸來的，所有得分將作廢。\n祝$N"HIR"下次能夠取得好成績，領取更多的獎勵！\n"NOR,me);
        // 若是測試時，必須要在ID LIST 內的玩家才記入 LOG.
        if( !IS_TEST || member_array(query("id", me),test_id_list) != -1 )
            hj_log_file( sprintf("\n○( %s - %s )\n○  %s(%s) ：遊戲 %d 時 %d 分 %d 秒，得分 %d (失敗，得分作廢)。\n",
                e_time ? ctime_format( e_time ) : "無進入時間記錄",
                o_time ? ctime_format( o_time ) : "無退出時間記錄",
                query("name", me),getuid(me),
                g_time ? g_time / 3600 : 0,
                g_time ? g_time % 3600 / 60 : 0,
                g_time ? g_time % 3600 % 60 : 0,
                query_temp("hj_score", me)));

        delete_temp("hj_score", me);
    }
    else
    {
        OkTimes++;

        // 若是測試時，必須要在ID LIST 內的玩家才記入 LOG.
        // 成功類的LOG使用實心圓形標記，查看起來清晰。
        // 而這兩個LOG都用了標記，是為了在查看時和其他LOG分開，清晰點。
        if( !IS_TEST || member_array(query("id", me),test_id_list) != -1 )
            hj_log_file( sprintf("\n●( %s - %s )\n●  %s(%s) ：遊戲 %d 時 %d 分 %d 秒，得分 %d 。%s\n",
                e_time ? ctime_format( e_time ) : "無進入時間記錄",
                o_time ? ctime_format( o_time ) : "無退出時間記錄",
                query("name", me),getuid(me),
                g_time ? g_time / 3600 : 0,
                g_time ? g_time % 3600 / 60 : 0,
                g_time ? g_time % 3600 % 60 : 0,
                query_temp("hj_score", me),
                xiaolv ? "(效率："+ xiaolv +" / 小時 )" : "(效率未知)") );


        /*
        if( score > 10000 )
        {
            message_vision("$N的得分是 "+score+" 點，超過了上限，按 10000 點計算。\n", me);
            set_temp("hj_score", 10000, me);
        }
        */

        message_vision(HIW"恭喜$N"HIW"成功歸來，將得到所有的遊戲分數！請輸入 <YEAH!!!> 指令查詢獎品兑換。\n"NOR,me);
    }

    delete_temp("huanjing", me);

    // 記錄該玩家本次的技能、力量。
    // 該數據將在下一次進入遊戲時被七星燈判斷使用，
    // 這裏不作任何判斷。

    set("huanjing2003/last_power",query_temp("hj_game_mepower",  me), me);
    set("huanjing2003/last_skills_name",query_temp("hj_game_skills",  me), me);
    set("huanjing2003/last_skills_lv",query_temp("hj_game_damages",  me), me);
    // 即使玩家沒有該項數值，也設只不過是設個 0 罷了。燈那邊會處理。

    me->save();

    delete("is_checking");
    AllTimes ++;
    setlong();
    save();
    // 只有在這裏的時候才 save() .

    if( IS_TEST && !TEST_AWARD_GXD )
    {
        message_vision(HIY"\n由於現在是測試期間，並且沒有任何獎勵，$N"HIY"的得分被清除了。\n\n"NOR, me);
        delete_temp("hj_score", me);
    }

    if( IS_TEST && member_array(query("id", me),test_id_list) == -1 )
    {
        message_vision(HIY"\n由於現在是測試期間，並且$N"HIY"沒有報名參加測試，$N"HIY"的得分被清除了。\n\n"NOR, me);
        delete_temp("hj_score", me);
    }
}


// ############## 上面是計算得分的函數 ################

// ####################################################
// ############## 以下是領取獎品的函數 ################
// ####################################################

#include "z_gameover_hj.h"
