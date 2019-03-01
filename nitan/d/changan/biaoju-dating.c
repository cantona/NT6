//Room: biaoju-dating.c

inherit ROOM;

void create()
{
        set("short", "河洛鏢局大廳");
        set("long", @LONG
廳堂中的陳設，全是十分精致的紫檀木家具，單是那扇巨大的八
摺屏風，上面鑲了各色寶玉，砌成極其生動的八仙圖，已是罕見的古
物。上首一虎皮交椅，上面坐著一個相貌威猛的漢子。
LONG );
        set("exits", ([
                "north" : "/d/changan/biaoju-dayuan",
        ]));
        set("objects", ([
                "/quest/job/wang" : 1,
                "/d/changan/npc/zong-biaotou" : 1,
        ]) );
        set("no_fight",1);

        set("coor/x", -10700);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}