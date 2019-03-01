// Room: /yangzhou/ershisiqiao.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","二十四橋");
        set("long",@LONG
二十四橋連接熙春台與望春樓東西兩岸，單孔玉帶臥波，長十丈，
橋面寬一丈，橋兩端踏步各二十四階，橋兩側圍以二十四根玉石欄桿和
二十四塊欄板，欄板雕雲月紋飾。橋頭接水處，以湖石堆疊成巧雲狀。
橋兩端採用錯位隱藏手法，使橋身若浮于水面，半圓形橋孔與水中倒影
合成一輪滿月。“兩堤花柳全依水，一路樓台直到山”。夜來佇立橋上，
可遠眺蜀岡，俯視湖面，望月聽簫。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "east" : __DIR__"wangchunlou",
                "west" : __DIR__"pingtai5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -40);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}