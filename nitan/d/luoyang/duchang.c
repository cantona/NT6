inherit ROOM;

void create()
{
        set("short", "長樂坊");
        set("long", @LONG
在大門上掛者一塊黑色的簾子，簾子上繡了個大大的“賭”字，原來
這裡是一個賭場，就開在路邊，好招搖呀！走進賭場，卻發現裡面的布置
如此繁華，熱鬧。金錢敲擊之聲不絕于耳，押注時的的吆喝聲充斥了每個
人的耳朵，古語曰“十賭九輸“，一旦踏進這裡就難以回頭了，不輸個傾
家盪產，妻離子散你是不知道後悔的，只有少數幾個贏家才是賭徒們羨慕
的對象和內心的希望。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad3",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 1,
                "/d/city/npc/liumang" : 2,
                "/d/beijing/npc/haoke1" : 2,
                "/d/beijing/npc/duke" : 3,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}