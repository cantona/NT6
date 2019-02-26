//                標準描述長度示例                                   |
// 幻境內物品  其他類型（包括補充HP的物品）
// by naihe  2002-10-25  於茂名

#include <ansi.h>

inherit ITEM;


string *names=({
    "無名果",
    "仙人果",
    "淘氣之果",
    "毒龍果",
    "野生果實",
    ""HIR"紅色寶石"NOR"",
    ""HIG"綠色寶石"NOR"",
    ""HIB"藍色寶石"NOR"",
    ""YEL"試煉之果"NOR"",
});

string *ids=({
    "wm guo",
    "xr guo",
    "tq guo",
    "dl guo",
    "ys guo",
    "red baoshi",
    "green baoshi",
    "blue baoshi",
    "sl guo",
});

string *heal_hps=({
    "yes",
    "yes",
    "yes",
    "yes",
    "yes",
    "no",
    "no",
    "no",
    "yes",
});

string *longs=({
    "這是一枚很小的不知名的果實，你可以把它吃下(chixia)。\n",
    "這是一枚小小的果子，名叫“仙人果”，相傳是仙人們吃了增加道行的東西。\n你可以把它吃下(chixia)。\n",
    "這枚果子怪模怪樣的，但卻有補血活氣的功效。你可以把它吃下(chixia)。\n",
    "這是一枚毒龍果，相傳是遠古毒龍曾用於療傷的果品。\n人類吃下(chixia)了可不知道會發生什麼事。\n",
    "這是一枚野生果實，在林子裏隨處可見。你可以把它吃下(chixia)。\n",
    "這是一顆紅色的寶石，散發着迷人的幽幽光芒。\n",
    "這是一顆綠色的寶石，散發着迷人的幽幽光芒。\n",
    "這是一顆藍色的寶石，散發着迷人的幽幽光芒。\n",
    "這是一枚“試煉之果”，似有特別神奇的功效。你可以把它吃下(chixia)試試看。\n",
});


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set("iii", iii );

    if( iii < 5 ||  iii == 8)
        set_name(names[ iii ], ({ids[ iii ],"guo"}));
    else set_name(names[ iii ], ({ids[ iii ] , "baoshi", "bao shi", "bs" }));

    set_weight(100);

    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("heal_hp",heal_hps[ iii ]);
    set("unit", "枚");
    set("value", 0);  // 該物扔下後將消失
    //set("no_refresh", 1); // 此類允許被MUD刷掉

    set("hj_game/obj","other");
}


void create()
{
    setme( 99 );
    setup();
}

void init()
{
    if( query("heal_hp") == "yes") add_action("do_chixia","chixia");
}

int do_chixia(string arg)
{
    object ob,me;
    int temp,temp1,temp_add;

    if( !query("room_mark", environment(this_player())) && !wizardp(this_player()) )
        return 0;

    me=this_player();
    ob=this_object();

    if( !arg || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return 0;

    if( !query_temp("hj_hp_max", me))return 0;
    if( !query_temp("hj_game_mepower", me))return 0;

    if( query("heal_hp") != "yes" || !arg || !id(arg) )
        return 0;
    //if(me->is_busy()) return notify_fail("你還忙着呢，小心吃了噎着。\n");
    // 不限制忙時，否則果品沒什麼大用處。

    if( query("id", ob) == "slguo" )
    {
        if( !random(3) )
        {
            if( random(3) )
            {
                message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，頓時覺得精神一振，似乎力量增強了一點！\n"NOR,me);
                addn_temp("hj_game_mepower", 1, me);
            }
            else
            {
                message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，頓時覺得精神一振，似有無窮內息湧湧而來！\n"NOR,me);
                addn_temp("hj_hp_max", 10+random(11), me);
            }
        }
        else
        {
            message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，但覺腹中絞痛，看來是吃下了有毒的東西！\n"NOR,me);
            addn_temp("hj_hp", -(20+random(31)), me);
        }

        destruct(ob);
        return 1;
    }

// 無論是否飽和都能吃，但最多也就加到 MAX HP 。
// 若是飽和狀態下吃，將會增加忙時！
// 否則無忙時。

    temp=query_temp("hj_hp", me);

    if( temp >= query_temp("hj_hp_max", me) )
    {
        me->start_busy(2);
        tell_object(me,"你吃得飽飽的，差點給噎住了。\n");
    }

    switch(query("id", ob) )
    {
        case "wm guo":temp_add=10+random(11);break;   //  10-20
        case "tq guo":if(random(2)) temp_add=1;  //  1 or 30
            else temp_add=30;break;
        case "xr guo":temp_add=30+random(21);break;   //  30-50
        case "dl guo":temp_add=100-random(150);break; //  -50  -  100
        case "ys guo":temp_add=10;break;              //  10
    }
    temp_add *= 3;  // 加強效力

    temp1 = 1 + temp_add + temp;

    if( temp1>query_temp("hj_hp_max", me) )
        temp1=query_temp("hj_hp_max", me);

    set_temp("hj_hp", temp1, me);
    if( temp_add>=0 )
    message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，頓時覺得精神一振。\n"NOR,me);
    else 
    message_vision(CYN"$N"NOR+CYN"吞下一"+query("unit", ob)+query("name", ob)+""NOR+CYN"，只覺得腹如絞痛，看來是吃下了有毒的東西！\n"NOR,me);

    destruct(ob);
    return 1;
}