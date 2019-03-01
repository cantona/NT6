#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_tiao(string arg);

void create()
{
        set("short", "水簾洞外");
        set("long", 
"水簾洞在紫蓋峰下，紫蓋峰之水經過山澗匯入紫蓋仙洞之\n中，深不可測，"
"水滿則溢，飛瀑(pubu)高二十余丈，數疊垂簾，\n飄泄而下，蔚為壯觀。"
"明張居正詩曰「" HIW "誤疑瀛海翻瓊波，莫擬\n銀河倒碧流，自是湘妃深隱處，"
"水晶簾掛五雲頭。" NOR "」以讚嘆這\n衡山大四絕之一的 水簾洞之奇 。\n"
);
        set("exits", ([ 
               "westdown"    : __DIR__"shanlu12",
               "northeast"   : __DIR__"shanlu15",        
        ]));

        set("no_clean_up", 0);

        set("outdoors", "henshan");

        set("item_desc",([
                "pubu" : HIG "\n只見瀑布飛瀉而下，氣勢磅礡，景致壯觀，下面卻"
                         "是萬丈深淵，\n一望無底，水蓮洞卻偏偏生瀑布之後。\n\n" NOR,
        ]));

	set("coor/x", -6870);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
}


void init()
{
        add_action("do_tiao", ({"tiao", "jump"}));
}

int do_tiao(string arg)
{
        string msg;
        object obj, me = this_player();
        int skill_dodge;

        skill_dodge = me->query_skill("dodge", 1);

        if (! obj = find_object(__DIR__"inhole")) 
                obj = load_object(__DIR__"inhole");
            
        if (! arg || (arg != "pubu" && arg != "瀑布"))
        {        
                write("你想往哪兒跳？\n");
                return 1;
        }        

        if (skill_dodge < 60)
        {        
                message_vision(HIC "\n$N" HIC "使勁向前一躍，眼見要到洞口，但$N"
                               HIC "感覺氣力已盡，身在半\n空卻被瀑布沖了下去。\n\n"
                               NOR, me);

                 tell_object(me, HIW "你迷迷糊糊地任湍急的水流將你沖走，身上"
                                "卻是一點力氣也使\n不出來。\n\n" NOR, me);

                me->move(__DIR__"heishatan");
                me->unconcious();     

                return 1;
        }

        if (skill_dodge < 140)
        {
                     message_vision(HIC "\n$N" HIC "奮力往前一跳，險些被瀑布打落，但有驚"
                               "無險，$N" HIC "終于落在洞口處，可樣子卻甚是狼狽。\n\n" 
                               NOR, me);
                me->move(obj);
                message("vision", HIW "\n" + me->name() + HIW "從瀑布外跳狼狽萬分地"
                                  "跳了進來。\n\n" NOR, obj, me);

                return 1;
        }

        msg = HIC "\n$N" HIC "提氣向前一縱，輕鬆地落在洞口處。\n\n" NOR;        
        message_vision(msg, me);
        me->move(obj);
        message("vision", HIW "\n" + me->name() + HIW "從瀑布外跳了進來。\n" NOR, 
                          obj, me);

               return 1;
}