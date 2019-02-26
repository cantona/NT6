// Room: /d/kunlun/conglinggu.c 葱嶺谷
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "葱嶺谷");
        set("long",@long
你的眼前突然為之一亮，只見一條象被一刀劈開的峽谷巖石間，高
山的雪水瀉落到千丈以下的山澗裏去，濺起的密密的飛沫激起一種驚心
動魄的震憾。就在這深山野谷的溪流邊，卻長滿了各種各樣的花草樹木，
春天繁花開遍峽谷秋天果實壓滿山腰，人跡罕至，正是鳥獸們(bird)的
樂園。
long );
        set("item_desc",([
                "bird" : "各種珍奇異鳥,你不禁拿起了地上的石子,向他們投(tou)去。\n",
        ]));
        set("exits",([
                "out" : __DIR__"shanlin"+(random(5)+1),
        ]));
        set("objects", ([
                VEGETABLE_DIR"huangqi" : 1,
                VEGETABLE_DIR"dongchongcao" : 2,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119990);
        set("coor/y", 40130);
        set("coor/z", 90);
        setup();
}

int init()
{
        add_action("do_tou","tou");
}

int do_tou(string arg)
{
        object me = this_player();
        if ( !living(this_player()) || arg != "bird" )
                return notify_fail("你用石頭投擲誰？\n");
        if ((int)me->query_skill("throwing", 1) > 100)
                return notify_fail("你的暗器功夫已相當高了，對這種小兒科毫無興趣。\n");
        if( query("qi", me)<30 )
        {
                me->receive_damage("qi", 10);
                write("你的胳膊已經酸了,還是先休息一會吧！\n");
                return 1;
        }
        me->receive_damage("qi", random(25));
        message_vision("$N正在用石頭打鳥。\n", me);
        write("你專心致志的向鳥羣投擲石頭，感覺基本暗器又進了一步。\n");
        me->improve_skill("throwing", me->query_int());
        return 1;
} 