// Room: /d/wuxi/chongansi.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "崇安寺");
        set("long", @LONG
這座江南古剎興修於東晉初年，歷經興衰，香火日漸旺盛。每逢六
月十九，寺中還召以為集，四方商賈鹹集，輦物來市，踵趾相接；再逢
元宵節，這裏還日放爆竹，夜燃煙火，十分熱鬧。不少得道高僧都相繼
來此主持，九方也在此形成共約，廟內不得打架鬥毆。向東是大殿。
LONG );
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        set("exits", ([
                "enter"  : __DIR__"chongandadian",
                "west"   : __DIR__"northroad1",
        ]));
        set("coor/x", 1050);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}