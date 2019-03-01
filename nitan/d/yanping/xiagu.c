// Room: /d/yanping/xiagu.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "溪源峽谷");
        set("long", @LONG
溪源峽谷“原始風物天然美，神瀑幽谷甲東南”。此地之水，變化
多端。有猛浪若奔的激瀨，也有汨汨而淌的細流；有騰空飛寫的瀑布，
也有隨風飄洒的水簾；有沿崖淌落的巖流，也有潛入于巖的冷泉。十裡
溪山，山光水色，上下交映，猶如一幅天然水墨長卷。
LONG );
        set("exits", ([
                "northup"   : __DIR__"xiyuanan",
                "southeast" : __DIR__"youlang",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1420);
        set("coor/y", -6130);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}