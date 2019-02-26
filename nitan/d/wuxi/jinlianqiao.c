// Room: /d/wuxi/jinlianqiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "金蓮橋");
        set("long", @LONG
這是一座三孔石橋，每孔六塊石樑。橋台的兩端是八個橫帽雕有怪
魚頭和螭頭各四個。華版石上刻的“童子穿牡丹”圖栩栩如生。石欄杆
由蓮花狀望柱和透空欄板組成，還雕有荷葉淨瓶和枴杖。整座橋造型優
美勻稱，美侖美奐，樑溪河水從橋下潺潺流過，南北都是鬧市大街，橋
上人來人往。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"northroad2",
                "south" : __DIR__"northroad1",
        ]));
        set("objects", ([
                        "/d/city/npc/liumang" : 2,
        ]));
        set("coor/x", 1040);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}