//                標準描述長度示例                                   |
// 幻境內物品  迷題型（包括學習技能的類型）
// by naihe  2002-10-23  于茂名
// 本物件只作為學習技能型的物品使用。 21:42 02-10-28 by naihe
// naihe 05-9-7 9:15 v1.7 繼續調整。

#include <ansi.h>

inherit ITEM;

string *names=({
    HIW"呼風之石"NOR,
    MAG"喚雨之石"NOR,
    HIC"落雷之石"NOR,
    HIG"引電之石"NOR,
    YEL"滾石之石"NOR,
    RED"飛火之石"NOR,
    BLU"奪魂之石"NOR,
    CYN"復活之石"NOR,
    CYN"復活之石"NOR,  // 多一個機會獲得本物品
});

string *ids=({
    "hufeng shi",
    "huanyu shi",
    "luolei shi",
    "yindian shi",
    "gunshi shi",
    "feihuo shi",
    "duohun shi",
    "fuhuo shi",
    "fuhuo shi",
});

string *longs=({
    "這是一顆呼風之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆喚雨之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆落雷之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆引電之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆滾石之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆飛火之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆奪魂之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆復活之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
    "這是一顆復活之石，它似乎給你一種神秘的感覺。\n你不妨仔細領會(linghui)一下這種感覺。\n",
});

string *units=({
    "顆",
    "顆",
    "顆",
    "顆",
    "顆",
    "顆",
    "顆",
    "顆",
    "顆",
});

string *skills=({
    "hfzj",
    "hyzj",
    "llzj",
    "ydzj",
    "gszj",
    "fhzj",
    "dhzj",
    "heal",
    "heal",
});

string *skills_names=({
    "呼風之技",
    "喚雨之技",
    "落雷之技",
    "引電之技",
    "滾石之技",
    "飛火之技",
    "奪魂之技",
    "恢復之技",
    "恢復之技",
});

int *sks_damages=({   // 初學時能得到的 效力（等級）
    3+random(3),
    3+random(3),
    3+random(3),
    3+random(3),
    5,
    5,
    3,
    5+random(6),
    5+random(6),
});


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set( "iii", iii );
    set_name(names[ iii ], ({ids[ iii ],"shi"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", units[ iii ]);
    set("hj_game/obj","quest");

    set("value", 1);  // 該物件扔下後不會消失。
    set("use_times", 5 + random(4)); // 最大領會5-8次
    set("no_refresh",1); // 不會被房間更新。
}

void create()
{
    setme( 99 );
    setup();
}

void init()
{
    add_action("do_linghui", ({ "linghui", "lh"}) );
}

void delete_me()
{
    message_vision("$N靈氣已盡，「□」地一聲消失了。\n"NOR,this_object());
    destruct(this_object());
}

int do_linghui(string arg)
{
    object me,ob;
    string temp;
    int iii = query("iii"), lh_fail;

    if(query("delete_now")) return 0;

    ob=this_object();
    me=this_player();

    if( !environment(me) || !query("room_mark", environment(me)) )
        return 0;

    if( query("room_mark", environment(me)) == 1 )
        return notify_fail("這個地方不能領會技能。\n");
    if( !arg || (arg != query("id", ob) && arg != skills[iii] && arg != "shi") )
        return 0;

    if( !query_temp("huanjing", me) || query_temp("huanjing", me) != "start" || 
        !query_temp("hj_hp", me) || query_temp("hj_hp", me)<1 )
        return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return notify_fail("你還忙著呢。\n");

    if( query_temp("hj_hp", me)<50 )
        return notify_fail("你已經頭昏眼花了，還是先休息休息吧。\n");

    message_vision(CYN"$N"NOR+CYN"拿起$n"NOR+CYN"仔細端詳著，領會著它所帶來的神秘氣息。\n"NOR,me, ob);
    addn_temp("hj_hp", -(5+random(6)), me);

    lh_fail = random(3);  // 0, 1, 2.  0 時才是成功的
    // 雨之國度被動技能效果  領會神秘石的技能時，成功幾率上漲。
    // 失敗了的話，還有一次機會
    if( lh_fail && query_temp("hj_special/cm", me) )
        lh_fail = random(3);    // 0, 1, 2.  0 時才是成功的
    if( lh_fail )
        message_vision(CYN"$N"NOR+CYN"似乎十分疲憊，卻仍是無法抓住那種飄渺之感。\n"NOR,me);
    else
    {
        if( !query_temp("hj_game_skills/"+skills[iii], me )
           || !query_temp("hj_game_damages/"+skills[iii], me )
        )
            temp="new";
        else
            temp="up";
        if(temp == "new")
        {
            set_temp("hj_game_skills/"+skills[iii], skills_names[iii], me);
            set_temp("hj_game_damages/"+skills[iii], sks_damages[iii], me);
            message_vision(CYN"$N"NOR+CYN"只覺得突然之間似有神靈啟示，已領悟了「"+skills_names[ iii ]+"」！\n"NOR,me);
        }
        else
        {
            if( query_temp("hj_game_damages/"+skills[iii], me) >= 99 )
                message_vision(CYN"$N"NOR+CYN"只覺得心若冰清，看來早已把它全數領會了。\n"NOR,me);
            else
            {
                addn_temp("hj_game_damages/"+skills[iii], 1, me);
                message_vision(CYN"$N"NOR+CYN"只覺得突然之間心境大清，對「"+skills_names[ iii ]+"」的領會又進了一層！\n"NOR,me);
            }
        }
    }
    me->start_busy(1);      // 忙時下調了
    addn("use_times", -1);
    if( !random(2) || query("use_times") < 1 )
    {
        if( query("wait_delete") )
        {
            set("delete_now", 1);
            remove_call_out("delete_me");
            call_out("delete_me",1);
        }
        set("wait_delete",1);
    }
    return 1;
}