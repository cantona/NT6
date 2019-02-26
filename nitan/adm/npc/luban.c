// luban.c 魯班
// Written by Doing Lu 1998/11/17
// 魯班是負責建造房間的NPC， 首先，玩家去魯班那裏索要圖紙，然後到想建房
// 的地點描繪圖紙，必須要有30級以上的繪畫技巧才可以，如果不到30級，可以
// 和魯班學習。然後玩家要把圖紙給魯班，魯班詢問房屋的名稱，不能和那裏已
// 有的房屋重名，然後再詢問房屋的類型（房屋的類型都定義在roomtype.h）中，
// 並且詢問每個房間的描述，每個描述不能超過三百二十個字符（即最多四行），
// 其中所有的房間的short 都由房屋名稱生成，不需要玩家輸入，然後魯班記錄
// 所有的信息，並提示玩家等待巫師（權限在arch以上）的批准。
//
// 巫師上線後到魯班處，魯班提示巫師處理玩家的信息，如果巫師批准了，就更
// 新信息，等玩家再上線後到魯班處，魯班提示玩家可以建房（如果沒有被批准，
// 就顯示原因，清除信息），玩家交一定的費用，就可以生成房屋文件，並修改
// 玩家的檔案，記錄玩家已經建過房，並贈送一把鑰匙，然後清除記錄的信息。
//
// 如果玩家丟了鑰匙，可以到魯班處重新配一把鑰匙，如果玩家需要複製鑰匙，
// 也可以向魯班要求。
//
// 如果玩家需要拆除房屋，可以向魯班提出，經過確認後，刪除房屋檔案。

// 生成房屋的説明
// 在選擇好房屋類型時，魯班將紀錄需要建設的房屋原型的所有文件，這些文件
// 一定要在/d/room/XXXX/內，比如玩家選用了獨樂居，則房屋文件都在/d/room
// /dule/內。在生成房屋文件時，魯班將把這些文件拷貝到/data/room/playerid/，
// 同時原型房屋必須由一個出口：/d/room/xiaoyuan魯班將將這個出口替換成玩
// 家建房的地點，所以原型房還必須有一個以xiaoyuan命名的小院。
//
// 對於原型房還有一些其他要求，比如原型房繼承的是ROOM類型，而建造的房將
// 繼承PRIVATE_ROOM類型，因此在原型房的文件中，inherit ROOM那一句要求包
// 含有/**/的字樣，或是/* EXAMPLE */，而在inhert PRIVATE_ROOM之前需要有
// //**的字樣，因為魯班會自動的將包含/**/的行去掉，並去掉//**的字樣。另
// 外，所有有門的原型房，都必須有以下語句，set ("room_key", "ROOM_KEY");
// 這是為了給建好的房子添加鑰匙。同時原型房中最好有主人set ("room_owner_id",
// "ROOM_OWNER_ID")和類型的設置。

// 關於鑰匙的一點説明
// 每個玩家房屋鑰匙要生成一個文件，其實這完全可以用一個通用的鑰匙文件在
// 每次AUTOLOAD的時候自動的更新，之所以不這麼做是因為為了使玩家的房屋數
// 據能夠保持一個獨立性，不至於過於分散，而且在一個人身上帶多把鑰匙的時
// 候不至於過於繁瑣。

// 一些變量的説明
// 玩家在商談時紀錄的數據
// contract/luban          : 紀錄商談數據的mapping，這記錄在玩家的臨時變量
// contract/luban/room     : 紀錄房屋描述信息的mapping
// contract/luban/descs    : 紀錄房屋描述的mapping
// contract/luban/questing : 玩家商談狀態 quest_name/quest_id/quest_desc
// contract/luban/value    : 建設房屋所需要的價格(以coin為單位)
// contract/luban/position : 建造房屋的地點

// 魯班記錄玩家申請的數據
// form : 記錄玩家申請的表單
// form/player/player   : 申請者的名稱
// form/player/position : 申請建房的地點
// form/player/room     : 申請建房的類型名稱
// form/player/type     : 申請建房的類型代號
// form/player/name     : 房屋的名稱
// form/player/id       : 房屋的代號
// form/player/status   : 表單的狀態 - 申請/允許/拒絕
// form/player/time     : 申請的時間
// form/player/wizard   : 處理表單的巫師
// form/player/memo     : 巫師填寫的備註
// form/player/descs    : 玩家填寫的描述

// 玩家自身數據的修改
// private_room/build   : 已經建過房屋
// private_room/position: 房屋所在的位置，即入口處所在場景的文件路徑
// private_room/entry   : 房屋入口處的文件路徑
// private_room/name    : 房屋名稱
// private_room/id      : 房屋ID
// private_room/type    : 房屋類型名稱

// 實現方法
// 商談過程是一個簡單的自動機，其狀態儲存在用户的數據結構中的contract/
// luban字段，接收消息的函數是do_answer， 這個函數根據狀態處理接收的消
// 息即字符串，最要是調用不同的判斷函數，如果返回1則已記錄輸入的信息，
// 如果返回0則表示不與處理或是終止商談。如果用户在商談過程輸入了stop，
// 則清除自動機的狀態和用户數據庫中記錄的商談信息。

// 數據存放
// 階段1 - 商談
// 數據存放在player->contract/luban/這個mapping中

// 階段2 - 申請
// 數據存放在luban->form/player/這個mapping中

// 階段3 - 建設完畢
// 數據存放在player->private_room/這個mapping中
// 生成的文件存放在/data/room/player/這個目錄中
// 玩家房屋的存盤文件存放在/data/room/player/這個目錄中
// 建房處的存盤文件存放在相同的目錄中，不過後綴不一樣

// 相關文件
// inherit::PRIVATE_ROOM(/inherit/room/privateroom.c)
// 這是用户建造的房屋所具有的屬性，主要是用鑰匙開門和存放物品
//
// inherit::BUILD_ROOM(/inherit/room/buildroom.c)
// 這是建房處的環境所具有的屬性，主要是可以記錄增加的出口，並修改LONG描述

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

// 這裏記錄了各種樣式房屋
// 這裏是一個mapping數組，其中每一個mapping指明瞭一種型號的房屋。 每一個mapping中有三個
// 元素，一是名字、二是類型、三是房屋字符串數組：字符串數組指明瞭這種房屋所擁有的文件。
// files中的必須有一個是入口文件(既有到/d/room/xiaoyuan的出口)，否則建房時將產生錯誤。

// 另外：type 和 name 都可以作為房屋類型的標誌，只不過一個是中文，另一個是英文的而已，
// 在最終保存在玩家數據庫中的是中文的類型名即name字段。

// 注意：由於魯班是一個需要保存數據的NPC，在改動魯班的文件後可能會發生一些問題，這時可以
// 將他的存盤文件刪除。
nosave mapping *room_example = ({
([      "name"     : "獨樂居",
        "type"     : "dule",
        "value"    : 20000000,
        "files"    : ([ "xiaoyuan" : "/d/room/dule/xiaoyuan.c",
                        "xiaowu"   : "/d/room/dule/dulewu.c" ,
                     ]),
]),
([      "name"     : "彩虹居",
        "type"     : "caihong",
        "value"    : 70000000,
        "files"    : ([ "xiaoyuan" : "/d/room/caihong/xiaoyuan.c",
                        "dating"   : "/d/room/caihong/dating.c",
                        "houyuan"  : "/d/room/caihong/houyuan.c",
                        "woshi"    : "/d/room/caihong/woshi.c",
                     ]),
]),
([      "name"     : "盤龍居",
        "type"     : "panlong",
        "value"    : 800000000,
        "files"    : ([ "dayuan"   : "/d/room/panlong/dayuan.c",
                        "qianting" : "/d/room/panlong/qianting.c",
                        "zuowei"   : "/d/room/panlong/zuowei.c",
                        "youwei"   : "/d/room/panlong/youwei.c",
                        "zoudao"   : "/d/room/panlong/zoudao.c",
                        "yingke"   : "/d/room/panlong/yingke.c",
                        "chashi"   : "/d/room/panlong/chashi.c",
                        "yishi"    : "/d/room/panlong/yishiting.c",
                        "zuoyanwu" : "/d/room/panlong/yanwu1.c",
                        "youyanwu" : "/d/room/panlong/yanwu2.c",
                        "zhongting": "/d/room/panlong/zhongting.c",
                        "zuoxiang" : "/d/room/panlong/zuoxiang.c",
                        "youxiang" : "/d/room/panlong/youxiang.c",
                        "houyuan"  : "/d/room/panlong/houyuan.c",
                        "chufang"  : "/d/room/panlong/chufang.c",
                        "wuchang"  : "/d/room/panlong/lianwu.c",
                        "huayuan"  : "/d/room/panlong/huayuan.c",
                        "zhulin"   : "/d/room/panlong/zhulin.c",
                        "tingtao"  : "/d/room/panlong/tingtao.c",
                        "jusuo"    : "/d/room/panlong/jusuo.c",
                        "shufang"  : "/d/room/panlong/shufang.c",
                        "woshi"    : "/d/room/panlong/woshi.c",
                     ]),
]),

});

#define WIZLEVEL        3       // 能夠處理表單的巫師等級

nosave string *ban_room_id = ({
        "north",
        "south",
        "east",
        "west",
        "northup",
        "southup",
        "eastup",
        "westup",
        "northdown",
        "southdown",
        "eastdown",
        "westdown",
        "northeast",
        "northwest",
        "southeast",
        "southwest",
        "up",
        "down",
        "enter",
        "out",
});

// 內部函數
private int     ask_me();
private int     ask_paper();
private int     ask_drawing();
private int     ask_demolish();
private int     ask_rebuild();
private int     ask_modify();
private int     ask_key();
private int     ask_desc();
private int     recognize_apprentice(object me);
private int     accept_object(object me, object ob);
private void    tell_user_status(object me);
private void    luban_say(string msg);
private void    user_say(string msg);
private int     do_answer(string arg);
private int     do_stop();
private int     do_desc(string arg);
private int     do_show(string arg);
private int     do_changename(string arg);
private int     do_changeid(string arg);
private int     do_changetype(string arg);
private int     do_changedesc(string arg);
private int     do_finish();
private int     do_withdraw();
private int     decide_withdraw();
private int     do_destory();
private void    show_desc(mixed player, string arg);
private void    promote_type(object me);
private int     quest_user(object me);
private int     quest_info(object me);
private int     check_name(object me, string arg);
private int     check_id(object me, string arg);
private int     check_type(object me, string arg);
private int     check_legal_name(string name, string position);
private int     check_legal_id(string name, string position);
private mixed   check_legal_type(string type);
private string  obey_description(string desc);
private object  get_object(string file_name);
private int     record_desc(object me, string room_name, string desc);
private void    record_contract(object me);
private int     modify_desc_in_form(string player_id, string room_name, string desc);
private string  sort_desc(mixed me, string desc);

// 巫師使用的管理命令相關的函數
private void    show_brief(string player_id);
private int     exist_form();
private int     do_help(string arg);
private int     do_list(string arg);
private int     do_type(string arg);
private int     do_agree(string arg);
private int     do_reject(string arg);
private int     do_delete(string arg);
private void    show_apply();
private void    show_agree();
private void    show_reject();
private void    show_old();
private void    show_all();
private void    show_brief_title();
private void    show_brief_list(string info, string msg);

// 生成/拆毀房屋的相關函數
private string  file_dir(mixed me);
private string  to_player(string player_id, string file_name);
private void    create_room(object me);

// 下面這個函數將提供給外部調用(/adm/daemons/updated)，用於更新玩家
// 的數據(數據故障或是玩家自殺，被PURGE)
int     demolish_room(object me);

// 生成鑰匙的函數
private int     create_new_key(object me);
private object  get_user_key(object me);

mapping* forms;
mapping my_form;        // 一個表單，用來存放用户提交的建房信息

// 這是提供的函數，之所以用宏定義，僅僅是為了減小運行時的開銷
// 查詢form
#define query_form(pid, item)           query("form/" + pid + "/" + item)
// 設置form內的值
#define set_form(pid, item, content)    set("form/" + pid + "/" + item, content)
// 判斷該玩家是否有提交申請
#define submit_form(pid)                mapp(query("form/" + pid))

void create()
{
        seteuid(getuid());
        restore();

        set_name("魯班", ({ "lu ban", "lu", "luban" }));
        set("title", "天下第二巧匠");
        set("nickname", HIC "鬼斧神工" NOR);
        set("shen_type", 0);

        set("str", 10000);              // 防止接收的東西過多而導致丟失
        set("int", 60);

        set("gender", "男性");
        set("age", 1450);
        set("long",@LONG
這就是號稱天下第二巧匠的建築大師公輸班，不論是造什麼樣子房屋，在
他手下都不是問題。
LONG
);
        set("attitude", "friendly");
        set("inquiry", ([
                "造房"  : (: ask_me :),
                "造屋"  : (: ask_me :),
                "買房"  : (: ask_me :),
                "買屋"  : (: ask_me :),
                "建房"  : (: ask_me :),
                "建屋"  : (: ask_me :),
                "房子"  : (: ask_me :),
                "屋子"  : (: ask_me :),
                "home"  : (: ask_me :),
                "room"  : (: ask_me :),
                "house" : (: ask_me :),
                "圖紙"  : (: ask_paper :),
                "紙張"  : (: ask_paper :),
                "紙"    : (: ask_paper :),
                "paper" : (: ask_paper :),
                "拆屋"  : (: ask_demolish :),
                "拆房"  : (: ask_demolish :),
                "拆毀"  : (: ask_demolish :),
                "demolish": (: ask_demolish :),
                "destroy" : (: ask_demolish :),
                "重建"  : (: ask_rebuild :),
                "再建"  : (: ask_rebuild :),
                "鑰匙"  : (: ask_key :),
                "鎖匙"  : (: ask_key :),
                "鎖鑰"  : (: ask_key :),
                "配鑰匙": (: ask_key :),
                "配鎖匙": (: ask_key :),
                "新鑰匙": (: ask_key :),
                "新鎖匙": (: ask_key :),
                "key"   : (: ask_key :),
                "描述"  : (: ask_desc :),
                "描寫"  : (: ask_desc :),
                "desc"  : (: ask_desc :),
                "規則"  : (: ask_desc :),
                "修改"  : (: ask_modify :),
                "修正"  : (: ask_modify :),
                "改正"  : (: ask_modify :),
                "修改信息": (: ask_modify :),
                "繪畫"    : (: ask_drawing :),
                "畫"      : (: ask_drawing :),
                "畫圖"    : (: ask_drawing :),
                "畫畫"    : (: ask_drawing :),
                "繪畫技巧": (: ask_drawing :),
                "drawing" : (: ask_drawing :),
        ]));

        set_skill("literate",  120);            // 讀書寫字
        set_skill("drawing",   500);            // 繪畫技巧
        set_skill("certosina", 500);            // 鑲嵌技藝

        set("no_teach", ([
                "literate" : "我可不是教書先生。",
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        move("/d/room/xiaoyuan");
        set("startroom", base_name(environment()));
        if (! clonep()) CHANNEL_D->register_relay_channel("chat");
}

// 毀滅時保存進度
void remove()
{
        save();
}

void init()
{
        object me;

        ::init();

        if (interactive(me = this_player()))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

        delete_temp("decide_withdraw", me);
        delete_temp("demolish_room", me);

        add_action("do_stop", "stop");
        add_action("do_answer", "answer");
        add_action("do_desc", "desc");
        add_action("do_show", "show");
        add_action("do_changename", "changename");
        add_action("do_changeid",   "changeid");
        add_action("do_changetype", "changetype");
        add_action("do_changedesc", "changedesc");
        add_action("do_finish", "finish");
        add_action("do_finish", "ok");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "chexiao");
        add_action("decide_withdraw", "decide");
        add_action("do_demolish", "demolish");

        // 如果來的是有資格處理表單的巫師就增加處理表單的命令
        if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
        {
                add_action("do_help", "help");
                add_action("do_list", "list");
                add_action("do_type", "type");
                add_action("do_agree", "agree");
                add_action("do_reject", "reject");
                add_action("do_delete", "delete");
        }
}

// 存盤文檔
string query_save_file()
{
        return "/data/npc/luban";
}

void greeting(object me)
{
        if (!objectp(me) || environment(me) != environment())
                return;

        // 對巫師提示的信息
        if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
        {
                if (query("form") && sizeof(query("form")) >= 1)
                {
                        message_vision("魯班對$N道，來的正好，我這裏有"
                                       "些單子正要處理呢。\n", me);
                        tell_object(me, HIG "魯班告訴你：請用" HIW "list" HIG "察看，" +
                                        HIW "type" HIG "顯示詳細信息，" HIW "agree" HIG +
                                        "同意，" HIW "reject" HIG "拒絕，" HIW "delete" HIG
                                        "刪除表單。\n            使用" HIW "help" HIG
                                        "可以查看上述命令的説明和使用幫助。\n" NOR);
                } else
                        message_vision("魯班對$N點點頭，道：公輸班正在授課，不及遠迎，失禮了！\n", me);
                return ;
        } else
        if( query("form/"+query("id", me)) )
        {
                tell_user_status(me);
        } else
        // 對玩家提示的信息
        if( query_temp("contract/luban", me) )
        {
                message_vision("魯班對$N笑道：這位" +
                               RANK_D->query_respect(me) +
                               "，剛才怎麼談着談着就走了？若是有"
                               "意，咱們繼續談嘛。\n", me);
        } else
        switch(random(3)) {
        case 0 :
                message_vision("魯班對$N説道：這位" +
                               RANK_D->query_respect(me) +
                               "，可是對建房有興趣？\n", me);
                break;
        case 1 :
                message_vision("魯班對$N笑道：這位" +
                               RANK_D->query_respect(me) + "，行走江湖"
                               "，若是沒有個落腳之處怎麼行啊！\n", me);
                break;
        case 2 :
                message_vision("魯班對$N一拱手，説道：這位" +
                               RANK_D->query_respect(me) +
                               "，很久沒見啊，別來無恙？\n", me);
                break;
        }
}

// 認證學習
int recognize_apprentice(object me)
{
        if( query_temp("mark/魯班", me) && 
            !query_temp("learnd_from/魯班", me) )
        {
                message_vision("魯班對$N説：好，你既然有心學，我就"
                               "教你一點吧。\n", me);
                set_temp("learnd_from/魯班", 1, me);
        }

        set_temp("mark/魯班", 1, me);
        return 1;
}

// 接受物品：圖紙
int accept_object(object me, object ob)
{
        object room;
        object build;           // 建房的地點

        if( ob->id("key") && query("item_make", ob) )
        {
                // 如果接收的是鑰匙，就收下
                message_vision("$N把" + ob->name() + "遞給了魯班，魯班"
                               "點點頭，接過來隨手把它扔到了一邊的箱子"
                               "裏。\n", me);
                destruct(ob);
                return 1;
        }

        if( query("money_id", ob) && query_temp("ask_for_key", me) && 
            mapp(query("private_room", me)) )
        {
                room=get_object(query("private_room/entry", me));
                if (! room)
                {
                        message_vision("魯班擾擾頭，苦惱的對$N道：我怎麼"
                                       "找不到你的家呢？怪事。\n", me);
                        delete_temp("ask_for_key", me);
                        return 0;
                }

                if (ob->value() >= 50000)
                {
                        message_vision("魯班道：好！不過鑰匙換了以後，"
                                       "以前的鑰匙可就全都作廢啦。\n", me);
                        delete_temp("ask_for_key", me);
                        if (create_new_key(me));
                        {
                                destruct(ob);
                                return 1;
                        }
                        return 0;
                } else
                if (ob->value() >= 1000)
                {
                        object ko;

                        delete_temp("ask_for_key", me);
                        ko = get_user_key(me);
                        if (ko)
                        {
                                message_vision("魯班拿出一把鑰匙，遞給"
                                               "$N道：諾！鑰匙配好了，"
                                               "你把它收好！\n", me);
                                ko->move(me);
                                destruct(ob);
                                return 1;
                        }

                        message_vision("魯班疑惑道：奇怪，我找不到鑰匙"
                                       "的原型，你問一下巫師吧。\n", me);
                        return 0;
                }
                message_vision("魯班看了看$N的錢，皺眉道：你這點錢幹什"
                               "麼也不夠啊！\n", me);
                return 0;
        }

        if (ob->id("paper of drawing"))
        {
                if( mapp(query("private_room", me)) )
                {
                        message_vision("魯班呵呵笑道：莫非你有一處住房還是不夠？\n", me);
                        return 0;
                }
                // 這是為了防止出現不正確的build_room的標記
                delete("private_room", me);

                if( query("form/"+query("id", me)) )
                {
                        message_vision("魯班笑道：慌甚！你不是已經提交"
                                       "了申請麼？可以用show察看申請。\n", me);
                        return 0;
                }
                if( query_temp("contract/luban", me) )
                {
                        message_vision("魯班疑惑的對$N説道：幹什麼？剛"
                                       "才不是給過我了麼？若是有什麼想"
                                       "法，可以改日再談(stop)。\n", me);
                        return 0;
                }

                if( !query("draw", ob) )
                {
                        message_vision("魯班看了一下，對$N説道：你給我"
                                       "一張白紙幹什麼？你要是不會就和"
                                       "我學學繪畫技巧(drawing)吧。\n", me);
                        return 0;
                }

                if( query("draw/info", ob) == "unknow" )
                {
                        message_vision("魯班接過圖紙，看了半天，問$N道"
                                       "：你這畫的是什麼東西？你要是不"
                                       "會跟我學學繪畫技巧(drawing)。\n", me);
                        return 0;
                }

                if( query("draw/type", ob) != "風景" )
                {
                        message_vision("魯班對$N歎道：我説你建房得把那"
                                       "地方畫給我看啊，你現在畫" +
                                       query("draw/type", ob)+
                                       "給我有什麼用？\n", me);
                        return 0;
                }

                message_vision("魯班接過圖紙看了看，對$N笑道："
                               "畫的還行，馬馬虎虎吧。\n", me);

                build=get_object(query("draw/info", ob));
                if (! objectp(build))
                {
                        message_vision("魯班仔細看了看，歎了口氣説道："
                                       "那個地方現在好像已經不存在了.."
                                       ".\n", me);
                        return 0;
                }

                if (! build->is_build_room())
                {
                        message_vision("魯班仔細看了看，不禁皺了皺眉，"
                                       "對$N説道：那個地方好像不能建房"
                                       "吧...\n", me);
                        return 0;
                }

                if( query("max_room", build) && 
                    query("max_room", build) <= build->query_room_count() )
                {
                        message_vision("魯班看完了以後沉思片刻，對$N道"
                                       "：那個地方的房屋已經太多了，我"
                                       "看你就算了吧！\n", me);
                        return 1;
                }

                set_temp("contract/luban/position",query("draw/info",  ob), me);
                destruct(ob);
                quest_user(me);
                return 1;
        }

        // 看看是否填寫了表單
        if( (query("money_id", ob) || ob->id("fee free card")) && 
            mapp(query("form/"+query("id", me))) )
        {
                int value;

                if( query("form/"+query("id", me)+"/status") != "同意" )
                {
                        message_vision("魯班搖搖頭，對$N道：巫師還沒有"
                                       "批准你的申請，你先請回吧。\n", me);
                        return 0;
                }

                value=query("form/"+query("id", me)+"/value");
                if( query("money_id", ob) && ob->value()<value )
                {
                        message_vision("魯班接過" + ob->name() + "掂了"
                                       "掂，對$N呵呵笑道"
                                       "：這錢似乎不夠吧？\n", me);
                        return 0;
                }

                if (ob->id("fee free card") &&
                    query("fee free", ob)<value )
                {
                        message_vision("魯班接過免費卡看了一會兒對$N笑"
                                       "道：真是抱歉，不過這卡還不夠購"
                                       "買這間房！\n", me);
                        return 0;
                }

                message_vision("魯班接過" + ob->name() + "，對$N道："
                               "好！馬上就好！\n", me);
                destruct(ob);
                create_room(me);
                return 1;
        }

        // 看看是否夠手續費
        if( query("money_id", ob) || ob->id("fee free card") )
        {
                if( query_temp("contract/luban/questing", me) != "quest_desc" )
                {
                        message_vision("魯班微微一笑，對$N道：幹什麼這"
                                       "麼客氣？我不收無功之祿。\n", me);
                        return 0;
                }
                if (ob->value() < 50000 && ! ob->id("fee free card"))
                {
                        message_vision("魯班嘿然冷笑，對$N道：五兩黃金"
                                       "你都吝惜？哼哼，就算是天神親臨"
                                       "，我也不打折扣。\n", me);
                        return 0;
                }
                message_vision("魯班接過" + ob->name() + "，在手中掂了"
                               "掂，滿意的對$N説道：很好，我就給你記錄"
                               "在案，若是有了消息，一定通知你。\n", me);
                record_contract(me);
                delete_temp("contract", me);

                if (ob->id("fee free card"))
                {
                        message_vision("魯班又道：這張免費卡你先留着吧"
                                       "，建房的時候再給我。\n", me);
                        return -1;
                } else
                {
                        destruct(ob);
                        return 1;
                }
        }
        message_vision("魯班擺擺手，對$N道：你還是自己留着吧，我可用不着。\n", me);
        return 0;
}

private void tell_user_status(object me)
{
        int value;

        // 該玩家提交了表單，根據表單的狀態返回提示信息
        switch(query("form/"+query("id", me)+"/status")){
        case "申請" :
                luban_say("巫師還沒有查閲你的申請，要想查看你提"
                          "交的表單可以用show，如果想修改可以問我。\n");
                break;

        case "拒絕" :
                luban_say("你的申請被拒絕了，你可以用show查看詳"
                          "情，如果想修改可以問我。\n");
                break;

        case "同意" :
                value=query("form/"+query("id", me)+"/value");
                if (! value)
                {
                        luban_say("你的申請已經被批准了，隨便意思意思"
                                  "給點錢即可建房，查看詳情請用show，"
                                  "如果想修改可以問我。\n");
                } else
                {
                        luban_say("你的申請已經被批准了，繳納" +
                                  MONEY_D->price_str(value) +
                                  "即可建房，查看詳情請用show，如果想"
                                  "修改可以問我。\n");
                }
                break;
        }
}

// 製作新的鑰匙
private int create_new_key(object me)
{
        string key_short;
        string key_file;
        string content;
        string old_id;
        string new_id;
        mixed *file;
        object room;
        int i;
        int n;

        // 生成新鑰匙
        n=1+query("private_room/key_no", me);
        if (n <= 1) n = 2;
        key_short = file_dir(me) + "key";
        key_file = key_short + (string) (n % 100);
        content = read_file(key_short + ".c");
        if (! content)
        {
                message_vision("魯班聳聳肩，無奈的對$N道：我幫不了你了，"
                               "鑰匙的原型找不到了，你問問巫師吧。\n", me);
                return 0;
        }

        // 更新並寫入鑰匙的文件
        old_id="1 of "+query("id", me);
        new_id=n+" of "+query("id", me);
        content = replace_string(content, "這是原配鑰匙", "這是" +
                                 query("name", me)+"第"+
                                 chinese_number(n) + "次配的鑰匙");
        content = replace_string(content, old_id, new_id);
        rm(key_file + ".c");
        write_file(key_file + ".c", content);
        VERSION_D->append_sn(key_file + ".c");

        // 修正所有房屋對象
        file = get_dir(file_dir(me) + "*.c", -1);
        if (! sizeof(file))
        {
                message_vision("魯班聳聳肩，無奈的對$N道：我幫不了你了，"
                               "你的房間我找不着了，你問問巫師吧。\n", me);
                rm(key_file + ".c");
                return 0;
        }
        for (i = 0; i < sizeof(file); i++)
        {
                if (file[i][1] <= 0)
                        // 不是文件
                        continue;

                room = get_object(file_dir(me) + file[i][0]);
                if (! room || ! room->is_private_room())
                        // 無法找到對象或者對象不是私有房間類型
                        continue;

                room->restore();
                if( !stringp(query("room_key", room)) )
                        // 該房間不需要鑰匙
                        continue;

                // 設置新鑰匙
                set("room_key", new_id, room);
                room->save();

                // 提示信息
                message("vision", @LONG
一個垂髫童子拎着箱子走了過來，摸出工具，三下五除二，你還沒能
明白過來是怎麼回事，他就“咔咔”幾下把鎖換掉了，飛也似的走了。
LONG, room);

        }

        // 更新配製鑰匙的信息
        set("private_room/key_no", n, me);

        clone_object(key_file)->move(me);
        message_vision("魯班接過摸出一把鑰匙遞給$N，道：你就用這把鑰匙吧，"
                       "鎖我馬上就給你換掉。\n", me);

        return 1;
}

// 複製玩家的鑰匙
private object get_user_key(object me)
{
        string key_file;
        string content;
        object entry;
        int n;

        key_file = file_dir(me) + "key";
        n=query("private_room/key_no", me);
        if (n > 1) key_file += (string) (n % 100);

        return new(key_file);
}

// 回答有關建房的信息
private int ask_me()
{
        object me;
        me = this_player();

        if( mapp(query("private_room", me)) )
        {
                message_vision("魯班點點頭，對$N説道：怎麼樣，住得可滿"
                               "意？若是不滿意，可以找我重建哦。\n", me);
                return 1;
        }

        if( query("form/"+query("id", me)) )
        {
                tell_user_status(me);
                return 1;
        }

        message_vision(@SAY
魯班微一歎氣，説道：想江湖兒女，一劍縱橫，快意恩仇，馳騁天下，若
是沒有個落腳之處怎生得了？或隱身於鬧市，或遁跡於險川，你若有意何
不畫張圖紙給我，若是地點合適，你且挑個滿意的樣式，我給你建個住房。
今生今世，不再懼那風雨。
SAY , me);
        return 1;
}

// 回答有關圖紙的信息
private int ask_paper()
{
        object  me;
        object  ob;

        me = this_player();

        if (is_busy())
        {
                tell_object(me, "魯班正忙着呢，沒功夫理你...\n");
                return 1;
        }

        if( mapp(query("private_room", me)) || 
            query("form/"+query("id", me)) )
        {
                message_vision("魯班翻出一張紙，遞給$N道：自個兒玩去吧。\n", me);
        } else
        {
                message_vision("魯班點點頭，對$N説道：很好，你拿這份圖"
                               "紙，到了想要建房的地點，畫下來(draw)拿"
                               "回給我看看。\n", me);
        }
        ob = new("/d/room/obj/paper");
        if (objectp(ob))
        {
                message_vision("魯班翻了翻，找到一張圖紙，遞給了$N。\n", me);
                ob->move(me);
        } else
        {
                message_vision("魯班翻了半天也沒找到，不禁一呆，説道："
                               "怎麼回事，沒有了？你去找巫師問問吧！\n", me);
        }

        start_busy(4);
        return 1;
}

// 回答有關繪畫技巧的信息
private int ask_drawing()
{
        message_sort("魯班對$N説道：要想畫張好點的圖紙，不會"
                     "點繪畫技巧是不行的，沒有人天生就會作畫"
                     "，都得學習，你若有意，不妨和我學學。\n",
                     this_player());
        return 1;
}

// 打聽拆屋的消息
private int ask_demolish()
{
        object me;

        me = this_player();
        if( query_temp("contract/luban", me) )
        {
                message_vision("魯班對$N説：你不是要建房麼，怎麼還沒建"
                               "好就要拆房了？真是未雨綢繆啊！\n", me);
                return 1;
        }

        if( query("form/"+query("id", me)) )
        {
                message_vision("魯班哼了一聲，對$N道：你的房子還沒見到"
                               "渣呢！你要是不想建了，就撤消(withdraw)"
                               "申請算了。\n", me);
                return 1;
        }

        if( !mapp(query("private_room", me)) )
        {
                message_vision("魯班哈哈大笑，對$N道：拆屋？你還沒有呢"
                               "，拆什麼拆！亂拆別人的屋子可是犯法的！"
                               "\n", me);
                return 1;
        }

        if( query_temp("demolish_room", me) )
        {
                message_vision("魯班對$N説：你要是真的想拆屋，就請下決"
                               "心(demolish)！\n", me);
                return 1;
        }

        message_vision("魯班睜大了眼睛，奇怪的看着$N，過了良久才説：你"
                       "若是真到要拆屋，就下決心吧(demolish)！\n", me);
        set_temp("demolish_room", 1, me);
        return 1;
}

// 打聽重建的消息
private int ask_rebuild()
{
        object me;

        me = this_player();
        if( !mapp(query("private_room", me)) )
        {
                message_vision("魯班搖搖頭，對$N説：你還沒有房子呢，"
                               "談什麼重建！\n", me);
                return 1;
        }
        message_vision("魯班歎了口氣，對$N説：你若是要重建，就先把房"
                       "拆了吧！\n", me);
        return 1;
}

// 重新配置鑰匙
private int ask_key()
{
        object me;

        me = this_player();

        if (is_busy())
        {
                write("魯班正忙着呢，沒空理你...\n");
                return 1;
        }

        if( !mapp(query("private_room", me)) )
        {
                message_vision("魯班看了$N半天，才説：沒有房子你要鑰"
                               "匙幹什麼？\n", me);
                return 1;
        }

        if( query_temp("ask_for_key", me) )
        {
                message_vision("魯班對$N怒道：你羅不羅唆，我説了配鑰"
                               "匙十兩紋銀，換鎖五兩黃金！\n", me);
                return 1;
        }

        message_vision("魯班對$N道：容易！配把鑰匙十兩紋銀，換鎖帶作一"
                       "把新的鑰匙五兩黃金，不還價！\n", me);
        set_temp("ask_for_key", 1, me);
        return 1;
}

// 打聽描述規則信息
private int ask_desc()
{
        luban_say(@INFORMATION
描述信息可以使用顏色，並且可以分行，但是最多不能超過160個漢字：

顏色的規則：
$BLK$ - 黑色            $NOR$ - 恢復正常顏色
$RED$ - 紅色            $HIR$ - 亮紅色
$GRN$ - 綠色            $HIG$ - 亮綠色
$YEL$ - 土黃色          $HIY$ - 黃色
$BLU$ - 深藍色          $HIB$ - 藍色
$MAG$ - 淺紫色          $HIM$ - 粉紅色
$CYN$ - 藍綠色          $HIC$ - 天青色
$WHT$ - 淺灰色          $HIW$ - 白色

換行：
只要在描述信息中添加一個\n就可以。比如：“這是一間小院。\n院子邊上的牆很矮。”
實際看到的描述使這個樣子的：
這是一間小院。
院子邊上的牆很矮。

説明：
系統自動會在描述字符串的尾端加一個 $NOR$ 和 \n。因此描述最好不要以\n結束，以免
空行太多。另外，系統會自動的規範你輸入的描述信息，因此你不需要在描述信息前面添
加段落起始的空格，同時也不需要在一個段落內部插入\n以實現換行，對於過長的段落系
統會自動的添加換行符。


INFORMATION );
        return 1;
}

// 打聽修改的消息
private int ask_modify()
{
        object me;

        me = this_player();
        if( !submit_form(query("id", me)) && 
            query_temp("contract/luban/questing", me) != "quest_desc" )
        {
                message_vision("魯班搖搖頭，對$N説：你只有描述時或是提"
                               "交了申請以後才用得着修改。\n", me);
                return 1;
        }

        message_vision("魯班點點頭，對$N説：你可以修改你提交的申請中的各種信息：\n" +
                "\n你可以通過以下指令修改房屋的各種信息：\n" +
                HIW "changename " NOR "name : 修改房屋的中文名字。\n" +
                HIW "changeid   " NOR "id   : 修改房屋的英文代號。\n" +
                HIW "changetype " NOR "type : 修改房屋的類型。\n" +
                HIW "changedesc " NOR "room desc : 修改某間房屋的描述。\n", me);
        return 1;
}

// 輸出魯班説話時的表情
private void luban_say(string msg)
{
        object me;
        me = this_player();
        message("vision","魯班對"+query("name", me)+"嘀嘀咕咕説了"
                "些話。\n", environment(me), ({ me }));
        tell_object(me, "魯班説道：" + msg);
}

// 輸出用户説話時的表情
private void user_say(string msg)
{
        object me;

        me = this_player();
        tell_object(me, "你對魯班小聲道：" + msg);
        message("vision",query("name", me)+"對魯班嘀嘀咕咕説了些話。"
                "\n", environment(me), ({ me }));
}

// 用户中止商談
private int do_stop()
{
        object me;
        me = this_player();
        if( !query_temp("contract/luban", me) )
        {
                message_vision("魯班一臉傻樣......\n", me);
                return 1;
        }
        delete_temp("contract/luban", me);
        message_vision("魯班對$N點點頭，説道：既然如此，改日再談也不妨"
                       "。\n", me);
        return 1;
}

// 用户回答問題
// 根據當前狀態做出相應的反應
private int do_answer(string arg)
{
        object me;
        string questing;

        me = this_player();
        questing=query_temp("contract/luban/questing", me);

        // 判斷現在是否正在商談
        if (! questing)
                return 0;

        if (! arg)
                return notify_fail("你回答什麼啊？\n");

        switch (questing) {
        // 商談房屋名字
        case "quest_name" :
                user_say("房屋的名字就叫" + arg + "吧！\n\n");
                check_name(me, arg);
                break;

        case "quest_id" :
                user_say("代號就叫" + arg + "吧！\n\n");
                check_id(me, arg);
                break;

        case "quest_type" :
                user_say("你覺得" + arg + "的房型怎麼樣？我就要這個了。\n\n");
                check_type(me, arg);
                break;

        default:
                write("沒人問你問題，你想回答什麼？\n");
                break;
        }
        return 1;
}

// 記錄用户輸入的描述信息
private int do_desc(string arg)
{
        object me;
        string room_name;
        string desc;

        me = this_player();

        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        if (arg)
        {
                if (sscanf(arg, "%s %s", room_name, desc) != 2)
                {
                        room_name = arg;
                        desc = 0;
                }
        }
        else
        {
                show_desc(me, 0);
                return 1;
        }

        record_desc(me, room_name, desc);
        return 1;
}

// 顯示用户自己輸入的描述信息
private int do_show(string arg)
{
        show_desc(this_player(), arg);
        return 1;
}

// 改變房屋名字
// 分兩種狀態處理：商談中或是申請中
private int do_changename(string arg)
{
        object me;
        string player_id;
        string position;

        me = this_player();
        player_id=query("id", me);

        if (submit_form(player_id))
        {
                // 正在申請
                position = query_form(player_id, "position");
                if (! check_legal_name(arg, position)) return 1;

                luban_say("好吧，就改成" + arg + "這個名字吧！\n");
                set_form(player_id, "name", arg);
                set_form(player_id, "status", "申請");
                save();
                return 1;
        } else
        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        // 正在商談
        if( check_legal_name(arg,query_temp("contract/luban/position", me)) )
        {
                set_temp("contract/luban/name", arg, me);
                luban_say("好吧，就改成" + arg + "這個名字吧！\n");
        }
        return 1;
}

// 改變房屋代號
// 分兩種狀態處理：商談中或是申請中
private int do_changeid(string arg)
{
        object me;
        string player_id;
        string position;

        me = this_player();
        player_id=query("id", me);

        if (submit_form(player_id))
        {
                // 正在申請
                position = query_form(player_id, "position");
                if (! check_legal_id(arg, position)) return 1;
                luban_say("行啊，就改成" + arg + "這個房屋代號吧！\n");
                set_form(player_id, "id", arg);
                set_form(player_id, "status", "申請");
                save();
                return 1;
        } else
        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        // 正在商談
        if( check_legal_id(arg,query_temp("contract/luban/position", me)) )
        {
                set_temp("contract/luban/id", arg, me);
                luban_say("行啊，就改成" + arg + "這個房屋代號吧！\n");
        }
        return 1;
}

// 改變房屋類型
// 分兩種狀態處理：商談中或是申請中
private int do_changetype(string arg)
{
        object me;
        int value;
        string player_id;
        string position;
        mapping example;

        me = this_player();
        player_id=query("id", me);

        if (! arg)
        {
                user_say("慢着... 我看看是不是換個房型更好...\n\n");
                check_type(me, arg);
                return 1;
        }

        if (submit_form(player_id))
        {
                // 正在申請
                user_say("我得改改房型，就換成" HIC + arg + NOR "吧。\n\n");
                if (! (example = check_legal_type(arg)))
                {
                        write("找不到這種類型的房屋，所以沒有改變房屋的類型。\n");
                        return 1;
                }
                set_form(player_id, "room", example["name"]);
                value = example["value"];
                if (wizardp(me)) value = 0;
                set_form(player_id, "value", value);
                set_form(player_id, "descs", ([ ]));
                set_form(player_id, "status", "申請");
                save();
                luban_say("換一種房型也行，不過請你填寫新的描述(changedesc)。\n");
                return 1;
        } else
        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        // 正在商談
        user_say("慢着... 我得改改房型，就換成" HIC + arg + NOR "吧。\n\n");

        if (! check_type(me, arg))
                write("你沒有改變房屋類型。\n");
        return 1;
}

// 改變房屋名字
// 分兩種狀態處理：商談中或是申請中
private int do_changedesc(string arg)
{
        object me;
        string player_id;
        mapping example;
        string room_name;
        string room_desc;

        me = this_player();
        player_id=query("id", me);

        if (submit_form(player_id))
        {
                // 正在申請
                if (! arg)
                        return notify_fail("請按照正確格式輸入：changedesc"
                                           " room_name description\n");

                if (sscanf(arg, "%s %s", room_name, room_desc) != 2)
                {
                        room_name = arg;
                        room_desc = 0;
                }

                // 修改描述信息
                modify_desc_in_form(player_id, room_name, room_desc);
                set_form(player_id, "status", "申請");
                save();
                return 1;
        } else
        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        // 正在商談
        do_desc(arg);
        return 1;
}

// 結束輸入
private int do_finish()
{
        object me;
        int value;
        string msg;

        me = this_player();
        if( query_temp("contract/luban/questing", me) != "quest_desc" )
                return 0;

        show_desc(me, 0);

        value=query_temp("contract/luban/value", me);
        user_say("好了，我弄完了，你們這就開始麼？\n\n");
        if (value)
        {
                msg = "金臨撥拉撥拉算盤，慢條斯理的對$N説道：要造這樣"
                      "的房子，少説也得" + MONEY_D->price_str(value) +
                      "，不二價！\n";
                if (wizardp(me))
                {
                        msg += "魯班對金臨喝道：不得無理！此乃上屆仙人"
                               "... 嘿嘿，到時意思意思就算了吧。\n";
                }
        } else
        {
                msg = "金臨拉撥拉算盤，對$N説道：便宜你了，造這個房子"
                      "免費，不要錢！\n";
        }

        msg += "魯班略一沉吟，然後説道：你看看有沒有什麼問題麼？若是沒"
               "有，請先交"HIR"五兩黃金的手續費。\n\n"NOR;
        message_vision(msg, me);

        return 1;
}

// 撤消表單
private int do_withdraw()
{
        object me;

        me = this_player();
        if( query_temp("contract/luban", me) )
        {
                do_stop();
                return 1;
        }
        if( !query("form/"+query("id", me)) )
        {
                message_vision("魯班一臉茫然......對$N説道：現在你好像"
                               "沒有提交的申請吧！\n", me);
                return 1;
        }

        if( query_temp("decide_withdraw", me) )
        {
                message_vision("魯班對$N説道：你若是要撤消申請，就請下"
                               "決定(decide)！\n", me);
                return 1;
        }

        switch(query("form/"+query("id", me)+"/status")){
        case "申請":
                luban_say("可惜，你怎麼這就反悔了？\n");
                break;

        case "同意":
                luban_say("哎呀！真是可惜，巫師都同意了，你怎麼打退堂"
                          "鼓了？\n");
                break;

        case "拒絕":
                luban_say("唉！沒能被批准也別就打退堂鼓麼，看看怎麼回"
                          "事再説麼。\n");
                break;
        }
        message_vision("魯班歎了口氣，對$N説道：既然如此，此事也不必勉"
                       "強，如果你想好了，就下決定(decide)吧！\n", me);
        set_temp("decide_withdraw", 1, me);
        return 1;
}

// 刪除表單
private int decide_withdraw()
{
        object me;

        me = this_player();
        if( !query_temp("decide_withdraw", me) )
                return 0;

        delete_temp("decide_withdraw", me);
        delete("form/"+query("id", me));
        save();
        message_vision("魯班搖搖頭，掏出一個賬本，翻了翻，不知道劃掉了"
                       "什麼東西。\n", me);
        return 1;
}

// 拆毀房屋
// 必須先詢問魯班有關拆房的信息
private int do_demolish()
{
        object me;

        me = this_player();
        if( !query_temp("demolish_room", me) )
                return notify_fail("你要拆什麼？拆屋可要先和魯班説一聲。\n");

        delete_temp("demolish_room", me);
        demolish_room(me);
        return 1;
}

// 拆毀房屋的執行函數，該函數可能會被外部調用，所以必須察看權限
int demolish_room(object me)
{
        string *names;
        string room_name;
        string key_id;
        mixed *file;

        object ob;
        object *obs;

        int i, t;
        int n;

        if (! is_root(previous_object()))
        {
                write ("你沒有權利拆毀房屋。\n");
                return 0;
        }

        if( !mapp(query("private_room", me)) )
        {
                write("數據錯誤，無法繼續執行！\n");
                return 0;
        }

        // 先清除所有的鑰匙，以免留在當前玩家手中出問題。
        room_name=query("private_room/name", me)+"("+
                    query("private_room/id", me)+")";
       command("chat 手裏有"+query("name", me)+"的"+
                room_name + "鑰匙的，請你把鑰匙交回到我這裏來。");

        // updated by Lonely@nitan3
        n=query("private_room/key_no", me);

        for (t = 1; t <= n; t++)
        {
                reset_eval_cost();
                key_id=t+"of"+query("id", me);
                obs = users();
                for (i = 0; i < sizeof(obs); i++)
                {
                        int flag;
                        int k;
                        object *carries;

                        if ((i + 1) % 100 == 0)
                                // 防止執行時間過長而發生錯誤
                                reset_eval_cost();

                        // 去掉玩家身上所有被毀掉的住房的鑰匙
                        carries = all_inventory(obs[i]);
                        for (k = 0, flag = 0; k < sizeof(carries); k++)
                        {
                                if (! carries[k]->id(key_id))
                                        continue;

                                destruct(carries[k]);
                                if (flag) continue;

                                tell_object(obs[i], "\n你覺得身上好像少了點什麼"
                                            "東西，仔細一看原來是" +
                                            query("name", me)+
                                            "家的鑰匙不見了。\n\n");
                                flag = 1;
                        }
                }
        }

        // 防止執行時間過長而發生錯誤
        reset_eval_cost();

        // 刪除用户創建的所有文件
        // 同時刪除鑰匙文件，鑰匙有可能留在某些玩家手裏，所以登錄的
        // 時候可能會產生一些問題。
        file = get_dir(file_dir(me), -1);
        seteuid(getuid());
        if (file)
        {
                // 先清除所有的對象(object)
                for (i = 0; i < sizeof(file); i++)
                {
                        object room;

                        if (strsrch(file[i][0], ".c") == -1)
                                continue;

                        room = find_object(file_dir(me) + file[i][0]);
                        if (room)
                        {
                                message("vision", "突然幾個童子飛也似"
                                        "的衝了過來，手裏操着各種傢伙"
                                        "，嚷嚷道：閃開！都閃開！\n",
                                        room);
                                catch(DBASE_D->clear_object(room));
                        } else
                        {
                                // clear the data in dbase
                                catch(DBASE_D->clear_object(file_dir(me) + file[i][0][0..<3]));
                        }
                }

                // 然後清除文件，因為清除對象的時候有可能因為保存
                // 進度而生成文件
                file = get_dir(file_dir(me), -1);
                for (i = 0; i < sizeof(file); i++)
                        rm(file_dir(me) + file[i][0]);
        }
        rmdir(file_dir(me));

        ob=get_object(query("private_room/position", me));
        if (! objectp(ob))
        {
                write("有關房屋的信息已經被刪除。但是建房的地點已經找"
                      "不到了！你和巫師聯繫吧。\n");
                delete("private_room", me);
                me->save();
                return 0;
        }

        ob->destroy_room(query("private_room/id", me));
        ob->save();
        delete("private_room", me);
        me->save();
        if (environment(me) == environment(this_object()))
        {
                // 玩家在現場
                message_vision("魯班點點頭，對$N説：好了，剩下的事情"
                               "我會辦妥的！你可以走了。\n", me);
        }

        return 1;
}

// 顯示用户輸入的描述信息
// 如果用户正在商談，就顯示用户剛輸入的描述信息，如果用户在等待審批，則顯示用户
// 以前輸入的描述信息
// 獲得一個player對房屋的描述
// room_name是用户指定的房屋中的某一間的short描述
private void show_desc(mixed player, string room_name)
{
        mapping filesp;         // 原型房屋描述的文件mapping
        mapping descsp;         // 玩家的描述mapping

        int i;
        int value;              // 房屋造價
        int count;              // 顯示的描述信息的數目
        object me;              // 調用該函數的對象
        object ob;              // 被描述的房屋的object或是建房場景的object

        string player_id;       // 建造房屋的玩家ID
        string desc;            // 房屋描述的mapping
        string *names;          // 房屋mapping的關鍵字的字符串表
        string room_nameid;     // 房屋名字及ID
        string room_type;       // 房屋類型
        string position;        // 建房的位置

        string ids;             // 查詢時使用

        string info;            // 最後給出的提示信息
        string msg;             // 臨時變量，用於顯示信息

        me = this_player();
        info = "";

        if (objectp(player))
                player_id=query("id", player);
        else
        if (stringp(player))
                player_id = player;
        else
                return;

        if (mapp(query("form/" + player_id)))
        {
                // 在表單中有該玩家提交的表單
                ids = "form/" + player_id + "/";
                room_type = query(ids + "type");
                for (i = 0; i < sizeof(room_example); i++)
                {
                        if (room_example[i]["type"] == room_type)
                        {
                                filesp = room_example[i]["files"];
                                break;
                        }
                }
                if (! mapp(filesp))
                {
                        write("你申請的房屋類型(" + room_type + ")已經"
                              "不存在了，請和巫師聯繫。\n");
                        return;
                }
                descsp = query(ids + "descs");
                room_type = query(ids + "room") + "(" + room_type + ")";
                room_nameid = query(ids + "name") + "(" + query(ids + "id") + ")";
                value = query(ids + "value");
                position = query(ids + "position");
                // 提示信息中給出該房屋的申請結果
                msg = query(ids + "wizard");
                switch (query(ids + "status")) {
                case "申請" :
                        info = "巫師還沒有查閲這份申請。";
                        break;

                case "拒絕" :
                        info = msg + "已經拒絕了這份申請！";
                        if (query(ids + "memo") != "無")
                                info += "\n原因是：" + query(ids + "memo");
                        break;

                case "同意" :
                        info = msg + "已經同意了這份申請！";
                        break;
                }

                if( query("id", this_player()) == player_id )
                {
                        if (query(ids + "status") == "同意")
                        {
                                info += HIW "\n你現在可以建造房屋了。"
                                        "如果這時修改了房屋的信息，就"
                                        "要得到巫師的再次批准。" NOR;
                        } else
                        if (query(ids + "status") == "拒絕")
                        {
                                info += HIR "\n你現在最好修改房屋的信"
                                        "息以獲得巫師的批准，否則請撤"
                                        "消申請。" NOR;
                        }
                        info += "\n你可以撤消(withdraw)你提交的申請。";
                }
        } else
        if (objectp(player = present(player_id, environment(this_object()))) &&
            query_temp("contract/luban/questing", player) == "quest_desc" )
        {
                // 找到了在魯班面前正在商談的玩家
                filesp=query_temp("contract/luban/room/files", player);
                descsp=query_temp("contract/luban/descs", player);
                room_type=query_temp("contract/luban/room/name", player);
                room_type+="("+query_temp("contract/luban/room/type", player)+")";
                room_nameid=query_temp("contract/luban/name", player)+"("+
                              query_temp("contract/luban/id", player)+")";
                value=query_temp("contract/luban/value", player);
                position=query_temp("contract/luban/position", player);
        } else
        {
                // 沒有商談
                luban_say("呵呵，這位好像還沒有打算建房子吧。\n");
                return;
        }

        ob = get_object(position);
        if (! objectp(ob))
        {
                write("你申請的建造房屋的地方(" + position + ")已經不"
                      "存在了，請和巫師聯繫!\n");
                return;
        }

        user_say("來，讓我我看看" + room_nameid + "究竟打算怎麼建。\n\n");
        msg = "好，你看看吧：" + "這裏選用的是" + room_type +
              "這種類型的房屋。\n它的名字是" + room_nameid +
              "，將建築在"+query("short", ob);
        if (wizardp(me) && wiz_level(me) >= WIZLEVEL)
                msg += "(" + position + ")";
        msg += "。\n";
        luban_say(msg);

        names = keys(filesp);
        count = 0;
        for (i = 0; i < sizeof(filesp); i++)
        {
                // 查找該房屋的object
                ob = get_object(filesp[names[i]]);
                if (! objectp(ob))
                {
                        write(HIR "找不到示例的房屋(" + names[i] + "::" + filesp[names[i]] + ")，請和巫師聯繫。\n" NOR);
                        continue;
                }
                if (! room_name || room_name == "" ||
                    query("short", ob) == room_name || names[i] == room_name )
                {
                        // 查找用户輸入的描述信息
                        desc = descsp[names[i]];
                        write(YEL "───────────────────────────────────────\n" NOR);
                        write(YEL+"關於"+query("short", ob)+"("+names[i]+")"+YEL+"的描述：\n"+NOR);
                        if (! desc)
                        {
                                // 用户沒有輸入描述信息，顯示缺省信息
                                desc = CYN "現在還沒有輸入描述信息，使"
                                       "用缺省的描述信息。如下：\n";
                                desc += "    ";
                                if( stringp(query("default_long", ob)) )
                                        desc += sort_desc(player,
                                                          query("default_long", ob));
                                else
                                        desc += sort_desc(player,
                                                          replace_string(query("long", ob),"\n",""));
                                desc += NOR;
                        } else
                                desc = "    " + sort_desc(player, desc);
                        write(desc);
                        count++;
                }
        }

        if (! count)
        {
                write("但是這裏沒有" + room_name + "這個房間，請用show查看所有的房間！\n");
                return ;
        }

        write(YEL "───────────────────────────────────────\n" NOR);
        write("描述就是上面列出的這些內容。\n");

        if (! value)
                info += "\n建造這些房間不需要花費任何銀兩。";
        else
                info += "\n建造這些房間需要花費" HIY + MONEY_D->price_str(value) + NOR "。";

        write(info + "\n\n");

        return ;
}

private void promote_type(object me)
{
        int i;
        int len;
        string msg;

        msg = "你眼光略略一掃，看到的房屋類型有：" +
              room_example[0]["name"] + "(" +
              room_example[0]["type"] + ")";
        len = strlen(msg);
        for (i = 1; i < sizeof(room_example); i++)
        {
                string temp;

                temp = "、" + room_example[i]["name"] + "(" +
                              room_example[i]["type"] + ")";
                msg += temp;
                len += strlen(temp);
                if (len > 70)
                {
                        msg += "\n";
                        len = 0;
                }
        }
        if (len) msg += "。\n";
        tell_object(me, msg);
}

// 詢問玩家必要的建房信息，然後記錄，留給巫師審批
private int quest_user(object me)
{
        message_vision("魯班對$N説道：好，來，咱們仔細談談！\n", me);
        // 詢問房屋名稱
        luban_say("先告訴我你想建的房子叫什麼名字(answer name)。\n"
                  "你若是不想談了(stop)，告訴我也無妨。\n");
        set_temp("contract/luban/questing", "quest_name", me);
        return 1;
}

// 詢問描述信息
private int quest_info(object me)
{
        message_vision("魯班對$N説道：好，看來你喜歡" +
                       query_temp("contract/luban/room/name", me)+
                       "這種樣式的。\n", me);
        // 顯示房屋樣式信息

        luban_say(@INFORMATION
你可以為你的房間添加你喜歡的描述，格式是：desc 房間名稱 描述。當
然你也可以使用原有的描述，如果你想看看你輸入的情況，可以用show來察看。
若一切都輸入好了以後鍵入finish或是ok就可以了。如果想修改輸入的房屋名
字，代號，類型的信息可以向我詢問<修改>的方法。

舉個描述的例子：“desc 小院 這裏是一間別致的小院。”這樣就給小院添加
了一行描述。如果想取消小院的描述可以鍵入：“desc 小院”就可以了。

描述還可以使用顏色，可以多行，具體細節可以問我 <規則> 這裏要需要注意
的是：系統自動會在描述字符串的尾端加一個 $NOR$ 和 \n。因此描述不要以
\n結束，以免空行太多，觀之不雅。另外，系統會自動的規範你輸入的描述信
息，因此你不需要在描述信息前面添加段落起始的空格，同時也不需要在一個
段落內部插入\n以實現換行，對於過長的段落系統會自動的添加換行符。

另外，在描述的字符串內部不要輸入空格，跳格，這些輸入都會被抹掉。
INFORMATION );

        set_temp("contract/luban/questing", "quest_desc", me);

        // 清除描述信息
        delete_temp("contract/luban/descs", me);
        set_temp("contract/luban/descs", ([]), me);
        return 1;
}

// 判斷用户輸入的房屋名字
private int check_name(object me, string arg)
{
        if (! arg)
        {
                luban_say("你怎麼不説話？要是不想談了(stop)，明説就是！\n");
                return 0;
        }

        if( !check_legal_name(arg,query_temp("contract/luban/position", me)) )
                return 0;

        // 記錄商談好的房屋名字
        set_temp("contract/luban/name", arg, me);

        luban_say("請確定你的房屋的代號(3到10個英文字母)，考慮好了就回"
                  "答我(answer id)。\n");
        set_temp("contract/luban/questing", "quest_id", me);
        return 1;
}

// 判斷用户輸入的房屋代號
private int check_id(object me, string arg)
{
        if (! arg)
        {
                luban_say("你怎麼不説話？要是不想談了(stop)，明説就是！\n");
                return 0;
        }

        if( !check_legal_id(arg,query_temp("contract/luban/position", me)) )
                return 0;

        // 記錄商談好的房屋代號
        set_temp("contract/luban/id", arg, me);

        luban_say("你想要哪種樣式的住房(answer type)? 若是不太清楚，你"
                  "可以到附近的小院一觀。\n");
        promote_type(me);
        set_temp("contract/luban/questing", "quest_type", me);
        return 1;
}

// 判斷用户輸入的房屋類型
private int check_type(object me, string arg)
{
       mixed example;
        int value;

        if (! arg)
        {
                luban_say("你想要哪種樣式的住房(answer type)？若是不"
                          "太清楚，你可以到附近的小院一觀。\n");
                promote_type(me);
                return 0;
        }

        if (! (example = check_legal_type(arg)))
        {
                luban_say("你要的樣式真稀奇，我這現在還沒有。看清楚了"
                          "再告訴我。\n");
                return 0;
        }
        // 記錄用户選定的房屋類型
        set_temp("contract/luban/room", example, me);

        // 計算房屋的價值
        value=query_temp("contract/luban/room/value", me);
        if (wizardp(me)) value = 0;
        set_temp("contract/luban/value", value, me);

        quest_info(me);
        return 1;
}

// 判斷用户輸入的房屋名是否合法
// 同時判斷該處是否已經有住房
private int check_legal_name(string name, string position)
{
        object ob;

        if ((strlen(name) < 4) || (strlen(name) > 12 )) {
                write("對不起，你房屋的名字必須是 2 到 6 箇中文字。\n");
                return 0;
        }

        if (!is_chinese(name))
        {
                write("對不起，請您用「中文」為房屋取名字。\n");
                return 0;
        }

        ob = get_object(position);
        if (! objectp(ob)) return 1;

        if (ob->query_room_name(name))
        {
                luban_say("對不起，據我所知，那裏已經有一個住房叫這個"
                          "名字了！請另外起一個名字。\n");
                return 0;
        }

        return 1;
}

// 判斷用户輸入的房屋代號是否合法
private int check_legal_id(string roomid, string position)
{
        object ob;
        int i;

        i = strlen(roomid);

        if( (strlen(roomid) < 3) || (strlen(roomid) > 10 ) ) {
                write("對不起，你房屋的代號必須是 3 到 10 個英文字母。\n");
                return 0;
        }
        while(i--)
        {
                if(((roomid[i] < 'A') || (roomid[i] > 'Z')) &&
                   ((roomid[i] < 'a') || (roomid[i] > 'z')))
                {
                        write("對不起，你房屋的代號必須用英文字母。\n");
                        return 0;
                }
        }

        if (member_array(roomid, ban_room_id) != -1)
        {
                command("shake");
                luban_say("不要起這種名字！免得人家誤會。\n");
                return 0;
        }

        ob = get_object(position);
        if (! objectp(ob)) return 1;

        if (ob->query_room_id(roomid))
        {
                luban_say("對不起，據我所知，那裏已經有一個住房使用了"
                          "這個英文代號了，請另選一個。\n");
                return 0;
        }

        return 1;
}

// 判斷用户輸入的房屋類型是否存在
// 如果存在則返回那個房屋類型對應的mapping的指針
private mixed check_legal_type(string type)
{
        int i;
        for (i = 0; i < sizeof(room_example); i++)
        {
                if (room_example[i]["type"] == type ||
                    room_example[i]["name"] == type )
                return room_example[i];
        }
        return;
}

// 獲得一個房屋對象
private object get_object(string file_name)
{
        object ob;

        if (! file_name || file_name == "")
                return 0;

        if (! (ob = find_object(file_name)))
                ob = load_object(file_name);

        return ob;
}

// 記錄用户描述某一間房間的信息
private int record_desc(object me, string room_name, string desc)
{
        mapping filesp;
        mapping descsp;

        int i;
        object ob;
        string *names;

        if (! (desc = obey_description(desc))) return 0;

        filesp=query_temp("contract/luban/room/files", me);
        descsp=query_temp("contract/luban/descs", me);

        names = keys(filesp);
        for (i = 0; i < sizeof(names); i++)
        {
                // 查找該房屋的object
                ob = get_object(filesp[names[i]]);
                if( query("short", ob) == room_name || names[i] == room_name )
                {
                        // 查找用户輸入的描述信息
                        if (! desc || desc =="")
                        {
                                string msg;
                                msg="你沒有輸入描述"+query("short", ob)+"("+
                                      room_name + ")的信息，將使用系統缺省的描述信息。\n";
                                msg += CYN "缺省的描述信息如下：\n";
                                if( stringp(query("default_long", ob)) )
                                      msg+=sort_desc(me,query("default_long", ob));
                                else
                                      msg+=sort_desc(me,replace_string(query("long", ob),"\n",""));
                                msg += NOR;
                                write(msg);
                                map_delete(descsp, names[i]);
                        } else
                        {
                                descsp[names[i]] = desc;
                                write("你描述了"+query("short", ob)+
                                      "(" + room_name + ")。\n");
                        }
                        return 1;
                }
        }
        write("沒有找到" + room_name + "，請查證再輸入描述信息。\n");
        return 0;
}

// 保存用户輸入的建房信息
private void record_contract(object me)
{
        string id;
        mapping descp;

        id=query("id", me);
        if (! mapp(query("form"))) delete("form");

        set_form(id,"player",query("name", me));
        set_form(id,"name",query_temp("contract/luban/name", me));
        set_form(id,"id",query_temp("contract/luban/id", me));
        set_form(id,"room",query_temp("contract/luban/room/name", me));
        set_form(id,"type",query_temp("contract/luban/room/type", me));
        set_form(id,"position",query_temp("contract/luban/position", me));
        set_form(id,"value",query_temp("contract/luban/value", me));
        set_form(id, "time", time());
        /*
        set_form(id, "status", "申請");
        set_form(id, "wizard", "無");
        */
        set_form(id, "status", "同意");
        set_form(id, "wizard", "NITAN3");
        set_form(id, "memo", "無");

        descp=query_temp("contract/luban/descs", me);

        set_form(id, "descs", descp);
        save();
}

// 改變玩家描述某一間房間的信息
// 修改的數據是存放在form中的
private int modify_desc_in_form(string player_id, string room_name, string desc)
{
        mapping example;
        mapping filesp;
        mapping descsp;

        int i;
        object ob;
        string *names;

        if (! (desc = obey_description(desc))) return 0;

        if (! (example = check_legal_type(query_form(player_id, "type"))))
        {
                write("這種房屋的類型已經不存在了，所以沒有改變房屋的描述，請和巫師聯繫。\n");
                return 1;
        }

        filesp = example["files"];
        descsp = query_form(player_id, "descs");
        names = keys(filesp);

        for (i = 0; i < sizeof(names); i++)
        {
                // 查找該房屋的object
                ob = get_object(filesp[names[i]]);
                if( query("short", ob) == room_name || names[i] == room_name )
                {
                        // 查找用户輸入的描述信息
                        if (! desc || desc =="")
                        {
                                write("你沒有輸入描述" + room_name +
                                      "的信息，將使用系統缺省的描述信息。\n");
                                write("缺省的描述信息如下：\n" +
                                      stringp(query("default_long", ob))?
                                      sort_desc(player_id,query("default_long", ob)):
                                      sort_desc(player_id,replace_string(query("long", ob),"\n","")));
                                map_delete(descsp, names[i]);
                        } else
                        {
                                descsp[names[i]] = desc;
                                write("你重新描述了"+query("short", ob)+"。\n");
                        }
                        return 1;
                }
        }
        write("沒有找到" + room_name + "，所以沒有修改描述信息。請查證再修改描述信息。\n");
        return 0;
}

// 講一個描述的字符串正規化
private string obey_description(string desc)
{
        if (strlen(desc) > 420)
        {
                luban_say("你的描述也太長了吧...\n");
                return 0;
        }

        if (! desc || desc == "") return "";

        desc = replace_string(desc, "\"", "'");
        desc = replace_string(desc, "\\n", "\n");
        desc = replace_string(desc, "\t", "");
        desc = replace_string(desc, " ", "");

        desc = replace_string(desc, "$BLK$", BLK);
        desc = replace_string(desc, "$RED$", RED);
        desc = replace_string(desc, "$GRN$", GRN);
        desc = replace_string(desc, "$YEL$", YEL);
        desc = replace_string(desc, "$BLU$", BLU);
        desc = replace_string(desc, "$MAG$", MAG);
        desc = replace_string(desc, "$CYN$", CYN);
        desc = replace_string(desc, "$WHT$", WHT);
        desc = replace_string(desc, "$HIR$", HIR);
        desc = replace_string(desc, "$HIG$", HIG);
        desc = replace_string(desc, "$HIY$", HIY);
        desc = replace_string(desc, "$HIB$", HIB);
        desc = replace_string(desc, "$HIM$", HIM);
        desc = replace_string(desc, "$HIC$", HIC);
        desc = replace_string(desc, "$HIW$", HIW);
        desc = replace_string(desc, "$NOR$", NOR);

        desc = desc + NOR;

        return desc;
}

// 操作表單的命令幫助
private int do_help(string arg)
{
        if (! arg)
                return notify_fail("你要查詢什麼幫助信息？\n");

        switch (arg)
        {
        case "list":
                write(@WRITE
列出所有或者是部分玩家提交的表單。如果參數是all 或者沒有，就
將所有的表單列出；如果參數是apply， 就列出所有申請中的表單；
如果參數是agree， 就列出所有已經批准的表單；如果參數是reject
則列出所有已經被巫師拒絕的表單；參數old 將把所有長期沒有執行
的表單列出來。

命令規則：list all | apply | agree | reject | old
WRITE );
                return 1;

        case "type":
                write(@WRITE
顯示某個玩家提交表單中的具體描述信息，如果指明瞭房屋名稱，就
只顯示該玩家對於該房屋的描述。

命令規則：type 玩家ID [房屋名稱]
WRITE );
                return 1;

        case "agree":
                write(@WRITE
批准某個玩家提交的表單，批准以後玩家只需要繳納現金即可建房。

命令規則：agree 玩家ID
WRITE );
                return 1;

        case "reject":
                write(@WRITE
拒絕某個玩家提交的表單，可以在拒絕的時候説明原因，原因將紀錄
在表單中的備註中。

命令規則：reject 玩家ID [原因]
WRITE );
                return 1;

        case "delete":
                write(@WRITE
刪除某個玩家提交的表單，表單在申請的狀態不能被刪除，必須拒絕
或同意以後才可以刪除。這是為了避免玩家長期沒有處理自己提交的
表單而設置的命令。

命令規則：delete 玩家ID
WRITE );
                return 1;
        }
}

// 列出表單
// 巫師使用
private int do_list(string arg)
{
        if (! exist_form()) return 1;

        if (! arg || arg == "all" || arg == "全部" || arg == "所有")
        {
                show_all();
                return 1;
        }

        switch (arg) {
        case "apply":
        case "申請":
        case "new":
                show_apply();
                return 1;

        case "agree":
        case "同意":
        case "批准":
                show_agree();
                return 1;

        case "reject":
        case "否決":
        case "不批准":
        case "沒批准":
                show_reject();
                return 1;

        case "old":
        case "舊":
                show_old();
                return 1;
        }

        write("list的使用説明：\nlist all   : 顯示所有的表單。\nlist apply : 顯示申請的表單。\n" +
              "list agree : 顯示巫師已經批准的表單。\nlist reject : 顯示巫師已經否決的表單。\n" +
              "list old   : 顯示過期很久的表單。\n\n");
        return 1;
}

// 顯示錶單的詳細信息
// 格式：type player_id room_name 顯示該player描述的某間房屋
//   或：type player_id           顯示該player的所有描述
// 此時如果由其他玩家正在輸入，也可以察看
private int do_type(string arg)
{
        string player_id;
        string room_name;
        int a;

        if (! wizardp(this_player()) || wiz_level(this_player()) < WIZLEVEL)
        {
                write("你無權察看錶單中的描述信息！\n");
                return 1;
        }
        if (! arg)
        {
                write("usage: type player_id [room_name]\n");
                return 1;
        }

        if (sscanf(arg, "%s %s", player_id, room_name) != 2)
        {
                player_id = arg;
                room_name = "";
        }

        show_desc(player_id, room_name);
        return 1;
}

// 顯示一個申請的簡要説明
private void show_brief(string player_id)
{
        mapping form;
        string msg;
        string wizard;
        string memo;
        int i;

        form = query("form/" + player_id);
        if (! form || ! mapp(form)) return;

        // 申請者的代號 申請者姓名  申請時間    房  型  狀態  處 理 者  備   注
        // 12           .10        . 10        . 6      .4    .8         .16
        msg = sprintf("%-12s  %-10s  %-10s  %-6s",
                      player_id, form["player"],
                      ctime(form["time"])[0..9], form["room"]);

        // 現實表單的狀態
        switch (form["status"]) {
        case "申請" :
                msg += HIW;
                break;

        case "同意" :
                msg += HIY;
                break;

        case "拒絕" :
                msg += HIR;
                break;
        }
        msg += "  " + form["status"] + NOR + "  ";

        wizard = form["wizard"];
        memo = form["memo"];

        if (! stringp(wizard) || wizard == "無" || wizard == "")
                wizard = "--------";

        if (! stringp(memo) || memo == "無" || memo == "")
                memo = "------";

        msg += sprintf("%-8s  %s\n", wizard, memo);
        write(msg);
        return;
}

// 判斷表單是否存在，調用者是否有資格處理該表單
private int exist_form()
{
        if (! mapp(query("form")) || sizeof(query("form")) < 1)
        {
                write("現在魯班這裏並沒有任何表單需要處理。\n");
                return 0;
        }
        if (! wizardp(this_player()) || wiz_level(this_player()) < WIZLEVEL)
        {
                write("你無權處理表單。\n");
                return 0;
        }
        return 1;
}

// 批准表單
// 巫師使用
private int do_agree(string arg)
{
        object ob;
        if (! exist_form()) return 1;

        if (! arg || ! query("form/" + arg))
        {
                write("usage: agree playerid\n");
                return 1;
        }

        if (query("form/" + arg + "/status") == "同意")
        {
                write("此表單已經被批准了。\n");
                return 1;
        }
        set("form/" + arg + "/status", "同意");
        set("form/"+arg+"/wizard",query("name", this_player()));
        set("form/" + arg + "/memo", "無");
        write("你批准了" + query("form/" + arg + "/player") + "(" + arg + ")的申請。\n");
        save();

        if (objectp(ob = find_player(arg)) && ob != this_player())
                tell_object(ob, HIG + name() + "告訴你：你的表單已經被" +
                            this_player()->name() + "批准了，快來交錢吧。\n" + NOR);

        return 1;
}

// 拒絕表單
// 巫師使用
private int do_reject(string arg)
{
        object ob;
        string player;
        string memo;

        if (! exist_form()) return 1;

        if (! arg)
        {
                write("usage: reject player_id [because]\n");
                return 1;
        }

        if (sscanf(arg, "%s %s", player, memo) != 2)
        {
                player = arg;
                memo = "無";
        }

        if (! query("form/" + player))
                return notify_fail("你要操作誰的表單？\n");

        if (memo == "無")
        {
                write("你可以添加備註信息(reject player 備註信息)，説明拒絕的理由。\n");
        }

        set("form/" + player + "/status", "拒絕");
        set("form/"+player+"/wizard",query("name", this_player()));
        set("form/" + player + "/memo", memo);

        write("你已經拒絕了" + query("form/" + player + "/player") + "(" + player + ")的申請。\n");
        save();

        if (objectp(ob = find_player(arg)) && ob != this_player())
                tell_object(ob, HIG + name() + "告訴你：你的表單已經被" +
                            this_player()->name() + HIR "拒絕" NOR HIG
                            "了，快來看看吧。\n" + NOR);
        return 1;
}

// 刪除表單
// 巫師使用
private int do_delete(string arg)
{
        if (! exist_form()) return 1;

        if (! arg)
        {
                write("usage: delete player_id\n");
                return 1;
        }

        if (query("form/" + arg + "/status") == "申請")
        {
                return notify_fail("你不能刪除一個申請後還沒有處理的表單。\n");
        }

        write((string)query("form/" + arg + "/player") + "(" + arg +
              ")提交的表單被刪除了。\n");
        delete("form/" + arg);
        save();

        return 1;
}

// 顯示剛剛申請的表單
private void show_apply()
{
        show_brief_list("申請", HIW + "以下是玩家提交的申請的表單" + NOR);
}

// 顯示被批准的表單
private void show_agree()
{
        show_brief_list("同意", HIY + "以下是巫師已經批准申請的表單" + NOR);
}

// 顯示被拒絕的表單
private void show_reject()
{
        show_brief_list("拒絕", HIR + "以下是被巫師拒絕申請的表單" + NOR);
}

// 顯示被拒絕的表單
private void show_all()
{
        show_brief_list(0, HIG + "以下是所有的表單" + NOR);
}

// 顯示比較陳舊的表單 - 過了15天的表單
private void show_old()
{
        int i;
        int count;

        string *ids;

        if (! exist_form()) return;

        count = 0;
        ids = keys(query("form"));
        for (i = 0; i < sizeof(ids); i++)
        {
                if (query("form/" + ids[i] + "/time") - time() > 86400 * 15)
                {
                        // 超過15天的表單
                        if (! count)
                        {
                                write(HIC "以下是玩家提交了很久的表單：\n" + NOR);
                                write(YEL "────────────────────────────────────────\n" NOR);
                                show_brief_title();
                        }
                        count++;
                        show_brief(ids[i]);
                }
        }
        if (count)
        {
                write(YEL "────────────────────────────────────────\n" NOR);
                write("共有" + ((string) count) + "張比較陳舊的表單。\n");
        } else
                write("目前沒有陳舊的表單。\n");
}

// 顯示列表
// info是顯示的表單的類型 - info為空表示顯示所有表單
// msg是顯示的列表的名稱 - 如“這是巫師批准的表單”
private void show_brief_list(string info, string msg)
{
        int i;
        int count;

        string *ids;

        if (! exist_form()) return;

        count = 0;
        ids = keys(query("form"));
        for (i = 0; i < sizeof(ids); i++)
        {
                if (! info || query("form/" + ids[i] + "/status") == info)
                {
                        if (! count)
                        {
                                write(msg + "\n");
                                write(YEL "────────────────────────────────────────\n" NOR);
                                show_brief_title();
                        }
                        count++;
                        show_brief(ids[i]);
                }
        }
        if (count)
        {
                write(YEL "────────────────────────────────────────\n" NOR);
                write("共有" + ((string) count) + "張表單。\n");
        } else
                write("目前沒有任何符合要求的表單。\n");
}

// 顯示列表題頭
private void show_brief_title()
{
        write(WHT "申請者的代號  申請者姓名  申請的時間  房  型  狀態  處理巫師  備   注\n" NOR);
}

// 根據一個表單建造房屋
private void create_room(object me)
{
        mapping filesp;         // 建造的原型房的文件mapping
        mapping descsp;         // 玩家填寫的描述mapping

        string player_id;       // 建找房間的玩家的ID
        string room_type;       // 房屋類型
        string room_name;       // 房屋名字
        string room_id;         // 房屋ID
        string room_key;        // 房屋的鑰匙
        string room_owner;      // 房屋的主人
        string position;        // 建造房屋的地點(路徑名)
        string position_short;  // 建造房屋的地點的中文名字
        string outdoors;        // 房屋所在的區域
        string entry;           // 房屋的入口

        string *content;        // 源文件的內容
        string *names;          // filesp的關鍵字集合
        string filename;        // 生成的文件名稱
        string dstfile;         // 生成的文件內容

        string desc;            // 某間房屋的描述::鑰匙的描述
        object room;
        object ob;              // 房屋的object

        int i;
        int k;
        string ids;             // 快捷查詢字符串

        me = this_player();
        if (! objectp(me)) return;

        player_id=query("id", me);
        room_name=query("name", me);
        entry = "";

        if (! mapp(query("form/" + player_id)))
        {
                // 沒有找到玩家提交的表單
                return;
        }

        // 在表單中有該玩家提交的表單
        ids = "form/" + player_id + "/";
        room_type = query(ids + "type");
        for (i = 0; i < sizeof(room_example); i++)
        {
                if (room_example[i]["type"] == room_type)
                {
                        filesp = room_example[i]["files"];
                        break;
                }
        }

        if (! mapp(filesp))
        {
                write("你申請的房屋類型(" + room_type + ")已經不存在了"
                      "，請和巫師聯繫。\n");
                return;
        }

        descsp = query(ids + "descs");
        room_type = query(ids + "room");
        room_name = query(ids + "name");
        room_id = query(ids + "id");
        room_owner = query(ids + "player");
        position = query(ids + "position");
        names = keys(filesp);

        room_key = "1 of " + player_id;

        ob = get_object(position);
        if (! objectp(ob))
        {
                write ("你建房的地點已經不存在了，請和巫師聯繫！\n");
                return ;
        }
        position_short=query("short", ob);
        if( !(outdoors=query("outdoors", ob)) )
                outdoors = "unknow";
        message("vision", HIY "魯班拍拍手，説道：弟子們，生意來了！賺金子"
                              "銀子的時候到了！！！\n" NOR +
                          YEL "霎時天昏地暗，你只覺得眼前模模糊糊，什麼也"
                              "看不清楚，渾然不知道發生了什麼事情。\n" NOR,
                          environment());

        // 讀入並處理所有的文件
        for (i = 0; i < sizeof(names); i++)
        {
                // long_flag 是為了將原型房文件中出現在@LONG和LONG之間的字符串去掉而使用的標誌。
                int long_flag;

                // enter_receive 是為了消除過多的空行使用的
                int enter_receive;

                if (file_size(filesp[names[i]]) <= 0)
                {
                        write("缺少文件:" + filesp[names[i]] +
                              "，不能生成房屋，請和巫師聯繫。\n");
                        // 刪除已經產生的文件
                        for (k = i - 1; k >= 0; k--)
                                rm(to_player(player_id, filesp[names[k]]));
                        return;
                }
                content = explode(read_file(filesp[names[i]]), "\n");
                long_flag = 0;
                enter_receive = 0;
                filename = to_player(player_id, filesp[names[i]]);
                dstfile = "// File(" + to_player(player_id, filesp[names[i]]) + ")" +
                          " of " + player_id + "'s room\n// Create by LUBAN written by Doing Lu\n";
                for (k = 0; k < sizeof(content); k++)
                {
                        if (strsrch(content[k], "LONG") != -1)  // 查到了一個LONG標誌
                        {
                                long_flag = ! long_flag;
                                if (! long_flag)
                                {
                                        // 填充新的long描述
                                        desc = descsp[names[i]];
                                        if (! desc || desc == "")
                                        {
                                                // 採用了缺省描述
                                                ob = get_object(filesp[names[i]]);
                                                desc=query("default_long", ob);
                                               if (! desc) desc = replace_string(query("long",ob), "\n", "");
                                        }
                                        desc = replace_string(desc, "ROOM_POSITION", position_short);
                                        desc = sort_desc(me, desc);
                                        dstfile += "\tset (\"long\", @LONG\n" + desc + "LONG );\n";
                                }
                                continue;
                        }
                        // 如果是LONG描述則忽略
                        if (long_flag) continue;

                        // 如果該句包含有/**/則忽略
                        if (strsrch(content[k], "/**/") != -1) continue;
                        if (strsrch(content[k], "/* EXAMPLE */") != -1) continue;
                        if (strsrch(content[k], "/* example */") != -1) continue;

                        // 去除語句中的//**
                        content[k] = replace_string(content[k], "//**", "    ");

                        // 如果該句以//開頭，表示註釋，則忽略
                        if (content[k][0..1] == "//") continue;

                        // 判斷該文件是否是入口文件，即該文件是否有到建房處(position)的出口
                        if (strsrch(content[k], "/d/room/xiaoyuan") != -1)
                                entry = filename;

                        // 替換語句中的ROOM/KEY, OWNER, position
                        content[k] = replace_string(content[k], "ROOM_KEY", room_key);
                        content[k] = replace_string(content[k], "ROOM_OWNER_ID", player_id);
                        content[k] = replace_string(content[k], "ROOM_OWNER", room_owner);
                        content[k] = replace_string(content[k], "ROOM_NAME", room_name);
                        content[k] = replace_string(content[k], "ROOM_ID", room_id);
                        content[k] = replace_string(content[k], "ROOM_POSITION", position_short);
                        content[k] = replace_string(content[k], "OUTDOORS", outdoors);
                        content[k] = replace_string(content[k], "/d/room/xiaoyuan", position);

                        // 添加該語句
                        if (content[k] == "")
                                enter_receive ++;
                        else
                                enter_receive = 0;
                        if (enter_receive > 1) continue;

                        dstfile += content[k] + "\n";
                }
                if (long_flag)
                {
                        write("文件:" + filesp[names[i]] + "格式錯誤，"
                              "LONG不匹配，不能生成房屋，請和巫師聯繫。\n");
                        // 刪除已經產生的文件
                        for (k = i - 1; k >= 0; k--)
                                rm(to_player(player_id, filesp[names[k]]));
                        return;
                }

                // 寫入磁盤
                seteuid(getuid());
                rm(filename);
                assure_file(filename);
#if 0
                if (wiz_level(this_player()) >= WIZLEVEL)
                {
                        write(HIY "Try to write file:" + filename + "\n" NOR);
                        write(dstfile);
                        write(HIC "\nOk.\n" NOR);
                }
#endif
                // avoid the old object's data in dbase
                DBASE_D->clear_object(filename[0..<3]);
                write_file(filename, dstfile);
                VERSION_D->append_sn(filename);
                room = load_object(filename);
                DATABASE_D->db_create_item(room, room->save_dbase_data());

                dstfile = "";
        }

        // 在建房處添加入口到玩家的房屋
        if (! entry || entry == "")
        {
                message("vision", "\n過了一會，魯班和眾弟子踉踉蹌蹌的"
                                  "趕了回來。魯班苦着臉説：這是怪事，"
                                  "居然找不到入口！你去問問巫師究竟是"
                                  "怎麼搞的！\n", environment());
                // 刪除已經產生的文件
                for (k = i - 1; k >= 0; k--)
                        rm(to_player(player_id, filesp[names[k]]));
                return;
        }

        ob = get_object(position);
        if (! ob || ! ob->create_room(room_name, room_id, entry))
        {
                message("vision", "\n過了一會，魯班和眾弟子踉踉蹌蹌的"
                                  "趕了回來。\n魯班一臉黴樣，苦着臉説"
                                  "：真邪門了，居然沒有建成房子，\n奶"
                                  "奶的頭，我公輸班活了一千多年還是頭"
                                  "次遇到這種事！\n",
                                  environment());
                // 刪除已經產生的文件
                for (k = i - 1; k >= 0; k--)
                        rm(to_player(player_id, filesp[names[k]]));
                return;
        }
        
        message("vision", "\n須臾，魯班和眾弟子已然歸來。\n"
                          "魯班喜道：呵呵，房屋建好了，一切"
                          "順利，恭喜恭喜！\n", environment());
        DATABASE_D->db_remove_item(base_name(ob));
        DATABASE_D->db_create_item(ob, ob->save_dbase_data());
        ob->save();

        // 創建玩家房屋的鑰匙文件
        filename = file_dir(player_id) + "key.c";
        dstfile = "// File(" + filename + ")" +
                  " of " + player_id + "'s key\n// Create by LUBAN written by Doing Lu\n";
        dstfile += @KEY

#include <ansi.h>

inherit ITEM;

int query_autoload() { return 1; }

void create()
{
        set_name(YEL "KEY_NAME" NOR, ({ "key", "KEY_ID" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", @LONG
KEY_DESCRIPTION。
這是原配鑰匙。
LONG );
                set("unit", "把");
                set("no_pawn", 1);
                set("no_sell", 1);
                set("no_store", 1);
                set("item_make", 1);
                set("value", 1);
        }
}
KEY;
        // 替換鑰匙名稱，ID，描述
        desc = "一把用來開啟" + room_name + "(" + room_id + ")的鑰匙";
        dstfile = replace_string(dstfile, "KEY_DESCRIPTION", desc);
        dstfile=replace_string(dstfile,"KEY_NAME",query("name", me)+"家的鑰匙");
        dstfile = replace_string(dstfile, "KEY_ID", room_key);

        seteuid(getuid());
        rm(filename);
        assure_file(filename);
        write_file(filename, dstfile);
        VERSION_D->append_sn(filename);

        // 生成鑰匙
        ob = clone_object(filename);
        message_vision("魯班拿出一把鑰匙，對$N説：諾，這是鑰匙，收好了！"
                       "若是丟了可以到我這裏再配一把。\n", me);
        ob->move(this_object());
       command("give key to "+query("id", me));

        // 刪除魯班處紀錄的表單
        delete("form/" + player_id);
        save();

        // 設置玩家的數據庫
        set("private_room/build", 1, me);//已經建過房屋
        set("private_room/position", position, me);//房屋所在的位置
        set("private_room/entry", entry, me);//房屋入口處的文件路徑
        set("private_room/name", room_name, me);//房屋的名字
        set("private_room/id", room_id, me);//房屋的ID
        set("private_room/type", room_type, me);//房屋的類型
        set("private_room/key_no", 1, me);//使用原配鑰匙
        me->save();

        command("chat* heihei");
        return;
}

// 獲得玩家保存房屋文件的路徑名
private string file_dir(mixed me)
{
        string dir;

        dir =  DATA_DIR + "room/";
        if (objectp(me))
                dir+=query("id", me)+"/";
        else
        if (stringp(me))
                dir += me + "/";
        else
                return 0;

        return dir;
}

// 將原型房的文件名轉化成為用户房屋的文件名
private string to_player(string player_id, string file_name)
{
        string typestr;
        string retstr;

        sscanf(file_name, "/d/room/%s/%s", typestr, retstr);
        return file_dir(player_id) + retstr;
}

// 這是為了加快運行速度使用的宏函數
// 判斷首部的字符串是否相同(字符串1必須比字符串2長)
#define IS_HEAD(s1,s2)    (s1[i..i + strlen(s2) - 1] == s2)
// 判斷字符串首部是否為英文標點符號
#define IS_HEAD_ESIGH(s1) (s1[i] == '.' || s1[i] == '!' || s1[i] == ';' || s1[i] == ',' || s1[i] == ':')
// 判斷字符串首部是否為中文標點符號
#define IS_HEAD_CSIGH(s1) (s1[i..i + 1] == "。" || s1[i..i + 1] == "！" || s1[i..i + 1] == "；" || s1[i..i + 1] == "，" || s1[i..i + 1] == "：")
// 判斷字符串首部是否是中文字符
#define IS_HEAD_CHN(s1)   (s1[i] > 160)

// 規範描述信息
// 這個函數主要為講用户輸入的描述信息添加回車和跳格
private string sort_desc(mixed me, string desc)
{
        string res;
        string space;           // 段落前面的空格
        int curlen;             // res的當前行長
        int perline = 60;       // 最大行長(如果有標點符號，可能會超出)
        int crlen;              // 換行符的長度
        int escflag;            // 轉義序列的長度
        int colorflag;          // 本行是否有顏色
        int len;                // 字符串的長度
        int i;

        object pos;
        string player_id;
        string ids;
        string room_name;
        string room_owner;
        string position_short;

        space = "    ";
        res = "";               // 第一個段落前的不加空格
        curlen = strlen(space);
        colorflag = 0;

        crlen = strlen("\n");

        if (! desc || desc =="")
                return 0;

        if (stringp(me)) player_id = me; else
        if( objectp(me))player_id=query("id", me);else 
                         return 0;
        if (mapp(query("form/" + player_id)))
        {
                ids = "form/" + player_id + "/";
                room_name = query(ids + "name");
                room_owner = query(ids + "player");
                pos = get_object(query(ids + "position"));
                if (pos) position_short = pos->short(); else
                         position_short = "不知何處";
        } else
        if (objectp(me))
        {
                ids = "contract/luban/";
                room_name=query_temp(ids+"name", me);
                room_owner=query("name", me);
                pos=get_object(query_temp(ids+"position", me));
                if (pos) position_short = pos->short(); else
                         position_short = "不知何處";
        } else
                return 0;

        // 替換語句中的ROOM_OWNER, position
        desc = replace_string(desc, "ROOM_NAME", room_name);
        desc = replace_string(desc, "ROOM_OWNER", room_owner);
        desc = replace_string(desc, "ROOM_POSITION", position_short);

        i = 0;
        len = strlen(desc);
        desc += " ";            // 防止比較過程中溢出
        while (len > i)
        {
                // 添加字符
                // 判斷是否為漢字
                while (curlen < perline)
                {
                        if (IS_HEAD_CHN(desc))
                        {
                                res += desc[i..i+1];
                                i += 2;
                                curlen += 2;
                        } else
                        if (desc[i] >= 32)
                        {
                                res += desc[i..i];
                                i++;
                                curlen ++;
                        } else
                          break;
                }

                // 判斷下一個字符是否為標點，標點不能出現在行首
                if (IS_HEAD_CSIGH(desc) && curlen < perline + 2)
                {
                        res += desc[i..i+1];
                        i += 2;
                        curlen += 2;
                }

                if (IS_HEAD_ESIGH(desc) && curlen < perline + 2)
                {
                        res += desc[i..i];
                        i++;
                        curlen ++;
                }

                // 判斷是否為換行
                if (IS_HEAD(desc, "\n"))
                {
                        if (curlen) res += "\n";        // 避免剛剛有換行
                        res += space;
                        curlen = strlen(space);
                        i += crlen;
                        colorflag = 0;
                        continue;
                }

                // 掃描desc，查找轉義字符
                if (desc[i] == 27)
                {
                        escflag = 0;
                        colorflag = 1;
                        while (i + escflag < len && desc[i + escflag] != 'm')
                                escflag++;
                }

                if (escflag > 0)
                {
                        // 顏色不計長度
                        res += desc[i..i + escflag];
                        i += escflag + 1;
                }

                // 如果計滿一行，並且沒有遇到換行符號或者是轉義符號就
                // 就自動添加一個換行符
                if (curlen >= perline && ! IS_HEAD(desc, "\n") &&
                    desc[i] != 27)
                {
                        res += "\n";
                        curlen = 0;
                        colorflag = 0;
                }
        }

        if (curlen || colorflag) res += "\n";
        return res;
}
