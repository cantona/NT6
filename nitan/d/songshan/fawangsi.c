// Room: /d/songshan/fawangsi.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "法王寺");
        set("long", @LONG
法王寺在嵩山玉柱峯下，隱約於茂密松林中，背後是太室，兩邊有
峻嶺，好像一把椅子，古剎位於中間。法王寺建於東漢明帝永平十四年
（公元七十一年），是佛教傳入中國後建造最早的寺院，是漢明帝專為
印度高僧攝摩騰和竺法蘭譯經傳教而敕建的，成為中國第一所菩提道場，
規模宏大，結構嚴謹，殿堂樓閣，金碧輝煌。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shandao4",
                "northeast" : __DIR__"shandao5",
                "northup"   : __DIR__"tayuan",
                "west"      : __DIR__"yuetai",
        ]));
        set("objects", ([
                __DIR__"npc/gao": 1,
                __DIR__"npc/dizi" : 1,
        ]));
        set("coor/x", -30);
        set("coor/y", 810);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}