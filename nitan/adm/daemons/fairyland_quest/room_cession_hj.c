//                標準描述長度示例                                   |
// 自由轉讓 幻境遊戲內 EXP POT 的房間
// by naihe  2002-11-09  于茂名

#include <ansi.h>
inherit ROOM;
#include "temp/ctime_format_func.h"

#include "z_hj_log_func.h"
// 此文件中定義了LOG文件的文件名：HJ1_LOG_FILE
// 以及 hj_log_file(string log_msg) 函數。
// 本文件及 遊戲出口處 都使用 hj_log_file() 函數，而不直接使用 log_file() .

void create()
{
    set("short", "幻境遊戲獎品轉讓處");
    set("long", "
    幻境遊戲是一個沒有EXP、沒有SKILLS要求的遊戲，人人可玩，
並且效果一樣。更重要的是，它允許你在自己的主ID練功時，使用
一個別的ID（甚至是新注冊的ID）來進行遊戲，並且：

       "HIR"遊戲得到的經驗值、潛能值允許轉讓給登記的ID"NOR"

    將兩個ID都登記一次，即可相互轉讓在遊戲裡得到的 EXP/POT 。
    "HIG"<dengji 人物ID>"NOR"   登記你的相互ID(主ID及大米各登記一次)
    "HIG"<checkme>"NOR"         查詢自己的未轉出的 EXP/POT 情況
    "HIG"<take exp / pot 點數>"NOR"  把 EXP/POT 兌現
    "HIG"<zhuan exp / pot 點數>"NOR" 把 EXP/POT 轉給登記ID並同時兌現

    更詳細的說明，請輸入<help here> 指令。\n\n");
    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("valid_startroom", 1);

    set("exits", ([
        "down":__DIR__"room_door_hj",
        ]));

    setup();
}

void init()
{
    add_action("do_zhuan","zhuan");
    add_action("do_take", "take");
    add_action("do_checkme","checkme");
    add_action("do_dengji","dengji");
    add_action("do_help","help");
}

int do_help(string arg)
{
    string msg;
    if(!arg || arg!="here") return 0;

    msg = "###########  幻境遊戲登記ID詳細說明 #############
    為了防止出現“眾多大米造就一個獲益ID”的情況，
故實行“相互登記”的規則。在這裡，你只需要把任何
兩個ID都登記上對方的ID，就可以完成登記手續，而在
接下來的任何時候，無論你用哪一個ID進行遊戲，它所
得到的經驗值和潛能值，都可以轉讓給另一個ID。舉例：

    我希望能夠把這兩個ID的得益相互轉讓：
    \"naihe\" ----> 主ID  \"money\" ----> 大米ID\n";

    msg += "
    那麼，我先用\"naihe\"輸入指令：<dengji money>，
再用\"money\"輸入指令：<dengji naihe>，即可完成。
完成以後，在日後進行遊戲時，無論是\"naihe\"還是
\"money\"所得到的經驗、潛能獎勵，都可以在相互之間
隨意轉讓了。

    祝遊戲愉快！
                           by naihe 2003-10-22
#################################################\n";

    this_player()->start_more( msg );
    return 1;
}

int do_dengji(string arg)
{
    object me = this_player();

    if( query("huanjing2003/together_id", me) )
        return notify_fail("你已經登記過你的相互ID了，請輸入 <checkme> 指令查看。\n如需更改，請以 <mto> 指令發送信件，聯系巫師奈何(naihe)。\n");
    if(!arg) return notify_fail("你還未登記你的相互ID，請輸入一個ID。請注意，登記後，你不能再次更改這個ID。\n如有不明白之處，請輸入 <help here> 查詢。\n");
    if( arg == query("id", me))return notify_fail("不必登記自己，可直接轉讓。\n");

    set("huanjing2003/together_id", arg, me);

    write("登記成功！如果 \""+arg+"\" 未登記你的這個ID，請登記它，否則無法相互轉讓。\n");
    return 1;
}

int do_take( string arg )
{
    object me = this_player();
    int amount;
    string type;

    if(!arg) return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

/*
    if( sscanf(arg, "exp %d", amount) )
        type = "exp";
    if( type != "exp" && sscanf(arg, "pot %d", amount) )
        type = "pot";
*/
     if( sscanf(arg, "%s %d", type, amount) != 2 )
         return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

    if( type != "exp" && type != "pot" )
        return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

    if( amount<1 || !query("huanjing2003/"+type, me )
       || query("huanjing2003/"+type, me)<amount )
        return notify_fail("你沒有足夠的 "+type+" 可以兌現或數值不正確。請輸入<checkme>查詢。\n");

    if( type == "exp" )
    {
        if( amount < 1000 )
            return notify_fail("EXP 兌現，每次至少 1000 點。\n");
        addn("huanjing2003/exp", -amount, me);
        addn("combat_exp", amount, me);
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(me)) 
                addn("combat_exp", amount, me);
#endif
    }
    if( type == "pot" )
    {
        if( amount < 500 )
            return notify_fail("POT 的兌現，每次至少 500 點。\n");
        addn("huanjing2003/pot", -amount, me);
        addn("potential", amount, me);
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(me)) 
                addn("potential", amount, me);
#endif
    }


    message_vision( sprintf("$N將 %d 點幻境遊戲獎勵的 %s 兌現成了MUD裡的 %s 。\n", amount, type, type), me );

    hj_log_file( sprintf("\n%s(%s)兌現了 %d 點幻境 %s 。(%s)\n",
        query("name", me),getuid(me),amount,type,ctime_format()));
    return 1;
}


int do_zhuan(string arg)
{
    object me=this_player(),target;
    int amount;
    string target_id, type = ".";

    // 無論格式正確與否，先給提示。
    target_id=query("huanjing2003/together_id", me);
    if( !target_id ) return notify_fail("你並未登記你的相互ID！\n");

    target = find_player( target_id );
    if( !target )
        return notify_fail("你所登記的ID \""+target_id+"\" 並不在線，不能轉讓。\n");
    if( query("huanjing2003/together_id", target) != getuid(me) )
        return notify_fail("你所登記的ID \""+target_id+"\" ，對方並沒有登記你的ID，不能轉讓。\n");

    // ok.
    if(!arg) return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

/*
    if( sscanf(arg, "exp %d", amount) )
        type = "exp";
    if( type != "exp" && sscanf(arg, "pot %d", amount) )
        type = "pot";
*/
     if( sscanf(arg, "%s %d", type, amount) != 2 )
         return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

    if( type != "exp" && type != "pot" )
        return notify_fail("指令的正確格式請輸入 <look> 查看。\n");

    if( amount<1 || !query("huanjing2003/"+type, me )
       || query("huanjing2003/"+type, me)<amount )
        return notify_fail("你沒有足夠的 "+type+" 可以轉讓或數值不正確。請輸入<checkme>查詢。\n");

    if( type == "exp" )
    {
        if( amount < 1000 )
            return notify_fail("EXP 的轉讓每次至少 1000 點。\n");
        addn("huanjing2003/exp", -amount, me);
        addn("combat_exp", amount, target);
#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(me) && MEMBER_D->is_double_reward(target)) 
                addn("combat_exp", amount, target);
#endif
    }
    if( type == "pot" )
    {
        if( amount < 500 )
            return notify_fail("POT 的轉讓每次至少 500 點。\n");
        addn("huanjing2003/pot", -amount, me);
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(me) && MEMBER_D->is_double_reward(target)) 
                addn("potential", amount, target);
#endif
        addn("potential", amount, target);
    }

    message_vision( sprintf("$N將 %d 點幻境遊戲獎勵的 %s 轉給了$n。\n",amount,type ),
        me, target );

    hj_log_file( sprintf("\n%s(%s)轉讓 %d 點幻境 %s 予 %s(%s) 。(%s)\n",
        query("name", me),getuid(me),amount,type,
        query("name", target),getuid(target),ctime_format()));

    return 1;
}


int do_checkme()
{
    object me=this_player();

    if( query("huanjing2003/exp", me)>0 )
        write(HIY"你有"+query("huanjing2003/exp", me)+"點在本遊戲裡獲得的經驗值。\n"NOR);
    else write(HIY"你沒有在本遊戲裡獲得的經驗值。\n"NOR);

    if( query("huanjing2003/pot", me)>0 )
        write(HIY"你有"+query("huanjing2003/pot", me)+"點在本遊戲裡獲得的潛能值。\n"NOR);
    else write(HIY"你沒有在本遊戲裡獲得的潛能值。\n"NOR);

    write("你可以直接把它們兌換成你的經驗值或潛能值；或者把它們轉給你所登記的相互ID。\n");

    if( query("huanjing2003/together_id", me) )
        write("你登記的相互ID是：\""+query("huanjing2003/together_id", me)+"\"\n");
    else write("你還未登記相互ID，不能轉讓這些得分。需要轉讓時，請先登記。\n");

    return 1;
}
