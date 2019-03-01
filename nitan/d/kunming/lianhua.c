#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蓮花峰");
        set("long", @LONG
你爬上蓮花峰，整個石林的風光盡收眼底，眼見北邊不遠
刻有一大字(zi)，峰壁上刻有一小詩 (shi)，向下觀望，只見
腳下一潭碧水盪漾。奇景迭出，險象環生，峰回路轉，異境天
開，常使人心動神馳，樂而忘返矣。
LONG);
        set("outdoors", "kunming");

        set("exits", ([                
                "southdown" : __DIR__"shilin2",
                "up" : __DIR__"wfting",
        ]));

        set("item_desc", ([
                     "zi" : WHT "\n         ※※※※ \n"
                             "         ※    ※ \n"
                             "         ※ 天 ※ \n"
                             "         ※    ※ \n"
                             "         ※ 下 ※ \n"
                             "         ※    ※ \n"
                             "         ※ 第 ※ \n"
                             "         ※    ※ \n"
                             "         ※ 一 ※ \n"
                             "         ※    ※ \n"
                             "         ※ 奇 ※ \n"
                             "         ※    ※ \n"
                             "         ※ 觀 ※ \n"
                             "         ※    ※ \n"
                             "         ※※※※ \n\n\n" NOR,

                     "shi" : HIR "\n\n\n            攀登直欲奪天工\n\n"
                             "            一頂凌雲挈眾峰\n\n"
                             "            不是猱升揮汗水\n\n"
                             "            何來雙手撫晴空\n\n\n" NOR,
                  ]));

        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
	set("coor/x", -16780);
	set("coor/y", -7200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}