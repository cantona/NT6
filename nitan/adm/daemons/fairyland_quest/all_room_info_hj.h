//                標準描述長度示例                                   |

void delete_exit();
void back_exit();
void add_exit();
void back_exit2();
void full_all( object me );

string the_exit;
string the_exit2;

#include    "npc_obj/hj_settings/room_amount_hj.h"


void create()
{
    set("room_mark",mark);
    set("short",MAG"幻境"NOR+GRN"·迷失之寶物隱匿之林"NOR);

    set("long","這裏是一片望不到邊的密林，氣息卻很是古怪。周圍的樹木都高大粗壯、枝
藤糾結，你見不到日月光亮，周圍也悄無聲息。腳下的土地上樹木的根鬚蔓延糾
纏，你好不容易才勉強踏得幾條小徑往四處通去。\n");

    set("no_fight", "1");
    set("no_magic", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

// 下面是對應的出口。

    set("exits",([
        "east":__DIR__"hj_room"+( mark +1),
        "west":__DIR__"hj_room"+( mark -1),
        "south":__DIR__"hj_room"+( mark +10),
        "north":__DIR__"hj_room"+( mark -10),
        "northeast":__DIR__"hj_room"+( mark -9),
        "northwest":__DIR__"hj_room"+( mark -11),
        "southeast":__DIR__"hj_room"+( mark +11),
        "southwest":__DIR__"hj_room"+( mark +9),
    ]));

    if( mark <= 10 ) // 方陣型房間，最上面一橫無 北向 方向
    {
        if(query("exits/north")) delete("exits/north");
        if(query("exits/northeast")) delete("exits/northeast");
        if(query("exits/northwest")) delete("exits/northwest");
    }

    if( (mark % 10) == 1 ) // 方陣型房間，最左邊一豎無 西向 方向
    {
        if(query("exits/west")) delete("exits/west");
        if(query("exits/southwest")) delete("exits/southwest");
        if(query("exits/northwest")) delete("exits/northwest");
    }

    if( (mark % 10) == 0 ) // 方陣型房間，最右邊一豎無 東向 方向
    {
        if(query("exits/east")) delete("exits/east");
        if(query("exits/southeast")) delete("exits/southeast");
        if(query("exits/northeast")) delete("exits/northeast");
    }

    if( mark >= (HJ_ROOM_AMOUNT - 9) ) // 方陣型房間，最下面一橫無 南向 方向
    {
        if(query("exits/south")) delete("exits/south");
        if(query("exits/southeast")) delete("exits/southeast");
        if(query("exits/southwest")) delete("exits/southwest");
    }

// 總共的房間數必須是整十數。

    set("all_exit","ok");


// 西北方即 1 號房間，有特殊文件支持
// 其餘各點如下：

// 第一橫最後一個房間加入支持鑄劍指令的NPC，即右上角（東北方）
    if( mark == 10 )
        set("objects", ([ __DIR__"npc_obj/hj_npc_zhujian" : 1 ]));

// 最後一橫第一個房間加入支持煉魔指令的NPC，即左下角（西南方）
    if( mark == HJ_ROOM_AMOUNT - 9 )
        set("objects", ([ __DIR__"npc_obj/hj_npc_lianmo" : 1 ]));

// 最後一個號碼的房間加入支持交易指令的 NPC，即右下角（東南方）
    if( mark == HJ_ROOM_AMOUNT )
        set("objects", ([ __DIR__"npc_obj/hj_npc_trader" : 1 ]));

    setup();
}


void init()
{
// 所有的共有動作(即 all_room_info_hj.h 及 1_room_info_special.h 共有)
#include "all_common_init.h"

    if( query("all_exit", this_object()) == "ok" )
    {
        if( !random(3) ) delete_exit();
        else if( !random(2) ) add_exit();
    }
}

// 所有的共有函數(即 all_room_info_hj.h 及 1_room_info_special.h 共有)
#include "all_common_func.h"


void delete_exit()
{
    string *the_exits;

    if( query("all_exit") != "ok" ) return;


    the_exits = ({    "east", "west", "north", "south",
        "northeast", "northwest", "southeast", "southwest", });

    the_exit = the_exits[ random(8) ];

    if( query("exits/"+ the_exit) )
        delete( "exits/" + the_exit );
    else the_exit = "none";

    if(the_exit != "none")
    {
        set("all_exit","be_delete");
        if(random(3) == 1) message("vision",HIB"你似乎看到幾棵樹木的位置移動了一下！……\n"NOR,this_object());
        remove_call_out("back_exit");
        call_out("back_exit",30+random(90));
    }
}

void back_exit()
{
    int temp;
    mapping the_marks;

    if( query("all_exit") == "ok" || query("all_exit") != "be_delete" )
        return;

    temp = mark;

    the_marks = ([
        "east"        : temp + 1,
        "west"        : temp - 1,
        "south"        : temp + 10,
        "north"        : temp - 10,
        "northeast"    : temp - 9,
        "northwest"    : temp - 11,
        "southeast"    : temp + 11,
        "southwest"    : temp + 9,
    ]);

    if( !undefinedp( the_marks[ the_exit ] ) )
        set( "exits/" + the_exit , __DIR__"hj_room" + the_marks[ the_exit ] );

    if(random(3) == 1) message("vision",HIB"你似乎看到幾棵樹木的位置移動了一下！……\n"NOR,this_object());
    set("all_exit","ok");
}

void add_exit()
{
    string temp_add_exit, *the_exits;

    if( query("all_exit") != "ok" ) return;

    the_exits = ({    "east", "west", "north", "south",
        "northeast", "northwest", "southeast", "southwest", });


    the_exit2 = the_exits[ random(8) ];
    temp_add_exit=__DIR__"hj_room"+(1+random( HJ_ROOM_AMOUNT ));

    if( !query("exits/"+ the_exit2) )
        set( "exits/"+ the_exit2, temp_add_exit );
    else the_exit2 = "none";

    if( the_exit2 != "none" )
    {
        set("all_exit","be_add");
        if(random(3) == 1) message("vision",HIB"你似乎看到幾棵樹木的位置移動了一下！……\n"NOR,this_object());
        remove_call_out("back_exit2");
        call_out("back_exit2",30+random(90));
    }
}

void back_exit2()
{
    if( query("all_exit") == "ok" || query("all_exit") != "be_add" )
        return;

    delete( "exits/" + the_exit2 );

    if(random(3) == 1) message("vision",HIB"你似乎看到幾棵樹木的位置移動了一下！……\n"NOR,this_object());
    set("all_exit","ok");
}
