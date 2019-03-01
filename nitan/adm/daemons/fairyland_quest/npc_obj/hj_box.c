//                標準描述長度示例                                   |
// “幻境”裡的寶箱
// by naihe  2002-10-23  于茂名

#include <ansi.h>

inherit ITEM;

#include "hj_settings/room_amount_hj.h"

string *color=({
    ""HIR"",
    ""HIW"",
    ""HIG"",
    ""HIC"",
    ""HIM"",
    ""HIB"",
    ""HIY"",
    ""HIY"",
});

void create()
{
    set_name( color[random(8)] +"寶箱"NOR, ({"box","bao xiang","xiang"}));

    set_weight(10000000);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "一個未曾開啟(open)的寶箱。\n");
        set("unit", "個");
        set("value", 0);
    }

    set("hj_game/obj","box");
    set("no_get","1");
    set("be_open","no");
    set("no_refresh",1); // 不會被房間更新。
    setup();
}

void init()
{
    add_action("do_open","open");
}

int do_open(string arg)
{
    string *obj_list=({
        "/clone/money/silver",
        __DIR__"hj_obj_quest",   // 神秘石類領悟技能的物品
        __DIR__"hj_obj_tools",   // 對本遊戲有幫助的物品（如定向水晶）
        __DIR__"hj_obj_weapon",  // 武器型的物品
        __DIR__"hj_obj_other",   // 果品、寶石等
        __DIR__"hj_obj_other",   // 果品、寶石類出現的幾率上調
    });

    object obj,me;
    int temp;
    string msg=""HIB"只見一陣煙霧冒起……這裡似乎多了一些什麼！"NOR"\n";

    me=this_player();
    temp=1+random(3); // 最多時打開一個箱子可獲得3個機會

    if(arg!="box" && arg!="bao xiang" && arg!="xiang")
        return 0;

    if(query("be_open") == "yes")
        return notify_fail("這個寶箱已被打開過了。\n");

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return notify_fail("你還忙著呢。\n");

    message_vision(CYN"$N"NOR+CYN"小心地把"+query("name")+NOR+CYN"打了開來。\n"NOR,me);
    me->start_busy(1);
    set("be_open","yes");
    set("long","這個寶箱已經被打開過了。\n");
    set_name(CYN"打開的寶箱"NOR,({"box","bao xiang","xiang"}));


    // 由寶箱抽出的物件統一描述。
    while( temp-- )
    {
    // 滾石之技唯一體現，打開寶箱時得到技能石的幾率提升
        if( query_temp("hj_special/xs", me) && !random(3) )
            obj = new( __DIR__"hj_obj_quest" );
        else obj=new( obj_list[random(sizeof(obj_list))] );
        obj->move(environment(this_object()));
        message_vision(msg,this_object());
    }

    call_out("delete_me",30+random(31));
    return 1;
}

void delete_me()
{
    message_vision("$N忽地消失不見了。\n",this_object());
    destruct(this_object());
}