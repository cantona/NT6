// Room: /d/yanziwu/shiwu.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "石屋");
        set("long", @LONG
這間石屋是蔓陀山莊的花肥房，屋裏一個弓腰曲背的老婆子手中拿
着一柄雪亮的長刀，她容貌醜陋，目光中盡是煞氣，兩根尖尖的犬齒露
了出來，便似要咬人一口，登覺説不出的噁心難受，身旁一鍋沸水，煮
得直冒水氣。
LONG );
        set("exits", ([
                "west"   : __DIR__"path6",
        ]));
        set("objects", ([
                __DIR__"npc/yan" : 1,
        ]));
        set("coor/x", 1260);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}