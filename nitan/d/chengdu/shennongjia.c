//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "神農架");
        set ("long", @LONG
這是一片綿延不絕的山嶺，方圓幾千裏。相傳上古時神農氏曾在這
裏遍嘗百草，因千峯陡峭，須搭架採藥，故得“神農架”地名。這裏冷
杉、箭竹、香柏林立，古樹參天密佈，藥草遍地，野果滿綴，異獸時現。
層巒疊嶂中，可見山峯雲霧繚繞，似有積雪覆蓋。
LONG);
        set("outdoors", "jiangling");
        set("exits", ([
                "east" : __DIR__"longzhong",
                "south": __DIR__"shandao",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -15070);
	set("coor/y", -1810);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}