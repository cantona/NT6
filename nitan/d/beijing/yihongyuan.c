inherit ROOM;

void create()
{
        set("short", "怡紅院");
        set("long", @LONG
你一走進來，一眼就看到大廳的牆上掛著一幅幅春宮圖，一下子
就明白了這是什麼地方。廳內到處張燈結彩，香氣撲鼻。幾名打扮得
妖裡妖氣的女人分站兩旁對你發出媚笑。一個老鴇婆連忙上前招呼客
人。從樓上傳來了陣陣打情罵俏的聲音。
LONG );
        set("exits", ([
                "west" : "/d/beijing/wang_8",
        ]));

        set("objects", ([
                "/d/beijing/npc/laobaopo" : 1,
                "/d/beijing/npc/piaoke" : 1,
                "/d/beijing/npc/jinv" : 2,
        ]));

	set("coor/x", -2760);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}