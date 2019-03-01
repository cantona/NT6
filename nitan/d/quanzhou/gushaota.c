// Room: /d/quanzhou/gushaota.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "姑嫂塔");
        set("long", @LONG
姑嫂塔又名「關鎖塔」，巍峨挺拔。登塔遠望，則「手摩霄漢千山
盡，眼入滄溟百島通」。相傳古時有一張姓男子，拋妻別妹，遠涉重洋，
不料海塗遇風，人舟盡沉。姑嫂倆登台遠眺，日復一日，積思成疾，雙
雙而亡。後人建造此塔紀念二人。同時此塔也是泉州港重要的導航塔。
西邊是安海港，北邊則是永寧港。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "west"  : __DIR__"anhaigang",
                "north" : __DIR__"yongninggang",
        ]));
        set("objects", ([
                __DIR__"npc/langren" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}