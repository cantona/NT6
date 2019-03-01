// Room: /d/taiwan/bengang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "笨港");
        set("long", @LONG
明朝天啟四年，“開台王”顏思齊率眾立寨入墾台灣，即擇苯港登
陸。思齊見島上地肥水美、大片荒野未辟，決意在此開疆拓土，幹一番
事業。乃率聚伐木辟土，構築寮寨。是時，土番以為外敵侵犯，聚族攻
擊。思齊遣人加以安撫，商定疆界，互不侵擾。笨港分南北，中隔一溪，
曰南街，曰北街，舟車輻輳，百貨駢闐，俗稱小台灣。民諺說「一府二
笨」，不是虛言。
LONG );
        set("exits", ([
                "east" : __DIR__"taiwanfu",
        ]));
        set("objects", ([
                __DIR__"npc/shangren": 2,
        ]));

        set("outdoors", "taiwan");
        set("coor/x", 2490);
        set("coor/y", -7010);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
