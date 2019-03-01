// Room: /d/shaolin/dzdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "地藏殿");
        set("long", @LONG
這是地藏殿。供奉地藏王菩薩。地藏王主宰陰間，手下自然有不
少鬼兵鬼卒，羅列帳前。菩薩眉橫煞氣，手斷陰陽。令人一見之下，
頓覺心驚膽戰，惶恐不已。
LONG );
        set("exits", ([
                "east" : __DIR__"guangchang5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
