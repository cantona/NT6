//                標準描述長度示例                                   |
// “幻境”尋寶系列主題之準備進入遊戲房間
// by naihe  2002-10-24

// 14:23 03-10-25 加入了一幅水晶的圖片
// PS： 這是自己畫的 HOHOHO



#include <ansi.h>
inherit ROOM;

#define        QXD_FILE    __DIR__"npc_obj/_qxd_"


void sing_song(int i);

string *context=({
    " ",   // 這個莫要刪了
    "親愛的勇士啊  既然你來到了這個地方",
    "就請聽我敘述我曾知道的故事",
    "讓我告訴你  那古老的傳說吧……",
    "相傳在遠古的時候",
    "大地上有著四個古老的國度",
    "他們是風、雨、雷、電之國度",
    "他們都有著自己的寶物",
    "用于維系自身  生活于各自的領土",
    "時光變遷  混亂出現",
    "他們之間爆發了戰爭",
    "不復停留在原本的家園",
    "他們之間的戰爭由寶物而起",
    "但最終卻都未能得到它們",
    "四個國家由此而消亡",
    "寶物們也四散消藏。",
    "親愛的勇士啊",
    "你是否願意尋求寶物",
    "來見識那古老國度的神秘光芒？",
    "來吧  踏出你選擇的步伐",
    "進入你將走向的未知之端。",
});

string singing="no";
string look_shuijing();

string pler1,pler2,pler3,pler4,id1,id2,id3,id4,
pler1="風翔",pler2="雨洒",pler3="雷鳴",pler4="電閃",
id1="aa",id2="bb",id3="cc",id4="dd";

int *pler_data1=({
    20+random(10),        // 悟性
    20+random(10),        // 膂力
    20+random(10),        // 根骨
    25+random(5),         // 身法
    1000+random(1000),    // 存款
});

int *pler_data2=({
    25+random(5),
    20+random(10),
    20+random(10),
    20+random(10),
    1000+random(1000),
});

int *pler_data3=({
    20+random(10),
    25+random(5),
    20+random(10),
    20+random(10),
    1000+random(1000),
});

int *pler_data4=({
    20+random(10),
    20+random(10),
    25+random(5),
    20+random(10),
    1000+random(1000),
});

void hjset_long()
{
    string cl = ({ HIC, HIG, HIM, HIW })[ random(4) ];

    set("long", cl + "
                        __   +
                     */____\\
                      \\    /  .
                    +  \\  /  
                      . \\/  *


  "NOR"這裡一片漆黑，你只見得面前空中懸浮著一塊"+cl+"水晶"NOR"(shuijing)。\n");
}

void create()
{
    set("short",BLU"虛空之境"NOR);
    hjset_long();

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_magic", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("item_desc",([
        "shuijing": (: look_shuijing :),
    ]));

    setup();
}

void init()
{
    if( !query_temp("hj2003-valid_enter", this_player()) )
    {
        call_out("get_out_here",1, this_player());
        return;
    }

    hjset_long();
    add_action("do_xuanze","xuanze");
    add_action("do_nocmds", ({ "scheme", "drop", "put", "set", "unset", }) );
}

int do_nocmds()
{
    write("這裡禁止使用這個指令。\n");
    return 1;
}

void get_out_here(object me)
{
    if( !me || !environment(me) || environment(me) != this_object() ) return;

    message_vision( HIR"一陣奇異震盪襲來，$N"HIR"還未及反應，已發現自己身處別處了。\n"NOR, me);
    me->move( __DIR__"room_door_hj" );
    message_vision("一陣莫名的震盪忽來忽逝，$N不知怎麼的就忽地出現在這裡了。\n",me);
}

void reset()
{
    ::reset(); 
    set("no_clean_up", 1); 
}

string look_shuijing()
{
    write("水晶散發著幽幽的光芒。");
    if( singing == "yes" || !query_temp("hj2003-valid_enter", this_player()) )
        return "\n";

    remove_call_out("sing_song");
    call_out("sing_song",1);
    return "\n";
}

void sing_song(int i)
{
    object me=this_player();

    singing="yes";
    if (i<sizeof(context))
    {
        if(i==0) message_vision(CYN"$N忽地聽到了一陣歌聲傳來，卻不知道來自何處。\n"NOR,me);
        else message("vision",MAG"      "+context[ i ] + "\n"NOR,this_object());
        i ++;
        remove_call_out("sing_song");
        call_out("sing_song",3,i);
    }
    else
    {
        singing="no";
        message("vision",CYN"歌聲漸弱，似是漸漸遠去般，終于聽不見聲息了。\n"NOR,this_object());
        message("vision","你將要選擇(xuanze)哪一個國度？ 例如：風之國度 <xuanze feng>\n"NOR,this_object());
    }
}

// 風 = 身法dex   雨 = 悟性int   雷 = 膂力str   電 = 根骨con
// 美麗 = 容貌per   善良 = 神shen(shen_type=-1為負神)   年紀 = 年齡age   富有 = 存款balance

int do_xuanze(string arg)
{
    object *all_mine,old_obj,qx_deng,me=this_player();
    int i,temp;
    mapping xuanze_arg;

    // 從正門走進來的才可以。
    if( !query_temp("hj2003-valid_enter", me) )
        return 0;
    if( !arg )
        arg = "@_@";
    xuanze_arg = ([
        "風" : "feng",
        "雨" : "yu",
        "雷" : "lei",
        "電" : "dian",
    ]);
    // 可以輸入中文進行選擇
    if( xuanze_arg[ arg ] )
        arg = xuanze_arg[ arg ];
    if( arg!="feng" && arg!="yu" && arg!="lei" && arg!="dian" )
        return notify_fail("你將要選擇(xuanze)哪一個國度？ 例如：風之國度 <xuanze feng>\n");
    delete_temp("hj2003-valid_enter", me);
    all_mine = deep_inventory(me); // 原來是  all，現在改為 deep ，BUG 哪裡逃
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( query("hj_game", all_mine[i]) )
            { destruct(all_mine[i]);temp++; }
        }
    }

    if(temp)
        write(HIR"你身上之前的"+chinese_number(temp)+"個幻境相關物品被清除掉了。\n"NOR);
    set_temp("huanjing", arg, me);
    qx_deng=new( QXD_FILE );

// ########  下面為 七星燈 設置遊戲內所需資訊。 ########


    set("my_master", me, qx_deng);

    set("hj_quest_info1/name", pler1, qx_deng);
    set("hj_quest_info1/int", pler_data1[0], qx_deng);
    set("hj_quest_info1/str", pler_data1[1], qx_deng);
    set("hj_quest_info1/con", pler_data1[2], qx_deng);
    set("hj_quest_info1/dex", pler_data1[3], qx_deng);
    set("hj_quest_info1/balance", pler_data1[4], qx_deng);

    set("hj_quest_info2/name", pler2, qx_deng);
    set("hj_quest_info2/int", pler_data2[0], qx_deng);
    set("hj_quest_info2/str", pler_data2[1], qx_deng);
    set("hj_quest_info2/con", pler_data2[2], qx_deng);
    set("hj_quest_info2/dex", pler_data2[3], qx_deng);
    set("hj_quest_info2/balance", pler_data2[4], qx_deng);

    set("hj_quest_info3/name", pler3, qx_deng);
    set("hj_quest_info3/int", pler_data3[0], qx_deng);
    set("hj_quest_info3/str", pler_data3[1], qx_deng);
    set("hj_quest_info3/con", pler_data3[2], qx_deng);
    set("hj_quest_info3/dex", pler_data3[3], qx_deng);
    set("hj_quest_info3/balance", pler_data3[4], qx_deng);

    set("hj_quest_info4/name", pler4, qx_deng);
    set("hj_quest_info4/int", pler_data4[0], qx_deng);
    set("hj_quest_info4/str", pler_data4[1], qx_deng);
    set("hj_quest_info4/con", pler_data4[2], qx_deng);
    set("hj_quest_info4/dex", pler_data4[3], qx_deng);
    set("hj_quest_info4/balance", pler_data4[4], qx_deng);

    if(arg == "feng")
        set("find_name", "風之國度", qx_deng);
    if(arg == "yu")
        set("find_name", "雨之國度", qx_deng);
    if(arg == "lei")
        set("find_name", "雷之國度", qx_deng);
    if(arg == "dian")
        set("find_name", "電之國度", qx_deng);
    set_temp("hj_game_find", arg, me);

// ############## 資訊更新 ###############

    if( query("id", me) != id1 && 
        query("id", me) != id2 && 
        query("id", me) != id3 && 
        query("id", me) != id4 )
    {
        pler1=pler2;
        pler2=pler3;
        pler3=pler4;
        pler4=query("name", me);

        id1=id2;
        id2=id3;
        id3=id4;
        id4=query("id", me);

        pler_data1=pler_data2;
        pler_data2=pler_data3;
        pler_data3=pler_data4;
        pler_data4=({
            query("int", me),
            query("str", me),
            query("con", me),
            query("dex", me),
            to_int(query("balance", me)),
        });
    }

    write("你得到一盞七星燈。\n");
    qx_deng->move(me);
    return 1;
}