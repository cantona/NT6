// Room: /binghuo/haitan.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "冰火島海灘");
        set("long", @LONG
這是一個極大的島嶼。島中心火柱周圍一片青綠，島嶼西部都是
尖石嶙峋的山峰，奇形怪樣，莫可名狀。這些山峰均是火山的熔漿千
萬年來堆積而成。島東卻是一片望不到盡頭的平野，乃火山灰逐年傾
入海中而成。該處雖然地近北極，但因火山萬年不滅，島上氣候便和
長白山、黑龍江一帶相似，高山處玄冰白雪，平野上卻極目青綠，蒼
鬆翠柏，高大異常，更有諸般奇花異樹，皆為中土所無。這島上既有
萬載玄冰，又有終古不滅的火窟，便被稱為冰火島。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "east"   : __DIR__"caodi1",
                "west"   : __DIR__"shulin1",
                "north"  : __DIR__"pingyuan1",
                "enter"  : __DIR__"southboat1",
        ]));
        setup();
}

void init()
{
        object me;
        me=this_player();
        set("startroom", base_name(environment(me)), me);
        return;
}