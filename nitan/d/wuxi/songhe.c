// Room: /d/wuxi/songhe.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "松鶴樓");
        set("long", @LONG
此乃江南四大名樓之一的松鶴樓，正中一塊金字招牌迎街而立，招
牌年深月久，被煙燻成一團漆黑，上面的三個金字卻依舊閃爍發光。陣
陣酒香肉氣從廚房中傳出。廚子刀杓聲和跑堂吆喝聲響成一片，樓下布
置簡易，顧客多是匆匆的行人，買點包子、雞腿、米酒就趕路去了。樓
上是雅座。
LONG );
        set("exits", ([
                "up"    : __DIR__"songhe2",
                "west"  : __DIR__"southroad1",
        ]));
        set("objects", ([
                        __DIR__"npc/xiaoer2" : 1,
        ]));
        set("coor/x", 1050);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}