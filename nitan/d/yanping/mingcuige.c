// Room: /d/yanping/mingcuige.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "明翠閣");
        set("long", @LONG
明翠閣始建于南宋，初為觀音閣。清康熙三十一年擴建，改稱明翠
閣。它攀附于鳳冠石的懸巖絕壁上，酷似空中樓閣，以險著稱。參差錯
落的木構建築群，“廊腰漫回，檐牙高啄”，隔岸遠觀，像是一條騰空
盤旋的蟠龍，隱現于巍峨的山巔上和薈蔚的林木中。古詩雲：“曲磴盤
空行，人語出林來”。閣內花紅柳綠，風光旖旎。清代詩人朱宏作詩讚
頌：“四面八方皆入畫，春花秋葉隔橋紅。”
LONG );
        set("exits", ([
                "down" : __DIR__"fengguanyan",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/shami" : 1,
        ]));
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}