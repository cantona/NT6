//                標準描述長度示例                                   |
// “幻境”尋寶系列主題之主控地點
// by naihe  2002-10-22
// 巫師可用 <mewiz> 指令進行一些遊戲相關的操作。具體請輸入 <mewiz> 查詢。
// 強制清除所有 幻境 房間內存在之所有物品（除了玩家之外的一切，都將刪除）
//   指令 ： <mewiz del_all>   請謹慎使用！！！
// 更改了一下流程  naihe 8:35 03-11-3

// naihe 05-9-7 10:35  V1.7 繼續更新

#include <ansi.h>
inherit ROOM;

#include    "npc_obj/hj_settings/obj_list.h"
// 道具及NPC列表

#include    "npc_obj/hj_settings/room_amount_hj.h"
// 隨機發放物品時，需要用到這裏面一個變量 幻境總房間數 HJ_ROOM_AMOUNT

int is_gameing = 0;
// 遊戲當前狀態，即“未啟動”

#define        KILL_NPC_DISPERSION_TIME     60
#define        KILL_NPC_AMOUNT_MIN          3
#define        KILL_NPC_AMOUNT_RANDOM       6
// 這三個量決定系統在每隔 TIME 秒鐘，向遊戲內加入  MIN + random( RANDOM ) 個
// 殺戮型的NPC。
// 現在的設置是 3 分鐘 1-3 個。 15:18 03-10-18


#define        QUEST_NPC_DISPERSION_TIME    300
// 多少時間就給遊戲中發放一個額外的 "quest" 類NPC，
// 即老人、孩童、商人、藏劍生及珠寶客等

#define        ROUND_DISPERSION_TIME        900
// 每隔一段時間沒有新玩家進入 hj，那麼有必要補充一些物品以防止冷場。
#define        ROUND_DISPERSION_AMOUNT_MIN      30
#define        ROUND_DISPERSION_AMOUNT_RANDOM   10
// 補充的數量範圍是 MIN + random( RANDOM )


int dispersion( object me );
int del_all( object me );
void random_dispersion_to_hj( string *dis_list, int times );
void clean_hj();


void c_msg( string msg )
{
    object naihe;
    if( !msg ) return;
    naihe = find_player( "naihe" );
    if( !naihe || !userp(naihe) || query("env/no_hj_wizmsg", naihe) )
        CHANNEL_D->do_channel( this_object(), "sys", YEL+ msg + NOR);
    else tell_object( naihe, HIR"〖幻境系統通知〗："+msg + "\n"NOR );
}

void create()
{
    set("short",MAG"虛空之境"NOR);
    set("long","

      你 將 進 入 的 是 幻 境 …… 進 入(enter) 吧……

\n");

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "enter":__DIR__"room_readygo_hj",
    ]));

    set("channel_id", HIY"※幻境主控中心※"NOR);
    setup();
}

void init()
{
    if(wizardp(this_player())) add_action("do_mewiz","mewiz");
    add_action("do_nocmds", ({ "scheme", "drop", "put"}) );
}

int do_nocmds()
{
    write("這裏禁止使用這個指令。\n");
    return 1;
}

void reset()
{ 
    ::reset(); 
    set("no_clean_up", 1); 
}

int valid_leave(object me, string dir)
{
    if(dir == "enter")
    {
        if( !userp(me) )
            return notify_fail("豬頭不得入內。\n");

        //if( !me->query_temp("enter_hj") )
            //return notify_fail("請從幻境正門進入這裏，才可以繼續進入下一個地方！\n");

        // 允許進入
        // 如果遊戲未啟動，啟動它，併發放物件
        if( !is_gameing )
        {
            remove_call_out("start_game");
            call_out("start_game",1);
        }
        // 無論如何，每隔一段時間就重新發放一次遊戲人物或物品，小量
        // 但若有新玩家進入，這個計時會重新開始
        // 並且該函數會判斷，若調用時已是非遊戲狀態(!is_gameing)，則不操作。
        remove_call_out("dispersion_again");
        call_out("dispersion_again", ROUND_DISPERSION_TIME );

        // 1個半小時後，遊戲設置為“關閉中”，同時清理所有場內物品
        // 但若有新玩家進入，這個計時會重新開始
        remove_call_out("reset_game");
        call_out("reset_game",6600);

        // 免得造成什麼誤會
        if( !is_gameing )
            return notify_fail("請稍等數秒，幻境遊戲正在啟動中……\n");
    }
        return ::valid_leave(me, dir);
}


int dispersion( object me )
{
    int times;

    if( !me || !wizardp(me) ) return 0;
    if( !is_gameing )
    {
        tell_object(me, "遊戲狀態並不是 啟動中 ，請勿隨意派發物件。\n");
        return 1;
    }

    times = 50 + random(11);
    tell_object( me, "Ok. 已執行函數，請留意 sys 信息。\n");
    CHANNEL_D->do_channel(me,"sys",sprintf("%s手動執行幻境遊戲主控中心派發隨機物件函數(%d個物件)。",query("id", me),times));
    random_dispersion_to_hj( obj_list_all, times );
    return 1;
}


int del_all( object me )
{
    if( !me || !wizardp(me) ) return 0;

    tell_object( me, "Ok. 已執行函數，請留意 sys 信息。\n");
    CHANNEL_D->do_channel(me,"sys",sprintf("%s手動執行幻境遊戲主控中心的強制清除所有境內物件函數。",query("id", me)));
    clean_hj();
    return 1;
}

int do_mewiz(string arg)
{
    object me = this_player();

    if( !arg )
    {
        write("
可使用之強制指令：

<mewiz dispersion>      隨機派發 50 -60 個隨機物品至所有隨機房間裏
                            本指令只能在 is_gameing 狀態(遊戲啟動中) 才可以使用。
<mewiz del_all>         強制清除所有 幻境 所有房間內存在的物件（玩家除外）
                            本指令將直接更改遊戲狀態為 !is_gameing 。

務必謹慎使用！\n");
        return 1;
    }

    if( arg == "dispersion" )
        return dispersion(me);

    if( arg == "del_all" )
        return del_all(me);

    write("指令有誤。請直接輸入 <mewiz> 指令作查詢。\n");
    return 1;
}


// 為了避免玩家在林內遊戲過久，東西揀光NPC殺光JOB做光而產生冷場，
// 加入這個函數，一定時間後將會重新變得熱鬧起來
void dispersion_again()
{
    int times;
    
    remove_call_out("dispersion_again");
    if( !is_gameing )
        return;
    // 如果已是非啟動狀態，就別理
    times = ROUND_DISPERSION_AMOUNT_MIN + random( ROUND_DISPERSION_AMOUNT_RANDOM );
    c_msg( "幻境遊戲已有 "+(ROUND_DISPERSION_TIME/60)+" 分鐘無新玩家進入，正在給境內地點補充各類道具或人物(共"+times+"件)。");
    random_dispersion_to_hj( obj_list_all, times);
    call_out("dispersion_again", ROUND_DISPERSION_TIME );  // 一定時間後又來
}

// 遊戲啟動
void start_game()
{
    int times;

    if( is_gameing ) return;
    // 如果已在啟動，不理。不過這個情況除非有人作弊，否則理論上不會發生

    times = 50+random(21);

    c_msg( "幻境遊戲自動啟動！正在清除殘餘境內物件……" );
    remove_call_out("clean_hj");
    clean_hj();
    c_msg( "幻境遊戲自動啟動！正在給境內地點發放各類道具或人物(共"+times+"件)……");
    random_dispersion_to_hj( obj_list_all, times);
    is_gameing = 1;

    // 開始不斷地發放殺戮型NPC
    remove_call_out("random_dispersion_killer");
    call_out("random_dispersion_killer", 1);

    // 開始不斷地發放“特別”類型的NPC
    remove_call_out("random_dispersion_questnpc");
    call_out("random_dispersion_questnpc", 1);

    remove_call_out("reset_game");
    call_out("reset_game", 6600 );
}


void reset_game()
{
    c_msg( "幻境遊戲已經100分鐘無人進入了，將自動清理境內所有物件，並恢復遊戲為“未啟動”。" );
    clean_hj();
}


// 這個函數用於不斷地往幻境裏添加 quest 型 npc
void random_dispersion_questnpc()
{
    if( !is_gameing ) return;
    random_dispersion_to_hj( ({ __DIR__"npc_obj/hj_npc_quest" }), 1 );

    remove_call_out("random_dispersion_questnpc");
    call_out("random_dispersion_questnpc", QUEST_NPC_DISPERSION_TIME );
}


// 這個函數用於不斷地往幻境裏添加殺戮型NPC
void random_dispersion_killer()
{
    if( !is_gameing ) return;
    random_dispersion_to_hj( ({ __DIR__"npc_obj/hj_npc_kill" }),
        KILL_NPC_AMOUNT_MIN + random( KILL_NPC_AMOUNT_RANDOM ) );

    remove_call_out("random_dispersion_killer");
    call_out("random_dispersion_killer", KILL_NPC_DISPERSION_TIME );
}

// 此函數發放隨機物件，傳入兩個參數，分別是 物件列表 及 次數(物件個數)
// 執行此函數時，不會自動進行“清除”。請勿隨意調用
void random_dispersion_to_hj( string *dis_list, int times )
{
    int i;
    string r, msg;
    object rs, obj;

    if( !dis_list || sizeof(dis_list) < 1 ) return;

    i = times;
    while( i-- )
    {
        r = __DIR__"hj_room"+( 1+random(HJ_ROOM_AMOUNT) );
        rs = find_object( r );
        if( !rs ) rs = load_object( r );

        // 這裏不進行 file_size 的判斷。
        obj=new( dis_list[random(sizeof(dis_list))] );
        obj->move(rs);
        if( query("msg", obj))msg=query("msg", obj);
        else msg="忽然一小陣輕煙掠過……這裏似乎多了一些什麼。\n";
        tell_room( r ,msg);
    }

    if( times < 10 ) return; // 免得連 killer 的發放也不停地報

    c_msg( "幻境遊戲隨機發放物件完畢，共發放 "+times+" 件各式物品或NPC。" );
}

// 此函數清除幻境世界。
void clean_hj()
{
    int i,j, c1, c2;
    string f, *files;
    object ob;

    is_gameing = 0;
    // 直接恢復遊戲狀態為 “未啟動”
    for( i = 1; i <= HJ_ROOM_AMOUNT; i++ )
    {
        ob = find_object(__DIR__"hj_room"+i);
        if(!ob)
            continue;
        destruct( ob );
        c1 ++;
    }
    // 刪除其它物件
    files = get_dir( __DIR__"npc_obj/");
    foreach( f in files )
    {
        f = __DIR__ "npc_obj/" + f;
        if( f[<2..<1] != ".c" )
            continue;
        if( (ob = find_object( f )) )
        {
            destruct( ob );
            c2 ++;
        }
    }
    c_msg( "幻境遊戲世界清除，共清理 "+c1+" 個已載入內存的房間；"+c2+" 個遊戲參考物件。遊戲恢復為“未啟動”狀態。" );
}