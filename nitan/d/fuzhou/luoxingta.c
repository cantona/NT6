// Room: /d/fuzhou/luoxingta.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "羅星塔");
        set("long", @LONG
羅星塔矗立馬江畔。這裏是東方大港，相傳鄭和七下西洋，即在此
造舟鑄鐘，放洋西海的。西洋水手亦將此塔做為到達東方的認記。塔上
有銘文對聯“朝朝朝朝朝朝夕  長長長長長長消”。
LONG );
        set("exits", ([
                "northup" : __DIR__"gushan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -30);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}