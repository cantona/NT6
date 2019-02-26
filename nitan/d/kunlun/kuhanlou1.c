// Room: /d/kunlun/kuhanlou1.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "苦寒樓一層");
        set("long", @LONG
這裏是苦寒樓的底層。苦寒樓結構簡單，四周為濃密的雲杉包圍。
取名自“梅花香自苦寒來”之意，乃是崑崙派前輩為了激勵後進崑崙派
弟子而建的，往上看，長長的木樓梯盤繞而上，似乎永無盡頭。青磚地
相當潔淨，看來經常有人打掃。四面牆上的壁畫(bihua) 都是前輩們留
下武功圖譜。
LONG );
        set("item_desc",([
                "bihua" : "壁畫上人物的招式全是守禦招法，綿綿不絕，妙不可言，引得你凝神揣摩(chuaimo)。\n",
        ]));
        set("exits", ([
                "up"  : __DIR__"kuhanlou2",
                "out" : __DIR__"kuhanlou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -119980);
        set("coor/y", 40130);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "up")set_temp("count", 1, me);
        else addn_temp("count", -1, me);

        return ::valid_leave(me, dir);
}

int init()
{
        add_action("do_chuaimo","chuaimo");
}

int do_chuaimo(string arg)
{
        object me = this_player();
        if ( !living(this_player()) || arg != "parry" )
                return notify_fail("你要揣摩什麼武功？\n");
        if ((int)me->query_skill("parry", 1) > 40)
                return notify_fail("壁畫上所刻的武功你已全部領會了，不必再浪費時間了。\n");
        if ( me->query_skill("xuantian-wuji", 1)<30)
        {
                me->receive_damage("jing", 10);
                write("你本門內功實在太差，還是先休息一會吧！\n");
                return 1;
        }
        if( query("jing", me)<30 )
        {
                me->receive_damage("jing", 10);
                write("你的琢磨的腦袋都大了，還是先休息一會吧！\n");
                return 1;
        }
        me->receive_damage("jing", random(25));
        message_vision("$N正在揣摩壁畫上的武功。\n", me);
        write("你專心致志的揣摩壁畫上的招式，感覺基本招架又進了一步。\n");
        me->improve_skill("parry", me->query_int());
        return 1;
} 