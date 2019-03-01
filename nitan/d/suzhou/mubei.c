// Room: /d/suzhou/mubei.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "御書碑");
        set("long",@long
在山之西南麓，有南宋抗金名將韓世忠與樑紅玉等四位妻妾的合葬
墓。墓左豎巨碑，碑上篆刻著宋孝宗皇帝御書“中興佐命定國元勛之碑
”，碑文長達一萬三千多字，自古稱“天下第一碑”。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"shiyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1160);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}