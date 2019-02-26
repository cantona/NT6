// Room: /d/suzhou/jianchi.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short","劍池");
        set("long",@LONG
劍池位於千人石的西南，池形狹長，如一柄平放之劍。池水終年不
乾枯。闔閭墓，均無所得，所鑿之處遂成深澗，呈劍形。門旁石壁上刻
“虎丘劍池”四個大字。劍池景緻幽深獨絕，池之兩旁，崖壁如削，藤
蘿垂掛，左壁刻大篆“劍池”兩字。
LONG);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"qianrenshi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1090);
	set("coor/y", -1050);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}