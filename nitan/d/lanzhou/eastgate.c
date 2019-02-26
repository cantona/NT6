//  Room:  /d/lanzhou/eastgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "東門");
        set("long",  @LONG
這裏是蘭州東門。城外是一片茂密的樹林，不過最近那邊治安不太
好，因此幾個守門官兵將城門緊緊關閉了。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" : __DIR__"street1",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/bing": 4,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15730);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}