// Room: /d/huangshan/lianhua.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "蓮花峰");
        set("long", @LONG
黃山第一高峰。它超然鶴立，群峰簇擁，象一多初綻蓮花，仰天怒
放，融雄偉俏麗于一體，是當之無愧的“菡萏金芙蓉”。峰上景色皆以
蓮花為名，如蓮花溝，蓮花梗等。每逢天氣晴朗，東望天目，西瞻匡廬，
北眺九華，南臨諸峰，視野極為開闊。北去便是後山。
LONG
        );
        set("exits", ([ 
                "south"     : __DIR__"yuping",
                "northdown" : __DIR__"guangming",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -1040);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}