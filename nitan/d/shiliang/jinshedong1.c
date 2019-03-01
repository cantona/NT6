// Feb. 6, 1999 by Winder
#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_break(string arg);
int do_ba(string arg);
void create()
{
        set("short", "石室");
        set("long", @LONG
你來到另一間石室內，突然發現牆上有個劍柄。石壁(shibi)看
上去不是很結實。
LONG
        );
        set("exits", ([
                "west" : __DIR__"jinshedong",
        ]));
       set("item_desc",([
            "劍柄" : "這是一個很奇怪的劍柄，不知道有沒有劍身。你試著去拔它。\n",
            "shibi" : "也許你可以打開(break)它。\n",
             ]));
        set("jiancount",1);
        set("no_clean_up",0);
        set("coor/x", 1590);
        set("coor/y", -1980);
        set("coor/z", 10);
        setup();
}
void init()
{
    add_action("do_break", "break");
    add_action("do_ba", "ba");
}
int do_break(string arg)
{
    int n;
    n=query("neili", this_player());
    if( !arg || arg!="shibi" ) {
        write("你不是超人，怎麼亂來啊？\n");
        return 1;
    }
    message_vision(
    "$N走到石壁前，大吼一聲，一掌擊過去。\n", this_player());
        
    if (n>=1000) {
        message_vision(
        "$N只聽一聲巨響，$N把石壁震開一個大洞！\n", this_player());
        set("exits/north", __DIR__"shandao1");
        set("neili", n-1000, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else {
        message_vision(
        "$N大吼一聲“開！”，結果什麼也沒發生。看來$N的內力不夠強。\n", this_player());
        set("neili", 0, this_player());
    }
    return 1;
}
void close(object room)
{
    message("vision","石壁忽然間很神秘得合上了。\n", room);
    delete("exits/north", room);
}
int do_ba(string arg)
{        object jian;
         object me;
         me = this_player();
         if( !arg || arg=="" ) {
message_vision("你想拔什麼？\n", me);
return 1;
}
if( arg=="劍柄"||arg=="jian" ){
        if(query("jiancount") < 1)
        return notify_fail("你伸出手去拔那劍柄。不料卻撲了個空，看樣子劍已經被人取走了。\n");
        if( query("str", me)<28 )
        return notify_fail("你的臂力太小，使出吃奶的勁，劍柄依然紋絲不動。\n");
        if( query("neili", me)<2000 )
        return notify_fail("你的內力不夠了，拔不動劍柄。\n");
          jian = new("/clone/weapon/treasure/jinshe-jian");
        if (jian->volate_unique()) 
        {
                destruct(jian);
        return notify_fail("你伸出手去拔那劍柄。不料卻撲了個空，看樣子劍已經被人取走了。\n");
        }
        message_vision(
        HIW "$N凝神靜氣，默運玄功，神遊物外，一時間仿佛入定了。\n"+
            "突然間$N眼中精光大盛，提起全身的潛力，猛地拔向那劍\n"+
            "柄。剎那間，風雲為之變色，鬼神為之哭泣，只見一柄閃\n"+
            "著怪異碧色的蛇形長劍至石壁中飛將而出！！！\n"NOR, me);
        addn("neili", -2000, me);
        jian->move(me);
        addn("jiancount",-1);
        return 1;
        }else
        message_vision(
        "你望著石壁上的劍柄直發愣.....\n", me);
        return 1;             
}
void do_jian()
{
        set("jiancount",1);
}
int valid_leave(object me, string dir)
{
        tell_object(this_player(),WHT "冥冥間，虛空中有個聲音告訴你：此間有一不祥之物。 \n"+
                                      "此物一出，人神共怖，稀世寶物，世間獨一。\n"NOR,this_player());
        return 1;
}