// Room: /yangzhou/siqiaoyanyu.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","四橋煙雨");
        set("long",@LONG
四橋煙雨樓位於瘦西湖東岸，與小金山隔湖相望，舊為鹽商黃履暹
別墅，為黃園的南半部分。乾隆南巡時賜名“趣園”。
    四橋煙雨樓面西，二層三楹，四面廊。登樓遠眺，虹橋、長春橋、
玉版橋、蓮花橋諸橋看似近在咫尺，卻橋橋造型各異，風格趣味全然不
同。若在細雨中登樓遠眺，諸橋同處雨霧之中，如蒙上一層輕紗，空朦
變幻，空濛變幻，可得四橋煙雨之意趣。乾隆每次遊湖，均要登四橋煙
雨樓憑窗眺望。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "west"  : __DIR__"chunboqiao",
                "south" : __DIR__"hepuxunfeng",
        ]));
        set("objects", ([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
        set("coor/x", 2);
        set("coor/y", 40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}