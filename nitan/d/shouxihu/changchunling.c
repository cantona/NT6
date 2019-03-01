// Room: /yangzhou/changchunling.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","長春嶺");
        set("long",@LONG
長春嶺因形似鎮江金山，俗稱小金山。當時為使乾隆帝能坐船直抵
平山堂，便開挖了蓮花埂新河，挖出泥土堆積而成小金山。此嶺四面環
水，嶺上遍植春梅、淡竹，香氣四溢，故曰"梅嶺春深"。李亞如撰聯雲：
“借取西湖一角堪夸其瘦，移來金山半點何惜乎小”。一對參天銀杏間
陳列一款原形似山水盆景的鐘乳石雲盆。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "northdown" : __DIR__"balongqiao",
                "southdown" : __DIR__"xiaohongqiao",
                "southeast" : __DIR__"qinshi1",
                "westdown"  : __DIR__"changchunqiao",
                "east"      : __DIR__"qishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 110);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}