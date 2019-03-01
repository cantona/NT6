// Room: jiudian.c

inherit ROOM;
void create()
{
        set("short", "蓉城酒樓");
        set("long", @LONG
這是一座有着三開間門面的大酒樓，雖説不上雕樑畫棟，卻也氣
派不凡。正首門樑上掛着一幅黑漆匾，上寫着『蓉城酒樓』四個金漆
大字。樓中桌潔椅淨，座中客人衣飾豪奢，十九是富商大賈。這是一
家百年老店，傳到現在的這位掌櫃已經是第四代，據説和提督大人有
點不清楚，卻也保佑了這間酒樓的日進斗金。東南角有一道方梯通往
樓上雅座，往西南則可以出到東大街。
LONG );
        set("exits", ([
                "southwest" : __DIR__"eastroad1",
                "east" : __DIR__"chufang",
        ]));
        set("objects", ([
                __DIR__"npc/tanghua" : 1,
                __DIR__"npc/xiaoer2" : 1,
        ]) );
        set("coor/x", -15190);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}