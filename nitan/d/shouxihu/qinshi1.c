// Room: /yangzhou/qinshi1.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","琴室");
        set("long",@LONG
琴室面南三楹，臨湖而築，外嵌“琴室”石額。東側設小門通觀自
在亭。兩山開方窗，中懸包契常書“琴室”橫匾，外柱懸掛楹聯(lian)。
此室為遊客品茗佳處，東南檐角挑一“茶”字枋。
    室前栽有兩株百年古柏。此處臘梅為湖上一絕，霜降時綠葉未落即
暗香四溢，直至春節仍繁花朵朵，為臘梅珍品。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : "
        一        畫
        水        船
        回        來
        環        往
        楊        藕
        柳        花
        外        天
\n",
        ]));
        set("exits", ([
                "northwest"  : __DIR__"changchunling",
                "southeast"  : __DIR__"zizaiting",
                "north"      : __DIR__"qishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 20);
        set("coor/y", 100);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}