// Room: /city/lichunyuan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "麗春院");
        set("long", @LONG
你一走進來，一眼就看到大廳的牆上掛着一幅幅春宮圖(tu)，一
下子就明白了這是什麼地方。廳內到處張燈結綵，香氣撲鼻。幾名打
扮得妖里妖氣的女人分站兩旁對你發出媚笑。主人韋春芳上上下下、
前前後後招呼着客人。從樓上傳來了陣陣打情罵俏的聲音。
LONG );
	set("objects", ([
                CLASS_D("gaibang") + "/kongkong" : 1,
                "/d/city/npc/wei" : 1,
                "/d/city/npc/mao18" : 1, 
	]));

	set("item_desc", ([
		"cannotsawtu" :
"                                      Ο        Ο          Ο             
                                    ┌│        │          │
      ┌—Ο┌—  —┬——Ο        │┤      ┌┘          └┐
    —┘Ο—┘    ————Ο  Ο——┘│  Ο—┼┴—  Ο——┴┼


   Ο       Ο    ΟΟΟ                 Ο                  ○
   │       │    │├┼       ┌—Ο  ┌┼                  │
   ├ Ο┬┐┤    ├└┼┐   —┘Ο——┘┤          ○┬—┐┤
   │   ┘└│    │  │                 └            │  ││
	\n"]));
	set("exits", ([
		"west"  : "/d/city/nandajie2",
		"up"    : "/d/city/lichunyuan2",
	]));

    set("no_fight", 1);
	set("coor/x", 10);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
    "/adm/npc/wei"->come_here(); 
}