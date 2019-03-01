//  Room:  /d/lanzhou/westgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "西門");
        set("long",  @LONG
這裡是蘭州西門。由于早年遭受進攻，因此城牆破損較為嚴重。再
往西北過黃河便是官府勢力以外的地方了，不少在中原犯了大案的盜匪
在這裡闖關西逃。守城的幾個官兵正在盤查過往行人。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"street3",
                "west" : "/d/xingxiu/xxroad1",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/wujiang": 1,
                "/d/city/npc/bing": 4,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15770);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}