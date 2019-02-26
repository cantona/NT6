// Room: /d/yueyang/xiangfeici1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "湘妃祠");
        set("long", @LONG
湘妃祠座落在二妃墓的東北側，它東臨洞庭湖，遠映岳陽甑簞山，
後以蒼松翠柏為屏，小青瓦蓋面，素而古樸。白的院牆，青色的屋面，
與青山遙相呼應，白牆與藍天綠樹，相映和諧。大門上方由兩條龍捧着
“湘妃祠”的三個金色大字，門內便是湖廣總督張之洞撰寫的四百字的
天下第一聯。南面的紅牆上，為九嶷山圖，北面是煙波水浮的君山。詩
人孫宜題此：“悽悽湘君調，惋惋舜帝吟。載歌屈原詠，落日愁沾襟。”
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"xiaolu6",
                "north" : __DIR__"xiangfeici2",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2310);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}