// Room: /yangzhou/pingyuanlou.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","平遠樓");
        set("long",@LONG
平遠樓共三層，取宋代畫家郭熙《山水訓》“自近山而望遠山，謂
之平遠”之意，命名平遠樓。樓前庭院古木參天，花木繁多，湖石花台
正中植一株古瓊花。樓內中堂為“瓊花圖”，兩壁楹聯(lian)。樓前東
南隅有“印心石屋”碑一座。後門向北庭院內，湖石花壇盛栽牡丹，東
角叢植芭蕉，西牆披掛木香，卵石鋪地，庭院雖小，壺天自春。
LONG );
        set("item_desc", ([
                "lian" : "
        三級曩增高，兩點金焦，助起杯中吟興

        雙峯今聳秀，萬株鬆栝，湧來檻外濤聲
\n",
        ]));
        set("exits", ([
                "west"  : __DIR__"yongdao",
                "north" : __DIR__"qingkongge",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 160);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}