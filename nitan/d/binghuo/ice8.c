// Room: /binghuo/ice8.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", "冰山");
        set("long", @LONG
眼前銀光閃爍，大冰山在月光下發出青紫色的光芒，顯得又是奇
麗，又是可怖。你站在冰山之側的一塊棱角上，一眼望去，這座冰山
有陸地上一個小山丘大小，橫廣二十余丈，縱長八九丈，比原來的座
船寬敞得多了。遠近都是大大小小的冰山(ice)。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("item_desc", ([
                "ice" : "那是又一座冰山，好象相距不遠耶。何不跳過去看看？\n",
        ]));
        set("exits", ([
                "east"  : __FILE__,
                "west"  : __FILE__,
                "north" : __FILE__,
                "south" : __FILE__,
        ]));
        set("objects", ([
                __DIR__"npc/haibao" : random(2),
        ]));
        setup();
}

void init()
{
        add_action("do_jump", "jump");
        add_action("do_jump", "tiao");
}

int do_jump(string arg)
{
        object me = this_player();
        if ((!arg) || (arg != "east" && arg != "west" && arg != "south" && arg != "north"))
        {
                return notify_fail("東西南北都有冰山，你往哪跳？\n");
        }
        else
        {
                switch (random(5))
                {
                        case 0:
tell_object(me , BLU"冰山向北飄浮了。白天銀冰反射陽光，炙得人皮膚也焦了，眼
目更是紅腫發痛。\n" NOR) ;
                                break;
                        case 1:
tell_object(me , BLU"冰山向北飄浮了。說也奇怪，越是北行，白天越長，到後來每
天幾乎有十一個時辰是白日，黑夜卻是一晃即過。\n" NOR) ;
                                break;
                        case 2:
tell_object(me , BLU
"便在此時，眼前一"WHT"亮"BLU"，北方映出一片奇異莫可名狀的光彩，無
數奇麗絕倫的光色，在黑暗中忽伸忽縮，大片"YEL"橙黃"BLU"之中夾著絲
絲"MAG"淡紫"BLU"，忽而"MAG"紫色"BLU"癒深癒長，"MAG"紫色"BLU"之中，迸射出一條條"HIY"金光"BLU"、
"HIB"藍光"BLU"、"HIG"綠光"BLU"、"HIR"紅光"BLU"。\n" NOR) ;
                                break;
                        case 3:
tell_object(me , BLU"你眼望西天，血紅的夕陽仍未落入海面。原來地近北極，天時
大變，這些地方半年中白日不盡，另外半年卻是長夜漫漫，種
種怪異，宛若到了世界的盡頭。\n" NOR) ;
                                break;
                        case 4:
tell_object(me , BLU"忽見到正北方一縷黑煙沖天而起，你登時嚇得臉都白了，但黑
煙越來越高，到後來竟隱隱見煙中夾有火光。你顫聲道：“這
……這是地獄門！”\n" NOR) ;
                                break;
                }
                me->move(__DIR__"ice"+(random(9)+1));
                return 1;
        }
}
int valid_leave(object me, string dir)
{
        tell_object(me , 
"你在冰山上走來走去。\n" NOR) ;
        return ::valid_leave(me, dir);
}
