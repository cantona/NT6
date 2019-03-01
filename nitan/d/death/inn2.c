#include <ansi.h>
inherit ROOM;
 
int do_stuff(object ob);
 
void create()
{
        set("short", HIB "【黑店】" NOR);
        set("long", HIB @LONG

                      黑                店  

    屋裡相當冷清，外面的濃霧還不時地從半開著的門縫飄進來，地面
上散著一些破舊的物品，不過光從外表已經無法分辨出那是些什麼東西
了。牆上(wall)刻著一些潦草的字體，牆角的一盞燈籠掙紮似地發出一
陣陣微弱的光芒，也始得那些字看來格外的詭異。


LONG NOR);
        set("exits", ([
                "west" : "/d/death/road1",
        ]) );

        set("objects", ([
                __DIR__"npc/ghost": 1,
        ]) );

        if (random(10) == 1)
                add("objects", ([ __DIR__"npc/wang2" : 1]));
        set("item_desc", ([
                "wall" : @WALL
幾行你勉強分辨得出來的字:
我被困在這裡了.... 我要回家啦!!!!!!!!!!!
                      ^^^^
                        靠自己啦...
什麼叫靠自己啊?!?!? 這裡連個活人都沒有...

看到你自己時問一下吧... 自己人都會互相幫忙的說.. 
                                    ^^^^
                                 你... 確... 定?!?!
喔.. 
WALL
        ]) );

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
        replace_program(ROOM);
}

