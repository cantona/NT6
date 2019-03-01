//                標準描述長度示例                                   |
// 玩家與幻境之啟動房間 之進入間
// 所有售票、檢票等相關工作在此進行，符合條件的玩家，將可以轉移至下一個通道房間內。
// by naihe  2002-11-03  于茂名

// 已經改變了許多許多許多了……
// naihe 17:07 03-11-1 

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include "temp/ctime_format_func.h"

// 該文件定義遊戲地圖大小
#include "npc_obj/hj_settings/room_amount_hj.h"
// 該文件定義遊戲版本號  HJ2003_VERSION
#include "npc_obj/hj_settings/game_version.h"

// ##################################
// ##########  一些宏定義 ###########
// ##################################
#define        HJ_DOOR_DATA    "/data/fairyland/door_data"
// 儲存資料的文件名
#define        HJ_ROOM_CREATE_D    "/adm/daemons/hj_room_created"
// 該文件擁有足夠權限進行寫文件的操作。

#ifndef        HJ_DIR
#define        HJ_DIR        __DIR__
#endif


////////////////////////////////////////////////////
//// 以下數值可以指令 (mewiz) 更改，並自動儲存 /////
////////////////////////////////////////////////////

int GAME_OPEN = 1;
// 本遊戲是否開放。 1開放，0關閉
// 關閉時，任何人不得進入（巫師進入了也無法遊戲）
// 可以用 mewiz 指令更改值，重啟動後亦不會恢復！

int FREE_GAME = 0;
// 免費遊戲， 1 開放，0關閉
// 本設置必須在 GAME_OPEN 為開放狀態時才有效。
// 說明同上

int MAX_HJ_ENTER = 10;
// 最大場內人數。超過此人數時，玩家不得繼續進入遊戲。

int MP_GOLD = 20;
// 門票價格（黃金），使用錢莊轉帳

int MSG_GOLD = 5;
// 信息價格，使用錢莊轉帳

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

// ##################################
// ##########  各類統計  ############
// ##################################

// 進入人次，收入情況
int in_times, max_in_hj, in_money, buy_piao_times, buy_sm_times, buy_msg_times;

mapping player_level_info = ([ ]);

// ##################################
// ##################################


string look_ban();
string look_pai();
string del_player_level( string id );
void lucky( object me );

string query_save_file()
{
    return HJ_DOOR_DATA;
}

// 這個方法使被房間記錄的數據不被清除。至于非本房間所屬NPC、物品，若想不被更新，則需要再其上設置 no_refresh 標記
void reset()
{
    ::reset();
    set("no_clean_up", 1);
}

// 設置這裡的隨機顏色地點名
void hjset_short()
{
    string *color;
    string cl1, cl2, cl3, cl4, cl5, cl6, cl7;
    int size;

    color = ({ HIY, HIR, HIB, HIG, HIC, HIW, HIM });

    // 隨機去掉4個顏色，那麼7個字相同顏色的概率就大了很多很多
    if( !random(5) )
    {
        size = 4;
        while( size-- ) color -= ({ color[ random( sizeof(color) ) ] });
    }

    size = sizeof( color );
    cl1 = color[ random(size) ];
    cl2 = color[ random(size) ];
    cl3 = color[ random(size) ];
    cl4 = color[ random(size) ];
    cl5 = color[ random(size) ];
    cl6 = color[ random(size) ];
    cl7 = color[ random(size) ];

    set("color_short_hj",cl1+"遙"+cl2+"遠"+cl3+"傳"+cl4+"說"+cl5+"之"+cl6+"起"+cl7+"緣"NOR);
    set("short", MAG"幻境2003 "+HJ2003_VERSION+NOR );

    if( cl1 == cl2 && cl1 == cl3 && cl1 == cl4 && cl1 == cl5 && cl1 == cl6 && cl1 == cl7 )
        set("same_color", 1);
    else set("same_color", 0);
}

mapping who_in_hj()
{
    object rooms, *in_env;
    int i,j,amount;
    string msg, *all_ip=({});

    msg = "";
    // 包括正待進入的兩個地點
    rooms = find_object( __DIR__"room_master_hj");
    if( rooms )
    {
        in_env = all_inventory( rooms );
        if( in_env && sizeof(in_env) )
        {
            for( j=0;j<sizeof(in_env);j++ )
            {
                if( userp(in_env[j]) )
                {
                    amount++;
                    msg += sprintf( "%s\n",
                        in_env[j]->short());
                    all_ip += ({ query_ip_name( in_env[j] ) });
                }
            }
        }
    }

    rooms = find_object( __DIR__"room_readygo_hj");
    if( rooms )
    {
        in_env = all_inventory( rooms );
        if( in_env && sizeof(in_env) )
        {
            for( j=0;j<sizeof(in_env);j++ )
            {
                if( userp(in_env[j]) )
                {
                    amount++;
                    msg += sprintf( "%s\n",
                        in_env[j]->short());
                    all_ip += ({ query_ip_name( in_env[j] ) });
                }
            }
        }
    }

    // 密林內玩家
    for( i=1;i<=HJ_ROOM_AMOUNT;i++ )
    {
        rooms = find_object( __DIR__"hj_room"+i );
        if( !rooms ) continue;
        in_env = all_inventory( rooms );
        if( !in_env || !sizeof(in_env) ) continue;
        for( j=0;j<sizeof(in_env);j++ )
        {
            if( userp(in_env[j]) )
            {
                amount++;
                msg += sprintf( "%s\n",
                    in_env[j]->short());
                all_ip += ({ query_ip_name( in_env[j] ) });
            }
        }
    }

    if( !amount ) msg = "幻境內現在沒有任何玩家。\n";
    else  msg = "包括正待進入的以及幻境密林內，現在共有"+chinese_number( amount )+"位玩家：\n" + msg;

    if( amount > max_in_hj )
    {
        max_in_hj = amount;
        save();
    }

    set( "all_ip_in_hj", all_ip );
    return ([ "amount": amount, "info": msg ]);
}


// 奈何按：門口的效果寫了2個小時！單單是描述的幾句文字，大小地方
//         改了8次，嘿。
void hjset_long()
{
    mapping temp;
    string temp_str, longs;

    if( !GAME_OPEN ) temp_str = HIR"     (遊戲關閉)"NOR;
    else if( FREE_GAME )
        temp_str = sprintf( HIC"(免費開放﹒場內%2d人)"NOR,
                who_in_hj()["amount"] );
    else temp_str = sprintf( HIG"(正常開放﹒場內%2d人)"NOR,
                who_in_hj()["amount"] );

    longs= "\n        　 "HIW"□──────────────────────□     
           "NOR+WHT"□□   "NOR+WHT"幻境 ﹒ "+query("color_short_hj")+NOR+WHT" ﹒ 幽靈顯現"NOR+WHT"   □□     
           "NOR+HIW"□□            "NOR+WHT"BY naihe 2003.10"NOR+HIW"            □□     
           "NOR+WHT"□──────────────────────□     "NOR"
                         "+temp_str+"

    你踏進了一處幽暗的所在，四周似有隱約光亮，卻又無法覓其源頭。一塊
  巨大的木板(ban)飄忽地于你身前不遠之處隱現，巨板下帶著一塊小木牌(pai)。
這裡便是傳說中的“幻境”與現實之間的接口，由此而進，你將隨之步入那神秘的
                          幻境之地，不復存在……

    ----------------------------------------------------------------\n";

    // 格式
    //    set("player_msg3", ([ "id": "12345678", "time":"03.10.24", "msg":"啦啦" ]) );
    if( query("player_msg1") )
    {
        temp = query("player_msg1");
        longs += sprintf("    【 %-8s 發布消息(%8s):%-32s】\n", 
            temp[ "id" ], temp[ "time" ], temp["msg"] );
    }
    if( query("player_msg2") )
    {
        temp = query("player_msg2");
        longs += sprintf("    【 %-8s 發布消息(%8s):%-32s】\n", 
            temp[ "id" ], temp[ "time" ], temp[ "msg" ] );
    }
    if( query("player_msg3") )
    {
        temp = query("player_msg3");
        longs += sprintf("    【 %-8s 發布消息(%8s):%-32s】\n", 
            temp[ "id" ], temp[ "time" ], temp[ "msg" ] );
    }

    if( !query("player_msg1") && !query("player_msg2") && !query("player_msg3") )
        longs += sprintf("             【 %s 】\n", "現在沒有玩家發布信息 (指令：hjmsg 內容)");

    set( "long", longs + 
"    ----------------------------------------------------------------\n" );
}

void create()
{
    restore();
    // 載入歷史統計
    if( !query("begin_time") )
        set("begin_time", time() );

    hjset_short();
    hjset_long();

    // 這是個長期公布的信息
    if( random(3) )
        set("player_msg1", ([ "id": "naihe", "time":"03.10.24",
            "msg":"最佳字體：宋體小四(12)或小五(10)" ]) );

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("valid_startroom", 1);

    set("item_desc",([
        "ban": (: look_ban :),
        "pai": (: look_pai :),
    ]));

    set("exits", ([
        "down":"/d/city/guangchang",  // 揚州中央廣場使用 jump 指令進入。
        "enter":__DIR__"room_master_hj",
        "up":__DIR__"room_cession_hj",
        ]));

// 附： cs 代碼：
/*
void init()
{
    add_action("do_enter_hj", "jump");
}

int do_enter_hj(string arg)
{
    object rooms, me=this_player();
    if( !arg || arg != "up" ) return 0;

    rooms = find_object( "/adm/daemons/huanjing2003/room_door_hj" );
    if( !rooms ) rooms = load_object( "/adm/daemons/huanjing2003/room_door_hj" );
    if( !rooms ) return 0;

    tell_room(environment(me),query("name", me)+"使勁地往上一跳，突然卷來一陣旋風，"+query("name", me)+"頓時被風刮得不知所蹤。\n",me);
    me->move(rooms);
    write("你使勁地往上一跳，忽地平地卷起一陣旋風，恍惚中你已來到了「幻境」。\n");
    tell_room(rooms,"忽然一陣旋風襲過，"+query("name", me)+"已出現在這裡。\n",me);
    return 1;
}
*/

    setup();
}

void init()
{
    object me = this_player();
    
    if( !userp(me) || !living(me) )
        return;
    delete_temp("hj2003-valid_enter", me);
    if( query_temp("hj_apply_short", me) )
    {
        delete_temp("hj_apply_short", me);
        delete_temp("apply/short", me);
    }
    if( wizardp(me) )
    {
        add_action("do_mewiz","mewiz");
        add_action("do_create_room_file", "create_room_file");
    }
    add_action("do_maipiao","maipiao");
    add_action("do_goumai","goumai");
    add_action("do_msg", "hjmsg");
    add_action("do_top", "top");
    add_action("do_huanjing", "huanjing");
    add_action("do_who_in_hj", "gwho");
    add_action("do_look", "look");

    if( !query("huanjing2003", me )
       || !mapp(query("huanjing2003", me) )
    )
    {
        delete("huanjing2003", me);
        set("huanjing2003/welcome_to_hj_time", ctime_format(), me);
    }

    // 這兩句是刪除以前的版本時，給玩家添加的信息的。
    delete("aaaaa_hj_award", me);
    delete("aaaaa_hj_gift", me);

    // 刪除非法的 level 。
    if( query("huanjing2003/lv", me) && undefinedp(player_level_info[getuid(me)]) )
    {
        delete("huanjing2003/lv", me);
        me->save();
        call_out( "xxxxx", 1, me );
    }
    hjset_short();
    hjset_long();
    if( query("same_color") )
    {
        me->start_busy(5);
        lucky( me );
    }
}

void xxxxx( object me )
{
    if( !me ) return;
    message_vision( "$N只覺得身體發生了一些變化，$N的“幻境”等級被刪除了……請聯系幻境巫師。\n", me);
}


void lucky( object me )
{
    if(!me || !environment(me) || environment(me) != this_object() ) return;

    message_vision("
$N剛走過來，突然一陣轟動之聲大作，只見旁邊沖出來幾個怪模怪樣的人！
其中一個樣貌古怪的女子說對著$N說道：“恭喜恭喜！幻境正在發放特別獎勵，你是這次的幸運者！”
另外一個比較像正常人的男子接著說道：“你若要進入幻境的話，將獲得特別的獎勵！”
只見他手一揮似的動作，$N覺得微微一震，就像被什麼東西輕輕碰撞了一下一般！
這幾個人忽來忽去，說話間竟然就此退下，往裡面進去了。\n\n",me);
    set("huanjing2003/gift", "幸運", me);
    me->save();
}

int do_look(string arg)
{
    if( !arg ) hjset_long();
    return 0;
}

string look_pai()
{
    return "#################################################################################
本遊戲需要買票進入，除非遊戲免費開放。價格 "+HIR+MP_GOLD+NOR" GOLD，指令："HIY"(maipiao)"NOR"
常年發售遊戲說明手冊，價格 "HIR"1"NOR" GOLD。指令： "HIY"(goumai shuoming)"NOR"
玩家可以發布信息，價格 "+HIR+MSG_GOLD+NOR" GOLD。指令："HIY"(hjmsg)"NOR"
玩家可以查詢誰在幻境遊戲裡，指令："HIY"(gwho)"NOR"
幻境遊戲相關公告及資訊，指令："HIY"(huanjing list)"NOR"
#################################################################################\n";
}

int do_who_in_hj()
{
    write( who_in_hj()[ "info" ] );
    return 1;
}

int do_huanjing( string arg )
{
    string *dirs;
    string msg;
    int i;

    if( !arg ) return notify_fail("這個指令可以讓你查看幻境遊戲的一些公告和其他信息。\n請輸入 (huanjing list) 指令查看列表。\n");

    if( arg == "list" )
    {
        dirs = get_dir( __DIR__"other_info/" );
        if( !dirs || sizeof( dirs ) < 1 )
            return notify_fail("現在沒有任何記錄。\n");
        msg = "============= 下面是幻境遊戲的公告及信息記錄：=============\n\n";

        for( i=0; i<sizeof( dirs ); i++ )
        {
            msg += sprintf( "『幻境遊戲活動記錄』  --  %s\n",
                replace_string( dirs[i], ".txt", "" ) );
        }

        msg += "\n========== 請以指令 (huanjing 記錄名) 查看內容 ===========\n";
        this_player()->start_more( msg );
        return 1;
    }

    if( file_size( __DIR__"other_info/"+ arg +".txt" ) < 1 )
        return notify_fail("無該記錄或該記錄無內容。\n");

    msg = read_file( __DIR__"other_info/"+ arg + ".txt" );
    if( !msg ) return notify_fail("無法讀取該記錄內容。\n");

    msg = "============== "+arg+ " 內容全文 ==============\n\n"+ msg + "\n\n===================================================\n";
    this_player()->start_more( msg );
    return 1;
}


int do_goumai(string arg)
{
    object me=this_player(),gold;

    // 已刪除此物件
    return notify_fail("請直接輸入 help hj2003 查詢遊戲說明。\n");

    if(!arg || arg!="shuoming")
        return notify_fail("購買遊戲說明手冊，價格1 GOLD，指令 <goumai shuoming> 。\n");

    gold = present("gold_money",me);
    if(!gold) return notify_fail("你身上沒有黃金。\n");
    gold->add_amount(-1);
    new(__DIR__"other_obj/obj_shows")->move(me);
    message_vision("$N掏出一兩黃金，買下了一本遊戲說明手冊。\n",me);
    in_money ++;
    buy_sm_times ++;
    save();
    return 1;
}

string look_ban()
{
    object out_room;

    write("
       □□□□□□□□□□□□□□□□□□
       □ "WHT"幻境﹒"+query("color_short_hj")+NOR+WHT"﹒幽靈顯現"NOR" □
       □□□□□□□□□□□□□□□□□□
");

    out_room = find_object( __DIR__"room_gameover_hj" );
    if( !out_room ) out_room = load_object( __DIR__"room_gameover_hj" );
    if( out_room ) write( out_room->get_TOP_pic()+"\n"NOR);

    if(wizardp(this_player()))
        write("\n你是巫師，可使用 <mewiz> 指令。具體請查詢 <mewiz> 。");

    return "\n";
}

int do_top(string arg)
{
    if( !arg || (arg != "hj" && arg != "huanjing") )
        return 0;

    write("大木板上正寫著最高成績記錄呢。\n");
    return 1;
}

int do_msg( string arg )
{
    object me = this_player();
    string time;

    if( !arg ) return notify_fail("<hjmsg> 指令可以讓你在幻境入口處發布信息。
每次發布信息需要 "HIR+MSG_GOLD+" 兩黃金 "NOR"，在錢莊自動轉帳。
你只能發布長度不超過16個漢字的信息。
你發布的信息可能會被系統在任何時候清理，或者被其他人新發布的信息所清理。
指令格式： msg 內容\n");

    if( strlen( arg ) > 32 )
        return notify_fail("你只能發布長度最多為16個漢字的信息。\n");

    if( arg == "clean" && wizardp(me) )
    {
        message_vision("$N把正在發布的信息都清除了。\n",me);
        delete("player_msg1");
        delete("player_msg2");
        delete("player_msg3");
        hjset_long();
        save();
        return 1;
    }

    if( query("balance", me)<MSG_GOLD*10000 )
        return notify_fail("你的錢莊存款不夠，無法發布信息。\n");

    // OK,發表。

    addn("balance", -MSG_GOLD*10000, me);

    if( query("player_msg2") )
        set( "player_msg1", query("player_msg2") );
    if( query("player_msg3") )
        set( "player_msg2", query("player_msg3") );

    time = ctime_format( "Y.M.D" );
    set("player_msg3",(["id":query("id", me),"time":time,"msg":arg]));
    hjset_long();
    message_vision("$N支付了"+chinese_number(MSG_GOLD)+"兩黃金，發布了一則短消息。\n",me);

    in_money += MSG_GOLD;
    buy_msg_times ++;

    save();
    return 1;
}

int do_mewiz(string arg)
{
    int temp, time, i;
    object ts;
    string msg, *key;
    mixed ppp;

    if(!wizardp(this_player())) return 0;

    if(!arg) return notify_fail(
"可操作參數如下(例如 <mewiz open 1>：
open 1          --> 遊戲啟動
open 0          --> 遊戲關閉
free 1          --> 允許免費遊戲
free 0          --> 關閉免費遊戲
mpgold 數量     --> 門票價格(黃金)
msggold 數量    --> 公布信息價格(黃金)
maxenter 數量   --> 最大進場人數，場內玩家到達此數量時，不再放人進場
ts              --> 領取巫師專用的 幻境工具
ck              --> 查詢當前遊戲的所有設置狀態
cklevel         --> 查詢所有幻境玩家的 level 狀態
dellv ID        --> 清除某玩家在這裡的 level 記錄(並不清除其實際有效 level)\n");

    if( arg == "ts" )
    {
        ts = new( __DIR__"npc_obj/hj_wiztools" );
        ts->move(this_player());
        write("OK，已取得一個 幻境巫師工具。\n");
        return 1;
    }

    if( arg == "cklevel" )
    {
        if( !player_level_info || !sizeof(player_level_info) )
            return notify_fail("現在還沒有任何玩家的 level 記錄。\n");

        key = keys( player_level_info );
        msg = "共有 "+sizeof(key)+" 個記錄。詳細資料如下：\n\n";
        for( i=0;i<sizeof(key);i++ )
        {
            ppp = player_level_info[ key[i] ];
            if( !mapp(ppp) ) continue;
            time ++;
            msg += sprintf( "%s(%s)  LV %d    (%s)\n",
                ppp["name"], key[i], ppp["lv"], ctime_format( ppp["time"] ) );
        }
        msg += "\n有效記錄共 "+time+" 個。\n";
        this_player()->start_more( msg );
        return 1;
    }

    if( sscanf( arg, "dellv %s", msg ) )
    {
        if( getuid( this_player() ) != "naihe" )
            return notify_fail("本指令只能由奈何執行。\n");
        write( del_player_level( msg ) );
        return 1;
    }

    if(arg == "ck")
    {
        time = query("begin_time");
        temp = time() - time;

        msg = sprintf("
************************************************************
%s         最大入場人數限制：%d
%s
系統啟動于：%s 。
現在是：    %s 。

    "HIY"至今已過了 %d 天 %d 小時 %d 分鐘 %d 秒"NOR"

總入場人次(包括巫師)："HIG"%-10d"NOR" 最大同時在場："HIC"%d"NOR"
    (平均每 %d 天 %d 小時 %d 分 %d 秒進場一人次)
總收入："HIY"%d"NOR" 黃金 (售票 %d 張，發布信息 %d 次，售出說明 %d 本)
(門票 %d GOLD / 張，說明 1 GOLD / 本，發布信息 %d GOLD / 次)
************************************************************\n",
            GAME_OPEN ? HIG"主遊戲  -->啟動中"NOR : HIR"主遊戲  -->關閉中"NOR,
            MAX_HJ_ENTER,
            FREE_GAME ? HIY"現在是免費遊戲。"NOR : HIG"現在是正常遊戲，非免費。"NOR, 
            ctime_format( time ), ctime_format(), 
            temp / 86400, (temp % 86400) / 3600,
            (temp % 86400 % 3600) / 60, temp % 86400 % 3600 % 60,
            in_times, max_in_hj,
            in_times ? (temp / in_times) / 86400 : 0,
            in_times ? ((temp / in_times) % 86400) / 3600 : 0,
            in_times ? ((temp / in_times) % 86400 % 3600) / 60 : 0,
            in_times ? ((temp / in_times) % 86400 % 3600) % 60 : 0,
            in_money, buy_piao_times, buy_msg_times, buy_sm_times,
            MP_GOLD, MSG_GOLD );
        write( msg );
        return 1;
    }

    if( sscanf(arg, "open %d", temp) )
    {
        if(temp!= 1 && temp!=0) return notify_fail("只能設置 1 或 0 來開啟/關閉遊戲。\n");

        GAME_OPEN = temp;
        write("設置成功。請用 <mewiz ck> 指令查詢當前狀態。\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf(arg, "free %d", temp) )
    {
        if(temp!= 1 && temp!=0) return notify_fail("只能設置 1 或 0 來開啟/關閉免費遊戲。\n");

        FREE_GAME = temp;
        write("設置成功。請用 <mewiz ck> 指令查詢當前狀態。\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "mpgold %d", temp ) )
    {
        if( temp< 1 || temp > 1000 ) return notify_fail("設置門票價格，范圍 1-1000 黃金。\n");

        MP_GOLD = temp;
        write("設置成功。請用 <mewiz ck> 指令查詢當前狀態。\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "msggold %d", temp ) )
    {
        if( temp< 1 || temp > 1000 ) return notify_fail("設置發布信息價格，范圍 1-1000 黃金。\n");

        MSG_GOLD = temp;
        write("設置成功。請用 <mewiz ck> 指令查詢當前狀態。\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "maxenter %d", temp ) )
    {
        if( temp< 1 || temp > 100 ) return notify_fail("設置最大進場人數，范圍 1-100 。\n");

        MAX_HJ_ENTER = temp;
        write("設置成功。請用 <mewiz ck> 指令查詢當前狀態。\n");
        hjset_long();
        save();
        return 1;
    }

    write("格式有誤。請直接輸入 <mewiz> 指令查詢正確用法。\n");
    return 1;
}


int do_maipiao( )
{
    object me=this_player(),piao,gold;

    if( query("balance", me)<MP_GOLD*10000 )
        return notify_fail("你的錢莊存款不足以購買一張門票。門票價格是 "+MP_GOLD+" 兩黃金。\n");

    piao = new(__DIR__"other_obj/obj_menpiao");
    addn("balance", -MP_GOLD*10000, me);
    piao->move(me);
    message_vision("$N支付了"+chinese_number(MP_GOLD)+"兩黃金，買下了一張門票。\n",me);

    in_money += MP_GOLD;
    buy_piao_times ++;

    save();
    return 1;
}

int do_create_room_file()
{
    object me = this_player();
    int last_num;

    if( !wizardp(me) || getuid(me) != "naihe" )
        return notify_fail("本指令只能由 奈何 執行。\n");

    if( query_temp("hj_create_room", me) != 1 )
    {
        set_temp("hj_create_room", 1, me);
        return notify_fail("本指令將直接建立 .c 文件！它將建立文件名為：\n "+
__DIR__ + "hj_room1.c  至 "+ __DIR__ + "hj_room"+ HJ_ROOM_AMOUNT+ ".c 
共 "+HJ_ROOM_AMOUNT +" 個文件！你如果確定，請再次輸入本指令。\n");
    }

    delete_temp("hj_create_room", me);

    if( file_size( HJ_ROOM_CREATE_D +".c" ) < 0 )
        return notify_fail("無法找到 "+ HJ_ROOM_CREATE_D+" 文件。\n");

    last_num = HJ_ROOM_AMOUNT;
    write( HJ_ROOM_CREATE_D->create_room( me, __DIR__, last_num ) );
    return 1;
}


int valid_leave(object me, string dir)
{
    object menpiao;
    mapping conditions;
    
    if( dir != "enter" )
        return ::valid_leave(me,dir);
    if( !userp(me) )
        return notify_fail("豬頭不得進入！！！\n");
    // 氣死我了，居然有一堆NPC走了進去
    //     if( wizardp(me) ) return ::valid_leave(me,dir);
    // 巫師亦不能免費。
    if(GAME_OPEN != 1) return notify_fail("遊戲並未開放。\n");
    if( query("scheming", me) )
        return notify_fail("正在執行離線計劃者不得入內。\n");
    if( !interactive(me) )
        return notify_fail("斷線者不得入內。\n");
    // 檢測玩家狀態
    conditions = me->query_all_condition();
    if( conditions && sizeof( conditions ) > 0 )
        return notify_fail("你現在身體狀況不正常或你設置開啟了門派任務，請關閉門派任務(family_job)或稍後再試。\n");
    // 查看場內情況
    if( who_in_hj()[ "amount" ] >= MAX_HJ_ENTER )
        return notify_fail("現在已經有太多人在幻境裡了，請稍候再嘗試進入。\n");
    if( query("all_ip_in_hj") && sizeof( query("all_ip_in_hj") )
      && member_array( query_ip_name(me), query("all_ip_in_hj") ) != -1
    )
        return notify_fail("幻境裡已經有與你同IP的玩家了，同一IP只能進入一個玩家。\n");
    if( FREE_GAME == 1 )
    {
        in_times++;
        save();
        write("現在正進行免費遊戲活動，謝謝參與遊戲。\n");
    }
    else
    {
        menpiao = present("men piao",me);
        if( !menpiao || !query("hjmenpiao", menpiao) )
            return notify_fail("請先購票，方可入內。請查看牌子上的說明。\n");
        destruct(menpiao);
        message_vision("$N掏出一張門票塞進門邊的小盒子裡，隨即往裡邊走了進去。\n",me);
        in_times++;
        save();
    }
    set_temp("hj2003-valid_enter", 1, me);
    delete_temp("hj2003-enter_timeout", me);
    call_out("player_timeout", 180, me);
    return ::valid_leave(me, dir);
}

void player_timeout(object me)
{
    if( !me || !environment(me) || query("room_mark", environment(me) )
      || present("qixing deng",me ) || environment(me) == this_object()
      || strsrch( base_name( environment(me) ), "room_gameover_hj" ) != -1 )
        return;
    if( !query_temp("hj2003-enter_timeout", me) )
    {
        set_temp("hj2003-enter_timeout", 1, me);
        tell_object( me, HIR"\n遊戲提示：請盡快進入遊戲(xuanze 國度名，例如 xuanze feng)，否則將被踢出遊戲！\n\n"NOR );
        call_out( "player_timeout", 180, me);
        return;
    }
    message_vision( "$N呆在這裡太久了，忽然感到一陣震盪！\n",me);
    me->move( this_object() );
    message_vision( "$N被一陣莫名的震盪送到了這裡。\n",me);
}

void save_player_level( string name, string id, int lv, int time )
{
    player_level_info[ id ] = ([ "name":name, "lv":lv, "time":time ]);
    save();
}

string del_player_level( string id )
{
    if( !id ) return "要清除哪一位玩家的 level 記錄？\n";
    if( undefinedp( player_level_info[id] ) )
        return "沒有這個玩家的 level 記錄。\n";

    map_delete( player_level_info, id );
    save();
    return "該玩家的 level 記錄已清除，其 level 記錄將于下次進入本地時被清除。\n";
}