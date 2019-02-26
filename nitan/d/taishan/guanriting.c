// Room: /d/taishan/guanriting.c
// Last Modified by Winder on Aug. 25 2001

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "觀日亭");
        set("long", @LONG
玉皇廟東廂就是觀日亭。旭日東昇是泰山最迷人的奇觀。拂曉，天
晴氣朗，萬壑收暝，東方一線晨曦由灰暗變淡黃，又由淡黃變成橘紅。
繼而，天空雲朵赤紫交雜，瞬息萬變。滿天彩霞與地平線上的茫茫霧氣
連為一體，雲霞霧靄相映。赤輪乍啟，海面半吞半吐，欲上而止，跳蕩
恍惚，彷彿有二日捧出。待日輪掀開雲幕，冉冉升起，宛若飄蕩着的宮
燈。頃刻間，金光四射，羣峯盡染。
LONG );
        set("exits", ([
                "west" : __DIR__"yuhuang",
        ]));
        set("objects", ([
                "/d/village/npc/seller" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}