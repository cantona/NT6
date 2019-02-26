// Room:/d/changan/tulu2.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條黃土飛揚的路，不算太寬，南邊遠遠望過去可以看得到
巍峨的長安城牆，雖然這裏離長安並不遠，但是經常會受到北方的遊
牧民族的騷擾，因此人煙並不茂盛。
LONG );
        set("exits",  ([  /*  sizeof()  ==  2  */
                "northeast": "/d/changan/tulu2",
                "south"    : "/d/changan/bei-chengmen",
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}