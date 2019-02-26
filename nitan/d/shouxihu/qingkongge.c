// Room: /yangzhou/qingkongge.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","晴空閣");
        set("long",@LONG
晴空閣本名“真賞樓”，取歐陽修“遙知為我留真賞”句義。後由
户部員外郎孔尚任改題“晴空閣”，取歐陽修“平山欄檻倚晴空”句。
閣前有一小院落，兩側有廊，院中有四株古松柏，兩廊枋上懸木魚和雲
板。廊中闢有一門，上懸“方丈”匾額。院北為四鬆草堂。
LONG );
        set("exits", ([
                "west"  : __DIR__"daxiongbaodian",
                "south" : __DIR__"pingyuanlou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 170);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}