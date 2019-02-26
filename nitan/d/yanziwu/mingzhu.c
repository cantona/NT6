// Room: /d/yanziwu/mingzhu.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "明珠樓");
        set("long", @LONG
這裏是蔓陀山莊的主樓上房。樓建得非常富麗堂皇，飛檐琉瓦，畫
棟雕廊，還有一隻尺高的鸚鵡掛在欄下。樓名“明珠”，取自詩句“還
君明珠淚雙垂，恨不相逢未嫁時”。寄託着主人過去的一番情孽。不過
時間已經過去很久了，大家都不知道這個事情了知道的人也不敢在主人
面前提起了。
LONG );
        set("exits", ([
                "south"  : __DIR__"path11",
        ]));
        set("objects", ([
                __DIR__"npc/wangfuren" : 1,
        ]));
        set("coor/x", 1240);
        set("coor/y", -1210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}