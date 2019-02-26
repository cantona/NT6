// Room: /yangzhou/lianhuaqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","蓮花橋");
        set("long",@LONG
蓮花橋位於“水雲勝概”、“白塔晴雲”之間, 因橫跨瘦西湖蓮花
埂上，故名蓮花橋；又因橋上置五亭，故俗稱五亭橋。此橋為乾隆巡鹽
御史高恆所建，橋基平面分成十二個大小不同的橋墩，主軸線兩側有四
雙對稱的方形橋墩，構成橋的四個翼角。每個突出的翼角，其三面各有
一個券洞，寬近一丈，小舟可穿遊其間；中心券洞闊三丈，可通畫舫；
兩側橋堍是少見的半拱形券洞，正側共十五個券洞，互相通連，月滿時，
每洞各銜一月。
    圓的橋洞，方的石塊，弧形的橋背，方、圓之間搭配和諧。橋上用
二十八根紅柱支撐五亭，中亭高出，為重檐四角攢尖式；翼角四亭，單
檐翹角，角系風鈴。亭面皆覆黃色琉璃瓦，檐脊為綠色琉璃瓦，亭內彩
繪藻井，亭間有廊相連，圍以石欄，柱頭雕各式石獅。宛如一條錦帶束
在瘦西湖腰間，又似一朵盛開的蓮花浮於水面，
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "north" : __DIR__"shuiyun",
                "south" : __DIR__"pingtai4",
        ]));
        set("objects", ([
                "/d/city/npc/lady2" : 2,
        ]));
        set("coor/x", -10);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}