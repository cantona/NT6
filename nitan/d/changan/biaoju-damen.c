inherit ROOM;
void create()
{
        set("short", "河洛鏢局");
        set("long", @LONG
一座建構宏偉的宅第之前，左右兩座石壇中各豎一根兩丈來高的
旗桿，旗桿頂飄揚青旗。右首旗上黃色絲線繡著一頭張牙舞爪、神態
威猛的金龍，旗子隨風招展，顯得金龍更奕奕若生。左首旗上繡著「
河洛鏢局」四個黑字，銀鉤鐵劃，剛勁非凡。進門處兩排長凳，分坐
著八名身著勁裝的漢子，個個腰板筆挺，顯出一股英悍之氣。
LONG );
        set("exits", ([
                "north" : "/d/changan/qixiang5",
                "south" : "/d/changan/biaoju-dayuan",
        ]));
        set("objects", ([
                "/d/changan/npc/biaoshi" : 1,
                "/d/changan/npc/tang" : 2,
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
}