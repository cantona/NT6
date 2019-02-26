//                標準描述長度示例                                   |
/*****************************************************
         幻境內人物  迷題型  包括如下：

 可購物型（以幻境內之寶石（電之國度寶石除外） 加 幻境
           內遊戲得分購買））
   所有可購物之資料，與 obj_copy.h 同步（即與巫師工具同步）

 任務型：帶領迷路孩童至其所需之房間  需要冒隨時走失
         （如隨機震盪導致玩家離開、或被攻擊時必須逃跑等）
         而被扣除得分的風險

 其他任務型不再詳細介紹。

 回答問題型，答對了可獲得幻境內分數 （遊戲後統計獎勵）
             而失敗了則有極長的忙時（視情況而定，若回
             答錯誤的，20秒；未回答的，30秒；未回答而
             又不知道溜到哪裏去了的，言而無信，60秒。）
             實際上，這個類型在開始寫第一個物件（房間）
             的時候就有考慮到了，玩家 七星燈 裏，還有
             着相當煩瑣的資料為備。當時擬使用設置值給
             玩家而強制停留的方案；但考慮到調用時容易
             出錯（例如本NPC自毀後無法執行刪除；而使用
             燈本身的 checking 又有點畫蛇添足的味道），
             故使用代碼安全方案，忙時。


 其他型：煉力老人  可為玩家增強力量

 藏劍生·珠寶客    任務型。
16:14 03-10-19
*****************************************************/

// by naihe  2002-10-29  於茂名

#include <ansi.h>

inherit NPC;

#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"
#include "hj_settings/obj_copy.h"
#include <set_del_color.h>

mapping list_temp;


string *names=({
    "精靈商販",
    "小孩童",
    "老人",
    "老人",   // 有點故意迷惑玩家的味道…… :)
    "精靈商販",  // 出現商販的機會加大了
    "藏劍生",
    "珠寶客",
});

string *ids=({
    "shang fan",
    "hai tong",
    "lao ren",
    "lao ren",
    "shang fan",
    "cangjian sheng",
    "zhubao ke",
    "小孩童",
});

string *ids2 = ({
    "fan",
    "tong",
    "ren",
    "ren",
    "fan",
    "sheng",
    "ke",
    "tong",
});

string *quests=({
    "購買",
    "為什麼着急",
    "煉力",   // 這個NPC可讓玩家提升力量！！！
    "英雄",
    "購買",
    "藏劍",
    "珠寶",
    "為什麼着急",
});

string *longs=({
    "這是一個精靈族的小商販，出售各式的物品。\n你可以問他關於「"+quests[0]+"」的事情。\n",
    "這是一個精靈族的小女孩子，不知道為什麼看起來一副神色着急的模樣。\n你可以問她關於「"+quests[1]+"」的事情。\n",
    "這是一個白髮蒼蒼的老人，但卻神采奕奕地十分強健的樣子。\n你可以問他關於「"+quests[2]+"」的事情。\n",
    "這是一個白髮蒼蒼的老人，神采飛揚，看似所知十分淵博的樣子。\n你可以問他關於「"+quests[3]+"」的事情。\n",
    "這是一個精靈族的小商販，出售各式的物品。\n你可以問他關於「"+quests[4]+"」的事情。\n",
    "這是一個大方瀟灑的中年人，腰間配着一柄長劍。\n你可以問他關於「"+quests[5]+"」的事情。\n",
    "這是一個神態猥瑣的中年人，矮矮胖胖的一副狡詐模樣。\n你可以問他關於「"+quests[6]+"」的事情。\n",
    "這是一個精靈族的小女孩子，不知道為什麼看起來一副神色着急的模樣。\n你可以問她關於「"+quests[7]+"」的事情。\n",

});

string *genders=({
    "男性",
    "女性",
    "男性",
    "男性",
    "男性",
    "男性",
    "男性",
    "女性",
});

string *ChatMsg=({
    "嘿嘿笑道：“我這裏有一些好東西賣，誰要來買一點？”\n",
    "四處張望着，神色間十分着急的模樣，好像快要哭了似的。\n",
    "「呵呵」地笑了幾聲，自言自語道：“年輕人哪，呵呵。”\n",
    "摸了摸鬍子，笑道：“爾等雖身在其中，但這俠義世界之事，卻又知曉幾分？”\n",
    "嘿嘿笑道：“我這裏有一些好東西賣，誰要來買一點？”\n",
    "低聲歎道：“唉！可不知何時才能見到那些寶劍？”\n",
    "低聲歎道：“唉！可不知何時才能見到那些水晶？”\n",
    "四處張望着，神色間十分着急的模樣，好像快要哭了似的。\n",
});

int *times=({
    5+random(6),
    3,
    5,
    1,
    5+random(6),
    1,
    1,
    3,
});

int *ages=({
    18+random(30),
    11,
    82,
    82,
    18+random(30),
    39+random(3),
    41,
    11,
});

int *del_me_time = ({
    600, 
    180,
    180,
    300,
    600,
    600,
    600,
    180,
});


int ask_help();

string *sell_kind=({"兵器類","果品類","奇特","神祕", });


int me_ok(object me)
{
    object inv_me;
    int iii = query("iii");

    if( !me ) return 0;
    if( !query_temp("huanjing", me) || query_temp("huanjing", me) != "start" || 
        !query_temp("hj_hp", me) || query_temp("hj_hp", me)<1 || 
        !query_temp("hj_hp_max", me) )
         return 0;
    inv_me = environment(me);
    if( !inv_me || !query("room_mark", inv_me) )
        return 0;

    if( ( iii == 0 || iii == 4 || iii == 5 || iii = 6 ) && !query("job_set_finish") )
        return 0;

    return 1;
}


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
// 此句測試用，讓它只出藏劍生或珠寶客
//    iii = 5 + random(2);
    set("iii", iii );

    set_name(names[ iii ],({ ids[ iii ], ids2[ iii ] }));
    set("long",longs[ iii ]);
    set("hj_game/npc","quest");
    set("msg",query("name")+"走了過來。\n");
    set("gender",genders[ iii ]);
    set("my_quest",quests[ iii ]);
    set("use_times",times[ iii ]);
    set("age",ages[ iii ]);
    set("no_refresh",1);

    set("inquiry",([
        quests[ iii ] : (: ask_help :),
        ]));

    set("chat_chance",1); 
    set("chat_msg",({ query("name")+ChatMsg[ iii ] }) );

    remove_call_out("delete_me");
    remove_call_out("random_move");
    remove_call_out("start_my_job");
    call_out("start_my_job", 1 );
}


void create()
{
    setme( 99 );
    setup();
}

void start_my_job()
{
    int q_iii, sp_weapon_set, r_mark, sp_weapon_times;
    object sp_weapon, weapon_room;

    if( !environment(this_object()) ) return;

    q_iii = query("iii");

    if( q_iii == 0 || q_iii == 4 )
    {
        set("sell_this_time", sell_kind[random(sizeof(sell_kind))]);
        switch( query("sell_this_time") )
        {
            case "兵器類": list_temp=can_sell_weapon; break;
            case "果品類": list_temp=can_sell_other; break;
            case "奇特": list_temp=can_sell_tools; break;
            case "神祕": list_temp=can_sell_quest; break;
            default:list_temp=can_sell_other;
        }
    }

// 若是這兩位，有特別的操作
// 藏劍生，產生有標記的劍 n 把，放於隨機地點內。這 n 把劍是同樣名字的，
// 拿到任意一把，都能夠完成這個 JOB。
// 若是珠寶客，產生有標記的水晶（攻擊類）n 顆，原理同上

    if( q_iii == 5 ) sp_weapon_set = random( 9 );
    if( q_iii == 6 ) sp_weapon_set = 9 + random( 7 );

// 產生中
    if( q_iii == 5 || q_iii == 6 )
    {
        sp_weapon_times = 1;
        while( sp_weapon_times -- )
        {
            sp_weapon = new( __DIR__"hj_obj_weapon" );
            sp_weapon->setme( sp_weapon_set );
            set("cj-sheng.zb-ke", this_object(), sp_weapon);
            r_mark = 1 + random( HJ_ROOM_AMOUNT );
            weapon_room = find_object( HJ_DIR + "hj_room" + r_mark );
            if( !weapon_room )
                weapon_room = load_object( HJ_DIR + "hj_room" + r_mark );
            sp_weapon->move( weapon_room );
            set("finding_name",delcolor(query("name", sp_weapon)));
        }
    }

    if( q_iii == 5 )
    {
        set("found_sword", "no");
        set("found_all_sword", "no");
    }
    if( q_iii == 6 )
    {
        set("found_crystal", "no");
        set("found_all_crystal", "no");
    }

    set("job_set_finish", 1);
    call_out("random_move", 1);
    call_out("delete_me", del_me_time[  q_iii  ] + random(120) );
}

int random_move()
{
    string *dirs;

    if(query("cannot_rdmove")) return 0;

    dirs=({
"east","west","south","north","northeast","northwest","southeast","southwest"
        });

    if(random(5) == 1 && living(this_object()))
        command(dirs[random(sizeof(dirs))]);

    remove_call_out("random_move");
    call_out("random_move",5,this_object());
    return 1;
}

#include "hj_npc_quest_action.h"