// Room: /d/suzhou/chitang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "池塘");
        set("long", @LONG
一池池水映入你的眼簾，小蓬萊翼然水中，曲折的石橋上架著紫籐
花棚。池東你可以看到曲溪樓、西樓、清風池等小築，掩映于花木山石
之間。池西的山腰間，桂樹叢生。秋日，置身于“聞木樨香軒”，陣陣
桂香，沁人心脾。軒下，水澗兩岸疊石重重，你不禁為此景而讚嘆不已。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"gumujiaohe",
        ]));
        set("objects", ([
                __DIR__"npc/lady1" : 1,
        ]));
	set("coor/x", 1070);
	set("coor/y", -1090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}